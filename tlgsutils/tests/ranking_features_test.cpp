#include <tlgsutils/ranking/features.hpp>
#include <drogon/drogon_test.h>
#include <algorithm>
#include <cmath>
#include <stdexcept>

using namespace tlgs::ranking;

DROGON_TEST(RankingFeatures)
{
    Page item{
        .url = "gemini://gemini.orchard.example/~user/a_b.gmi",
        .site = "gemini://gemini.orchard.example/~user/",
        .title = "Orchard",
        .size = 128,
        .document = {.headings = "Search", .body = "Notes.",
                     .link_text = "Search\nAbout", .has_explicit_title = true},
        .retrieval = {.bm25 = RetrievalScore{1, 4.0}}};
    const auto values = tlgs::ranking::features("orchard search", {item});
    auto get = [&](std::string_view name)
    {
        auto position = std::find(tlgs::ranking::feature_names.begin(),
                                  tlgs::ranking::feature_names.end(), name);
        if (position == tlgs::ranking::feature_names.end())
            throw std::runtime_error("Unknown feature");
        return values.at(position - tlgs::ranking::feature_names.begin());
    };
    CHECK(values.size() == 111);
    CHECK(get("query_terms") == 2);
    CHECK(get("body_coverage") == 1);
    CHECK(get("headings_coverage") == 0.5);
    CHECK(get("logical_path_depth") == static_cast<float>(1.0 / 12));
    CHECK(get("logical_root") == 0);
    CHECK(std::isnan(get("hilltop_rr")));
    CHECK(std::isnan(get("ctx_bm25_gap_12")));
    item.document.link_text = "Search\nAbout\nOrchard\nOrchard";
    const auto changed = tlgs::ranking::features("orchard search", {item});
    for (size_t index = 0; index < tlgs::ranking::feature_names.size(); ++index)
        if (tlgs::ranking::feature_names[index].starts_with("body_"))
            CHECK(values[index] == changed[index]);
    const auto unicode = tlgs::ranking::features("Straße STRASSE", {item});
    auto query_index = std::find(tlgs::ranking::feature_names.begin(),
                                 tlgs::ranking::feature_names.end(), "query_terms") -
                       tlgs::ranking::feature_names.begin();
    CHECK(unicode[query_index] == 1);
    // Version 2 stop words affect only navigation features in declared languages.
    const auto column = [](std::string_view name) {
        return std::find(feature_names.begin(), feature_names.end(), name) - feature_names.begin();
    };
    auto language_item = item;
    language_item.url = "gemini://example.org/und-garten.gmi";
    language_item.document.language = "DE-de";
    const auto old_de = features("und garten", {language_item});
    const auto new_de = features("und garten", {language_item}, {}, 2);
    CHECK(old_de[column("slug_precision")] == 1);
    CHECK(new_de[column("slug_precision")] == 0.5);
    CHECK(new_de[column("url_path_fraction")] < old_de[column("url_path_fraction")]);
    language_item.document.language = "en";
    CHECK(features("und garten", {language_item}, {}, 2)[column("slug_precision")] == 1);
    language_item.url = "gemini://example.org/для-сад.gmi";
    language_item.document.language = "ru_RU";
    CHECK(features("для сад", {language_item}, {}, 2)[column("slug_precision")] == 0.5);
    language_item.document.language = "zh";
    CHECK(features("для сад", {language_item}, {}, 2)[column("slug_precision")] == 1);
    // A shortlist must retain the original pool's score scales and BM25 gaps.
    auto second = item;
    second.retrieval.bm25 = RetrievalScore{2, 2.0};
    const auto full = tlgs::ranking::features("orchard search", {item, second});
    const auto selected = tlgs::ranking::features("orchard search", {second}, {item.retrieval, second.retrieval});
    for (size_t index = 0; index < selected.size(); ++index)
    {
        const auto expected = full[selected.size() + index];
        CHECK((selected[index] == expected ||
                (std::isnan(selected[index]) && std::isnan(expected))));
    }
    auto unicode_item = item;
    unicode_item.title = "";
    unicode_item.document.has_explicit_title = false;
    unicode_item.document.headings = "";
    unicode_item.document.link_text = "";
    unicode_item.document.body = "Straße\u2028STRASSE\r\nβeta 𝟜\n";
    const auto unicode_text = tlgs::ranking::features("STRASSE βeta 𝟜", {unicode_item});
    auto feature = [&](std::string_view name)
    {
        return unicode_text.at(std::find(tlgs::ranking::feature_names.begin(),
                                         tlgs::ranking::feature_names.end(), name) -
                               tlgs::ranking::feature_names.begin());
    };
    CHECK(feature("body_all_terms") == 1);
    CHECK(feature("body_exact_phrase") == 1);
    CHECK(feature("body_log_chars") == static_cast<float>(std::log1p(13)));
    CHECK(feature("body_log_tokens") == static_cast<float>(std::log1p(3)));
}
