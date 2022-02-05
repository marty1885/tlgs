#include "url_parser.hpp"
#include <iostream>
#include <filesystem>
#include <algorithm>

using namespace tlgs;

Url::Url(const std::string& str, bool normalize_url)
{
    if(str.empty()) {
        good_ = false;
        return;
    }

    good_ = true;
    std::string_view sv = str;

    // Find protocol
    auto idx = sv.find("://");
    if(idx == std::string_view::npos) {
        good_ = false;
        return;
    }
    protocol_ = sv.substr(0, idx);
    if(protocol_.empty()) {
        good_ = false;
        return;
    }
    for(auto ch : protocol_) {
        if(isalnum(ch) == false) {
            good_ = false;
            return;
        }
    }
    default_port_ = protocolDefaultPort(protocol_);
    // Find host
    sv = sv.substr(idx+3);
    idx = sv.find_first_of(":/");
    host_ = sv.substr(0, idx);
    if(idx == std::string::npos) {
        path_ = "/";
        if(normalize_url)
            normalize();
        return;
    }
    // Find port
    if(sv[idx] == ':') {
        sv = sv.substr(idx+1);
        idx = sv.find("/");
        auto port_sv = sv.substr(0, idx);
        if(port_sv.empty()) {
            good_ = false;
            return;
        }
        try {
            port_ = std::stoi(std::string(port_sv));
        }
        catch(...) {
            good_ = false;
            return;
        }
        if(idx != std::string_view::npos)
            sv = sv.substr(idx+1);
        else
            sv = std::string_view();
    }
    else 
        sv = sv.substr(idx+1);
    // Find path
    idx = sv.find_first_of("?#");
    path_ = "/"+std::string(sv.substr(0, idx));
    if(normalize_url)
        normalize();
    if(idx == std::string_view::npos)
        return;
    // Find param
    if(sv[idx] == '?') {
        sv = sv.substr(idx+1);
        idx = sv.find('#');
        param_ = sv.substr(0, idx);
    }

    // Find fragment
    if(idx == std::string_view::npos)
        return;
    sv = sv.substr(idx+1);
    fragment_ = sv;
}

std::string Url::str() const
{
    if(!cache_.empty())
        return cache_;

    std::string res = protocol_ + "://"+host_;
    if(port_ != 0 && default_port_ != port_)
        res += ":"+std::to_string(port_);
    res += path_;
    if(!param_.empty())
        res += "?"+param_;
    if(!fragment_.empty())
        res += "#"+fragment_;
    cache_ = res;
    return res;
}

std::string Url::hostWithPort(unsigned short default_port) const
{
    std::string res = host_;
    if(port_ == 0 && default_port != 0)
        res += ":" + std::to_string(default_port);
    else
        res += ":" + std::to_string(port_);
    return res;
}

Url& Url::withHost(const std::string& new_host)
{
    cache_.clear();
    host_ = new_host;
    return *this;
}

Url& Url::withPath(const std::string& new_path, bool normalize_path)
{
    cache_.clear();
    if(new_path.empty() || new_path.front() != '/')
        path_ = "/" + new_path;
    else
        path_ = new_path;

    if(normalize_path)
        path_ = std::filesystem::path(path_).lexically_normal().generic_string();
    return *this;
}

Url& Url::withParam(const std::string& new_param)
{
    cache_.clear();
    param_ = new_param;
    return *this;
}

Url& Url::withProtocol(const std::string& new_protocol)
{
    cache_.clear();
    protocol_ = new_protocol;
    return *this;
}

Url& Url::withPort(unsigned short new_port)
{
    cache_.clear();
    port_ = new_port;
    return *this;
}

Url& Url::withPort()
{
    cache_.clear();
    port_ = 0;
    return *this;
}

Url& Url::withDefaultPort(unsigned short n)
{
    cache_.clear();
    default_port_ = n;
    return *this;
}

Url& Url::withFragment(const std::string& new_fragment)
{
    cache_.clear();
    fragment_ = new_fragment;
    return *this;
}

Url& Url::normalize()
{
    cache_.clear();
    std::transform(protocol_.begin(), protocol_.end(), protocol_.begin(), ::tolower);
    path_ = std::filesystem::path(path_).lexically_normal().generic_string();
    std::transform(host_.begin(), host_.end(), host_.begin(), ::tolower);
    return *this;
}

int Url::port(int default_port) const
{
    if(port_ != 0)
        return port_;
    else if(default_port != 0)
        return default_port;
    else
        return default_port_;
}

const std::string& Url::protocol() const
{
    return protocol_;
}

const std::string& Url::host() const
{
    return host_;
}

const std::string& Url::path() const
{
    return path_;
}

const std::string& Url::param() const
{
    return param_;
}

const std::string& Url::fragment() const
{
    return fragment_;
}


int Url::protocolDefaultPort(const std::string_view& proto)
{
    if(proto == "http")
        return 80;
    else if(proto == "https")
        return 443;
    else if(proto == "gemini")
        return 1965;
    else if(proto == "gopher")
        return 70;
    else if(proto == "ftp")
        return 21;
    else 
        return 0;
}
