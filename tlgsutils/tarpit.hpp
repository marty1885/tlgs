#pragma once

#include <drogon/HttpResponse.h>

#include <string_view>

namespace tlgs
{
struct TarpitResponse
{
    drogon::HttpResponsePtr response;
    unsigned delayMs = 0;
};

drogon::HttpResponsePtr geminiTarpitWarning();
TarpitResponse geminiTarpitPassage(std::string_view token);
drogon::HttpResponsePtr httpTarpitWarning();
drogon::HttpResponsePtr httpTarpitPassage(std::string_view token);
}
