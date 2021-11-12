#include "gemini_parser.hpp"
#include "utils.hpp"
#include <string_view>
#include <regex>
#include <iostream>
#include <sstream>

static bool startsWith(const std::string_view sv, const std::string_view target)
{
    if(sv.size() < target.size())
        return false;
#if 0
    auto start_idx = sv.find_first_not_of(' ');
    if(start_idx+target.size() > sv.size())
        return false;

    for(size_t i=0;i<target.size();i++) {
        if(sv[start_idx+i] != target[i])
            return false;
    }
    return true;
#else
    return sv.substr(0, target.size()) == target;
#endif
}

namespace tlgs
{


std::vector<GeminiASTNode> parseGemini(const std::string_view str)
{
    std::vector<GeminiASTNode> nodes;
    size_t last_pos = 0;
    bool in_preformatted_text = false;
    size_t preformatted_text_start = 0; 
    for(size_t i=0;i<str.size()+1;i++) {
        if((i == str.size() && str[i-1] != '\n')|| str[i] == '\n') {
            if(in_preformatted_text == false) {
                std::string_view line(str.data()+last_pos, i-last_pos);
                auto crlf = line.find_last_not_of("\r\n");
                if(crlf != std::string_view::npos)
                    line = std::string_view(line.data(), crlf+1);
                else
                    line = std::string_view(line.data(), 0);

                GeminiASTNode node;
                node.orig_text = line;
                if(startsWith(line, "=>")) {
                    std::string_view sv = line.substr(2);
                    std::string_view link;
                    std::string_view text;
                    auto link_start = sv.find_first_not_of(" \t");
                    if(link_start != std::string_view::npos) {
                        sv = sv.substr(link_start);
                        auto link_end = sv.find_first_of(" \t");
                        link = sv.substr(0, link_end);
                        if(link_end != std::string_view::npos) {
                            sv = sv.substr(link_end);
                            auto text_start = sv.find_first_not_of(" \t");
                            if(text_start != std::string_view::npos) {
                                sv = sv.substr(text_start);
                                auto text_end = sv.find_last_not_of(" \t");
                                text = sv.substr(0, text_end == std::string_view::npos? text_end : text_end+1);
                            }
                        }
                    }
                    node.text = text;
                    node.meta = link;
                    node.type = "link";
                }
                else if(startsWith(line, "###")) {
                    const static std::regex re("### *(.*)");
                    std::smatch sm;
                    std::regex_match(node.orig_text, sm, re);
                    node.text = sm[1];
                    node.type = "heading3";
                }
                else if(startsWith(line, "##")) {
                    const static std::regex re("## *(.*)");
                    std::smatch sm;
                    std::regex_match(node.orig_text, sm, re);
                    node.text = sm[1];
                    node.type = "heading2";
                }
                else if(startsWith(line, "#")) {
                    const static std::regex re("# *(.*)");
                    std::smatch sm;
                    std::regex_match(node.orig_text, sm, re);
                    node.text = sm[1];
                    node.type = "heading1";
                }
                else if(startsWith(line, "*")) {
                    const static std::regex re(" *\\* *(.*)");
                    std::smatch sm;
                    std::regex_match(node.orig_text, sm, re);
                    node.text = sm[1];
                    node.type = "list";
                }
                else if(startsWith(line, "```")) {
                    in_preformatted_text = true;
                    preformatted_text_start = last_pos;
                    last_pos = i+1;
                    continue;
                }
                else {
                    node.text = line;
                    node.type = "text";
                }
                last_pos = i+1;

                nodes.emplace_back(std::move(node));
            }
            else {
                std::string_view line(str.data()+last_pos, i-last_pos);
                auto crlf = line.find_last_not_of("\r\n");
                if(crlf != std::string_view::npos)
                    line = std::string_view(line.data(), crlf+1);
                last_pos = i+1;

                if(startsWith(line, "```")) {
                    std::string_view preformatted_text(str.data()+preformatted_text_start, i-preformatted_text_start);
                    GeminiASTNode node;
                    node.orig_text = preformatted_text;

                    std::stringstream ss;
                    std::string line;
                    std::string content;
                    ss << preformatted_text;
                    std::getline(ss, line);
                    if(line.size() > 3)
                        node.meta = line.substr(4);
                    
                    while(std::getline(ss, line)) {
                        if(line.find("```") != 0)
                            content += line + "\n";
                    }
                    node.text = content;
                    node.type = "preformatted_text";
                    in_preformatted_text = false;
                    nodes.emplace_back(std::move(node));
                }
            }
        }
    }
    return nodes;
}

GeminiDocument extractGemini(const std::string_view sv)
{
    GeminiDocument doc;
    auto nodes = parseGemini(sv);
    for(const auto& node : nodes)
    {
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
    auto nodes = tlgs::parseGemini(sv);
    for(const auto& node : nodes) {
        // Avoid indexing ASCII art. This may remove code blocks. But it shoudn't matter
        if(node.type == "preformatted_text") {
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
        else if(node.type == "text" && !node.text.empty()){
            char first = node.text[0];
            bool is_all_same = node.text.find_first_not_of(first) == std::string::npos;
            if(is_all_same)
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
