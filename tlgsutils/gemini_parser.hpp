#pragma once

#include <string_view>
#include <vector>
#include <string>

namespace tlgs
{

struct GeminiDocument
{
    std::string text;
    std::string title;
    std::vector<std::string> links;
};

GeminiDocument extractGemini(const std::string_view sv);
GeminiDocument extractGeminiConcise(const std::string_view sv);
}
