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
    std::string config_file = "/etc/tlgs/config.json";
    cli.add_option("-s,--seed", seed_link_file, "Path to seed links for initalizing crawling");
    cli.add_option("-c", concurrent_connections, "Number of concurrent connections");
    cli.add_option("config_file", config_file, "Path to TLGS config file");

    CLI11_PARSE(cli, argc, argv);
    LOG_INFO << "Loading config from " << config_file;
    app().loadConfigFile(config_file);

    std::shared_ptr<GeminiCrawler> crawler;
    app().getLoop()->queueInLoop([&]() -> void {
        crawler = std::make_shared<GeminiCrawler>(app().getIOLoop(0));
        crawler->setMaxConcurrentConnections(concurrent_connections);
        if(!seed_link_file.empty()) {
            std::ifstream in(seed_link_file);
            if(in.is_open() == false) {
                std::cerr << "Cannot open " << seed_link_file << std::endl;
                abort();
            }
            std::string line;
            while (std::getline(in, line)) {
                std::cout << line << "\n";
                if(line.empty())
                    continue;
                crawler->addUrl(line);
            }
        }

        app().getIOLoop(0)->queueInLoop([crawler](){
            crawler->start();
        });

        app().getLoop()->queueInLoop([crawler]()->AsyncTask{
            co_await crawler->awaitEnd();
            app().quit();
        });
    });


    app().run();
}
