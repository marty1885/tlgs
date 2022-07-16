#include <drogon/HttpController.h>
#include <drogon/utils/coroutine.h>
#include <drogon/HttpAppFramework.h>
#include <tlgsutils/url_parser.hpp>
#include <tlgsutils/utils.hpp>
#include <nlohmann/json.hpp>
#include "search_result.hpp"

using namespace drogon;


namespace api
{
struct v1 : public HttpController<v1>
{
public:
	Task<HttpResponsePtr> known_hosts(HttpRequestPtr req);
    Task<HttpResponsePtr> known_feeds(HttpRequestPtr req);

	METHOD_LIST_BEGIN
    METHOD_ADD(v1::known_hosts, "/known_hosts", {Get});
    METHOD_ADD(v1::known_feeds, "/known_feeds", {Get});
    METHOD_LIST_END
};
}

Task<HttpResponsePtr> api::v1::known_hosts(HttpRequestPtr req)
{
    static CacheMap<std::string, std::shared_ptr<nlohmann::json>> cache(app().getLoop(), 600);
    std::shared_ptr<nlohmann::json> hosts;
    if(cache.findAndFetch("hosts", hosts) == false ) {
        auto db = app().getDbClient();
        auto known_hosts = co_await db->execSqlCoro("SELECT DISTINCT domain_name, port FROM pages");
        auto hosts_vector = std::vector<std::string>();
        hosts_vector.reserve(known_hosts.size());
        for(const auto& host : known_hosts) {
            auto host_name = host["domain_name"].as<std::string>();
            auto port = host["port"].as<int>();
            hosts_vector.push_back(tlgs::Url("gemini://"+host_name+":"+std::to_string(port)+"/").str());
        }
		hosts = std::make_shared<nlohmann::json>(hosts_vector);
        cache.insert("hosts", hosts, 3600*8);
    }

    co_await sleepCoro(app().getLoop(), 0.75);

	auto resp = HttpResponse::newHttpResponse();
	resp->setBody(hosts->dump());
	resp->setContentTypeCode(CT_APPLICATION_JSON);
	co_return resp;
}

Task<HttpResponsePtr> api::v1::known_feeds(HttpRequestPtr req)
{
    static CacheMap<std::string, std::shared_ptr<nlohmann::json>> cache(app().getLoop(), 600);
    const static std::array allowed_type = {"atom", "rss", "twtxt"};
    auto request_feed_type = req->getParameter("query");
    if(request_feed_type == "")
        request_feed_type = "atom";

    if(std::find(allowed_type.begin(), allowed_type.end(), request_feed_type) == allowed_type.end())
        throw std::invalid_argument("Invalid feed type");

    std::shared_ptr<nlohmann::json> feeds;
    if(cache.findAndFetch(request_feed_type, feeds) == false ) {
        auto feeds_in_db = co_await [&request_feed_type]() {
            auto db = app().getDbClient();
            if(request_feed_type == "rss")
                return db->execSqlCoro("SELECT url FROM pages WHERE content_type = 'application/rss+xml'");
            else if(request_feed_type == "twtxt")
                return db->execSqlCoro("SELECT url FROM pages WHERE content_type = 'text/plain' AND url LIKE '%/twtxt.txt'");
            else
                return db->execSqlCoro("SELECT url FROM pages WHERE content_type = 'application/atom+xml'");
        }();
        auto feeds_vector = tlgs::map(feeds_in_db, [](const auto& feed) { return feed["url"].template as<std::string>(); });
        feeds = std::make_shared<nlohmann::json>(std::move(feeds_vector));
        cache.insert(request_feed_type, feeds, 3600*8);
    }

    co_await sleepCoro(app().getLoop(), 0.75);

    auto resp = HttpResponse::newHttpResponse();
    resp->setBody(feeds->dump());
    resp->setContentTypeCode(CT_APPLICATION_JSON);
    co_return resp;
}