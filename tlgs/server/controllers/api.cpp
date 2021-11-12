#include <drogon/HttpController.h>
#include <drogon/utils/coroutine.h>
#include <drogon/HttpAppFramework.h>
#include <tlgsutils/url_parser.hpp>
#include <nlohmann/json.hpp>
#include "search_result.hpp"

using namespace drogon;


namespace api
{
struct v1 : public HttpController<v1>
{
public:
	Task<HttpResponsePtr> known_hosts(HttpRequestPtr req);

	METHOD_LIST_BEGIN
    METHOD_ADD(v1::known_hosts, "/known_hosts", {Get});
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