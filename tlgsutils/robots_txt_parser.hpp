#pragma once

#include <string>
#include <vector>
#include <set>

namespace tlgs
{
std::vector<std::string> parseRobotsTxt(const std::string& str, const std::set<std::string> agents);
bool isPathBlocked(const std::string& str, const std::vector<std::string> disallowed);
}