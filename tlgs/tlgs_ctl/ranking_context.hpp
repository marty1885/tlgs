#pragma once
#include <drogon/utils/coroutine.h>

drogon::Task<> rebuildRankingContext(bool dry_run, int *exit_status);
