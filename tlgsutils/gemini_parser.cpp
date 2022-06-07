#include "gemini_parser.hpp"
#include "utils.hpp"
#include <dremini/GeminiParser.hpp>
#include <string_view>
#include <regex>
#include <iostream>
#include <sstream>

namespace tlgs
{
GeminiDocument extractGemini(const std::string_view sv)
{
    GeminiDocument doc;
    auto nodes = dremini::parseGemini(sv);
    doc.text.reserve(sv.size());
    for(const auto& node : nodes) {
        doc.text += node.text + "\n";
        if(node.type == "link")
            doc.links.push_back(node.meta);
        else if(node.type == "heading1" && doc.title.empty())
            doc.title = node.text;
    }

    return doc;
}

GeminiDocument extractGeminiConcise(const std::string_view sv)
{
    // TODO: Optimize the function
    GeminiDocument doc;
    auto nodes = dremini::parseGemini(sv);
    bool first_content = true;
    for(const auto& node : nodes) {
        // Avoid indexing ASCII art. This may remove code blocks. But it shoudn't matter
        if(node.type == "preformatted_text") {
            // Usually if a preformatted text block is the first content, it's ASCII art
            if(first_content)
                continue;

            std::string meta = node.meta;
            // common text in the meta field that contains ASCII art
            std::transform(meta.begin(), meta.end(), meta.begin(), ::tolower);
            if(meta.find("ascii") != std::string::npos
                || meta.find("art") != std::string::npos
                || meta.find("banner") != std::string::npos
                || meta.find("logo") != std::string::npos
                || meta.find("title") != std::string::npos
                || meta.find("news") != std::string::npos
                || meta.find("capsule") != std::string::npos
                || meta.find("user") != std::string::npos
                || meta.find("image") != std::string::npos
                || meta.find("the") != std::string::npos
                || meta.find("graphics") != std::string::npos
                || meta.find("world") != std::string::npos)
                continue;
            
            if(tlgs::isAsciiArt(node.text) == true)
                continue;
        }
        // Avoid paragraph seperators
        // TODO: Handle unicode paragraph seperators
        else if(node.type == "text" && !node.text.empty()){
            first_content = false;

            // The entire line is made of the same character
            char first = node.text[0];
            bool is_all_same = node.text.find_first_not_of(first) == std::string::npos;
            if(is_all_same)
                continue;
            // The first character is repeated 3 times and the last is also repeated 3 times
            // Ex: ----- next up ------
            char last = node.text.back();
            if(node.text.size() > 6 && node.text.substr(0, 3).find_first_not_of(first) == std::string::npos
                && node.text.substr(node.text.size() - 3).find_first_not_of(last) == std::string::npos
                && first != ' ' && last != ' ' && first != '\t' && last != '\t')
                continue;

            // avoid people posting output of `tree` without formatting
            if(node.text.find("│") < 3)
                continue;
        }
        doc.text += node.text + "\n";
        if(node.type == "link") {
            doc.links.push_back(node.meta);
        }
        else if(node.type == "heading1" && doc.title.empty())
            doc.title = node.text;
    }
    return doc;
}
}
