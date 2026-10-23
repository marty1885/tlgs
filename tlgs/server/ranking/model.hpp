#pragma once
#include <cstddef>
#include <span>

namespace tlgs::ranking
{
// Input is row-major; output length is the row count. The generated callee checks
// its own column count and both buffer lengths before accessing either buffer.
void score_batch(std::span<const float> features, size_t columns, std::span<float> scores);
} // namespace tlgs::ranking
