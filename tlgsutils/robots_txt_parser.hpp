#pragma once

#include <string>
#include <vector>
#include <set>

namespace tlgs
{
/**
 * @brief Parse robots.txt and return a set of disallowed paths.
 * 
 * @param str robots.txt content
 * @param agents the user agents we care about. '*' must be explicitly specified otherwise it is ignored
 */
std::vector<std::string> parseRobotsTxt(const std::string& str, const std::set<std::string>& agents);
/**
 * @brief Check if the path is disallowed by a set of robots.txt rules.
 *
 * @param str the path to check
 * @param disallowed set of robots.txt rules
 * @note As of now, this function only supports the * wildcard. ?, [], etc... is undefined behavior.
 */
bool isPathBlocked(const std::string& str, const std::vector<std::string>& disallowed);
}