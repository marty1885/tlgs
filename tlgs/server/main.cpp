#include <drogon/drogon.h>
#include <dremini/GeminiServerPlugin.hpp>
#include <spartoi/SpartanServerPlugin.hpp>
#include <tlgsutils/url_parser.hpp>
#include <stdexcept>

#ifdef __linux__
#define LLUNVEIL_USE_UNVEIL
#include <llunveil.h>
#endif
#include <unistd.h>

#include "search_result.hpp"

#include "CLI/App.hpp"
#include "CLI/Formatter.hpp"
#include "CLI/Config.hpp"

using namespace drogon;
using namespace dremini;

void registerDecoyHandler();

int main(int argc, char** argv)
{
    app().setLogLevel(trantor::Logger::LogLevel::kTrace);
    registerDecoyHandler();
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
        auto allow = [](const std::string& path, const char* permissions) {
            if(path.empty()) return;
            const int result = unveil(path.c_str(), permissions);
            #if defined(__OpenBSD__)
            if(result == -1)
                throw std::runtime_error("unable to unveil: " + path);
            #else
            (void)result;
            #endif
        };
        allow(drogon::app().getDocumentRoot(), "r");
        allow(drogon::app().getUploadPath(), "rwc");
        // /add_seed contacts TARDIS with this client identity.
        const auto &tardis = drogon::app().getCustomConfig()["tardis"];
        allow(tardis.get("certificate", "").asString(), "r");
        allow(tardis.get("private_key", "").asString(), "r");
        const int locked = unveil(nullptr, nullptr);
        #if defined(__OpenBSD__)
        if(locked == -1)
            throw std::runtime_error("unable to lock TLGS server unveil rules");
        #else
        (void)locked;
        #endif
        #endif

        #if defined(__OpenBSD__)
        // we need wpatch and cpath for drogon's upload spool
        if(pledge("stdio rpath wpath cpath inet unix dns", nullptr) == -1)
            throw std::runtime_error("unable to pledge TLGS server");
        #endif
    });

    // HACK: Replace Gemini links that needs user input with =:
    app().registerPostHandlingAdvice([](const HttpRequestPtr& req, const HttpResponsePtr& resp) {
        if(req->getHeader("protocol") == "spartan" && resp->contentTypeString() == "text/gemini") {
            std::stringstream ss;
            ss << resp->getBody();

            std::string result;
            std::string line;
            while(std::getline(ss, line)) {
                if(line.starts_with("=>") &&
                    (line.find("/search") != std::string::npos || line.find("/backlinks") != std::string::npos
                    || line.find("/add_seed") != std::string::npos) && line.find("/doc") == std::string::npos
                    && line.find("?") == std::string::npos) {
                    utils::replaceAll(line, "=>", "=:");
                }
                result += line + "\n";
            }
            resp->setBody(result);
        }
    });

    CLI::App cli{"TLGS server"};
    std::string config_file = "/etc/tlgs/server_config.json";
    cli.add_option("config_file", config_file, "Path to TLGS config file");
    CLI11_PARSE(cli, argc, argv);
    LOG_INFO << "Loading config from " << config_file;
    app().loadConfigFile(config_file);

    app().run();
}
