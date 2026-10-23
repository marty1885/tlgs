#include "features.hpp"
#include <tlgsutils/url_parser.hpp>
#include <algorithm>
#include <cmath>
#include <limits>
#include <set>
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
static std::string unquote(const std::string &s)
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
struct Text
{
    Words words;
    size_t characters = 0;
};

static Text visible(const Page &item)
{
    const auto &d = item.document;
    std::vector<const std::string *> parts;
    if (d.has_explicit_title)
        parts.push_back(&item.title);
    parts.insert(parts.end(), {&d.headings, &d.body, &d.link_text});
    std::set<Words> seen;
    Text result;
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

template<FeaturePrefix Prefix>
static void field(Values &f, const Words &ts, size_t characters,
           const Words &query, const Terms &q)
{
    // Tokens outlive this table; views avoid copying every distinct body word.
    std::unordered_map<std::string_view, size_t> counts;
    counts.reserve(ts.size());
    for (const auto &t : ts)
        ++counts[t];
    size_t found = 0, total = 0, first = ts.size(), most = 0;

    double tmin = 1, tmax = 0, tsum = 0;
    for (auto &[t, n] : counts)
        most = std::max(most, n);
    for (auto &t : q)
    {
        auto n = counts.count(t) ? counts.at(t) : 0;
        found += n > 0;
        total += n;
        double tf = double(std::min(n, size_t{10})) / 10;
        tmin = std::min(tmin, tf);
        tmax = std::max(tmax, tf);
        tsum += tf;
    }
    for (size_t i = 0; i < ts.size(); ++i)
        if (q.count(ts[i]))
        {
            first = i;
            break;
        }
    double span = 0;
    if (!q.empty() && found == q.size())
    {
        std::unordered_map<std::string_view, size_t> window;
        size_t left = 0, best = ts.size() + 1;
        for (size_t right = 0; right < ts.size(); ++right)
        {
            if (q.count(ts[right]))
                ++window[ts[right]];
            while (window.size() == q.size())
            {
                best = std::min(best, right - left + 1);
                const auto &t = ts[left++];
                if (window.count(t) && --window[t] == 0)
                    window.erase(t);
            }
        }
        span = double(q.size()) / best;
    }
    const double n = std::max(ts.size(), size_t{1});
    f[featureIndex(Prefix, "coverage")] = double(found) / std::max(q.size(), size_t{1});
    f[featureIndex(Prefix, "all_terms")] = !q.empty() && found == q.size();
    f[featureIndex(Prefix, "exact_phrase")] = !query.empty() && std::search(ts.begin(), ts.end(), query.begin(),
                                                      query.end()) != ts.end();
    f[featureIndex(Prefix, "tf_min")] = q.empty() ? 0 : tmin;
    f[featureIndex(Prefix, "tf_max")] = tmax;
    f[featureIndex(Prefix, "tf_mean")] = tsum / std::max(q.size(), size_t{1});
    f[featureIndex(Prefix, "matched_fraction")] = total / n;
    f[featureIndex(Prefix, "unique_fraction")] = counts.size() / n;
    f[featureIndex(Prefix, "most_common_fraction")] = most / n;
    f[featureIndex(Prefix, "first_match")] = first < ts.size() ? 1. / (1 + first) : 0;
    f[featureIndex(Prefix, "best_span")] = span;
    f[featureIndex(Prefix, "log_chars")] = std::log1p(characters);
    f[featureIndex(Prefix, "log_tokens")] = std::log1p(ts.size());
    f[featureIndex(Prefix, "query_precision")] = double(found) / std::max(counts.size(), size_t{1});
}
template<FeaturePrefix Prefix>
static void field(Values &f, const std::string &text, const Words &query,
           const Terms &q)
{
    field<Prefix>(f, tokens(text), chars(text), query, q);
}

static double fraction(const std::string &source, const Words &query, const std::string& language, unsigned version)
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
static Values extract(const std::string &query, const Words &q, const Terms &qt,
               const Page &item, double maximum_bm25_score, double maximum_hilltop_score, double bm25_first_to_second_gap, double bm25_first_to_tail_gap, unsigned version)
{
    Values f{};
    const auto &doc = item.document;
    const tlgs::Url url(item.url, false);
    const tlgs::Url site(item.site, false);
    auto path = unquote(url.path()), root = unquote(site.path());
    while (!root.empty() && root.back() == '/')
        root.pop_back();
    auto relative = path;
    if (!root.empty() && (path == root || path.starts_with(root + "/")))
        relative = path.substr(root.size());
    auto parts = drogon::utils::splitString(relative, "/", false);
    std::string slug = parts.empty() ? "" : parts.back();
    for (auto ext : {".gmi", ".gemini", ".txt", ".md", ".html", ".htm"})
        if (fold(slug).ends_with(ext))
        {
            slug.resize(slug.size() - std::string(ext).size());
            break;
        }
    auto body = visible(item);
    field<"title">(f, item.title, q, qt);
    field<"headings">(f, doc.headings, q, qt);
    field<"body">(f, body.words, body.characters, q, qt);
    field<"link_text">(f, doc.link_text, q, qt);
    field<"url">(f, unquote(url.authority() + url.path()), q, qt);
    f[featureIndex("query_terms")] = qt.size();
    f[featureIndex("query_log_chars")] = std::log1p(chars(query));
    f[featureIndex("has_explicit_title")] = doc.has_explicit_title;
    f[featureIndex("logical_path_depth")] = double(std::min(parts.size(), size_t{12})) / 12;
    f[featureIndex("logical_root")] = parts.empty() || (parts.size() == 1 && (fold(parts[0]) == "index.gmi" ||
                                                                fold(parts[0]) == "index.gemini" ||
                                                                fold(parts[0]) == "index.html"));
    Terms meaningful;
    for (auto &t : q)
        if (chars(t) > 2 && !stopWord(t, doc.language, version))
            meaningful.insert(t);
    auto st = tokens(slug);
    auto slugterms = unique(st);
    f[featureIndex("slug_query_coverage")] = coverage(meaningful, slugterms);
    size_t overlap = 0;
    for (auto &t : meaningful)
        overlap += slugterms.count(t);
    f[featureIndex("slug_precision")] = double(overlap) / std::max(slugterms.size(), size_t{1});
    f[featureIndex("slug_repetition")] = 1. - double(slugterms.size()) / std::max(st.size(), size_t{1});
    f[featureIndex("slug_long_query_present")] = !meaningful.empty();
    const auto &truncated = doc.truncated;
    f[featureIndex("body_truncated")] = truncated.body || truncated.title || truncated.headings || truncated.link_text;
    f[featureIndex("size_log")] = std::log1p(std::max(item.size, int64_t{0}));
    f[featureIndex("outgoing_log")] = std::log1p(doc.external_link_count);
    f[featureIndex("internal_log")] = std::log1p(doc.internal_link_count);
    auto signal = [&]<FeaturePrefix Prefix>(const RetrievalScore *score, double maximum)
    {
        f[featureIndex(Prefix, "present")] = score != nullptr;
        f[featureIndex(Prefix, "log_score")] = score ? std::log1p(std::max(score->score, 0.)) : NAN;
        f[featureIndex(Prefix, "relative")] = score && maximum > 0 ? score->score / maximum : NAN;
        f[featureIndex(Prefix, "rr")] = score ? 1. / score->rank : NAN;
    };
    const auto &retrieval = item.retrieval;
    signal.operator()<"bm25">(retrieval.bm25 ? &*retrieval.bm25 : nullptr, maximum_bm25_score);
    signal.operator()<"hilltop">(retrieval.hilltop ? &*retrieval.hilltop : nullptr, maximum_hilltop_score);
    f[featureIndex("hilltop_sites_log")] = retrieval.hilltop ? std::log1p(retrieval.hilltop->independent_sites) : NAN;
    auto host = unique(tokens(unquote(site.host())));
    auto sp = drogon::utils::splitString(unquote(site.path()), "/", false);
    std::string last = sp.empty() ? "" : sp.back();
    while (last.starts_with("~"))
        last.erase(0, 1);
    auto rootterms = sp.empty() ? host : unique(tokens(last));
    f[featureIndex("ctx_hostname_coverage")] = coverage(qt, host);
    f[featureIndex("ctx_root_name_coverage")] = coverage(qt, rootterms);
    f[featureIndex("ctx_root_name_exact")] = !qt.empty() && qt == rootterms;
    f[featureIndex("ctx_hostname_at_root")] = f[featureIndex("ctx_hostname_coverage")] * f[featureIndex("logical_root")];
    f[featureIndex("ctx_root_name_at_root")] = f[featureIndex("ctx_root_name_coverage")] * f[featureIndex("logical_root")];
    f[featureIndex("ctx_root_exact_at_root")] = f[featureIndex("ctx_root_name_exact")] * f[featureIndex("logical_root")];
    f[featureIndex("ctx_bm25_gap_12")] = bm25_first_to_second_gap;
    f[featureIndex("ctx_bm25_gap_1k")] = bm25_first_to_tail_gap;
    f[featureIndex("ctx_gap12_bm25_rr")] = bm25_first_to_second_gap * f[featureIndex("bm25_rr")];
    f[featureIndex("ctx_gap1k_bm25_rr")] = bm25_first_to_tail_gap * f[featureIndex("bm25_rr")];
    f[featureIndex("ctx_gap12_title_coverage")] = bm25_first_to_second_gap * f[featureIndex("title_coverage")];
    f[featureIndex("ctx_gap1k_at_root")] = bm25_first_to_tail_gap * f[featureIndex("logical_root")];
    f[featureIndex("eng_title_body_coverage")] = f[featureIndex("title_coverage")] - f[featureIndex("body_coverage")];
    f[featureIndex("eng_headings_body_coverage")] = f[featureIndex("headings_coverage")] - f[featureIndex("body_coverage")];
    f[featureIndex("eng_prominent_coverage")] = std::max(f[featureIndex("title_coverage")], f[featureIndex("headings_coverage")]);
    f[featureIndex("eng_prominent_phrase")] = std::max(f[featureIndex("title_exact_phrase")], f[featureIndex("headings_exact_phrase")]);
    auto hostname = fold(url.host());
    while (hostname.ends_with('.'))
        hostname.pop_back();
    if (hostname.starts_with("gemini."))
        hostname.erase(0, 7);
    f[featureIndex("url_domain_fraction")] = fraction(hostname, q, doc.language, version);
    f[featureIndex("url_leftmost_fraction")] = fraction(hostname.substr(0, hostname.find('.')), q, doc.language, version);
    f[featureIndex("url_path_fraction")] = fraction(path, q, doc.language, version);
    return f;
}
std::vector<float> features(const std::string &query, const std::vector<Page> &items,
                            const std::vector<RetrievalSignals> &retrieval_context, unsigned version)
{
    if (version != 1 && version != 2)
        throw std::invalid_argument("Unsupported feature version");
    const auto q = tokens(query);
    const auto qt = unique(q);
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
        bm25_first_to_second_gap =
            std::clamp((first_bm25_score - ranked[1].second) / score_scale, 0., 1.);
        bm25_first_to_tail_gap =
            std::clamp((first_bm25_score - ranked[tail_index].second) / score_scale, 0., 1.);
    }
    std::vector<float> result;
    result.reserve(items.size() * feature_names.size());
    for (auto &item : items)
    {
        auto values = extract(query, q, qt, item, maximum_bm25_score, maximum_hilltop_score, bm25_first_to_second_gap, bm25_first_to_tail_gap, version);
        result.insert(result.end(), values.begin(), values.end());
    }
    return result;
}
} // namespace tlgs::ranking
