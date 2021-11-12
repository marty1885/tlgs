#pragma once

#include <string_view>
#include <vector>
#include <string>

namespace tlgs
{

struct GeminiASTNode
{
    std::string orig_text;
    std::string text;
    std::string type;
    std::string meta;
};

struct GeminiDocument
{
    std::string text;
    std::string title;
    std::vector<std::string> links;
};

std::vector<GeminiASTNode> parseGemini(const std::string_view sv);
GeminiDocument extractGemini(const std::string_view sv);
GeminiDocument extractGeminiConcise(const std::string_view sv);
}
