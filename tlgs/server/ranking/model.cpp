#include "model.hpp"
#include <tlgsutils/ranking/features.hpp>
#include <ranker.h>
#include <stdexcept>
#include <string>

namespace tlgs::ranking
{
static_assert(ranker_api::abi_version == 2, "Unsupported model scoring ABI");
static_assert(ranker_api::feature_count == feature_names.size(), "Model feature count mismatch");
static_assert(ranker_api::feature_set == feature_set, "Model feature set mismatch");
static_assert(ranker_api::feature_version == feature_version, "Model feature version mismatch");
static_assert(ranker_api::feature_names == feature_names, "Model feature names/order mismatch");

void score_batch(std::span<const float> features, size_t columns, std::span<float> scores)
{
    const auto status = ranker_api::score_batch(features, columns, scores);
    if (status != 0)
        throw std::invalid_argument("Reranker rejected buffers: status=" + std::to_string(status) +
                                    ", columns=" + std::to_string(columns) +
                                    ", input_values=" + std::to_string(features.size()) +
                                    ", output_rows=" + std::to_string(scores.size()));
}
} // namespace tlgs::ranking
