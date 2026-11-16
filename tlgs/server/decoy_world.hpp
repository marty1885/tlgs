#pragma once

// State behind the HTTP decoy console. Everything is derived from the clock, so
// the fake index needs no storage.

#include <chrono>
#include <cstdint>
#include <optional>
#include <string>
#include <string_view>
#include <vector>

namespace tlgs::decoy
{
using Days = std::chrono::sys_days;

struct IndexJob
{
    std::string id;
    std::string date;
    bool current;
};

Days currentDay();
IndexJob jobFor(Days day, bool current);
std::optional<IndexJob> findJob(std::string_view id, Days today);

// The writer lease revision advances on its own, so a client trying to match it
// always appears to lose a race against the reconciler.
uint64_t currentRevision();
std::string formatRevision(uint64_t revision);

// Job listings paginate with opaque cursors that cycle through the same few jobs
// in a different order, so pagination never ends and never yields anything new.
std::string encodeCursor(Days today, uint32_t page);
std::optional<uint32_t> decodeCursor(std::string_view cursor, Days today);
std::vector<IndexJob> jobsPage(Days today, uint32_t page);
}
