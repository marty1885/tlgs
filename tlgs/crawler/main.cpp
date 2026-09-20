#include <trantor/utils/Logger.h>
#include <drogon/HttpAppFramework.h>
#include "crawler.hpp"

#include "CLI/App.hpp"
#include "CLI/Formatter.hpp"
#include "CLI/Config.hpp"

using namespace drogon;
using namespace trantor;

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
    app().loadConfigFile(config_file);

    app().getLoop()->queueInLoop(async_func([&]() -> Task<void> {
        auto crawler = std::make_shared<GeminiCrawler>(app().getIOLoop(0));
        const auto tardis = app().getCustomConfig()["tardis"];
        if(tardis.isNull())
            throw std::runtime_error("missing tardis configuration");
        co_await crawler->syncTardis(tardis, maximum_pages);
        app().quit();
    }));


    app().run();
}
