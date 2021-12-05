#pragma once

#include <string>

namespace tlgs
{

struct Url
{
    Url() = default;
    Url(const std::string& str, bool normalize_url = true);
    Url(const Url&) = default;
    Url(Url&&) = default;
    Url& operator=(const tlgs::Url&) = default;
    inline bool good() const { return good_; }
    std::string str() const;
    std::string hostWithPort(unsigned short default_port) const;
    Url& withHost(const std::string& new_host);
    Url& withPath(const std::string& new_path, bool normalize_path = true);
    Url& withParam(const std::string& new_param);
    Url& withProtocol(const std::string& new_protocol);
    Url& withPort(unsigned short new_port);
    Url& withPort();
    Url& withDefaultPort(unsigned short n);
    Url& normalize();
    Url& withFragment(const std::string& new_fragment);
    inline bool validate()
    {
        good_ = !protocol_.empty() && !host_.empty() && !path_.empty();
        for(auto ch : protocol_) {
            if(isalnum(ch) == false) {
                good_ = false;
                break;
            }
        }
        return good_;
    }

    int port(int default_port = 0) const;
    const std::string& protocol() const;
    const std::string& host() const;
    const std::string& path() const;
    const std::string& param() const;
    const std::string& fragment() const;

    static int protocolDefaultPort(const std::string_view& proto);

protected:
    std::string protocol_;
    std::string host_;
    int port_ = 0;
    std::string path_;
    std::string param_;
    std::string fragment_;
    bool good_ = true;
    int default_port_;
};

}