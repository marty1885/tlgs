#include "features.hpp"
#include "context_features.hpp"
#include <unicode/locid.h>
#include <tlgsutils/url_parser.hpp>
#include <algorithm>
#include <cmath>
#include <limits>
#include <set>
#include <span>
#include <drogon/utils/Utilities.h>
#include <stdexcept>
#include <unicode/uchar.h>
#include <unicode/unistr.h>
#include <unicode/utf8.h>
#include <unordered_map>

namespace tlgs::ranking
{
using Words = std::vector<std::string>;
using Terms = std::set<std::string>;
using Values = std::array<float, feature_names.size()>;
// Every name is resolved during compilation; misspellings fail the build.
static consteval size_t featureIndex(std::string_view name)
{
    for (size_t i = 0; i < feature_names.size(); ++i)
        if (feature_names[i] == name) return i;
    throw "Unknown ranking feature";
}

template<size_t N>
struct FeaturePrefix
{
    char text[N];
    consteval FeaturePrefix(const char (&value)[N])
    {
        std::copy_n(value, N, text);
    }
    constexpr operator std::string_view() const { return {text, N - 1}; }
};

static consteval size_t featureIndex(std::string_view prefix, std::string_view suffix)
{
    for (size_t i = 0; i < feature_names.size(); ++i) {
        auto name = feature_names[i];
        if (name.starts_with(prefix) && name.substr(prefix.size()).starts_with("_") &&
            name.substr(prefix.size() + 1) == suffix) return i;
    }
    throw "Unknown ranking feature";
}

static const Terms stop = {"a",  "an", "and", "are", "as", "at",   "be",  "by",   "for", "from", "in",
                    "is", "it", "of",  "on",  "or", "that", "the", "this", "to",  "with"};
// Conservative function-word lists; only apply the document's declared language.
static const Terms german_stop = {"aber", "als", "auch", "auf", "aus", "bei", "das", "dass",
    "dem", "den", "der", "des", "die", "ein", "eine", "einem", "einen", "einer",
    "eines", "für", "hat", "ist", "mit", "nicht", "oder", "sich", "sind", "und",
    "von", "war", "wie", "wird", "zum", "zur", "über"};
static const Terms russian_stop = {"без", "был", "была", "были", "быть", "для", "его",
    "есть", "или", "как", "мне", "она", "они", "оно", "при", "так", "это",
    "что", "чтобы", "этот", "эта", "эти"};

static bool stopWord(const std::string& term, const std::string& language, unsigned version)
{
    if (stop.count(term)) return true;
    if (version == 1) return false;
    auto end = language.find_first_of("_-,");
    auto primary = language.substr(0, end);
    std::transform(primary.begin(), primary.end(), primary.begin(), [](unsigned char c) {
        return c >= 'A' && c <= 'Z' ? c + ('a' - 'A') : c;
    });
    return (primary == "de" && german_stop.count(term)) ||
           (primary == "ru" && russian_stop.count(term));
}
static icu::UnicodeString unicode(const std::string &s) { return icu::UnicodeString::fromUTF8(s); }
static std::string utf8(const icu::UnicodeString &s)
{
    std::string out;
    s.toUTF8String(out);
    return out;
}
static bool ascii(const std::string &s)
{
    return std::all_of(s.begin(), s.end(), [](unsigned char c) { return c < 128; });
}
static std::string fold(const std::string &s)
{
    if (ascii(s))
    {
        auto result = s;
        for (auto &c : result)
            if (c >= 'A' && c <= 'Z')
                c += 'a' - 'A';
        return result;
    }
    auto u = unicode(s);
    u.foldCase();
    return utf8(u);
}
static size_t chars(const std::string &s) { return ascii(s) ? s.size() : unicode(s).countChar32(); }
static bool alnum(UChar32 c)
{
    if (c < 128)
        return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9');
    return (U_MASK(u_charType(c)) & (U_GC_L_MASK | U_GC_N_MASK)) != 0;
}
static Words tokens(const std::string &s)
{
    // Fold once for the whole field. ASCII needs no ICU conversion; mixed text
    // keeps full Unicode case folding and scans the resulting valid UTF-8.
    const auto text = fold(s);
    Words out;
    int32_t start = 0;
    for (int32_t i = 0; i < static_cast<int32_t>(text.size());)
    {
        const auto position = i;
        UChar32 c;
        U8_NEXT(text.data(), i, static_cast<int32_t>(text.size()), c);
        if (!alnum(c))
        {
            if (start < position)
                out.emplace_back(text, start, position - start);
            start = i;
        }
    }
    if (static_cast<size_t>(start) < text.size())
        out.emplace_back(text, start);
    return out;
}
static Terms unique(const Words &w) { return {w.begin(), w.end()}; }
static double coverage(const Terms &q, const Terms &text)
{
    size_t n = 0;
    for (auto &t : q)
        n += text.count(t);
    return double(n) / std::max(q.size(), size_t{1});
}
static std::string decodePercentEscapes(const std::string &s)
{
    std::string out;
    auto hex = [](char c) -> int
    {
        if (c >= '0' && c <= '9')
            return c - '0';
        if (c >= 'a' && c <= 'f')
            return c - 'a' + 10;
        if (c >= 'A' && c <= 'F')
            return c - 'A' + 10;
        return -1;
    };
    for (size_t i = 0; i < s.size(); ++i)
    {
        if (s[i] == '%' && i + 2 < s.size() && hex(s[i + 1]) >= 0 && hex(s[i + 2]) >= 0)
        {
            out += char(hex(s[i + 1]) * 16 + hex(s[i + 2]));
            i += 2;
        }
        else
            out += s[i];
    }
    return utf8(unicode(out));
}
static Words lines(const std::string &text)
{
    Words out;
    int32_t start = 0;
    for (int32_t i = 0; i < static_cast<int32_t>(text.size());)
    {
        const auto position = i;
        UChar32 c;
        U8_NEXT(text.data(), i, static_cast<int32_t>(text.size()), c);
        if (c == 10 || c == 13 || c == 11 || c == 12 || c == 0x1c || c == 0x1d || c == 0x1e ||
            c == 0x85 || c == 0x2028 || c == 0x2029)
        {
            out.emplace_back(text, start, position - start);
            if (c == 13 && static_cast<size_t>(i) < text.size() && text[i] == '\n')
                ++i;
            start = i;
        }
    }
    if (static_cast<size_t>(start) < text.size())
        out.emplace_back(text, start);
    return out;
}
// Keep line tokens: deduplication and body statistics consume the same tokenization.
// Character counts retain original punctuation/spacing plus the inserted newlines.
struct VisibleText
{
    Words words;
    size_t characters = 0;
};

static VisibleText visibleText(const Page &item)
{
    const auto &d = item.document;
    std::vector<const std::string *> parts;
    if (d.has_explicit_title)
        parts.push_back(&item.title);
    parts.insert(parts.end(), {&d.headings, &d.body, &d.link_text});
    std::set<Words> seen;
    VisibleText result;
    bool first = true;
    for (const auto *part : parts)
        for (const auto &line : lines(*part))
        {
            auto words = tokens(line);
            if (!words.empty() && seen.insert(words).second)
            {
                result.characters += chars(line) + (first ? 0 : 1);
                first = false;
                result.words.insert(result.words.end(), std::make_move_iterator(words.begin()),
                                    std::make_move_iterator(words.end()));
            }
        }
    return result;
}

template <FeaturePrefix Prefix>
static void extractFieldFeatures(Values &values, const Words &words, size_t characters,
                                 const Words &query_words, const Terms &query_terms)
{
    // Tokens outlive this table; views avoid copying every distinct body word.
    std::unordered_map<std::string_view, size_t> counts;
    counts.reserve(words.size());
    for (const auto &term : words)
        ++counts[term];
    size_t matched_terms = 0, matched_tokens = 0, first_match = words.size(), highest_frequency = 0;

    double minimum_tf = 1, maximum_tf = 0, tf_sum = 0;
    for (auto &[term, frequency] : counts)
        highest_frequency = std::max(highest_frequency, frequency);
    for (auto &term : query_terms)
    {
        auto frequency = counts.count(term) ? counts.at(term) : 0;
        matched_terms += frequency > 0;
        matched_tokens += frequency;
        double normalized_frequency = double(std::min(frequency, size_t{10})) / 10;
        minimum_tf = std::min(minimum_tf, normalized_frequency);
        maximum_tf = std::max(maximum_tf, normalized_frequency);
        tf_sum += normalized_frequency;
    }
    for (size_t i = 0; i < words.size(); ++i)
        if (query_terms.count(words[i]))
        {
            first_match = i;
            break;
        }
    double span = 0;
    if (query_terms.size() == 1 && matched_terms == 1)
        span = 1;
    else if (!query_terms.empty() && matched_terms == query_terms.size())
    {
        std::unordered_map<std::string_view, size_t> window;
        size_t left = 0, best = words.size() + 1;
        for (size_t right = 0; right < words.size(); ++right)
        {
            if (query_terms.count(words[right]))
                ++window[words[right]];
            while (window.size() == query_terms.size())
            {
                best = std::min(best, right - left + 1);
                const auto &term = words[left++];
                if (window.count(term) && --window[term] == 0)
                    window.erase(term);
            }
        }
        span = double(query_terms.size()) / best;
    }
    const double token_count = std::max(words.size(), size_t{1});
    values[featureIndex(Prefix, "coverage")] =
        double(matched_terms) / std::max(query_terms.size(), size_t{1});
    values[featureIndex(Prefix, "all_terms")] = !query_terms.empty() && matched_terms == query_terms.size();
    values[featureIndex(Prefix, "exact_phrase")] =
        !query_words.empty() &&
        std::search(words.begin(), words.end(), query_words.begin(), query_words.end()) != words.end();
    values[featureIndex(Prefix, "tf_min")] = query_terms.empty() ? 0 : minimum_tf;
    values[featureIndex(Prefix, "tf_max")] = maximum_tf;
    values[featureIndex(Prefix, "tf_mean")] = tf_sum / std::max(query_terms.size(), size_t{1});
    values[featureIndex(Prefix, "matched_fraction")] = matched_tokens / token_count;
    values[featureIndex(Prefix, "unique_fraction")] = counts.size() / token_count;
    values[featureIndex(Prefix, "most_common_fraction")] = highest_frequency / token_count;
    values[featureIndex(Prefix, "first_match")] = first_match < words.size() ? 1. / (1 + first_match) : 0;
    values[featureIndex(Prefix, "best_span")] = span;
    values[featureIndex(Prefix, "log_chars")] = std::log1p(characters);
    values[featureIndex(Prefix, "log_tokens")] = std::log1p(words.size());
    values[featureIndex(Prefix, "query_precision")] =
        double(matched_terms) / std::max(counts.size(), size_t{1});
}
template <FeaturePrefix Prefix>
static void extractFieldFeatures(Values &values, const std::string &text, const Words &query_words,
                                 const Terms &query_terms)
{
    extractFieldFeatures<Prefix>(values, tokens(text), chars(text), query_words, query_terms);
}

static double queryCharacterFraction(const std::string &source, const Words &query, const std::string &language,
                       unsigned version)
{
    auto text = unicode(fold(source));
    std::vector<bool> marked(text.length());
    size_t numerator = 0, denominator = 0;
    for (auto &term : unique(query))
        if (chars(term) > 2 && !stopWord(term, language, version))
        {
            auto needle = unicode(term);
            int32_t start = 0, pos;
            while ((pos = text.indexOf(needle, start)) >= 0)
            {
                for (int32_t i = pos; i < pos + needle.length(); ++i)
                    marked[i] = true;
                start = pos + 1;
            }
        }
    for (int32_t i = 0; i < text.length();)
    {
        auto c = text.char32At(i);
        if (alnum(c))
        {
            ++denominator;
            numerator += marked[i];
        }
        i += U16_LENGTH(c);
    }
    return double(numerator) / std::max(denominator, size_t{1});
}
static Values extractPageFeatures(const std::string &query, const Words &query_words,
                                  const Terms &query_terms, const Page &item, double maximum_bm25_score,
                                  double maximum_hilltop_score, double bm25_first_to_second_gap,
                                  double bm25_first_to_tail_gap, unsigned version)
{
    Values values{};
    const auto &document = item.document;
    const tlgs::Url url(item.url, false);
    const tlgs::Url site(item.site, false);
    auto path = decodePercentEscapes(url.path()), root = decodePercentEscapes(site.path());
    while (!root.empty() && root.back() == '/')
        root.pop_back();
    auto relative = path;
    if (!root.empty() && (path == root || path.starts_with(root + "/")))
        relative = path.substr(root.size());
    auto path_parts = drogon::utils::splitString(relative, "/", false);
    std::string slug = path_parts.empty() ? "" : path_parts.back();
    for (auto ext : {".gmi", ".gemini", ".txt", ".md", ".html", ".htm"})
        if (fold(slug).ends_with(ext))
        {
            slug.resize(slug.size() - std::string(ext).size());
            break;
        }
    auto body = visibleText(item);
    extractFieldFeatures<"title">(values, item.title, query_words, query_terms);
    extractFieldFeatures<"headings">(values, document.headings, query_words, query_terms);
    extractFieldFeatures<"body">(values, body.words, body.characters, query_words, query_terms);
    extractFieldFeatures<"link_text">(values, document.link_text, query_words, query_terms);
    extractFieldFeatures<"url">(values, decodePercentEscapes(url.authority() + url.path()), query_words,
                                query_terms);
    values[featureIndex("query_terms")] = query_terms.size();
    values[featureIndex("query_log_chars")] = std::log1p(chars(query));
    values[featureIndex("has_explicit_title")] = document.has_explicit_title;
    values[featureIndex("logical_path_depth")] = double(std::min(path_parts.size(), size_t{12})) / 12;
    values[featureIndex("logical_root")] =
        path_parts.empty() || (path_parts.size() == 1 &&
                               (fold(path_parts[0]) == "index.gmi" || fold(path_parts[0]) == "index.gemini" ||
                                fold(path_parts[0]) == "index.html"));
    Terms meaningful;
    for (auto &t : query_words)
        if (chars(t) > 2 && !stopWord(t, document.language, version))
            meaningful.insert(t);
    auto slug_words = tokens(slug);
    auto slug_terms = unique(slug_words);
    values[featureIndex("slug_query_coverage")] = coverage(meaningful, slug_terms);
    size_t overlap = 0;
    for (auto &t : meaningful)
        overlap += slug_terms.count(t);
    values[featureIndex("slug_precision")] = double(overlap) / std::max(slug_terms.size(), size_t{1});
    values[featureIndex("slug_repetition")] =
        1. - double(slug_terms.size()) / std::max(slug_words.size(), size_t{1});
    values[featureIndex("slug_long_query_present")] = !meaningful.empty();
    const auto &truncated = document.truncated;
    values[featureIndex("body_truncated")] =
        truncated.body || truncated.title || truncated.headings || truncated.link_text;
    values[featureIndex("size_log")] = std::log1p(std::max(item.size, int64_t{0}));
    values[featureIndex("outgoing_log")] = std::log1p(document.external_link_count);
    values[featureIndex("internal_log")] = std::log1p(document.internal_link_count);
    auto signal = [&]<FeaturePrefix Prefix>(const RetrievalScore *score, double maximum)
    {
        values[featureIndex(Prefix, "present")] = score != nullptr;
        values[featureIndex(Prefix, "log_score")] = score ? std::log1p(std::max(score->score, 0.)) : NAN;
        values[featureIndex(Prefix, "relative")] = score && maximum > 0 ? score->score / maximum : NAN;
        values[featureIndex(Prefix, "rr")] = score ? 1. / score->rank : NAN;
    };
    const auto &retrieval = item.retrieval;
    signal.operator()<"bm25">(retrieval.bm25 ? &*retrieval.bm25 : nullptr, maximum_bm25_score);
    signal.operator()<"hilltop">(retrieval.hilltop ? &*retrieval.hilltop : nullptr, maximum_hilltop_score);
    values[featureIndex("hilltop_sites_log")] =
        retrieval.hilltop ? std::log1p(retrieval.hilltop->independent_sites) : NAN;
    auto host_terms = unique(tokens(decodePercentEscapes(site.host())));
    auto site_path_parts = drogon::utils::splitString(decodePercentEscapes(site.path()), "/", false);
    std::string root_name = site_path_parts.empty() ? "" : site_path_parts.back();
    while (root_name.starts_with("~"))
        root_name.erase(0, 1);
    auto root_terms = site_path_parts.empty() ? host_terms : unique(tokens(root_name));
    values[featureIndex("ctx_hostname_coverage")] = coverage(query_terms, host_terms);
    values[featureIndex("ctx_root_name_coverage")] = coverage(query_terms, root_terms);
    values[featureIndex("ctx_root_name_exact")] = !query_terms.empty() && query_terms == root_terms;
    values[featureIndex("ctx_hostname_at_root")] =
        values[featureIndex("ctx_hostname_coverage")] * values[featureIndex("logical_root")];
    values[featureIndex("ctx_root_name_at_root")] =
        values[featureIndex("ctx_root_name_coverage")] * values[featureIndex("logical_root")];
    values[featureIndex("ctx_root_exact_at_root")] =
        values[featureIndex("ctx_root_name_exact")] * values[featureIndex("logical_root")];
    values[featureIndex("ctx_bm25_gap_12")] = bm25_first_to_second_gap;
    values[featureIndex("ctx_bm25_gap_1k")] = bm25_first_to_tail_gap;
    values[featureIndex("ctx_gap12_bm25_rr")] = bm25_first_to_second_gap * values[featureIndex("bm25_rr")];
    values[featureIndex("ctx_gap1k_bm25_rr")] = bm25_first_to_tail_gap * values[featureIndex("bm25_rr")];
    values[featureIndex("ctx_gap12_title_coverage")] =
        bm25_first_to_second_gap * values[featureIndex("title_coverage")];
    values[featureIndex("ctx_gap1k_at_root")] = bm25_first_to_tail_gap * values[featureIndex("logical_root")];
    values[featureIndex("eng_title_body_coverage")] =
        values[featureIndex("title_coverage")] - values[featureIndex("body_coverage")];
    values[featureIndex("eng_headings_body_coverage")] =
        values[featureIndex("headings_coverage")] - values[featureIndex("body_coverage")];
    values[featureIndex("eng_prominent_coverage")] =
        std::max(values[featureIndex("title_coverage")], values[featureIndex("headings_coverage")]);
    values[featureIndex("eng_prominent_phrase")] =
        std::max(values[featureIndex("title_exact_phrase")], values[featureIndex("headings_exact_phrase")]);
    auto hostname = fold(url.host());
    while (hostname.ends_with('.'))
        hostname.pop_back();
    if (hostname.starts_with("gemini."))
        hostname.erase(0, 7);
    values[featureIndex("url_domain_fraction")] = queryCharacterFraction(hostname, query_words, document.language, version);
    values[featureIndex("url_leftmost_fraction")] =
        queryCharacterFraction(hostname.substr(0, hostname.find('.')), query_words, document.language, version);
    values[featureIndex("url_path_fraction")] = queryCharacterFraction(path, query_words, document.language, version);
    return values;
}
std::vector<float> features(const std::string &query, const std::vector<Page> &items,
                            const std::vector<RetrievalSignals> &retrieval_context, unsigned version)
{
    if (version != 1 && version != 2)
        throw std::invalid_argument("Unsupported feature version");
    const auto query_words = tokens(query);
    const auto query_terms = unique(query_words);
    double maximum_bm25_score = 0, maximum_hilltop_score = 0;
    std::vector<std::pair<size_t, double>> ranked;
    auto add_context = [&](const RetrievalSignals &signals)
    {
        if (signals.bm25)
        {
            maximum_bm25_score = std::max(maximum_bm25_score, signals.bm25->score);
            ranked.emplace_back(signals.bm25->rank, signals.bm25->score);
        }
        if (signals.hilltop)
            maximum_hilltop_score = std::max(maximum_hilltop_score, signals.hilltop->score);
    };
    if (retrieval_context.empty())
        for (const auto &item : items)
            add_context(item.retrieval);
    else
        for (const auto &signals : retrieval_context)
            add_context(signals);
    std::sort(ranked.begin(), ranked.end());
    // Relative score drops from the first BM25 hit to the second and to the
    // tenth (or last available) hit. NaN means fewer than two hits.
    double bm25_first_to_second_gap = NAN;
    double bm25_first_to_tail_gap = NAN;
    if (ranked.size() >= 2)
    {
        const double first_bm25_score = ranked.front().second;
        const double score_scale = std::max(std::abs(first_bm25_score), 1e-9);
        const size_t tail_index = std::min(ranked.size(), size_t{10}) - 1;
        bm25_first_to_second_gap = std::clamp((first_bm25_score - ranked[1].second) / score_scale, 0., 1.);
        bm25_first_to_tail_gap =
            std::clamp((first_bm25_score - ranked[tail_index].second) / score_scale, 0., 1.);
    }
    std::vector<float> result;
    result.reserve(items.size() * feature_names.size());
    for (auto &item : items)
    {
        auto values = extractPageFeatures(query, query_words, query_terms, item, maximum_bm25_score,
                                          maximum_hilltop_score, bm25_first_to_second_gap,
                                          bm25_first_to_tail_gap, version);
        result.insert(result.end(), values.begin(), values.end());
    }
    return result;
}
template <class Text, class Visitor> static void visitContextTerms(Text &&text, const Visitor &visitor)
{
    if (ascii(text))
    {
        std::string lower = std::forward<Text>(text);
        const std::string_view view(lower);
        size_t start = 0;
        for (size_t i = 0; i < lower.size(); ++i)
        {
            auto &c = lower[i];
            if (c >= 'A' && c <= 'Z')
                c += 'a' - 'A';
            if (!((c >= 'a' && c <= 'z') || (c >= '0' && c <= '9')))
            {
                if (i > start)
                    visitor(view.substr(start, i - start));
                start = i + 1;
            }
        }
        if (start < lower.size())
            visitor(view.substr(start));
        return;
    }
    auto u = unicode(text);
    u.toLower(icu::Locale::getRoot());
    const auto lower = utf8(u);
    const std::string_view view(lower);
    int32_t start = 0;
    for (int32_t i = 0; i < static_cast<int32_t>(lower.size());)
    {
        const auto at = i;
        UChar32 c;
        U8_NEXT(lower.data(), i, static_cast<int32_t>(lower.size()), c);
        if (!alnum(c))
        {
            if (at > start)
                visitor(view.substr(start, at - start));
            start = i;
        }
    }
    if (start < static_cast<int32_t>(lower.size()))
        visitor(view.substr(start));
}

void visit_context_terms(std::string text, const std::function<void(std::string_view)> &visitor)
{
    visitContextTerms(std::move(text), visitor);
}

std::vector<std::string> context_terms(const std::string &text)
{
    Words result;
    visitContextTerms(text, [&](std::string_view term) { result.emplace_back(term); });
    return result;
}

std::vector<std::string> context_url_terms(const std::string &text)
{
    const Url url(text, false);
    return context_terms(url.authority() + " " + decodePercentEscapes(url.path()));
}

enum TextField : size_t
{
    TitleField,
    HeadingField,
    BodyField,
    OutgoingLinkField,
    UrlField,
    IncomingLinkField,
    TextFieldCount
};

struct TokenizedLine
{
    TextField field;
    Words words;
};

static Words contentQueryTerms(const Words &words)
{
    Words content;
    for (const auto &word : words)
        if (!stop.count(word))
            content.push_back(word);
    return content.empty() ? words : content;
}

struct ContextQuery
{
    Words phrase_words;
    Terms content_terms;
    Words anchor_words;
    Terms anchor_unique_terms;

    // Context scores use lowercase words; link-overlap features use case folding.
    explicit ContextQuery(const std::string &query)
        : phrase_words(context_terms(query)), anchor_words(contentQueryTerms(tokens(query))),
          anchor_unique_terms(anchor_words.begin(), anchor_words.end())
    {
        const auto content = contentQueryTerms(phrase_words);
        content_terms.insert(content.begin(), content.end());
    }
};

struct QueryTermCounts
{
    std::array<std::unordered_map<std::string, size_t>, TextFieldCount> term_counts;
    std::array<size_t, TextFieldCount> token_counts{};
    std::unordered_map<std::string, size_t> first_positions;

    QueryTermCounts(const std::vector<TokenizedLine> &text_lines, const Terms &query_terms)
    {
        size_t position = 1;
        for (const auto &line : text_lines)
        {
            token_counts[line.field] += line.words.size();
            for (size_t i = 0; i < line.words.size(); ++i)
            {
                // Counts and first positions are only queried for search terms.
                if (query_terms.contains(line.words[i]))
                {
                    ++term_counts[line.field][line.words[i]];
                    first_positions.try_emplace(line.words[i], position + i);
                }
            }
            position += line.words.size() + 2;
        }
    }

    size_t count(size_t field, const std::string &term) const
    {
        const auto found = term_counts[field].find(term);
        return found == term_counts[field].end() ? 0 : found->second;
    }

    size_t matchedTokenCount(TextField field, const Terms &terms) const
    {
        size_t total = 0;
        for (const auto &term : terms)
            total += count(field, term);
        return total;
    }
};

struct ContextScores
{
    double bm25 = 0;
    double title_url = 0;
    double phrase = 0;
    double proximity = 0;
    double first_match = 0;
    double coverage = 0;
    double passes_all_terms = 0;
    double total = 0;
};

struct ContextScoreField
{
    std::string_view name;
    double ContextScores::*member;
};
// Preserve model feature names while keeping the score fields descriptive.
static constexpr std::array<ContextScoreField, 8> context_score_fields = {
    {ContextScoreField{"bm25", &ContextScores::bm25},
     {"flags", &ContextScores::title_url},
     {"phrase", &ContextScores::phrase},
     {"proximity", &ContextScores::proximity},
     {"first", &ContextScores::first_match},
     {"coverage", &ContextScores::coverage},
     {"passes_all_terms", &ContextScores::passes_all_terms},
     {"total", &ContextScores::total}}};

struct TermScores
{
    double bm25 = 0;
    double title_url = 0;
    size_t matched_terms = 0;
    size_t latest_first_match = 1;
};

static TermScores scoreQueryTerms(const ContextQuery &query, const QueryTermCounts &counts, const Page &page,
                                  const CorpusStatistics &stats)
{
    constexpr std::array<double, TextFieldCount> weights = {2.5, 1.25, 1., .2, .5, 1.5};
    const Url url(page.url, false);
    const auto domain = unique(context_terms(url.authority()));
    const auto path = unique(context_terms(decodePercentEscapes(url.path())));
    const size_t document_bytes =
        std::max<int64_t>(1, page.size ? page.size : static_cast<int64_t>(page.document.body.size()));
    TermScores result;
    for (const auto &term : query.content_terms)
    {
        double frequency = 0;
        for (size_t field = 0; field < TextFieldCount; ++field)
            frequency += weights[field] * counts.count(field, term);
        if (frequency > 0)
        {
            ++result.matched_terms;
            result.latest_first_match = std::max(result.latest_first_match, counts.first_positions.at(term));
        }
        const auto found = stats.document_frequency.find(term);
        const double document_frequency =
            found == stats.document_frequency.end() ? 0 : std::min(found->second, stats.documents);
        const double idf =
            std::log1p((stats.documents - document_frequency + .5) / (document_frequency + .5));
        result.bm25 += idf * (frequency * 2.2) / (frequency + 1.2 * (.5 + .5 * document_bytes / 5000.));
        const double url_weight = domain.contains(term) ? 3. : (path.contains(term) ? 1. : 0.);
        const double title_weight = counts.count(TitleField, term) ? 1.5 : 0.;
        const double title_url_weight = url_weight + title_weight;
        result.title_url += .5 * idf * (title_url_weight * 2.2) / (title_url_weight + 1.2);
    }
    const double normalization = std::sqrt(result.matched_terms + 1.);
    result.bm25 /= normalization;
    result.title_url /= normalization;
    return result;
}

struct PhraseMatches
{
    double score = 0;
    std::array<bool, TextFieldCount> matched_fields{};
};

static PhraseMatches scoreQueryPhrase(const Words &query, const std::vector<TokenizedLine> &text_lines)
{
    constexpr std::array<double, TextFieldCount> weights = {3., 1.5, 1., .2, .75, 2.};
    constexpr std::array<double, TextFieldCount> repeat_exponents = {1., .5, .5, .3, 1., 1.};
    std::array<size_t, TextFieldCount> hits{};
    size_t title_boundaries = 0;
    for (const auto &line : text_lines)
        for (size_t i = 0; i + query.size() <= line.words.size(); ++i)
            if (std::equal(query.begin(), query.end(), line.words.begin() + i))
            {
                ++hits[line.field];
                if (line.field == TitleField && (i == 0 || i + query.size() == line.words.size()))
                    ++title_boundaries;
            }
    PhraseMatches result;
    for (size_t field = 0; field < TextFieldCount; ++field)
        if (hits[field])
        {
            result.score += weights[field] * query.size() *
                            (1 + std::log1p(std::pow(hits[field], repeat_exponents[field])));
            result.matched_fields[field] = true;
        }
    result.score += 1.5 * title_boundaries;
    return result;
}

static PhraseMatches scoreSingleQueryWord(const std::string &term,
                                          const std::vector<TokenizedLine> &text_lines)
{
    PhraseMatches result;
    size_t exact_headings = 0, boundary_headings = 0, exact_links = 0, partial_links = 0;
    for (const auto &line : text_lines)
    {
        const auto &words = line.words;
        if (std::find(words.begin(), words.end(), term) == words.end())
            continue;
        const bool boundary = words.front() == term || words.back() == term;
        switch (line.field)
        {
        case TitleField:
            result.score += words.size() == 1 ? 4. : (boundary ? 2.5 : 1.) / std::sqrt(words.size());
            result.matched_fields[TitleField] = true;
            break;
        case HeadingField:
            exact_headings += words.size() == 1;
            boundary_headings += boundary;
            result.matched_fields[HeadingField] = true;
            break;
        case IncomingLinkField:
            exact_links += words.size() == 1;
            partial_links += words.size() != 1;
            result.matched_fields[IncomingLinkField] = true;
            break;
        default:
            break;
        }
    }
    result.score += .75 * std::sqrt(exact_headings) + .75 * std::sqrt(boundary_headings) + 1.5 * exact_links +
                    .5 * std::sqrt(partial_links);
    return result;
}

static double scoreTermWindow(const Terms &terms, const Words &words)
{
    std::unordered_map<std::string, size_t> window;
    size_t left = 0;
    double best = 0;
    for (size_t right = 0; right < words.size(); ++right)
    {
        if (terms.count(words[right]))
            ++window[words[right]];
        while (window.size() == terms.size())
        {
            const auto width = right - left + 1;
            if (width < terms.size() + 8)
                best = std::max(best, 2 / (.1 + std::sqrt(std::max<size_t>(width - 1, 1))));
            const auto found = window.find(words[left++]);
            if (found != window.end() && !--found->second)
                window.erase(found);
        }
    }
    return best;
}

static double scoreContextProximity(const Terms &terms, const std::vector<TokenizedLine> &text_lines,
                                    const QueryTermCounts &counts, const PhraseMatches &phrase_matches,
                                    size_t matched_terms)
{
    double proximity = 0;
    if (terms.size() > 2)
        for (const auto &line : text_lines)
            proximity = std::max(proximity, scoreTermWindow(terms, line.words));
    if (!phrase_matches.matched_fields[TitleField] && matched_terms >= 2 &&
        counts.matchedTokenCount(TitleField, terms) == matched_terms)
        proximity += matched_terms * (2.5 + 2. / std::max<size_t>(1, counts.token_counts[TitleField]));
    if (counts.token_counts[HeadingField] < 64 && !phrase_matches.matched_fields[HeadingField] &&
        matched_terms && counts.matchedTokenCount(HeadingField, terms) == matched_terms)
        proximity += matched_terms;
    return .5 * proximity;
}

static ContextScores scoreContextText(const ContextQuery &query, const std::vector<TokenizedLine> &text_lines,
                                      const Page &page, const CorpusStatistics &stats)
{
    const QueryTermCounts counts(text_lines, query.content_terms);
    const auto term_scores = scoreQueryTerms(query, counts, page, stats);
    PhraseMatches phrase_matches;
    if (query.phrase_words.size() == 1)
        phrase_matches = scoreSingleQueryWord(query.phrase_words.front(), text_lines);
    else if (query.phrase_words.size() > 1)
        phrase_matches = scoreQueryPhrase(query.phrase_words, text_lines);
    ContextScores result;
    result.bm25 = term_scores.bm25;
    result.title_url = term_scores.title_url;
    result.phrase = phrase_matches.score;
    result.proximity = scoreContextProximity(query.content_terms, text_lines, counts, phrase_matches,
                                             term_scores.matched_terms);
    result.first_match = term_scores.matched_terms ? 2.5 / std::sqrt(term_scores.latest_first_match) : 0.;
    result.coverage = double(term_scores.matched_terms) / std::max<size_t>(1, query.content_terms.size());
    result.passes_all_terms =
        !query.content_terms.empty() && term_scores.matched_terms == query.content_terms.size();
    result.total = result.bm25 + result.title_url + result.phrase + result.proximity + result.first_match;
    return result;
}

static void appendTokenizedLines(std::vector<TokenizedLine> &text_lines, TextField field,
                                 const std::string &text)
{
    for (const auto &line : lines(text))
    {
        auto words = context_terms(line);
        if (!words.empty())
            text_lines.push_back({field, std::move(words)});
    }
}

static std::vector<TokenizedLine> tokenizePageText(const Page &page)
{
    std::vector<TokenizedLine> text_lines;
    const auto title = context_terms(page.title);
    if (page.document.has_explicit_title)
        appendTokenizedLines(text_lines, TitleField, page.title);
    for (const auto &line : lines(page.document.headings))
    {
        auto words = context_terms(line);
        if (!words.empty() && (!page.document.has_explicit_title || words != title))
            text_lines.push_back({HeadingField, std::move(words)});
    }
    appendTokenizedLines(text_lines, BodyField, page.document.body);
    appendTokenizedLines(text_lines, OutgoingLinkField, page.document.link_text);
    const Url url(page.url, false);
    appendTokenizedLines(text_lines, UrlField, url.authority() + " " + decodePercentEscapes(url.path()));
    return text_lines;
}

struct IncomingLinkText
{
    std::string text;
    size_t max_independent_sites = 0;
};

static IncomingLinkText appendIncomingLinks(std::vector<TokenizedLine> &text_lines,
                                            const std::vector<IncomingContext> &incoming)
{
    IncomingLinkText result;
    for (const auto &context : incoming)
    {
        if (!result.text.empty())
            result.text += '\n';
        result.text += context.text;
        result.max_independent_sites = std::max(result.max_independent_sites, context.independent_sites);
        const auto repeats =
            std::clamp<size_t>(static_cast<size_t>(std::sqrt(context.independent_sites)), 1, 12);
        std::vector<TokenizedLine> link_lines;
        appendTokenizedLines(link_lines, IncomingLinkField, context.text);
        for (size_t i = 0; i < repeats; ++i)
            text_lines.insert(text_lines.end(), link_lines.begin(), link_lines.end());
    }
    return result;
}

using ContextFeatureValues = std::array<float, context_feature_names.size()>;
static consteval size_t contextFeatureIndex(std::string_view name)
{
    for (size_t i = 0; i < context_feature_names.size(); ++i)
        if (context_feature_names[i] == name)
            return i;
    throw "Unknown incoming150 feature";
}

static consteval size_t contextFeatureIndex(std::string_view prefix, std::string_view suffix)
{
    for (size_t i = 0; i < context_feature_names.size(); ++i)
    {
        const auto name = context_feature_names[i];
        if (name.starts_with(prefix) && name.substr(prefix.size()).starts_with("_") &&
            name.substr(prefix.size() + 1) == suffix)
            return i;
    }
    throw "Unknown incoming150 feature";
}

static constexpr auto base_feature_columns = []() consteval
{
    std::array<size_t, feature_names.size()> columns{};
    for (size_t i = 0; i < columns.size(); ++i)
        columns[i] = contextFeatureIndex(feature_names[i]);
    return columns;
}();

static constexpr auto incoming_link_columns = []() consteval
{
    constexpr auto count = std::count_if(feature_names.begin(), feature_names.end(),
                                         [](auto name) { return name.starts_with("link_text_"); });
    std::array<std::pair<size_t, size_t>, count> columns{};
    size_t next = 0;
    for (size_t i = 0; i < feature_names.size(); ++i)
        if (feature_names[i].starts_with("link_text_"))
            columns[next++] = {i, contextFeatureIndex("m_anchor", feature_names[i].substr(10))};
    return columns;
}();

template <FeaturePrefix Prefix, size_t Count = context_score_fields.size()>
static void storeContextScores(ContextFeatureValues &values, const ContextScores &components)
{
    static constexpr auto columns = []() consteval
    {
        std::array<size_t, Count> result{};
        for (size_t i = 0; i < Count; ++i)
            result[i] = contextFeatureIndex(Prefix, context_score_fields[i].name);
        return result;
    }();
    for (size_t i = 0; i < Count; ++i)
        values[columns[i]] = components.*context_score_fields[i].member;
}

static void storeIncomingLinkFeatures(ContextFeatureValues &values, const ContextQuery &query,
                                      const IncomingLinkText &incoming_text, size_t context_count)
{
    Values anchor{};
    extractFieldFeatures<"link_text">(anchor, incoming_text.text, query.anchor_words, query.anchor_unique_terms);
    for (const auto &[source, destination] : incoming_link_columns)
        values[destination] = anchor[source];
    values[contextFeatureIndex("m_anchor_contexts_log")] = std::log1p(context_count);
    values[contextFeatureIndex("m_anchor_max_support_log")] = std::log1p(incoming_text.max_independent_sites);
}

static ContextFeatureValues extractContextFeatures(const ContextQuery &query, const Page &page,
                                                   const std::vector<IncomingContext> &incoming,
                                                   const CorpusStatistics &stats, std::span<const float> base)
{
    ContextFeatureValues values{};
    for (size_t i = 0; i < base.size(); ++i)
        values[base_feature_columns[i]] = base[i];
    auto text_lines = tokenizePageText(page);
    const auto page_scores = scoreContextText(query, text_lines, page, stats);
    const auto page_line_count = text_lines.size();
    const auto incoming_text = appendIncomingLinks(text_lines, incoming);
    const auto combined_scores =
        text_lines.size() == page_line_count ? page_scores : scoreContextText(query, text_lines, page, stats);
    ContextScores score_delta;
    for (const auto &field : context_score_fields)
        score_delta.*field.member = combined_scores.*field.member - page_scores.*field.member;
    storeContextScores<"m_local">(values, page_scores);
    storeContextScores<"m_incoming">(values, combined_scores);
    // The feature contract includes deltas for every component except total.
    storeContextScores<"m_delta", context_score_fields.size() - 1>(values, score_delta);
    storeIncomingLinkFeatures(values, query, incoming_text, incoming.size());
    return values;
}

std::vector<float> context_features(const std::string &query, const std::vector<Page> &items,
                                    const std::vector<std::vector<IncomingContext>> &incoming,
                                    const CorpusStatistics &stats,
                                    const std::vector<RetrievalSignals> &retrieval_context)
{
    if (incoming.size() != items.size() || !stats.documents)
        throw std::invalid_argument("Missing incoming150 context/statistics");
    const auto base = features(query, items, retrieval_context, 1);
    const ContextQuery context_query(query);
    std::vector<float> result;
    result.reserve(items.size() * context_feature_names.size());
    for (size_t row = 0; row < items.size(); ++row)
    {
        const auto base_row =
            std::span<const float>(base).subspan(row * feature_names.size(), feature_names.size());
        const auto values = extractContextFeatures(context_query, items[row], incoming[row], stats, base_row);
        result.insert(result.end(), values.begin(), values.end());
    }
    return result;
}
} // namespace tlgs::ranking
