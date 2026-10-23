#pragma once
#include <stddef.h>
#ifdef __cplusplus
extern "C" {
#endif
/* Row-major float32, 111 columns; missing=NaN, no alignment required.
 * Returns 0 on success, 1 for wrong shape, 2 for invalid buffers, 3 for overlap.
 * Lengths count float elements, not bytes. No reads/writes on rejection.
 * Empty input/output supported; checked shape must still match this model. */
int ranker_batch_v2(const float *features, size_t values, size_t columns,
                      float *scores, size_t rows);
size_t ranker_lanes(void);
const char *ranker_target(void);
#ifdef __cplusplus
}
#if __cplusplus >= 202002L
#include <span>
#include <array>
#include <string_view>
namespace ranker_api {
inline constexpr unsigned abi_version = 2;
inline constexpr size_t feature_count = 111;
inline constexpr unsigned feature_version = 1;
inline constexpr std::string_view feature_set = "visiblebody111";
inline constexpr std::array<std::string_view, 111> feature_names = {{
    "bm25_log_score",
    "bm25_present",
    "bm25_relative",
    "bm25_rr",
    "body_all_terms",
    "body_best_span",
    "body_coverage",
    "body_exact_phrase",
    "body_first_match",
    "body_log_chars",
    "body_log_tokens",
    "body_matched_fraction",
    "body_most_common_fraction",
    "body_query_precision",
    "body_tf_max",
    "body_tf_mean",
    "body_tf_min",
    "body_truncated",
    "body_unique_fraction",
    "ctx_bm25_gap_12",
    "ctx_bm25_gap_1k",
    "ctx_gap12_bm25_rr",
    "ctx_gap12_title_coverage",
    "ctx_gap1k_at_root",
    "ctx_gap1k_bm25_rr",
    "ctx_hostname_at_root",
    "ctx_hostname_coverage",
    "ctx_root_exact_at_root",
    "ctx_root_name_at_root",
    "ctx_root_name_coverage",
    "ctx_root_name_exact",
    "eng_headings_body_coverage",
    "eng_prominent_coverage",
    "eng_prominent_phrase",
    "eng_title_body_coverage",
    "has_explicit_title",
    "headings_all_terms",
    "headings_best_span",
    "headings_coverage",
    "headings_exact_phrase",
    "headings_first_match",
    "headings_log_chars",
    "headings_log_tokens",
    "headings_matched_fraction",
    "headings_most_common_fraction",
    "headings_query_precision",
    "headings_tf_max",
    "headings_tf_mean",
    "headings_tf_min",
    "headings_unique_fraction",
    "hilltop_log_score",
    "hilltop_present",
    "hilltop_relative",
    "hilltop_rr",
    "hilltop_sites_log",
    "internal_log",
    "link_text_all_terms",
    "link_text_best_span",
    "link_text_coverage",
    "link_text_exact_phrase",
    "link_text_first_match",
    "link_text_log_chars",
    "link_text_log_tokens",
    "link_text_matched_fraction",
    "link_text_most_common_fraction",
    "link_text_query_precision",
    "link_text_tf_max",
    "link_text_tf_mean",
    "link_text_tf_min",
    "link_text_unique_fraction",
    "logical_path_depth",
    "logical_root",
    "outgoing_log",
    "query_log_chars",
    "query_terms",
    "size_log",
    "slug_long_query_present",
    "slug_precision",
    "slug_query_coverage",
    "slug_repetition",
    "title_all_terms",
    "title_best_span",
    "title_coverage",
    "title_exact_phrase",
    "title_first_match",
    "title_log_chars",
    "title_log_tokens",
    "title_matched_fraction",
    "title_most_common_fraction",
    "title_query_precision",
    "title_tf_max",
    "title_tf_mean",
    "title_tf_min",
    "title_unique_fraction",
    "url_all_terms",
    "url_best_span",
    "url_coverage",
    "url_domain_fraction",
    "url_exact_phrase",
    "url_first_match",
    "url_leftmost_fraction",
    "url_log_chars",
    "url_log_tokens",
    "url_matched_fraction",
    "url_most_common_fraction",
    "url_path_fraction",
    "url_query_precision",
    "url_tf_max",
    "url_tf_mean",
    "url_tf_min",
    "url_unique_fraction"
}};
[[nodiscard]] inline int score_batch(std::span<const float> features, size_t columns,
                       std::span<float> scores) {
    return ranker_batch_v2(features.data(), features.size(), columns,
                             scores.data(), scores.size());
}
}
#endif
#endif
