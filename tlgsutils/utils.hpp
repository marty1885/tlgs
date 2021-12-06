#include <string>
#include "url_parser.hpp"

namespace tlgs
{
bool isAsciiArt(const std::string& str);
std::string urlEncode(const std::string_view str);
tlgs::Url linkCompose(const tlgs::Url& url, const std::string& path);
bool isNonUriAction(const std::string& sv);
}