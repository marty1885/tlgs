#include "decoy_world.hpp"

#include <fmt/format.h>

#include <algorithm>
#include <charconv>
#include <random>

namespace tlgs::decoy
{
namespace
{
// Old job links stay valid long enough for a returning scanner to find its history.
constexpr int retainedDays = 60;
// Listings only ever draw from the most recent jobs.
constexpr int listedJobs = 6;
constexpr int jobsPerPage = 3;
constexpr auto revisionInterval = std::chrono::seconds{15};
constexpr uint64_t cursorMask = 0x5bd1e9955bd1e995ULL;
constexpr uint64_t cursorMultiplier = 0x9e3779b97f4a7c15ULL;

// Inverse of an odd multiplier modulo 2^64 (Newton iteration).
constexpr uint64_t inverse(uint64_t value)
{
    uint64_t result = value;
    for(int i = 0; i < 5; ++i)
        result *= 2 - value * result;
    return result;
}
static_assert(cursorMultiplier * inverse(cursorMultiplier) == 1);

// Bijective scramble so consecutive pages do not get consecutive cursors.
constexpr uint64_t scramble(uint64_t value)
{
    value ^= cursorMask;
    value *= cursorMultiplier;
    return value ^ (value >> 29);
}

constexpr uint64_t unscramble(uint64_t value)
{
    value ^= (value >> 29) ^ (value >> 58);
    value *= inverse(cursorMultiplier);
    return value ^ cursorMask;
}
static_assert(unscramble(scramble(0x123456789abcdef0ULL)) == 0x123456789abcdef0ULL);

uint32_t dayNumber(Days day)
{
    return static_cast<uint32_t>(day.time_since_epoch().count());
}
}

Days currentDay()
{
    return std::chrono::floor<std::chrono::days>(std::chrono::system_clock::now());
}

IndexJob jobFor(Days day, bool current)
{
    const std::chrono::year_month_day calendarDay{day};
    const auto date = fmt::format("{:04}-{:02}-{:02}",
                                  int(calendarDay.year()),
                                  unsigned(calendarDay.month()),
                                  unsigned(calendarDay.day()));
    const auto number = static_cast<uint64_t>(day.time_since_epoch().count());
    const auto suffix = (number * 2654435761ULL + 1013904223ULL) % 1000000;
    return {fmt::format("idx-{}-{:06}", date, suffix), date, current};
}

std::optional<IndexJob> findJob(std::string_view id, Days today)
{
    for(int age = 0; age < retainedDays; ++age)
    {
        auto job = jobFor(today - std::chrono::days{age}, age == 0);
        if(job.id == id)
            return job;
    }
    return std::nullopt;
}

uint64_t currentRevision()
{
    const auto now = std::chrono::system_clock::now().time_since_epoch();
    return static_cast<uint64_t>(now / revisionInterval);
}

std::string formatRevision(uint64_t revision)
{
    return fmt::format("r{}", revision);
}

std::string encodeCursor(Days today, uint32_t page)
{
    return fmt::format("{:016x}", scramble(uint64_t{dayNumber(today)} << 32 | page));
}

std::optional<uint32_t> decodeCursor(std::string_view cursor, Days today)
{
    if(cursor.size() != 16)
        return std::nullopt;
    uint64_t raw = 0;
    const auto [end, error] = std::from_chars(cursor.data(), cursor.data() + cursor.size(), raw, 16);
    if(error != std::errc{} || end != cursor.data() + cursor.size())
        return std::nullopt;
    raw = unscramble(raw);
    // Cursors quietly die at midnight UTC, which looks like a client-side bug.
    if(static_cast<uint32_t>(raw >> 32) != dayNumber(today))
        return std::nullopt;
    return static_cast<uint32_t>(raw);
}

std::vector<IndexJob> jobsPage(Days today, uint32_t page)
{
    // Pages start at drifting offsets, so neighbouring pages overlap by a job or
    // two and the listing looks like an off-by-one bug rather than a loop.
    const auto start = (uint64_t{page} * jobsPerPage + page / 2) % listedJobs;
    std::vector<IndexJob> jobs;
    jobs.reserve(jobsPerPage);
    for(int offset = 0; offset < jobsPerPage; ++offset)
    {
        const auto age = static_cast<int>((start + offset) % listedJobs);
        jobs.push_back(jobFor(today - std::chrono::days{age}, age == 0));
    }
    if(page != 0)
    {
        std::mt19937_64 order{uint64_t{page} << 32 | dayNumber(today)};
        std::shuffle(jobs.begin(), jobs.end(), order);
    }
    return jobs;
}
}
