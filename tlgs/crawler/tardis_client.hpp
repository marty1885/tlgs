#pragma once

#include <cstdint>
#include <string>
#include <unordered_map>
#include <vector>

#include <drogon/utils/coroutine.h>
#include <trantor/net/EventLoop.h>

struct TardisCapture
{
    std::string url;
    int status = 0;
    std::string meta;
    std::string body;
};

struct TardisPage
{
    std::vector<TardisCapture> captures;
    bool hasMore = false;
    std::string resumeToken;
    int64_t till = 0;
};

class TardisClient
{
  public:
    TardisClient(trantor::EventLoop *loop, std::string endpoint, std::string certificate,
                 std::string privateKey, std::string mode, int64_t maximumBodyBytes,
                 size_t pageSize, std::string mimeTypes);

    drogon::Task<TardisPage> updates(int64_t since, int64_t till,
                                     const std::string &pageToken = {});

  private:
    trantor::EventLoop *loop_;
    std::string endpoint_, certificate_, privateKey_, mode_;
    int64_t maximumBodyBytes_;
    size_t pageSize_;
    std::string mimeTypes_;
};
