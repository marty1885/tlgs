#include <drogon/HttpController.h>
#include <drogon/utils/coroutine.h>
#include <drogon/HttpAppFramework.h>
#include <tlgsutils/url_parser.hpp>
#include "search_result.hpp"

using namespace drogon;

struct ToolsController : public HttpController<ToolsController>
{
public:
	Task<HttpResponsePtr> statistics(HttpRequestPtr req);
	Task<HttpResponsePtr> known_hosts(HttpRequestPtr req);
	Task<HttpResponsePtr> add_seed(HttpRequestPtr req);

	METHOD_LIST_BEGIN
    ADD_METHOD_TO(ToolsController::statistics, "/statistics", {Get});
    ADD_METHOD_TO(ToolsController::known_hosts, "/known-hosts", {Get});
	ADD_METHOD_TO(ToolsController::add_seed, "/add_seed", {Get});
    METHOD_LIST_END
};

Task<HttpResponsePtr> ToolsController::statistics(HttpRequestPtr req)
{
    static CacheMap<std::string, std::shared_ptr<ServerStatistics>> cache(app().getLoop(), 600);
    std::shared_ptr<ServerStatistics> server_stat;
    if(cache.findAndFetch("server_stat", server_stat) == false) {
        auto db = app().getDbClient();
        auto domain_pages = co_await db->execSqlCoro("SELECT COUNT(DISTINCT LOWER(domain_name)) as domain_count, COUNT(*) AS count "
            "FROM pages WHERE content_body IS NOT NULL");
        auto content_type = co_await db->execSqlCoro("SELECT COUNT(content_type) AS COUNT, content_type FROM pages "
            "GROUP BY content_type ORDER BY count DESC;");

        uint64_t page_count = domain_pages[0]["count"].as<uint64_t>();
        uint64_t domain_count = domain_pages[0]["domain_count"].as<uint64_t>();
        std::vector<std::pair<std::string, uint64_t>> content_type_count;
        content_type_count.reserve(content_type.size());
        for(const auto& content : content_type) {
            if(content["content_type"].isNull() == true)
                continue;
            std::string type = content["content_type"].as<std::string>();
            if(type.empty())
                type = "<empty string>";
            content_type_count.push_back({type, content["count"].as<uint64_t>()});
        }
        
        server_stat = std::make_shared<ServerStatistics>();
        server_stat->page_count = page_count;
        server_stat->domain_count = domain_count;
        server_stat->content_type_count = std::move(content_type_count);
        server_stat->update_time = trantor::Date::now().toCustomedFormattedString("%Y-%m-%d %H:%M:%S", false);
        cache.insert("server_stat", server_stat, 3600*6);
    }

    HttpViewData data;
    data["title"] = std::string("TLGS Statistics");
    data["server_stat"] = server_stat;
    auto resp = HttpResponse::newHttpViewResponse("statistics", data);
    resp->setContentTypeCodeAndCustomString(CT_CUSTOM, "text/gemini");
    co_return resp;
}

Task<HttpResponsePtr> ToolsController::known_hosts(HttpRequestPtr req)
{
    static CacheMap<std::string, std::shared_ptr<std::vector<std::string>>> cache(app().getLoop(), 600);
    std::shared_ptr<std::vector<std::string>> hosts;
    if(cache.findAndFetch("hosts", hosts) == false ) {
        auto db = app().getDbClient();
        auto known_hosts = co_await db->execSqlCoro("SELECT DISTINCT LOWER(domain_name) as domain_name, port FROM pages");
        hosts = std::make_shared<std::vector<std::string>>();
        hosts->reserve(known_hosts.size());
        for(const auto& host : known_hosts) {
            auto host_name = host["domain_name"].as<std::string>();
            auto port = host["port"].as<int>();
            if(tlgs::Url("gemini://"+host_name).good() == false)
                continue;
            hosts->push_back(tlgs::Url("gemini://"+host_name+":"+std::to_string(port)+"/").str());
        }
        cache.insert("hosts", hosts, 3600*8);
    }
    HttpViewData data;
    data["title"] = std::string("Hosts known to TLGS");
    data["hosts"] = hosts;
    auto resp = HttpResponse::newHttpViewResponse("known_hosts", data);
    resp->setContentTypeCodeAndCustomString(CT_CUSTOM, "text/gemini");
    co_return resp;
}

Task<HttpResponsePtr> ToolsController::add_seed(HttpRequestPtr req)
{
    auto input = utils::urlDecode(req->getParameter("query"));

    if(input.empty())
    {
        auto resp = HttpResponse::newHttpResponse();
        resp->addHeader("meta", "URL to your capsule");
        resp->setStatusCode((HttpStatusCode)10);
        co_return resp;
    }

    auto url = tlgs::Url(input);
    if(url.good() == false || url.protocol() != "gemini")
    {
        auto resp = HttpResponse::newHttpResponse();
        resp->addHeader("meta", "Invalid URL. Try again");
        resp->setStatusCode((HttpStatusCode)10);
        co_return resp;
    }
    if(req->getHeader("protocol") != "gemini")
    {
        auto resp = HttpResponse::newHttpResponse();
        resp->setBody("We only accept links directly through Gemini");
        resp->setContentTypeCode(CT_TEXT_PLAIN);
        resp->setStatusCode(k403Forbidden);
        co_return resp;
    }

    // HACK: Force slow down
    co_await drogon::sleepCoro(app().getLoop(), 0.75);

    auto db = app().getDbClient();
    co_await db->execSqlCoro("INSERT INTO pages (url, domain_name, port, first_seen_at) "
        "VALUES ($1, $2, $3, CURRENT_TIMESTAMP) ON CONFLICT DO NOTHING;",
        url.str(), url.host(), url.port(1965));
    
    auto resp = HttpResponse::newHttpResponse();
    resp->setBody("# Adding Capsule\nAdded " + input);
    resp->setContentTypeCodeAndCustomString(CT_CUSTOM, "text/gemini");
    co_return resp;
}