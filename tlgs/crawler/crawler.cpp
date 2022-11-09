#include "crawler.hpp"

#include <filesystem>
#include <random>
#include <stdexcept>
#include <algorithm>

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

#include <fmt/core.h>

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

Task<std::optional<std::string>> GeminiCrawler::getNextPotentialCarwlUrl()
{
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
                sample_pct.compare_exchange_strong(tablesample_pct, new_value, std::memory_order_release);
            }
            if(urls.size() == 0 && tablesample_pct >= 100)
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
        "WHERE host = $1 AND port = $2 AND last_crawled_at > CURRENT_TIMESTAMP - INTERVAL '7' DAY", url.host(), url.port());
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
        auto [mime, _] = parseMime(resp->contentTypeString());
        int status = std::stoi(resp->getHeader("gemini-status"));
        // HACK: Some capsules have broken MIME
        bool have_robots_txt = status == 20 && (mime == "text/plain" || mime == "text/gemini");
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
        auto url = tlgs::Url(url_str);
        if(url.good() == false || url.protocol() != "gemini") {
            LOG_ERROR << "Failed to parse URL " << url_str;
            continue;
        }

        auto can_crawl = co_await shouldCrawl(url_str);
        if(can_crawl == false) {
            co_await db->execSqlCoro("UPDATE pages SET last_crawled_at = CURRENT_TIMESTAMP, last_status = $2, last_meta = $3 WHERE url = $1;"
                , url_str, 0, std::string("blocked"));
            co_await db->execSqlCoro("DELETE FROM pages WHERE url = $1 AND last_crawl_success_at < CURRENT_TIMESTAMP - INTERVAL '30' DAY;"
                , url_str);
            continue;
        }
        co_return url.str();
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

        try {
            bool success = co_await crawlPage(url_str.value());
            if(success)
                LOG_INFO << "Processed " << url_str.value();
            // else // we already print out the error message in crawlPage()
            //     LOG_ERROR << "Failed to process " << url_str.value();
        }
        catch(std::exception& e) {
            LOG_ERROR << "Exception escaped crawling "<< url_str.value() <<": " << e.what();
        }
        loop_->queueInLoop([this](){dispatchCrawl();});
    }
    catch(std::exception& e) {
        LOG_ERROR << "Exception escaped in dispatchCrawl(): " << e.what();
        dispatchCrawl();
    }});
}

Task<bool> GeminiCrawler::crawlPage(const std::string& url_str)
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
        if(co_await shouldCrawl(url.str()) == false)
            throw std::runtime_error("Blocked by robots.txt");
        auto record = co_await db->execSqlCoro("SELECT url, indexed_content_hash , raw_content_hash, last_status"
            ", last_crawled_at FROM pages WHERE url = $1;", url.str());
        bool have_record = record.size() != 0;
        auto indexed_content_hash = have_record ? record[0]["indexed_content_hash"].as<std::string>() : "";
        auto raw_content_hash = have_record ? record[0]["raw_content_hash"].as<std::string>() : "";

        if(!have_record) {
            co_await db->execSqlCoro("INSERT INTO pages(url, domain_name, port, first_seen_at)"
                " VALUES ($1, $2, $3, CURRENT_TIMESTAMP);",
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
                LOG_INFO << "Skipping " << url.str() << " that was proxy-errored recently";
                co_return true;
            }
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
                if(redirect_url.good() == false || crawl_url.str() == redirect_url.str())
                    throw std::runtime_error("Bad redirect");
                if(url.protocol() != "gemini")
                    throw std::runtime_error("Redirected to non-gemini URL");
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
            if(force_reindex_ == false && raw_content_hash == new_raw_content_hash) {
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
                if(url.path().ends_with("twtxt.txt"))
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
            // treat slow down as host not reachable as TLGS doesn't have a way to delay crawling yet
            if(status == 44)
                host_timeout_count_[url.hostWithPort(1965)]++;
            LOG_ERROR << "Failed to fetch " << url.str() << ": " << status;
            co_await db->execSqlCoro("UPDATE pages SET last_crawled_at = CURRENT_TIMESTAMP, last_status = $2, last_meta = $3 WHERE url = $1;"
                , url.str(), status, meta);
            co_await db->execSqlCoro("DELETE FROM pages WHERE url = $1 AND last_crawl_success_at < CURRENT_TIMESTAMP - INTERVAL '30' DAY;"
                , url.str());
            co_return false;
        }

        auto new_indexed_content_hash = tlgs::xxHash64(body);
        // Absolutelly no reason to reindex if the content hasn't changed even after post processing.
        if(new_indexed_content_hash == indexed_content_hash && new_raw_content_hash == raw_content_hash) {
            // Maybe this is too strict? The conent doesn't change means the content_type doesn't change, right...?
            co_await db->execSqlCoro("UPDATE pages SET last_crawled_at = CURRENT_TIMESTAMP, last_crawl_success_at = CURRENT_TIMESTAMP, "
                "last_status = $2, last_meta = $3, content_type = $4 WHERE url = $1;",
                url.str(), status, meta, mime);
            co_return true;
        }

        std::set<tlgs::Url> link_urls;
        for(const auto& link : links) {
            // ignore links like mailto: ldap:. etc..
            if(tlgs::isNonUriAction(link))
                continue;

            auto link_url = tlgs::Url(link);
            if(link_url.good()) {
                if(link_url.protocol() == "")
                    link_url.withProtocol(url.protocol());
                if(link_url.protocol() != "gemini")
                    continue;
            }
            // sometimes invalid host/port causes the URL to be invalid. Ignore them
            else if(link.starts_with("gemini://")) {
                continue;
            }
            else  {
                link_url = linkCompose(url, link);
                if(link_url.good() == false)
                    continue;
            }
            // We shall not send fragments
            link_url.withFragment("");

            // HACK: avoid mistyped links like gemini://en.gmn.clttr.info/cgmnlm.gmi?gemini://en.gmn.clttr.info/cgmnlm.gmi
            if(link_url.str().starts_with(link_url.param()) && link_url.path().ends_with(".gmi"))
                link_url.withParam("");
            link_urls.insert(std::move(link_url));
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

        // TODO: Guess the language of the content. Then index them with different parsers
        co_await db->execSqlCoro("UPDATE pages SET content_body = $2, size = $3, charset = $4, lang = $5, last_crawled_at = CURRENT_TIMESTAMP, "
            "last_crawl_success_at = CURRENT_TIMESTAMP, last_status = $6, last_meta = $7, content_type = $8, title = $9, "
            "cross_site_links = $10::json, internal_links = $11::json, indexed_content_hash = $12, raw_content_hash = $13, feed_type = $14 WHERE url = $1;",
            url.str(), body, body_size, charset, lang, status, meta, mime, title, nlohmann::json(cross_site_links).dump()
            , nlohmann::json(internal_links).dump(), new_indexed_content_hash, new_raw_content_hash, feed_type);

        // Full text index update
        auto index_firendly_url = indexFriendly(url);
        co_await db->execSqlCoro("UPDATE pages SET "
            "title_vector = to_tsvector(REPLACE(title, '.', ' ') || ' ' || $2), last_indexed_at = CURRENT_TIMESTAMP WHERE url = $1;"
            , url.str(), index_firendly_url);
        if(internal_links.size() == 0 && cross_site_links.size() == 0)
            co_return true;

        // Update link formation
        // XXX: Drogon does not support bulk insert API. We have to do with string concatenation (with proper escaping)
        std::string link_query = "INSERT INTO links (url, host, port, to_url, is_cross_site, to_host, to_port) VALUES ";
        std::string page_query = "INSERT INTO pages (url, domain_name, port, first_seen_at) VALUES ";
        size_t page_count = 0;
        for(const auto& link_url : link_urls) {
            bool is_cross_site = link_url.host() != url.host() || url.port() != link_url.port();

            using tlgs::pgSQLRealEscape;
            link_query += fmt::format("('{}', '{}', {}, '{}', {}, '{}', {}), ",
                pgSQLRealEscape(url.str()), pgSQLRealEscape(url.host()), url.port(), pgSQLRealEscape(link_url.str()),
                is_cross_site, pgSQLRealEscape(link_url.host()), link_url.port());

            if(co_await shouldCrawl(link_url.str()) == false)
                continue;
            page_query += fmt::format("('{}', '{}', {}, CURRENT_TIMESTAMP), ",
                pgSQLRealEscape(link_url.str()), pgSQLRealEscape(link_url.host()), link_url.port());
            page_count++;
        }

        co_await db->execSqlCoro("DELETE FROM links WHERE url = $1", url.str());
        co_await db->execSqlCoro(link_query.substr(0, link_query.size() - 2) + " ON CONFLICT DO NOTHING;");
        if(page_count != 0)
            co_await db->execSqlCoro(page_query.substr(0, page_query.size() - 2) + " ON CONFLICT DO NOTHING;");
    }
    catch(std::exception& e) {
        error = e.what();
    }

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
