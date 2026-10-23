#include "model.hpp"
#include <tlgsutils/ranking/context_features.hpp>
#include <ranker.h>
#include <stdexcept>
#include <string>

namespace tlgs::ranking
{
static_assert(ranker_api::abi_version == 2, "Unsupported model scoring ABI");
template<class T> consteval bool validContract(const T& names)
{
    if constexpr (std::tuple_size_v<T> == context_feature_names.size())
        return names == context_feature_names && ranker_api::feature_set == context_feature_set &&
               ranker_api::feature_version == context_feature_version;
    else if constexpr (std::tuple_size_v<T> == feature_names.size())
        return names == feature_names && ranker_api::feature_set == feature_set &&
               ranker_api::feature_version == feature_version;
    else return false;
}
static_assert(validContract(ranker_api::feature_names), "Model feature contract mismatch");
static_assert(ranker_api::feature_count == ranker_api::feature_names.size());
size_t model_feature_count() { return ranker_api::feature_count; }

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
