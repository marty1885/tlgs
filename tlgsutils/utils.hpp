#include <string>
#include "url_parser.hpp"

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
} // namespace tlgs