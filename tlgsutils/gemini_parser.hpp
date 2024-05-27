#pragma once

#include <string_view>
#include <vector>
#include <string>
#include <optional>

#include <dremini/GeminiParser.hpp>
#include "url_parser.hpp"

namespace tlgs
{

struct GeminiDocument
{
    std::string text;
    std::string title;
    std::vector<std::string> links;
};

/**
 * @brief Parse and convert a Gemini document into title
 *  , plaintext(without styling and heading) and links
 * 
 * @param sv the Gemini document
 */
GeminiDocument extractGemini(const std::string_view sv);
GeminiDocument extractGemini(const std::vector<dremini::GeminiASTNode>& nodes);

/**
 * @brief Parse and convert a Gemini document into title
 * , plaintext(without styling and heading and ASCII art) and links
 * 
 * @param sv the Gemini document
 */
GeminiDocument extractGeminiConcise(const std::string_view sv);
GeminiDocument extractGeminiConcise(const std::vector<dremini::GeminiASTNode>& nodes);

/**
 * @brief Check if a Gemini page can be interperd as Gemsub using heuristics
 * 
 * @param doc The parsed Gemini document
 * @param feed_url the url of the Gemini page. If set, the chceking heuristics only considers feed entries
 * that are hosted on the same domain as feed_url
 * @param
 */
bool isGemsub(const std::vector<dremini::GeminiASTNode>& nodes);
bool isGemsub(const std::vector<dremini::GeminiASTNode>& nodes, const tlgs::Url& feed_url, const std::string_view protocol = "");
}
