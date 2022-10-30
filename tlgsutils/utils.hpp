#include <string>
#include <vector>
#include <algorithm>
#include <optional>
#include <concepts>
#include "url_parser.hpp"
#include <drogon/HttpRequest.h>


namespace tlgs
{
/**
 * @brief Detects if the string is ASCII art using a simple heuristic
 * 
 * @param str the string to check
 */
bool isAsciiArt(const std::string& str);

/**
 * @brief URL encode
 * 
 * @param str the string to encode
 */
std::string urlEncode(const std::string_view str);

/**
 * @brief Compose a URL and a path
 * 
 * @param url the URL
 * @param path  the path
 * @begincode
 * 	linkCompose(url("https://example.com"), "/path/to/file.txt") == "https://example.com/path/to/file.txt";
 * @endcode
 */
tlgs::Url linkCompose(const tlgs::Url& url, const std::string& path);

/**
 * @brief Detect URIs like mailto:xxxx ldap:xxxx (Without ://)
 * 
 * @param sv the uri to check
 */
bool isNonUriAction(const std::string& sv);

/**
 * @brief Computes xxhash of a string
 * 
 * @param str the string
 * @return std::string hex encoded hash
 */
std::string xxHash64(const std::string_view str);

template <typename T, typename Func>
    requires std::is_invocable_v<Func, typename T::value_type>
auto filter(const T& data, Func&& func)
{
    std::vector<typename T::value_type> ret;
    std::copy_if(data.begin(), data.end(), std::back_inserter(ret), std::forward<Func>(func));
    return ret;
}

template <typename T, typename Func>
    requires std::is_invocable_v<Func, typename T::value_type>
auto map(const T& data, Func&& func)
{
    using func_ret_type = decltype(func(data.front()));
    std::vector<func_ret_type> ret;
    ret.reserve(data.size());
    std::transform(data.begin(), data.end(), std::back_inserter(ret), std::forward<Func>(func));
    return ret;
}

std::optional<unsigned long long> try_strtoull(const std::string& str);

std::string pgSQLRealEscape(std::string str);

/**
 * @brief Convert URL into index-friendly string
 */
std::string indexFriendly(const tlgs::Url& url);
} // namespace tlgs