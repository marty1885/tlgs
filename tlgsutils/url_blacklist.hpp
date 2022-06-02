
#pragma once

#include <unordered_map>
#include <string>

#include "url_parser.hpp"
#include "robots_txt_parser.hpp"

namespace tlgs
{

struct UrlBlacklist 
{

    void add(const std::string& url_str) 
    {
        tlgs::Url url(url_str);
        if(url.good() == false)
            throw std::runtime_error("Invalid URL: " + url_str);
        std::string key = tlgs::Url(url).withFragment("").withPath("").withParam("").str();
        blacklisted_.insert({key, url.path()});
    }

    bool isBlocked(const tlgs::Url& url) const
    {
        std::string key = tlgs::Url(url).withFragment("").withPath("").withParam("").str();
        auto [begin, end] = blacklisted_.equal_range(key);
        if(begin == end)
            return false;

        for(auto it = begin; it != end; it++) {
            const auto& path = it->second;
            if(tlgs::isPathBlocked(url.path(), path))
                return true;
        }
        return false;
    }

    bool isBlocked(const std::string& str) const
    {
        return isBlocked(tlgs::Url(str));
    }

    std::unordered_multimap<std::string, std::string> blacklisted_;
};

}
