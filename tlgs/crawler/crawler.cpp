#include "crawler.hpp"

#include <atomic>
#include <cstdint>
#include <random>
#include <stdexcept>
#include <algorithm>
#include <string_view>

#include <nlohmann/json.hpp> 

#include <dremini/GeminiClient.hpp>
#include <drogon/HttpAppFramework.h>
#include <drogon/utils/Utilities.h>
#include <drogon/utils/coroutine.h>

#include <tlgsutils/gemini_parser.hpp>
#include <tlgsutils/robots_txt_parser.hpp>
#include <tlgsutils/url_parser.hpp>
#include <tlgsutils/utils.hpp>
#include <trantor/utils/Logger.h>
#include <tlgsutils/counter.hpp>

#include <tbb/concurrent_unordered_map.h>

#include "iconv.hpp"
#include "blacklist.hpp"
#include "tardis_client.hpp"

#include <fmt/format.h>

using namespace drogon;
using namespace dremini;
using namespace trantor;

namespace
{
bool isSqlExecutionTimeout(std::string_view error)
{
    return error.find("SQL execution timeout") != std::string_view::npos;
}

void truncateUtf8(std::string& text, const size_t maximum)
{
    if(text.size() <= maximum)
        return;
    size_t size = maximum;
    while(size > 0 && (static_cast<unsigned char>(text[size]) & 0xc0) == 0x80)
        --size;
    text.resize(size);
}

std::string sampleUtf8(const std::string_view text, const size_t maximum)
{
    if(text.size() <= maximum)
        return std::string(text);
    if(maximum < 16) {
        auto sample = std::string(text.substr(0, maximum));
        truncateUtf8(sample, maximum);
        return sample;
    }

    constexpr size_t chunk_count = 8;
    const size_t separator_bytes = chunk_count - 1;
    const size_t payload_bytes = maximum - separator_bytes;
    const size_t base_chunk_size = payload_bytes / chunk_count;
    const size_t extra_bytes = payload_bytes % chunk_count;

    std::string sample;
    sample.reserve(maximum);
    for(size_t chunk = 0; chunk < chunk_count; ++chunk) {
        const size_t chunk_size = base_chunk_size + (chunk < extra_bytes ? 1 : 0);
        size_t start = chunk * (text.size() - chunk_size) / (chunk_count - 1);
        while(start < text.size()
              && (static_cast<unsigned char>(text[start]) & 0xc0) == 0x80)
            ++start;

        size_t end = std::min(start + chunk_size, text.size());
        while(end > start && end < text.size()
              && (static_cast<unsigned char>(text[end]) & 0xc0) == 0x80)
            --end;
        if(!sample.empty())
            sample.push_back('\n');
        sample.append(text.substr(start, end - start));
    }
    return sample;
}
}

GeminiCrawler::GeminiCrawler(EventLoop* loop) : loop_(loop) {}
GeminiCrawler::~GeminiCrawler() = default;

Task<void> GeminiCrawler::syncTardis(const Json::Value& config, size_t maximumPages)
{
    const auto endpoint = config.get("endpoint", "gemini://tardis.northwire.xyz").asString();
    const auto certificate = config["certificate"].asString();
    const auto private_key = config["private_key"].asString();
    if(certificate.empty() || private_key.empty())
        throw std::runtime_error("tardis.certificate and tardis.private_key are required");
    const auto mode = config.get("mode", "tlgs").asString();
    const auto limit = static_cast<size_t>(config.get("page_size", 100).asUInt());
    // `mime_types` was the pre-body-filter configuration.  Retain it as a
    // fallback so existing deployments keep their previous behaviour.
    const auto change_mimes = config.get("change_mime_types",
        config.get("mime_types", "text/gemini,text/plain,text/markdown,text/x-rst")).asString();
    const auto body_mimes = config.get("body_mime_types", change_mimes).asString();
    auto db = app().getDbClient();
    co_await db->execSqlCoro("CREATE TABLE IF NOT EXISTS crawler_sync_state (source text PRIMARY KEY, last_full_sync_unix_millis bigint NOT NULL DEFAULT 0, window_since bigint, window_till bigint, resume_token text);");
    auto state = co_await db->execSqlCoro("SELECT last_full_sync_unix_millis, window_since, window_till, resume_token FROM crawler_sync_state WHERE source = 'tardis';");
    int64_t since = 0, till = trantor::Date::now().microSecondsSinceEpoch() / 1000;
    std::string token;
    if(!state.empty()) {
        since = state[0]["last_full_sync_unix_millis"].as<int64_t>();
        if(!state[0]["window_since"].isNull()) since = state[0]["window_since"].as<int64_t>();
        if(!state[0]["window_till"].isNull()) till = state[0]["window_till"].as<int64_t>();
        if(!state[0]["resume_token"].isNull()) token = state[0]["resume_token"].as<std::string>();
    }
    else co_await db->execSqlCoro("INSERT INTO crawler_sync_state(source, last_full_sync_unix_millis, window_since, window_till) VALUES ('tardis', 0, $1, $2);", since, till);
    TardisClient client(loop_, endpoint, certificate, private_key, mode, limit,
                        change_mimes, body_mimes);
    size_t pages = 0;
    while(true) {
        auto page = co_await client.updates(since, till, token);
        tardis_active_ = true;
        ended_ = false;
        for(auto &capture : page.captures) {
            const auto url = capture.url;
            if(capture.hasBody) {
                tardis_captures_.emplace(url, std::move(capture));
                craw_queue_.push(url);
                continue;
            }

            // A metadata-only change (including a body excluded by
            // body-mime) is still an inventory update.  Record it without
            // passing an empty body to crawlPage(), which would otherwise
            // replace an existing indexed document with empty content.
            const tlgs::Url parsed_url(url);
            if(!parsed_url.good() || parsed_url.str() != url) {
                LOG_WARN << "Ignoring invalid TARDIS URL " << url;
                continue;
            }
            co_await db->execSqlCoro(
                "INSERT INTO pages(url, domain_name, port, first_seen_at, last_crawled_at, last_status, last_meta) "
                "VALUES ($1, $2, $3, CURRENT_TIMESTAMP, CURRENT_TIMESTAMP, $4, $5) "
                "ON CONFLICT(url) DO UPDATE SET last_crawled_at = CURRENT_TIMESTAMP, "
                "last_status = EXCLUDED.last_status, last_meta = EXCLUDED.last_meta;",
                parsed_url.str(), parsed_url.host(), parsed_url.port(), capture.status, capture.meta);
        }
        co_await crawlAll();
        if(page.hasMore) {
            token = page.resumeToken;
            co_await db->execSqlCoro("UPDATE crawler_sync_state SET window_since = $1, window_till = $2, resume_token = $3 WHERE source = 'tardis';", since, till, token);
            if(maximumPages != 0 && ++pages >= maximumPages)
                break;
        }
        else {
            co_await db->execSqlCoro("UPDATE crawler_sync_state SET last_full_sync_unix_millis = $1, window_since = NULL, window_till = NULL, resume_token = NULL WHERE source = 'tardis';", till);
            break;
        }
    }
    tardis_active_ = false;
    co_return;
}

static std::string sanitizeUtf8(const std::string_view input)
{
    std::string output;
    output.reserve(input.size());
    for(size_t i = 0; i < input.size();) {
        const auto first = static_cast<unsigned char>(input[i]);
        size_t length = 0;
        uint32_t codepoint = 0;
        uint32_t minimum = 0;
        if(first < 0x80) {
            if(first == 0)
                output.append("\xef\xbf\xbd");
            else
                output.push_back(static_cast<char>(first));
            ++i;
            continue;
        }
        if((first & 0xe0) == 0xc0) {
            length = 2;
            codepoint = first & 0x1f;
            minimum = 0x80;
        }
        else if((first & 0xf0) == 0xe0) {
            length = 3;
            codepoint = first & 0x0f;
            minimum = 0x800;
        }
        else if((first & 0xf8) == 0xf0) {
            length = 4;
            codepoint = first & 0x07;
            minimum = 0x10000;
        }

        bool valid = length != 0 && i + length <= input.size();
        for(size_t offset = 1; valid && offset < length; ++offset) {
            const auto next = static_cast<unsigned char>(input[i + offset]);
            valid = (next & 0xc0) == 0x80;
            codepoint = (codepoint << 6) | (next & 0x3f);
        }
        valid = valid && codepoint >= minimum && codepoint <= 0x10ffff
            && !(codepoint >= 0xd800 && codepoint <= 0xdfff);
        if(valid) {
            output.append(input.substr(i, length));
            i += length;
        }
        else {
            output.append("\xef\xbf\xbd");
            ++i;
        }
    }
    return output;
}

static std::string tryConvertEncoding(const std::string_view& str, const std::string& src_enc, const std::string& dst_enc, bool ignore_err = true)
{
    // still perform conversion event if source encoding is the same as destination encoding
    // because the input string might have bad encoding
    std::string res;
    try {
        iconvpp::converter converter(src_enc, dst_enc, true);
        converter.convert(str, res);
    }
    catch(...) {
        res = str;
    }
    return dst_enc == "utf-8" ? sanitizeUtf8(res) : res;
}

static std::pair<std::string, std::unordered_map<std::string, std::string>> parseMime(const std::string& mime)
{
    std::string mime_str;
    std::unordered_map<std::string, std::string> params;
    if(mime.empty())
        return {mime_str, params};

    size_t idx = 0;
    for(;idx<mime.size();idx++) {
        if(mime[idx] == ';')
            break;
    }
    mime_str = mime.substr(0, idx);
    if(idx == mime.size())
        return {mime_str, params};
    while(idx < mime.size()) {
        ++idx; // Skip the separator from the previous parameter.
        while(idx < mime.size() && (mime[idx] == ' ' || mime[idx] == '\t'))
            ++idx;
        if(idx == mime.size())
            break;

        const size_t key_begin = idx;
        const size_t key_end = mime.find('=', key_begin);
        const size_t parameter_end = mime.find(';', key_begin);
        if(key_end == std::string::npos || (parameter_end != std::string::npos && key_end > parameter_end)) {
            if(parameter_end == std::string::npos)
                break;
            idx = parameter_end;
            continue;
        }

        const size_t value_begin = key_end + 1;
        const size_t value_end = mime.find(';', value_begin);
        if(key_end != key_begin)
            params[mime.substr(key_begin, key_end - key_begin)] = mime.substr(value_begin, value_end - value_begin);
        if(value_end == std::string::npos)
            break;
        idx = value_end;
    }
    return {mime_str, params};
}

Task<std::optional<std::string>> GeminiCrawler::getNextPotentialCarwlUrl()
{
    if(tardis_active_) {
        std::string queued;
        if(craw_queue_.try_pop(queued)) co_return queued;
        co_return {};
    }

    std::string result;
    if(craw_queue_.try_pop(result))
        co_return result;

    // co_return {};

    // Even if multiple threads are trying to aquire data from the same table, they push into the same queue. Thus
    // we can safely stop querying if we got data in the queue. (as long as LIMIT >> max_concurrent_connections_)
    static std::atomic<int> sample_pct{1};
    constexpr int urls_per_batch = 360;
    while(craw_queue_.empty()) {
        auto db = app().getDbClient();
        try {
            int tablesample_pct = sample_pct.load(std::memory_order_acquire);
            // HACK: Seems we can't pass bind variables to a subquery, Just compose the query string
            std::string sample_str;
            if(tablesample_pct <= 80)
                sample_str = fmt::format("TABLESAMPLE SYSTEM({})", tablesample_pct);
            auto urls = co_await db->execSqlCoro(fmt::format("UPDATE pages SET last_queued_at = CURRENT_TIMESTAMP "
                "WHERE url in (SELECT url FROM pages {} WHERE (last_crawled_at < CURRENT_TIMESTAMP - INTERVAL '3' DAY "
                "OR last_crawled_at IS NULL) AND (last_queued_at < CURRENT_TIMESTAMP - INTERVAL '5' MINUTE OR last_queued_at IS NULL) "
                "LIMIT {} FOR UPDATE) RETURNING url"
                ,sample_str , urls_per_batch));
            if(urls.size() < urls_per_batch*0.9) {
                const int new_value = std::min(tablesample_pct + 10, 100);
                sample_pct.compare_exchange_strong(tablesample_pct, new_value, std::memory_order_acq_rel);
            }
            if(urls.size() == 0 && tablesample_pct >= 100)
                co_return {};
            
            thread_local std::mt19937 rng(std::random_device{}());
            std::vector<std::string> vec;
            vec.reserve(urls.size());
            for(const auto& url : urls)
                vec.push_back(url["url"].as<std::string>());
            // XXX: Half-working attempt at randomizing the crawling order.
            std::shuffle(vec.begin(), vec.end(), rng);
            for(auto&& url : vec)
                craw_queue_.emplace(std::move(url));
        }
        catch(std::exception& e) {
            // Only keep trying if is a transaction rollback
            if(std::string_view(e.what()).find("deadlock") == std::string_view::npos &&
                std::string_view(e.what()).find("transaction") == std::string_view::npos) {
                throw;
            }
            LOG_INFO << "Query for next URL failed due to transaction rollback. Retrying...";
        }
    }

    if(craw_queue_.try_pop(result))
        co_return result;
    co_return {};
}


Task<bool> GeminiCrawler::shouldCrawl(std::string url_str)
{
    if(url_str.empty())
        co_return false;
    const auto url = tlgs::Url(url_str);
    if(url.good() == false) {
        LOG_ERROR << "Failed to parse URL " << url_str;
        co_return false;
    }
    if(url.protocol() != "gemini") {
        LOG_ERROR << url_str << " is not a Gemini URL";
        co_return false;
    }
    if(tardis_active_)
        co_return true;
    if(inBlacklist(url.str()))
        co_return false;
    // Do not crawl hosts known to be down
    // TODO: Put this on SQL
    auto timeout = host_timeout_count_.find(url.hostWithPort(1965));
    if(timeout != host_timeout_count_.end() && timeout->second > 3)
        co_return false;

    // TODO: Use a LRU cache
    // Consult the database to see if this URL is in robots.txt. Contents from the DB is cache locally to 
    // redule the number of DB queries
    const std::string cache_key = url.hostWithPort(1965);
    static drogon::CacheMap<std::string, std::vector<std::string>> policy_cache(loop_, 5);
    std::vector<std::string> disallowed_path;
    if(policy_cache.findAndFetch(cache_key, disallowed_path))
        co_return !tlgs::isPathBlocked(url.path(), disallowed_path);

    LOG_TRACE << "Cannot find " << cache_key << " in local policy cache";
    auto db = app().getDbClient();
    auto policy_status = co_await db->execSqlCoro("SELECT have_policy FROM robot_policies_status "
        "WHERE host = $1 AND port = $2 AND last_crawled_at > CURRENT_TIMESTAMP - INTERVAL '2' DAY", url.host(), url.port());
    if(policy_status.size() == 0) {
        LOG_TRACE << url.hostWithPort(1965) << " has no up to date robots policy stored in DB. Asking the host for robots.txt";
        HttpResponsePtr resp;
        // FIXME: THe crawler may request robots.txt multiple times if multiple URLs on the same host are requested.
        // This is not as efficient as it could be. But does not cause any problems otherwise.
        try {
            std::string robot_url = tlgs::Url(url).withParam("").withPath("/robots.txt").withFragment("").str();
            LOG_TRACE << "Fetching robots.txt from " << robot_url;
            resp = co_await dremini::sendRequestCoro(robot_url, 10, loop_, 0x2625a0, {}, 10);
        }
        catch(std::exception& e) {
            // XXX: Failed to handshake with the host. We should retry later
            // Shoud we cache the result as no policy is available?
            // policy_cache[cache_key] = {};
            std::string error = e.what();
            if(error == "Timeout" || error == "NetworkFailure")
                host_timeout_count_[url.hostWithPort(1965)]++;
            co_return true;
        }

        assert(resp != nullptr);
        const auto status = tlgs::try_strtoull(resp->getHeader("gemini-status"));
        bool have_robots_txt = false;
        if(!status || *status > 99) {
            LOG_WARN << "Invalid Gemini status while fetching robots.txt from " << url.hostWithPort(1965);
        }
        else {
            auto [mime, _] = parseMime(resp->contentTypeString());
            // HACK: Some capsules have broken MIME
            have_robots_txt = *status == 20 && (mime == "text/plain" || mime == "text/gemini");
        }
        if(have_robots_txt) {
            disallowed_path = tlgs::parseRobotsTxt(std::string(resp->body()), {"*", "tlgs", "indexer"});
        }

        try {
            auto t = co_await db->newTransactionCoro();
            co_await t->execSqlCoro("DELETE FROM robot_policies WHERE host = $1 AND port = $2;", url.host(), url.port());
            for(const auto& disallow : disallowed_path) {
                co_await t->execSqlCoro("INSERT INTO robot_policies (host, port, disallowed) VALUES ($1, $2, $3)",
                    url.host(), url.port(), disallow);
            }
            co_await t->execSqlCoro("INSERT INTO robot_policies_status(host, port, last_crawled_at, have_policy) VALUES ($1, $2, CURRENT_TIMESTAMP, $3) "
                "ON CONFLICT (host, port) DO UPDATE SET last_crawled_at = CURRENT_TIMESTAMP, have_policy = $3;"
                , url.host(), url.port(), have_robots_txt);
        }
        catch(...) {
            // Screw it. Someone else updated the policies. They've done the same job. We can keep on working
        }
    }
    else if(policy_status[0]["have_policy"].as<bool>()) {
        LOG_TRACE << url.hostWithPort(1965) << " has robots policy stored in DB.";
        auto stored_policy = co_await db->execSqlCoro("SELECT disallowed FROM robot_policies WHERE host = $1 AND port = $2;"
            , url.host(), url.port());
        for(const auto& path : stored_policy)
            disallowed_path.push_back(path["disallowed"].as<std::string>());
    }

    bool should_crawl = !tlgs::isPathBlocked(url.path(), disallowed_path);
    policy_cache.insert(cache_key, std::move(disallowed_path), 60);
    co_return should_crawl;
}

Task<std::optional<std::string>> GeminiCrawler::getNextCrawlPage() 
{
    auto db = app().getDbClient();
    while(1) {
        auto next_url = co_await getNextPotentialCarwlUrl();
        if(next_url.has_value() == false)
            co_return {};
        
        auto url_str = next_url.value();

        // URL should not contain any ASCII control characters
        auto it = std::find_if(url_str.begin(), url_str.end(), [](char c) { return c < 0x20; });
        auto can_crawl = it == url_str.end() && co_await shouldCrawl(url_str);
        if(can_crawl == false) {
            co_await db->execSqlCoro("UPDATE pages SET last_crawled_at = CURRENT_TIMESTAMP, last_status = $2, last_meta = $3 WHERE url = $1;"
                , url_str, 0, std::string("blocked"));
            co_await db->execSqlCoro("DELETE FROM pages WHERE url = $1 AND last_crawl_success_at < CURRENT_TIMESTAMP - INTERVAL '30' DAY;"
                , url_str);
            continue;
        }

        // shouldCrawl() validates the URL. So we can safely use tlgs::Url here
        co_return tlgs::Url(url_str).str();
    }

    LOG_FATAL << "Should not reach here in Crawler::getNextCrawlPage()";
    co_return {};
}

void GeminiCrawler::dispatchCrawl()
{
    if(ended_)
        return;
    // In case I forgot how this works in the future:
    // Start new crawls up to max_concurrent_connections_. And launch new crawls when we might have more pages to crawl.
    // This function is tricky and difficult to understand. It's a bit of a hack. But it is 100% lock free. The general idea is asi
    // follows:
    // 1. A atomic counter is used to keep track of the number of active crawls.
    // 2. If we successfully got new url to crawl, we spawn dispatch a new crawl.
    // 3. When a crawl finishes, we resubmit the crawl task.
    //    * Keep re-submiting crawls until there's no more to crawl
    //    * It doesn't matter if currently enough crawler exists. Since the counter stops them from crawling
    // 4. Near the end of crawling. It might be possible that there's not enough pages to be crawled
    //    * But a crawler may suddenly submit more links for crawling.
    //    * The nature of dispatching more and more crawlers help. Reactivating crawls if neded.
    auto counter = std::make_shared<tlgs::Counter>(ongoing_crawlings_);
    if(counter->count() >= max_concurrent_connections_)
        return;

    async_run([counter, this]() mutable -> Task<void> {try{
        auto url_str = co_await getNextCrawlPage();
        // Crawling has ended if the following is true
        // 1. There's no more URL to crawl
        // 2. The current crawl is the last one in existance
        //    * Since a crawler can add new items into the queue
        if(url_str.has_value() == false) {
            if(counter->release() == 1)
                ended_ = true;
            co_return;
        }
        loop_->runInLoop([this](){dispatchCrawl();});

        size_t retry_count = 0;
        while(true) {
            double retry_delay = 0;
            try {
                bool success = co_await crawlPage(url_str.value(), retry_count != 0);
                if(success)
                    LOG_INFO << "Processed " << url_str.value();
                if(tardis_active_)
                    tardis_captures_.erase(url_str.value());
                break;
            }
            catch(std::exception& e) {
                if(tardis_active_ && isSqlExecutionTimeout(e.what())) {
                    ++retry_count;
                    const auto exponent = std::min<size_t>(retry_count - 1, 7);
                    retry_delay = std::min(30.0, 0.25 * static_cast<double>(size_t{1} << exponent));
                    LOG_WARN << "PostgreSQL is saturated while importing " << url_str.value()
                             << "; retry " << retry_count << " in " << retry_delay << " seconds";
                }
                else {
                    LOG_ERROR << "Exception escaped crawling " << url_str.value() << ": " << e.what();
                    if(tardis_active_) {
                        tardis_captures_.erase(url_str.value());
                        break;
                    }
                    abort();
                }
            }
            if(retry_delay != 0)
                co_await drogon::sleepCoro(loop_, retry_delay);
        }
        loop_->queueInLoop([this](){dispatchCrawl();});
    }
    catch(std::exception& e) {
        LOG_ERROR << "Exception escaped in dispatchCrawl(): " << e.what();
        dispatchCrawl();
    }});
}

Task<bool> GeminiCrawler::crawlPage(const std::string& url_str, bool retry_after_timeout)
{
    auto db = app().getDbClient();
    const auto url = tlgs::Url(url_str);
    if(url.good() == false || url.str() != url_str) {
        // It's fine we delete unnormalized URLs since the crawler will just add them back later when encounter it again
        LOG_WARN << "Warning: URL " << url_str << " is not normalized or invalid. Removing it from the queue.";
        co_await db->execSqlCoro("DELETE FROM pages WHERE url = $1", url_str);
        co_await db->execSqlCoro("DELETE FROM links WHERE url = $1 OR to_url = $1", url_str);
        co_return false;
    }

    std::string error;
    try {
        if(!tardis_active_ && co_await shouldCrawl(url.str()) == false)
            throw std::runtime_error("Blocked by robots.txt");
        auto record = co_await db->execSqlCoro("SELECT url, indexed_content_hash, raw_content_hash, last_status"
            ", last_crawled_at, search_schema_version FROM pages WHERE url = $1;", url.str());
        bool have_record = record.size() != 0;
        auto indexed_content_hash = have_record ? record[0]["indexed_content_hash"].as<std::string>() : "";
        auto raw_content_hash = have_record ? record[0]["raw_content_hash"].as<std::string>() : "";
        auto search_schema_version = have_record ? record[0]["search_schema_version"].as<int>() : 0;

        if(!have_record) {
            co_await db->execSqlCoro("INSERT INTO pages(url, domain_name, port, first_seen_at)"
                " VALUES ($1, $2, $3, CURRENT_TIMESTAMP) ON CONFLICT(url) DO NOTHING;",
                url.str(), url.host(), url.port());
        }
        else {
            // 53 proxy error. Likely misconfigured proxy/domain or bad links pointing to the wrong domain that is on the 
            // smae IP. Only retry once every 21 days
            auto last_status = record[0]["last_status"].isNull() ? 0 : record[0]["last_status"].as<int>();
            auto last_crawled_at = [&](){
                auto var = record[0]["last_crawled_at"];
                if(var.isNull())
                    return trantor::Date();
                else
                    return trantor::Date::fromDbStringLocal(var.as<std::string>());
            }();

            if(last_status == 53 && last_crawled_at.after(21*7*24*3600) < trantor::Date::now()) {
                co_await db->execSqlCoro("UPDATE pages SET last_crawled_at = CURRENT_TIMESTAMP, last_status = 0 WHERE url = $1;", url.str());
                LOG_INFO << "Skipping " << url.str() << " that was proxy-errored recently";
                co_return true;
            }
        }

        // Only fetch the entire page for content types we can handle.
        static const std::vector<std::string> indexd_mimes = {"text/gemini", "text/plain", "text/markdown", "text/x-rst", "plaintext"};
        HttpResponsePtr resp;
        int redirection_count = 0;
        int status;
        tlgs::Url crawl_url = url;
        if(tardis_active_) {
            const auto capture = tardis_captures_.find(url.str());
            if(capture == tardis_captures_.end()) throw std::runtime_error("missing TARDIS capture");
            resp = HttpResponse::newHttpResponse();
            resp->setBody(capture->second.body);
            resp->addHeader("gemini-status", std::to_string(capture->second.status));
            resp->addHeader("meta", capture->second.meta);
            resp->setContentTypeString(capture->second.meta);
            status = capture->second.status;
        }
        else do {
            auto redirect = co_await db->execSqlCoro("SELECT to_url FROM perma_redirects WHERE from_url = $1;", crawl_url.str());
            if(redirect.size() != 0) {
                crawl_url = tlgs::Url(redirect[0]["to_url"].as<std::string>());
                redirection_count++;
                status = 30;
                continue;
            }
            // 2.5MB is the maximum size of page we will index. 10s timeout, max 5 redirects and 25s max transfer time.
            resp = co_await dremini::sendRequestCoro(crawl_url.str(), 10, loop_, 0x2625a0, indexd_mimes, 25.0);
            if(resp == nullptr)
                throw std::runtime_error("No response from Gemini server");

            status = std::stoi(resp->getHeader("gemini-status"));
            if(status / 10 == 3) {
                auto redirect_url = tlgs::Url(resp->getHeader("meta"));
                if(redirect_url.good() == false || crawl_url.str() == redirect_url.str())
                    throw std::runtime_error("Bad redirect");
                if(url.protocol() != "gemini")
                    throw std::runtime_error("Redirected to non-gemini URL");
                if(co_await shouldCrawl(redirect_url.str()) == false)
                    throw std::runtime_error("Redirected to blocked URL");

                if(status == 31) {
                    co_await db->execSqlCoro("INSERT INTO perma_redirects (from_url, to_url) VALUES ($1, $2) ON CONFLICT (from_url) DO UPDATE SET to_url = $2;",
                            crawl_url.str(), redirect_url.str());
                }
                crawl_url = std::move(redirect_url);
            }
        } while(status / 10 == 3 && redirection_count++ < 5);

        if(resp == nullptr)
            throw std::runtime_error("No concrete response. Too many redirects?");

        const auto& meta = resp->getHeader("meta");
        std::string mime;
        std::optional<std::string> charset;
        std::optional<std::string> lang;
        std::string title;
        std::string body;
        std::string headings;
        std::string link_text;
        bool has_explicit_title = false;
        std::vector<std::string> links;
        std::vector<tlgs::GeminiLink> recommendations;
        size_t body_size = resp->body().size();
        std::optional<std::string> feed_type;
        auto new_raw_content_hash = tlgs::xxHash64(resp->body());
        if(status/10 == 2) {
            auto [mime_str, mime_param] = parseMime(meta);
            mime = std::move(mime_str);
            // trim leading and tailing space and tab from mime as some servers send it
            mime.erase(0, mime.find_first_not_of(" \t"));
            mime.erase(mime.find_last_not_of(" \t") + 1);
            charset = mime_param.count("charset") ? mime_param["charset"] : std::optional<std::string>{};
            lang = mime_param.count("lang") ? mime_param["lang"] : std::optional<std::string>{};

            // No reason to reindex if the content hasn't changed. `force_reindex_` is used to force reindexing of files
            if(!force_reindex_ && !retry_after_timeout && search_schema_version >= 3
                && raw_content_hash == new_raw_content_hash) {
                co_await db->execSqlCoro("UPDATE pages SET last_crawled_at = CURRENT_TIMESTAMP, last_crawl_success_at = CURRENT_TIMESTAMP, "
                    "last_status = $2, last_meta = $3, content_type = $4 WHERE url = $1;",
                    url.str(), status, meta, mime);
                    co_return true;
            }

            // We should only have text files at this point. Try convert everything to UTF-8 because iconv will
            // ignore all encoding errors. Thus make Postgres happy for files with doggy encodings.
            std::string body_raw = tryConvertEncoding(resp->body(), charset.value_or("utf-8"), "utf-8");
            // The worst case is 25% from UTF-32 to UTF-8. Smaller than 20% is definatelly a binary file. We don't want to index it.
            if(body_raw.size() < resp->body().size()/5)
                throw std::runtime_error("Possible binary files sent as text");

            if(mime == "text/gemini") {
                auto nodes = dremini::parseGemini(body_raw);
                tlgs::GeminiDocument doc = tlgs::extractGeminiConcise(nodes);
                body = std::move(doc.text);
                links = std::move(doc.links);
                recommendations = std::move(doc.recommendations);
                headings = std::move(doc.headings);
                link_text = std::move(doc.link_text);
                has_explicit_title = !doc.title.empty();
                title = std::move(doc.title);
                if(tlgs::isGemsub(nodes, url, "gemini"))
                    feed_type = "gemsub";

                // remove empty links
                links.erase(std::remove_if(links.begin(), links.end(), [](const std::string& link) {
                    return link.empty();
                }), links.end());
                if(title.empty())
                    title = url.str();
            }
            else if(mime == "text/plain" || mime == "plaintext" || mime == "text/markdown" || mime == "text/x-rst") {
                if(url.path().ends_with("/twtxt.txt"))
                    feed_type = "twtxt";
                title = url.str();
                body = std::move(body_raw);
            }
            else {
                if(mime == "application/rss+xml")
                    feed_type = "rss";
                else if(mime == "application/atom+xml")
                    feed_type = "atom";
                title = url.str();
                body = "";
                body_size = 0;
            }
        }
        else if(status/10 == 1) {
            body = meta;
            title = meta;
            body_size = meta.size();
            mime = "<gemini-request-info>";
        }
        else {
            if(!tardis_active_)
                LOG_ERROR << "Failed to fetch " << url.str() << ": " << status;
            co_await db->execSqlCoro("UPDATE pages SET last_crawled_at = CURRENT_TIMESTAMP, last_status = $2, last_meta = $3 WHERE url = $1;"
                , url.str(), status, meta);
            co_await db->execSqlCoro("DELETE FROM pages WHERE url = $1 AND last_crawl_success_at < CURRENT_TIMESTAMP - INTERVAL '30' DAY;"
                , url.str());
            co_return false;
        }
        // safeguard in case title is too long for Postgres
        if(title.size() > 1000) {
            truncateUtf8(title, 1000);
            title += "...";
        }

        std::string indexed_content;
        indexed_content.reserve(body.size() + headings.size() + link_text.size() + title.size() + 3);
        if(has_explicit_title)
            indexed_content.append(title);
        indexed_content.push_back('\n');
        indexed_content.append(headings);
        indexed_content.push_back('\n');
        indexed_content.append(link_text);
        indexed_content.push_back('\n');
        indexed_content.append(body);
        auto new_indexed_content_hash = tlgs::xxHash64(indexed_content);
        // Absolutelly no reason to reindex if the content hasn't changed even after post processing.
        if(!force_reindex_ && !retry_after_timeout && search_schema_version >= 3
            && new_indexed_content_hash == indexed_content_hash
            && new_raw_content_hash == raw_content_hash) {
            // Maybe this is too strict? The conent doesn't change means the content_type doesn't change, right...?
            co_await db->execSqlCoro("UPDATE pages SET last_crawled_at = CURRENT_TIMESTAMP, last_crawl_success_at = CURRENT_TIMESTAMP, "
                "last_status = $2, last_meta = $3, content_type = $4 WHERE url = $1;",
                url.str(), status, meta, mime);
            co_return true;
        }

        auto normalizeLink = [&url](const std::string& link) -> std::optional<tlgs::Url> {
            // ignore links like mailto: ldap:. etc..
            if(tlgs::isNonUriAction(link))
                return std::nullopt;

            auto link_url = tlgs::Url(link);
            if(link_url.good()) {
                if(link_url.protocol() == "")
                    link_url.withProtocol(url.protocol());
                if(link_url.protocol() != "gemini")
                    return std::nullopt;
            }
            // sometimes invalid host/port causes the URL to be invalid. Ignore them
            else if(link.starts_with("gemini://")) {
                return std::nullopt;
            }
            // Drop links that are too long and obviously invalid
            else if(link.size() > 1024) {
                return std::nullopt;
            }
            else  {
                link_url = linkCompose(url, link);
                if(link_url.good() == false)
                    return std::nullopt;
            }
            // We shall not send fragments
            link_url.withFragment("");

            // HACK: avoid mistyped links like gemini://en.gmn.clttr.info/cgmnlm.gmi?gemini://en.gmn.clttr.info/cgmnlm.gmi
            if(link_url.str().starts_with(link_url.param()) && link_url.path().ends_with(".gmi"))
                link_url.withParam("");
            return link_url;
        };

        std::set<tlgs::Url> link_urls;
        std::unordered_map<std::string, std::string> qualifying_text;
        for(const auto& recommendation : recommendations) {
            auto link_url = normalizeLink(recommendation.target);
            if(!link_url)
                continue;
            const auto normalized = link_url->str();
            auto& qualifier = qualifying_text[normalized];
            if(qualifier.empty())
                qualifier = recommendation.qualifying_text;
            else if(qualifier.find(recommendation.qualifying_text) == std::string::npos) {
                constexpr size_t max_qualifying_text_size = 4096;
                if(qualifier.size() < max_qualifying_text_size) {
                    qualifier.push_back('\n');
                    qualifier.append(recommendation.qualifying_text, 0,
                        max_qualifying_text_size - qualifier.size());
                }
            }
            link_urls.insert(std::move(*link_url));
        }
        // Keep this fallback for callers that construct GeminiDocument links without
        // recommendation context and for old parser behavior.
        for(const auto& link : links) {
            auto link_url = normalizeLink(link);
            if(link_url)
                link_urls.insert(std::move(*link_url));
        }

        // TODO: Use C++20 ranges. My basic implementation is not as efficent as it could be.
        auto cross_site_links = tlgs::map(tlgs::filter(link_urls, [&url](const tlgs::Url& link_url) {
                return link_url.host() != url.host() || url.port() != link_url.port();
            })
            , [](const tlgs::Url& link_url) {
                return link_url.str();
            });
        auto internal_links = tlgs::map(tlgs::filter(link_urls, [&url](const tlgs::Url& link_url) {
                return !(link_url.host() != url.host() || url.port() != link_url.port());
            })
            , [](const tlgs::Url& link_url) {
                return link_url.str();
            });

        auto index_friendly_url = indexFriendly(url);
        truncateUtf8(index_friendly_url, 2000);
        auto indexed_title = sampleUtf8(has_explicit_title ? title : "", 1024);
        auto indexed_headings = sampleUtf8(headings, 8 * 1024);
        auto indexed_link_text = sampleUtf8(link_text, 8 * 1024);
        auto indexed_body = sampleUtf8(body, 32 * 1024);
        auto reduced_headings = sampleUtf8(headings, 4 * 1024);
        auto reduced_link_text = sampleUtf8(link_text, 4 * 1024);
        auto reduced_body = sampleUtf8(body, 16 * 1024);
        auto minimal_headings = sampleUtf8(headings, 1024);
        auto minimal_link_text = sampleUtf8(link_text, 1024);
        auto minimal_body = sampleUtf8(body, 4 * 1024);
        co_await db->execSqlCoro("UPDATE pages SET content_body = $2, size = $3, charset = $4, lang = $5, last_crawled_at = CURRENT_TIMESTAMP, "
            "last_crawl_success_at = CURRENT_TIMESTAMP, last_status = $6, last_meta = $7, content_type = $8, title = $9, "
            "cross_site_links = $10::json, internal_links = $11::json, indexed_content_hash = $12, raw_content_hash = $13, feed_type = $14, "
            "has_explicit_title = $16, search_headings = $17, search_link_text = $18, "
            "search_vector = tlgs_bounded_search_vector('simple', $19, $20, $15, $21, $22, $23, $24, $25, $26, $27, $28), "
            "english_search_vector = CASE WHEN $5::text IS NULL OR lower(split_part($5::text, ',', 1)) ~ '^en([_-]|$)' THEN "
                "tlgs_bounded_search_vector('english', $19, $20, $15, $21, $22, $23, $24, $25, $26, $27, $28) ELSE NULL END, "
            "title_vector = to_tsvector('simple', $19), "
            "search_schema_version = 3, last_indexed_at = CURRENT_TIMESTAMP WHERE url = $1;",
            url.str(), body, body_size, charset, lang, status, meta, mime, title, nlohmann::json(cross_site_links).dump()
            , nlohmann::json(internal_links).dump(), new_indexed_content_hash, new_raw_content_hash, feed_type, index_friendly_url,
            has_explicit_title, headings, link_text, indexed_title, indexed_headings, indexed_link_text, indexed_body,
            reduced_headings, reduced_link_text, reduced_body, minimal_headings, minimal_link_text, minimal_body);
        if(internal_links.size() == 0 && cross_site_links.size() == 0)
            co_return true;

        // Update link formation. JSON recordsets keep the bulk insert parameterized.
        nlohmann::json link_rows = nlohmann::json::array();
        nlohmann::json page_rows = nlohmann::json::array();
        for(const auto& link_url : link_urls) {
            bool is_cross_site = link_url.host() != url.host() || url.port() != link_url.port();
            link_rows.push_back({
                {"to_url", link_url.str()},
                {"is_cross_site", is_cross_site},
                {"to_host", link_url.host()},
                {"to_port", link_url.port()},
                {"qualifying_text", qualifying_text[link_url.str()]}
            });

            if(co_await shouldCrawl(link_url.str()) == false)
                continue;
            page_rows.push_back({
                {"url", link_url.str()},
                {"domain_name", link_url.host()},
                {"port", link_url.port()}
            });
        }

        auto transaction = co_await db->newTransactionCoro();
        co_await transaction->execSqlCoro("DELETE FROM links WHERE url = $1", url.str());
        co_await transaction->execSqlCoro("INSERT INTO links (url, host, port, to_url, is_cross_site, to_host, to_port, qualifying_text, qualifying_vector) "
            "SELECT $1, $2, $3, link.to_url, link.is_cross_site, link.to_host, link.to_port, link.qualifying_text, to_tsvector('simple', link.qualifying_text) "
            "FROM jsonb_to_recordset($4::jsonb) AS link(to_url text, is_cross_site boolean, to_host text, to_port integer, qualifying_text text) "
            "ON CONFLICT DO NOTHING;", url.str(), url.host(), url.port(), link_rows.dump());
        if(!page_rows.empty()) {
            co_await transaction->execSqlCoro("INSERT INTO pages (url, domain_name, port, first_seen_at) "
                "SELECT page.url, page.domain_name, page.port, CURRENT_TIMESTAMP "
                "FROM jsonb_to_recordset($1::jsonb) AS page(url text, domain_name text, port integer) "
                "ON CONFLICT DO NOTHING;", page_rows.dump());
        }
    }
    catch(std::exception& e) {
        error = e.what();
    }

    // Snapshot responses stay resident until the page is committed. Let the dispatcher
    // retry the same response after database pressure subsides instead of running more SQL
    // in this already-timed-out attempt.
    if(tardis_active_ && isSqlExecutionTimeout(error))
        throw std::runtime_error(error);

    if(error == "Timeout" || error == "NetworkFailure")
        host_timeout_count_[url.hostWithPort(1965)]++;
    if(error != "") {
        co_await db->execSqlCoro("UPDATE pages SET last_crawled_at = CURRENT_TIMESTAMP, last_status = $2, last_meta = $3 WHERE url = $1;"
            , url.str(), 0, error);
        co_await db->execSqlCoro("DELETE FROM pages WHERE url = $1 AND last_crawl_success_at < CURRENT_TIMESTAMP - INTERVAL '30' DAY;"
            , url.str());
        co_return false;
    }
    co_return true;
}
