#pragma once

#include <string>
#include <vector>
#include <optional>
#include <tbb/concurrent_unordered_map.h>
#include <tbb/concurrent_queue.h>
#include <trantor/net/EventLoop.h>
#include <drogon/utils/coroutine.h>


class GeminiCrawler : public trantor::NonCopyable
{
public:
    using EventLoop = trantor::EventLoop;
    template<typename T>
    using Task = drogon::Task<T>;

    GeminiCrawler(EventLoop* loop) : loop_(loop) {}

    /**
     * @brief Adds a url to the crawling queue.
     * 
     * @param url the URL to be queued.
     */

    void addUrl(const std::string& url)
    {
        craw_queue_.push(url);
    }

    /**
     * @brief Start the crawler.
     * @note This function is async and returns immediately.
     * 
     */
    void start()
    {
        dispatchCrawl();
    }

    /**
     * @brief co_returns when the crawler is done.
     */
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
    /**
     * @brief Launches up to max_concurrent_connections_ concurrent crawler tasks (not threads)
     * to fetch content from URLs. This function is async and returns immediately.
     * 
     * @note await on `awaiteEnd()` to wait for all the tasks to finish.
     * @note This function continues launch tasks until all the URLs are crawled.
     */
    void dispatchCrawl();
    /**
     * @brief Should the crawler crawl this URL?
     * @param url The URL to check.
     * 
     * @return true if the crawler should crawl this URL.
     */
    Task<bool> shouldCrawl(std::string url_str);
    /**
     * 
     * @brief Get the next URL that the crawler should crawl.
     * @param url The URL to crawl.
     * 
     * @return std::nullopt if no URL is available.
     */
    Task<std::optional<std::string>> getNextCrawlPage();
    Task<std::optional<std::string>> getNextUrl();
    /**
     * @brief Crawl the given URL. Then add the content found in that URL to the DB
     * 
     * @param url_str the URL to crawl
     */
    Task<void> crawlPage(const std::string& url_str);

    EventLoop* loop_;
    tbb::concurrent_unordered_map<std::string, size_t> host_timeout_count_;
    tbb::concurrent_queue<std::string> craw_queue_;
    size_t max_concurrent_connections_ = 1;
    std::atomic<size_t> ongoing_crawlings_ = 0;
    std::atomic<bool> ended_ = false;
};
