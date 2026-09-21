#pragma once

#include <drogon/utils/coroutine.h>

#include <memory>
#include <string>
#include <vector>

drogon::Task<std::shared_ptr<std::vector<std::string>>> knownSecurityTxt();
