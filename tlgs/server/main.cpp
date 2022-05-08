#include <drogon/drogon.h>
#include <dremini/GeminiServerPlugin.hpp>
#include <tlgsutils/url_parser.hpp>

#ifdef __linux__
#define LLUNVEIL_USE_UNVEIL
#include <llunveil.h>
#endif

#include "search_result.hpp"

#include "CLI/App.hpp"
#include "CLI/Formatter.hpp"
#include "CLI/Config.hpp"

using namespace drogon;
using namespace dremini;


int main(int argc, char** argv)
{
    // app().setLogLevel(trantor::Logger::LogLevel::kTrace);
    app().registerHandler("/",
        [](const HttpRequestPtr& req,
           std::function<void (const HttpResponsePtr &)> &&callback)
        {
            auto resp = HttpResponse::newHttpViewResponse("homepage");
            resp->setContentTypeCodeAndCustomString(CT_CUSTOM, "text/gemini");
            callback(resp);
        });
    app().registerHandler("/about",
        [](const HttpRequestPtr& req,
           std::function<void (const HttpResponsePtr &)> &&callback)
        {
            HttpViewData data;
            data["title"] = std::string("About TLGS");
            auto resp = HttpResponse::newHttpViewResponse("about", data);
            resp->setContentTypeCodeAndCustomString(CT_CUSTOM, "text/gemini");
            callback(resp);
        });
    app().registerHandler("/news",
        [](const HttpRequestPtr& req,
           std::function<void (const HttpResponsePtr &)> &&callback)
        {
            HttpViewData data;
            data["title"] = std::string("TLGS News and Updates");
            auto resp = HttpResponse::newHttpViewResponse("news", data);
            resp->setContentTypeCodeAndCustomString(CT_CUSTOM, "text/gemini");
            callback(resp);
        });
    app().registerHandler("/doc/search",
        [](const HttpRequestPtr& req,
           std::function<void (const HttpResponsePtr &)> &&callback)
        {
            HttpViewData data;
            data["title"] = std::string("TLGS Search Documentation");
            auto resp = HttpResponse::newHttpViewResponse("doc_search", data);
            resp->setContentTypeCodeAndCustomString(CT_CUSTOM, "text/gemini");
            callback(resp);
        });
    app().registerHandler("/doc/index",
        [](const HttpRequestPtr& req,
           std::function<void (const HttpResponsePtr &)> &&callback)
        {
            HttpViewData data;
            data["title"] = std::string("TLGS Index Documentation");
            auto resp = HttpResponse::newHttpViewResponse("doc_indexing", data);
            resp->setContentTypeCodeAndCustomString(CT_CUSTOM, "text/gemini");
            callback(resp);
        });
    app().registerHandler("/doc/api",
        [](const HttpRequestPtr& req,
           std::function<void (const HttpResponsePtr &)> &&callback)
        {
            HttpViewData data;
            data["title"] = std::string("TLGS API Documentation");
            auto resp = HttpResponse::newHttpViewResponse("doc_api", data);
            resp->setContentTypeCodeAndCustomString(CT_CUSTOM, "text/gemini");
            callback(resp);
        });
    app().registerHandler("/doc/backlinks",
        [](const HttpRequestPtr& req,
           std::function<void (const HttpResponsePtr &)> &&callback)
        {
            HttpViewData data;
            data["title"] = std::string("TLGS Backlinks Documentation");
            auto resp = HttpResponse::newHttpViewResponse("doc_backlinks", data);
            resp->setContentTypeCodeAndCustomString(CT_CUSTOM, "text/gemini");
            callback(resp);
        });
    
    app().getLoop()->queueInLoop([](){
        #if defined(__linux__) || defined(__OpenBSD__)
        // Lockdown the server to only access the files in the document directory
        unveil(drogon::app().getDocumentRoot().c_str(), "r");
        unveil(drogon::app().getUploadPath().c_str(), "rwc");
        unveil(nullptr, nullptr);
        #endif
    });

    CLI::App cli{"TLGS server"};
    std::string config_file = "/etc/tlgs/server_config.json";
    cli.add_option("config_file", config_file, "Path to TLGS config file");
    CLI11_PARSE(cli, argc, argv);
    LOG_INFO << "Loading config from " << config_file;
    app().loadConfigFile(config_file);

    app().run();
}
