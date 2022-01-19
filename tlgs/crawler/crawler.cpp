#include "crawler.hpp"

#include <filesystem>
#include <random>

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

using namespace drogon;
using namespace dremini;
using namespace trantor;


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
    return res;
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
        do {idx++;} while(idx < mime.size() && (mime[idx] == ' ' || mime[idx] == '\t'));
        size_t key_begin = idx;
        do {idx++;} while(idx < mime.size() && mime[idx] != '=');
        size_t key_end = idx;
        do {idx++;} while(idx < mime.size() && mime[idx] != ';' );
        size_t value_end = idx;
        std::string key(mime.data()+key_begin, key_end-key_begin);
        std::string value(mime.data()+key_end+1, value_end-key_end-1);
        params[key] = value;
    }
    return {mime_str, params};
}

Task<std::optional<std::string>> GeminiCrawler::getNextUrl()
{
    if(craw_queue_.empty()) {
        // co_return {};
        auto db = app().getDbClient();
        while(true) {
            bool transaction_failed = false;
            try {
                // XXX: I really want to have a proper job queue. But using SQL is good enought for now
                auto urls = co_await db->execSqlCoro("UPDATE pages SET last_queued_at = CURRENT_TIMESTAMP "
                    "WHERE url in (SELECT url FROM pages WHERE (last_crawled_at < CURRENT_TIMESTAMP - INTERVAL '3' DAY "
                    "OR last_crawled_at IS NULL) AND (last_queued_at < CURRENT_TIMESTAMP - INTERVAL '5' MINUTE OR last_queued_at IS NULL) "
                    "LIMIT 120) RETURNING url");
                if(urls.size() == 0)
                    co_return {};
                
                thread_local std::mt19937 rng(std::random_device{}());
                std::vector<std::string> vec;
                vec.reserve(urls.size());
                for(const auto& url : urls)
                    vec.push_back(url["url"].as<std::string>());
                // XXX: Half-working attempt as randomizing the crawling order.
                std::shuffle(vec.begin(), vec.end(), rng);
                for(auto&& url : vec)
                    craw_queue_.emplace(std::move(url));
                break;
            }
            catch(std::exception& e) {
                // Only keep trying if is a transaction rollback
                if(std::string_view(e.what()).find("deadlock") == std::string_view::npos &&
                    std::string_view(e.what()).find("transaction") == std::string_view::npos) {
                    throw;
                }
            }
        }
    }

    std::string result;
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
    // hardcoeded: don't crawl from localhost or uneeded files
    if(url.path() == "/robots.txt" || url.path() == "/favicon.txt")
        co_return false;
    if(url.host().starts_with("127.0.0.") || url.host() == "[::1]" || url.host() == "localhost")
        co_return false;
    if(inBlacklist(url.str()))
        co_return false;
    // We don't have the ablity crawl hidden sites, yet
    if(url.host().ends_with(".onion"))
        co_return false;
    // Do not crawl hosts known to be down
    // TODO: Put this on SQL
    auto timeout = host_down_count_.find(url.hostWithPort(1965));
    if(timeout != host_down_count_.end() && timeout->second > 3)
        co_return false;

    // TODO: Use a LRU cache
    // Consult the database to see if this URL is in robots.txt. Contents from the DB is cache locally to 
    // redule the number of DB queries
    const std::string cache_key = url.hostWithPort(1965);
    static tbb::concurrent_unordered_map<std::string, std::vector<std::string>> policy_cache;
    auto it = policy_cache.find(cache_key);
    if(it != policy_cache.end()) {
        if(it->second.size() == 0)
            co_return true;
        co_return !tlgs::isPathBlocked(url.path(), it->second);
    }
    LOG_TRACE << "Cannot find " << cache_key << " in local policy cache";
    
    auto db = app().getDbClient();
    auto policy_status = co_await db->execSqlCoro("SELECT have_policy FROM robot_policies_status "
        "WHERE host = $1 AND port = $2 AND last_crawled_at > CURRENT_TIMESTAMP - INTERVAL '7' DAY", url.host(), url.port());
    std::vector<std::string> disallowed_path;
    if(policy_status.size() == 0) {
        LOG_TRACE << url.hostWithPort(1965) << " has no up to date robots policy stored in DB. Asking the host for robots.txt";
        HttpResponsePtr resp;
        try {
            std::string robot_url = tlgs::Url(url).withParam("").withPath("/robots.txt").str();
            LOG_TRACE << "Fetching robots.txt from " << robot_url;
            resp = co_await dremini::sendRequestCoro(robot_url, 10, loop_, 0x2625a0);
        }
        catch(std::exception& e) {
            // XXX: Failed to handshake with the host. We should retry later
            // Shoud we cache the result as no policy is available?
            // policy_cache[cache_key] = {};
            co_return true;
        }

        assert(resp != nullptr);
        auto [mime, _] = parseMime(resp->contentTypeString());
        int status = std::stoi(resp->getHeader("gemini-status"));
        bool have_robots_txt = status == 20 && mime == "text/plain";
        if(have_robots_txt) {
            disallowed_path = tlgs::parseRobotsTxt(std::string(resp->body()), {"*", "tlgs", "indexer"});
            have_robots_txt = true;
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
    policy_cache[cache_key] = disallowed_path;
    co_return !tlgs::isPathBlocked(url.path(), disallowed_path);
}

Task<std::optional<std::string>> GeminiCrawler::getNextCrawlPage() 
{
    auto db = app().getDbClient();
    std::optional<std::string> next_url;
    bool can_crawl = true;
    do {
        next_url = co_await getNextUrl();
        if(next_url.has_value() == false)
            co_return {};
        can_crawl = co_await shouldCrawl(next_url.value());
        if(can_crawl == false) {
            co_await db->execSqlCoro("UPDATE pages SET last_crawled_at = CURRENT_TIMESTAMP, last_status = $2, last_meta = $3 WHERE url = $1;"
                , next_url.value(), 0, std::string("blocked by robots"));
            co_await db->execSqlCoro("DELETE FROM pages WHERE url = $1 AND last_crawl_success_at < CURRENT_TIMESTAMP - INTERVAL '30' DAY;"
                , next_url.value());
        }
    } while(can_crawl == false);

    auto url_str = next_url.value();
    auto url = tlgs::Url(url_str);
    if(url.good() == false || url.protocol() != "gemini") {
        LOG_ERROR << "Failed to parse URL " << url_str;
        co_return {};
    }
    co_return url.str();
}

void GeminiCrawler::dispatchCrawl()
{
    // In case I forgot how this works in the future:
    // Start new crawls up to max_concurrent_connections_. And launch new crawls when one finishes. This function is tricky
    // and difficult to understand. It's a bit of a hack. But it is 100% lock free. The general idea is as follows:
    // 1. A atomic counter is used to keep track of the number of active crawls.
    // 2. We try to dispatch as many crawls as possible.
    // 3. When a crawl finishes, we resubmit the crawl task.
    //    * It is possible for crawls to finish at a close enough time. Causing a resubmit to dispatch multiple crawls.
    //    * It doesn't matter. Since the other dispatches will just dispatch 0 crawls.
    // 4. Near the end of crawling. It might be possible that there's not enough pages to be crawled
    //    * But a crawler may suddenly submit more links for crawling.
    //    * The nature to dispatch as much as possible helps here. Reactivating crawls if neded.
    while(!ended_) {
        auto counter = std::make_shared<tlgs::Counter>(ongoing_crawlings_);
        if(counter->count() >= max_concurrent_connections_)
            break;

        async_run([counter, this]() mutable -> Task<void> {
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

            try {
                co_await crawlPage(url_str.value());
                LOG_INFO << "Crawled " << url_str.value();
            }
            catch(std::exception& e) {
                LOG_ERROR << "Exception escaped crawling "<< url_str.value() <<": " << e.what();
            }
            loop_->queueInLoop([this](){dispatchCrawl();});
        });
    }
}

Task<void> GeminiCrawler::crawlPage(const std::string& url_str)
{
    auto db = app().getDbClient();
    const auto url = tlgs::Url(url_str);
    LOG_TRACE << "Crawling: " << url_str;
    if(url.str() != url_str) {
        LOG_WARN << "Warning: URL " << url_str << " is not normalized";
    }
    std::string error;
    bool failed = false;
    try {
        auto record = co_await db->execSqlCoro("SELECT url, indexed_content_hash , raw_content_hash "
            "FROM pages WHERE url = $1;", url.str());
        bool have_record = record.size() != 0;
        auto indexed_content_hash = have_record ? record[0]["indexed_content_hash"].as<std::string>() : "";
        auto raw_content_hash = have_record ? record[0]["raw_content_hash"].as<std::string>() : "";

        if(!have_record) {
            co_await db->execSqlCoro("INSERT INTO pages(url, domain_name, port, first_seen_at)"
                " VALUES ($1, $2, $3, CURRENT_TIMESTAMP);",
                url.str(), url.host(), url.port());
        }

        // Only fetch the entire page for content types we can handle.
        static const std::vector<std::string> indexd_mimes = {"text/gemini", "text/plain", "text/markdown", "text/x-rst", "plaintext"};
        HttpResponsePtr resp;
        int redirection_count = 0;
        int status;
        auto crawl_url = url;
        do {
            // 2.5MB is the maximum size of page we will index. 10s timeout, max 5 redirects and 25s max transfer time.
            resp = co_await dremini::sendRequestCoro(crawl_url.str(), 10, loop_, 0x2625a0, indexd_mimes, 25.0);

            status = std::stoi(resp->getHeader("gemini-status"));
            if(status / 10 == 3) {
                auto redirect_url = tlgs::Url(resp->getHeader("meta"));
                if(crawl_url.str() == redirect_url.str())
                    throw std::runtime_error("Bad redirect");
                if(co_await shouldCrawl(redirect_url.str()) == false)
                    throw std::runtime_error("Redirected to blocked URL");
                crawl_url = std::move(redirect_url);
            }
        } while(status / 10 == 3 && redirection_count++ < 5);

        const auto& meta = resp->getHeader("meta");
        std::string mime;
        std::optional<std::string> charset;
        std::optional<std::string> lang;
        std::string title;
        std::string body;
        std::vector<std::string> links;
        size_t body_size = resp->body().size();
        auto new_raw_content_hash = tlgs::xxHash64(resp->body());
        if(status/10 == 2) {
            // We should only have text files at this point. Try convert everything to UTF-8 because iconv will
            // ignore all encoding errors. Thus make Postgres happy for files with doggy encodings.
            std::string body_raw = tryConvertEncoding(resp->body(), charset.value_or("utf-8"), "utf-8");
            // The worst case is 25% from UTF-32 to UTF-8. Smaller than 20% is definatelly a binary file. We don't want to index it.
            if(body_raw.size() < resp->body().size()/5)
                throw std::runtime_error("Possible binary files sent as text");

            auto [mime_str, mime_param] = parseMime(meta);
            mime = std::move(mime_str);
            charset = mime_param.count("charset") ? mime_param["charset"] : std::optional<std::string>{};
            lang = mime_param.count("lang") ? mime_param["lang"] : std::optional<std::string>{};

            // No reason to reindex if the content hasn't changed. `force_reindex_` is used to force reindexing of files
            if(force_reindex_ == false && raw_content_hash == new_raw_content_hash) {
                co_await db->execSqlCoro("UPDATE pages SET last_crawled_at = CURRENT_TIMESTAMP, last_crawl_success_at = CURRENT_TIMESTAMP, "
                    "last_status = $2, last_meta = $3, content_type = $4 WHERE url = $1;",
                    url.str(), status, meta, mime);
                    co_return;
            }

            if(mime == "text/gemini") {
                tlgs::GeminiDocument doc = tlgs::extractGeminiConcise(body_raw);
                body = std::move(doc.text);
                links = std::move(doc.links);
                title = std::move(doc.title);
                if(title.empty())
                    title = url.str();
            }
            else if(mime == "text/plain" || mime == "plaintext" || mime == "text/markdown" || mime == "text/x-rst") {
                title = url.str();
                body = std::move(body_raw);
            }
            else {
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
            LOG_ERROR << "Failed to fetch " << url.str() << ": " << status;
            co_await db->execSqlCoro("UPDATE pages SET last_crawled_at = CURRENT_TIMESTAMP, last_status = $2, last_meta = $3 WHERE url = $1;"
                , url.str(), status, meta);
            co_await db->execSqlCoro("DELETE FROM pages WHERE url = $1 AND last_crawl_success_at < CURRENT_TIMESTAMP - INTERVAL '30' DAY;"
                , url.str());
            co_return;
        }
        // trim tailing spaces from title
        auto last_non_space = title.find_last_not_of(' ');
        if(last_non_space != 0 && last_non_space != std::string::npos)
            title.resize(last_non_space + 1);

        // TODO: Avoid parsing links when the content doesn't change
        std::vector<std::string> cross_site_links;
        std::vector<std::string> internal_links;
        for(const auto& link : links) {
            if(tlgs::isNonUriAction(link))
                continue;

            auto link_url = tlgs::Url(link);
            if(link_url.good()) {
                if(link_url.protocol() != "gemini")
                    continue;
            }
            else {
                link_url = linkCompose(url, link);
            }
            // We shall not send fragments
            link_url.withFragment("");

            // HACK: avoid mistyped links like gemini://en.gmn.clttr.info/cgmnlm.gmi?gemini://en.gmn.clttr.info/cgmnlm.gmi
            if(link_url.str().starts_with(link_url.param()) && link_url.path().ends_with(".gmi"))
                link_url.withParam("");

            bool is_cross_site = link_url.host() != url.host() || url.port() != link_url.port();
            if(is_cross_site)
                cross_site_links.push_back(link_url.str());
            else
                internal_links.push_back(link_url.str());
        }

        auto new_indexed_content_hash = tlgs::xxHash64(body);
        // Absolutelly no reason to reindex if the content hasn't changed even after post processing.
        if(new_indexed_content_hash == indexed_content_hash && new_raw_content_hash == raw_content_hash) {
            // Maybe this is too strict? The conent doesn't change means the content_type doesn't change, right...?
            co_await db->execSqlCoro("UPDATE pages SET last_crawled_at = CURRENT_TIMESTAMP, last_crawl_success_at = CURRENT_TIMESTAMP, "
                "last_status = $2, last_meta = $3, content_type = $4 WHERE url = $1;",
                url.str(), status, meta, mime);
                co_return;
        }

        // TODO: Guess the language of the content. Then index them with different parsers
        co_await db->execSqlCoro("UPDATE pages SET content_body = $2, size = $3, charset = $4, lang = $5, last_crawled_at = CURRENT_TIMESTAMP, "
            "last_crawl_success_at = CURRENT_TIMESTAMP, last_status = $6, last_meta = $7, content_type = $8, title = $9, "
            "cross_site_links = $10::json, internal_links = $11::json, indexed_content_hash = $12, raw_content_hash = $13 WHERE url = $1;",
            url.str(), body, body_size, charset, lang, status, meta, mime, title, nlohmann::json(cross_site_links).dump()
            , nlohmann::json(internal_links).dump(), new_indexed_content_hash, new_raw_content_hash);

        co_await db->execSqlCoro("UPDATE pages SET search_vector = to_tsvector(REPLACE(title, '.', ' ') || REPLACE(url, '-', ' ') || content_body), "
            "title_vector = to_tsvector(REPLACE(title, '.', ' ') || REPLACE(url, '-', ' ')), "
            "last_indexed_at = CURRENT_TIMESTAMP WHERE url = $1;", url.str());

        co_await db->execSqlCoro("DELETE FROM links WHERE url = $1", url.str());
        for(const auto& link : internal_links) {
            tlgs::Url link_url(link);
            co_await db->execSqlCoro("INSERT INTO links (url, host, port, to_url, is_cross_site, to_host, to_port) "
                "VALUES ($1, $2, $3, $4, $5, $6, $7);"
                , url.str(), url.host(), url.port(), link_url.str(), false, link_url.host(), link_url.port());

            if(co_await shouldCrawl(link_url.str()) == false)
                continue;
            co_await db->execSqlCoro("INSERT INTO pages (url, domain_name, port, first_seen_at) "
                "VALUES ($1, $2, $3, CURRENT_TIMESTAMP) ON CONFLICT DO NOTHING;",
                link_url.str(), link_url.host(), link_url.port());
        }
        for(const auto& link : cross_site_links) {
            tlgs::Url link_url(link);
            co_await db->execSqlCoro("INSERT INTO links (url, host, port, to_url, is_cross_site, to_host, to_port) "
                "VALUES ($1, $2, $3, $4, $5, $6, $7);"
                , url.str(), url.host(), url.port(), link_url.str(), true, link_url.host(), link_url.port());

            if(co_await shouldCrawl(link_url.str()) == false)
                continue;
            co_await db->execSqlCoro("INSERT INTO pages (url, domain_name, port, first_seen_at) "
                "VALUES ($1, $2, $3, CURRENT_TIMESTAMP) ON CONFLICT DO NOTHING;",
                link_url.str(), link_url.host(), link_url.port());
        }
    }
    catch(std::exception& e) {
        LOG_ERROR << "Failed to crawl " << url_str << ". Error: " << e.what();
        failed = true;
        error = e.what();
    }

    if(failed) {
        co_await db->execSqlCoro("UPDATE pages SET last_crawled_at = CURRENT_TIMESTAMP, last_status = $2, last_meta = $3 WHERE url = $1;"
            , url.str(), 0, error);
        co_await db->execSqlCoro("DELETE FROM pages WHERE url = $1 AND last_crawl_success_at < CURRENT_TIMESTAMP - INTERVAL '30' DAY;"
            , url.str());
        
        if(error == "Timeout" || error == "NetworkFailure")
            host_down_count_[url.hostWithPort(1965)]++;
    }
}
