#include "robots_txt_parser.hpp"
#include <regex>
#include <sstream>
#include <iostream>

std::vector<std::string> tlgs::parseRobotsTxt(const std::string& str, const std::set<std::string>& agents)
{
    std::vector<std::string> disallowed_path; 
    std::stringstream ss;
    ss << str;
    static const std::regex line_re(R"((.*):[ \t](.*))");
    std::smatch match;
    std::string line;
    bool care = false;
    while(std::getline(ss, line)) {
        if(line.empty()) {
            care = false;
            continue;
        }
        if(!std::regex_match(line, match, line_re))
            continue;
        
        std::string key = match[1];
        if(key == "User-agent") {
            std::string agent = match[2];
            if(agents.count(agent))
                care |= true;
        }
        else if(key == "Disallow" && care == true) {
            std::string path = match[2];
            if(path.empty())
                disallowed_path.clear();
            else
                disallowed_path.push_back(path);
        }
    }
    return disallowed_path;
}

bool tlgs::isPathBlocked(const std::string& path, const std::vector<std::string>& disallowed_paths)
{
    for(const auto& disallowed : disallowed_paths) {
        if(path == disallowed || path == disallowed+"/"
            || (path.size() > disallowed.size()+1 && path.find(disallowed) == 0 && (path[disallowed.size()] == '/' || disallowed.back() == '/'))) {
            return true;
        }
    }
    return false;
}