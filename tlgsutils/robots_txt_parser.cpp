#include "robots_txt_parser.hpp"
#include <drogon/utils/Utilities.h>
#include <regex>
#include <set>
#include <sstream>
#include <iostream>
#include <filesystem>

std::vector<std::string> tlgs::parseRobotsTxt(const std::string& str, const std::set<std::string>& agents)
{
    std::string lf_str = str;
    if(str.find("\r\n") != std::string::npos)
        drogon::utils::replaceAll(lf_str, "\r\n", "\n");

    std::set<std::string> disallowed_path; 
    std::stringstream ss(lf_str);
    static const std::regex line_re(R"([ \t]*(.*):[ \t]*(.*))");
    std::smatch match;
    std::string line;
    bool care = true;
    bool last_line_user_agent = false;
    while(std::getline(ss, line)) {
        if(!std::regex_match(line, match, line_re))
            continue;
        
        std::string key = match[1];
        //  convert to lowercase
        std::transform(key.begin(), key.end(), key.begin(), ::tolower);
        if(key == "user-agent") {
            std::string agent = match[2];
            if(last_line_user_agent) {
                care |= agents.count(agent) > 0;
            }
            else {
                care = agents.count(agent) > 0;
            }
            last_line_user_agent = true;
        }
        else {
            last_line_user_agent = false;
        }
        
        if(key == "disallow" && care == true) {
            std::string path = match[2];
            if(path.empty())
                disallowed_path.clear();
            else
                disallowed_path.insert(path);
        }
    }
    return std::vector<std::string>(disallowed_path.begin(), disallowed_path.end());
}


/**
 * @brief Fast matching for common cases. Otherwise, use the regex. Fast cases include
 *  1. No wildcard
 *  2. Starts with *
 *  3. Ends with *
 *  4. Starts with * and ends with $
 *  5. Starts with * and ends with *
 *  6. Contains * in the middle
 * 
 * @param pattern the wildcard pattern
 * @param str the string to match
 */
static bool wildcardPathMatch(std::string pattern, const std::string_view& str)
{
    if(pattern.empty())
        return false;

    size_t star_count = std::count(pattern.begin(), pattern.end(), '*');
    if(star_count == 0) {
        return str == pattern || str == pattern+"/"
            || (str.size() > pattern.size()+1 && str.starts_with(pattern) && (str[pattern.size()] == '/' || pattern.back() == '/'));
    }

    if(pattern.back() == '$' && (pattern.starts_with("*") || pattern.starts_with("/*")))
        pattern.pop_back();

    // */foo/bar/*
    if(pattern[0] == '*' && pattern.back() == '*' && star_count == 2)
        return str.find(pattern.substr(1, pattern.size()-2)) != std::string_view::npos;
    // /*/foo/*
    if(pattern.starts_with("/*") && pattern.back() == '*' && star_count == 2)
        return str.find(pattern.substr(2, pattern.size()-3)) != std::string_view::npos;
    // *fooo...
    if(pattern[0] == '*' && star_count == 1)
        return str.ends_with(pattern.substr(1));
    // /*foo...
    if(pattern.starts_with("/*") && star_count == 1)
        return str.ends_with(pattern.substr(2));
    // foo*
    if(pattern.back() == '*' && star_count == 1)
        return str.starts_with(pattern.substr(0, pattern.size() - 1));
    
    // Now * must be in the middle.
    auto n = pattern.find("*");
    if(n != std::string_view::npos && star_count == 1)
        return str.starts_with(pattern.substr(0, n)) && str.rfind(pattern.substr(n+1)) > n;
    
    // Else we convert the pattern to a regex and try to match
    std::string regex_pattern;
    const std::string_view escape_chars = "\\.+()[]{}|";
    for(char ch : pattern) {
        if(ch == '*')
            regex_pattern += ".*";
        else if(escape_chars.find(ch) != std::string_view::npos)
            regex_pattern += "\\" + std::string(1, ch);
        else
            regex_pattern += ch;
    }
    try {
        std::regex re(regex_pattern);
        std::smatch sm;
        std::string s(str);
        return std::regex_match(s, sm, re);
    }
    catch(std::regex_error& e) {
        return false;
    }
}

bool tlgs::isPathBlocked(const std::string& path, const std::vector<std::string>& disallowed_paths)
{
    for(const auto& disallowed : disallowed_paths) {
        if(wildcardPathMatch(disallowed, path))
            return true;
    }
    return false;
}

bool tlgs::isPathBlocked(const std::string& path, const std::string& disallowed_path)
{
    return wildcardPathMatch(disallowed_path, path);
}
