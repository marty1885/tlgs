#include <trantor/utils/Logger.h>
#include <drogon/HttpAppFramework.h>
#include "crawler.hpp"

#include "CLI/App.hpp"
#include "CLI/Formatter.hpp"
#include "CLI/Config.hpp"

#include <fstream>
#include <stdexcept>
#include <unistd.h>

using namespace drogon;
using namespace trantor;

namespace
{
Json::Value loadCrawlerConfig(const std::string& configFile)
{
    std::ifstream input(configFile);
    if(!input)
        throw std::runtime_error("unable to open config file: " + configFile);

    Json::Value source;
    Json::CharReaderBuilder reader;
    std::string errors;
    if(!Json::parseFromStream(reader, input, &source, &errors))
        throw std::runtime_error("unable to parse config file: " + errors);

    Json::Value config(Json::objectValue);
    config["app"]["handle_sig_term"] = false;
    if(source.isMember("db_clients"))
        config["db_clients"] = source["db_clients"];
    if(source.isMember("custom_config"))
        config["custom_config"] = source["custom_config"];
    return config;
}
}

int main(int argc, char** argv)
{
    trantor::Logger::setLogLevel(trantor::Logger::LogLevel::kInfo);
    CLI::App cli{"TLGS crawler"};

    size_t maximum_pages = 0;
    std::string config_file = "/etc/tlgs/config.json";
    cli.add_option("--max-pages", maximum_pages, "Stop after this many TARDIS update pages (for controlled runs)");
    cli.add_option("config_file", config_file, "Path to TLGS config file");

    CLI11_PARSE(cli, argc, argv);
    LOG_INFO << "Loading config from " << config_file;
    // Server configs may also contain HTTP listeners and server plugins.  The
    // crawler only needs its database and source settings and must never bind
    // a serving port or initialize serving plugins.
    const auto config = loadCrawlerConfig(config_file);
    app().loadConfigJson(config);

    app().getLoop()->queueInLoop(async_func([&]() -> Task<void> {
#ifdef __OpenBSD__
        // Drogon has started; install the sandbox before the first crawl.
        const auto uploadPath = app().getUploadPath();
        if(unveil(uploadPath.c_str(), "rwc") == -1)
            throw std::runtime_error("unable to unveil Drogon upload spool: " + uploadPath);
        // Trantor may use c-ares, which reads these files itself rather than
        // using libc's resolver access granted by the dns pledge.
        for(const auto* path : {"/etc/resolv.conf", "/etc/hosts"}) {
            if(unveil(path, "r") == -1)
                throw std::runtime_error("unable to unveil DNS configuration: " + std::string(path));
        }
        const auto& custom = app().getCustomConfig()["tardis"];
        for(const auto* field : {"certificate", "private_key"}) {
            const auto path = custom.get(field, "").asString();
            if(!path.empty() && unveil(path.c_str(), "r") == -1)
                throw std::runtime_error("unable to unveil crawler " + std::string(field) + ": " + path);
        }
        // Drogon does not expose database hosts through getCustomConfig().
        for(const auto& db : config["db_clients"]) {
            const auto host = db.get("host", "").asString();
            if(!host.empty() && host.front() == '/' && unveil(host.c_str(), "w") == -1)
                throw std::runtime_error("unable to unveil PostgreSQL socket directory: " + host);
        }
        if(unveil(nullptr, nullptr) == -1)
            throw std::runtime_error("unable to lock TLGS crawler unveil rules");
        if(pledge("stdio rpath wpath cpath inet unix dns", nullptr) == -1)
            throw std::runtime_error("unable to pledge TLGS crawler");
#endif
        auto crawler = std::make_shared<GeminiCrawler>(app().getIOLoop(0));
        const auto tardis = app().getCustomConfig()["tardis"];
        if(tardis.isNull())
            throw std::runtime_error("missing tardis configuration");
        co_await crawler->syncTardis(tardis, maximum_pages);
        app().quit();
    }));


    app().run();
}
