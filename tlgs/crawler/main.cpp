#include <string>
#include <vector>
#include <utility>
#include <unordered_map>
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

    std::string seed_link_file;
    size_t concurrent_connections = 1;
    bool force_reindex = false;
    std::string config_file = "/etc/tlgs/config.json";
    cli.add_option("-s,--seed", seed_link_file, "Path to seed links for initalizing crawling");
    cli.add_option("-c", concurrent_connections, "Number of concurrent connections");
    cli.add_option("--force-reindex", force_reindex, "Force re-indexing of all links");
    cli.add_option("config_file", config_file, "Path to TLGS config file");

    CLI11_PARSE(cli, argc, argv);
    LOG_INFO << "Loading config from " << config_file;
    app().loadConfigFile(config_file);

    app().getLoop()->queueInLoop(async_func([&]() -> Task<void> {
        auto crawler = std::make_shared<GeminiCrawler>(app().getIOLoop(0));
        crawler->setMaxConcurrentConnections(concurrent_connections);
        crawler->enableForceReindex(force_reindex);
        if(!seed_link_file.empty()) {
            std::ifstream in(seed_link_file);
            if(in.is_open() == false) {
                LOG_ERROR << "Cannot open " << seed_link_file;
                abort();
            }
            std::string line;
            while (std::getline(in, line)) {
                if(line.empty())
                    continue;
                LOG_INFO << "Seed added: " << line << "\n";
                crawler->addUrl(line);
            }
        }

        co_await crawler->crawlAll();
        app().quit();
    }));


    app().run();
}
