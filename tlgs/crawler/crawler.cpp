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

#include "iconv.hpp"
#include "blacklist.hpp"

using namespace drogon;
using namespace dremini;
using namespace trantor;


std::string tryConvertEncoding(const std::string_view& str, const std::string& src_enc, const std::string& dst_enc, bool ignore_err = true)
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

std::pair<std::string, std::unordered_map<std::string, std::string>> parseMime(const std::string& mime)
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
        // XXX: I really want to have a proper job queue. But using SQL is good enought for now
        // XXX: I Hope this does not cause a data race
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
    auto timeout = host_timeout_count_.find(url.hostWithPort(1965));
    if(timeout != host_timeout_count_.end() && timeout->second > 3)
        co_return false;

    // TODO: Use a LRU cache
    const std::string cache_key = url.hostWithPort(1965);
    static std::unordered_map<std::string, std::vector<std::string>> policy_cache;
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
        LOG_TRACE << url.hostWithPort(1965) << " has no up to date robots policy stored in DB. Asking for robots.txt";
        std::string robot_txt_content;
        int gemini_status = 0;
        std::string content_type;
        bool have_robots_txt = false;
        try {
            std::string robot_url = tlgs::Url(url).withParam("").withPath("/robots.txt").str();
            LOG_TRACE << "Fetching robots.txt from " << robot_url;
            auto resp = co_await dremini::sendRequestCoro(robot_url, 10, loop_, 0x2625a0);
            auto [mime, _] = parseMime(resp->contentTypeString());
            gemini_status = std::stoi(resp->getHeader("gemini-status"));
            robot_txt_content = std::string(resp->body());
            content_type = std::move(mime);
        }
        catch(std::exception& e) {
            // TODO: Site may no longer exist
        }
        // Don't have a robots.txt. Allow all crawler
        if(gemini_status == 20 && content_type == "text/plain") {
            disallowed_path = tlgs::parseRobotsTxt(robot_txt_content, {"*", "tlgs", "indexer"});
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
    while(!ended_) {
        auto counter =  std::make_shared<tlgs::Counter>(ongoing_crawlings_);
        if(counter->count() < max_concurrent_connections_) {
            loop_->queueInLoop(async_func([counter, this]() mutable -> Task<void> {
                auto url_str = co_await getNextCrawlPage();
                if(url_str.has_value()) {
                    try {
                        co_await crawlPage(url_str.value());
                    }
                    catch(std::exception& e) {
                        LOG_ERROR << "Exception escaped crawling "<< url_str.value() <<": " << e.what();
                    }
                    loop_->queueInLoop([this](){dispatchCrawl();});
                }
                else if(ongoing_crawlings_ == 1) {
                    ended_ = true;
                }
            }));
        }
        else
            break;
    }
}

Task<void> GeminiCrawler::crawlPage(const std::string& url_str)
{
    auto db = app().getDbClient();
    auto url = tlgs::Url(url_str);
    LOG_INFO << "Crawling: " << url_str;
    std::string error;
    bool failed = false;
    try {
        auto record = co_await db->execSqlCoro("SELECT url, content_body FROM pages WHERE url = $1;", url.str());
        bool have_record = record.size() != 0;

        if(!have_record) {
            co_await db->execSqlCoro("INSERT INTO pages(url, domain_name, port, first_seen_at)"
                " VALUES ($1, $2, $3, CURRENT_TIMESTAMP);",
                url.str(), url.host(), url.port());
        }

        // TODO: Use blake2b
        auto content_hash = have_record ? drogon::utils::getMd5(record[0]["content_body"].as<std::string>()) : "";
        std::string extension = std::filesystem::path(url.path()).extension().generic_string();
        std::transform(extension.begin(), extension.end(), extension.begin(), ::tolower);
        // HACK: Only fetch headers of text files
        static const std::vector<std::string> index_mimes = {"text/gemini", "text/plain", "text/markdown", "text/x-rst", "plaintext"};
        auto resp = co_await dremini::sendRequestCoro(url.str(), 10, loop_, 0x2625a0, index_mimes); // 2.5MB
        int status = std::stoi(resp->getHeader("gemini-status"));

        const auto& meta = resp->getHeader("meta");
        auto [mime, mime_param] = parseMime(meta);
        std::optional<std::string> charset = mime_param.count("charset") ? mime_param["charset"] : std::optional<std::string>{};
        std::optional<std::string> lang = mime_param.count("lang") ? mime_param["lang"] : std::optional<std::string>{};
        std::string title;
        std::string body;
        std::vector<std::string> cross_site_links;
        std::vector<std::string> internal_links;
        size_t body_size = resp->body().size();

        if(status/10 == 2) {
            std::vector<std::string> links;
            if(mime == "text/gemini") {
                // Still convert UTF-8 to UTF-8 because iconv will ignore all errors and make postgre happy
                std::string body_raw = tryConvertEncoding(resp->body(), charset.value_or("utf-8"), "utf-8");
                if(body_raw.size() < resp->body().size()/10) { // apprantly this is a binary file
                    throw std::runtime_error("Seeming binary files sent as text");
                }

                tlgs::GeminiDocument doc = tlgs::extractGeminiConcise(body_raw);
                body = std::move(doc.text);
                links = std::move(doc.links);
                title = std::move(doc.title);
                if(title.empty() && url.port() == 1965) {
                    std::string tmp = tlgs::Url(url).withPort(0).str();
                    title = tmp;
                }
                else if(title.empty() && url.port() != 1965)
                    title = url.str();

            }
            else if(mime == "text/plain" || mime == "plaintext" || mime == "text/markdown" || mime == "text/x-rst") {
                body = tryConvertEncoding(resp->body(), charset.value_or("utf-8"), "utf-8");
                if(body.size() < resp->body().size()/10) { // apprantly this is a binary file or totally broken
                    throw std::runtime_error("Seeming binary files sent as text");
                }
                if(url.port() == 1965)
                    title = tlgs::Url(url).withPort(0).str();
                else
                    title = url.str();
            }
            else {
                body.clear();
                body_size = 0;
                if(url.port() == 1965)
                    title = tlgs::Url(url).withPort(0).str();
                else
                    title = url.str();
            }

            // TODO: Avoid parsing links when the content doesn't change
            for(const auto& link : links) {
                auto link_url = tlgs::Url(link);
                if(link_url.good()) {
                    if(link_url.protocol() != "gemini")
                        continue;
                }
                else {
                    // FIXME: The current algorithm does not handle paths with parameters
                    auto link_path = std::filesystem::path(link);
                    if(link_path.is_absolute())
                        link_url = tlgs::Url(url).withPath(link);
                    else {
                        auto current_path = std::filesystem::path(url.path());
                        if(url.path().back() == '/') // we are visiting a directory  
                            link_url = tlgs::Url(url).withPath((current_path/link_path).generic_string());
                        else
                            link_url = tlgs::Url(url).withPath((current_path.parent_path()/link_path).generic_string());
                    }
                    link_url = link_url.withParam("").withDefaultPort(1965);
                }

                // HACK: avoid mistyped links like gemini://en.gmn.clttr.info/cgmnlm.gmi?gemini://en.gmn.clttr.info/cgmnlm.gmi
                if(link_url.str().starts_with(link_url.param()) && link_url.path().ends_with(".gmi"))
                    link_url.withParam("");

                bool is_cross_site = link_url.host() != url.host() || url.port() != link_url.port();
                if(is_cross_site)
                    cross_site_links.push_back(link_url.str());
                else
                    internal_links.push_back(link_url.str());
            }
        }
        else if(status/10 == 1) {
            body = meta;
            title = meta;
            body_size = meta.size();
            mime = "<gemini-request-info>";
        }
        else {
            // Nothing. We don't process them.
            throw std::runtime_error("Gemini status: " + std::to_string(status));
        }

        // TODO: Guess the language of the content. Then index them with different parsers
        // TODO: Only update the minimal parameters when we know the hash is the same
        auto new_content_hash = drogon::utils::getMd5(body);
        co_await db->execSqlCoro("UPDATE pages SET content_body = $2, size = $3, charset = $4, lang = $5, last_crawled_at = CURRENT_TIMESTAMP, "
            "last_crawl_success_at = CURRENT_TIMESTAMP, last_status = $6, last_meta = $7, content_type = $8, title = $9, "
            "cross_site_links = $10::json, internal_links = $11::json WHERE url = $1;",
            url.str(), body, body_size, charset, lang, status, meta, mime, title
            , nlohmann::json(cross_site_links).dump(), nlohmann::json(internal_links).dump());
        // No reason to update if hash is the same
        if(content_hash != new_content_hash) {
            co_await db->execSqlCoro("UPDATE pages SET search_vector = to_tsvector(REPLACE(title, '.', ' ') || content_body), "
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
        
        if(error == "Timeout")
            host_timeout_count_[url.hostWithPort(1965)]++;
    }
}