#pragma once

#include <string>
#include <vector>
#include <optional>
#include <tbb/concurrent_unordered_map.h>
#include <trantor/net/EventLoop.h>
#include <drogon/utils/coroutine.h>


class GeminiCrawler : public trantor::NonCopyable
{
public:
    using EventLoop = trantor::EventLoop;
    template<typename T>
    using Task = drogon::Task<T>;

    GeminiCrawler(EventLoop* loop) : loop_(loop) {}

    void addUrl(const std::string& url)
    {
        craw_queue_.push_back(url);
    }

    Task<std::optional<std::string>> getNextUrl();
    Task<bool> shouldCrawl(std::string url_str);
    Task<std::optional<std::string>> getNextCrawlPage();
    void dispatchCrawl();
    Task<void> crawlPage(const std::string& url_str);

    void start()
    {
        dispatchCrawl();
    }

    Task<void> awaitEnd()
    {
        while(true) {
            co_await drogon::sleepCoro(loop_, 0.2);
            if(ended_)
                break;
        }
        co_return;
    }

    void setMaxConcurrentConnections(size_t n)
    {
        max_concurrent_connections_ = n;
    }

    size_t maxConcurrentConnections() const
    {
        return max_concurrent_connections_;
    }
protected:
    EventLoop* loop_;
    tbb::concurrent_unordered_map<std::string, size_t> host_timeout_count_;
    std::vector<std::string> craw_queue_;
    size_t max_concurrent_connections_ = 1;
    std::atomic<size_t> ongoing_crawlings_ = 0;
    std::atomic<bool> ended_ = false;
};
