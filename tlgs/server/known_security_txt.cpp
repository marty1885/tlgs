#include "known_security_txt.hpp"

#include <drogon/CacheMap.h>
#include <drogon/HttpAppFramework.h>

using namespace drogon;

Task<std::shared_ptr<std::vector<std::string>>> knownSecurityTxt()
{
    static CacheMap<std::string, std::shared_ptr<std::vector<std::string>>> cache(app().getLoop(), 600);
    std::shared_ptr<std::vector<std::string>> security_txt;
    if(cache.findAndFetch("security_txt", security_txt) == false) {
        auto db = app().getDbClient();
        auto known_security_txt = co_await db->execSqlCoro("SELECT url FROM pages WHERE "
            "(content_type = 'text/plain' OR last_meta ILIKE 'text/plain%') "
            "AND url ~ '.*://[^\\/]+/.well-known/security.txt'");
        security_txt = std::make_shared<std::vector<std::string>>();
        security_txt->reserve(known_security_txt.size());
        for(const auto& entry : known_security_txt)
            security_txt->push_back(entry["url"].as<std::string>());
        cache.insert("security_txt", security_txt, 3600 * 8);
    }
    co_return security_txt;
}
