#pragma once

#include <string>
struct SearchResult
{
    std::string url;
    std::string title;
    std::string content_type;
    std::string preview;
    std::string last_crawled_at;
    size_t size;
    float score;
};

struct ServerStatistics
{
    std::string update_time;
    int64_t page_count;
    int64_t domain_count;
    std::vector<std::pair<std::string, uint64_t>> content_type_count;
};