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
    return context_terms(url.authority() + " " + unquote(url.path()));
}

enum ContextField : size_t
{
    TitleField,
    HeadingField,
    BodyField,
    OutgoingField,
    AddressField,
    IncomingField,
    ContextFieldCount
};

struct ContextPart
{
    ContextField field;
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
    Words phrase;
    Terms terms;
    Words anchor_phrase;
    Terms anchor_terms;

    explicit ContextQuery(const std::string &query)
        : phrase(context_terms(query)), anchor_phrase(contentQueryTerms(tokens(query))),
          anchor_terms(anchor_phrase.begin(), anchor_phrase.end())
    {
        const auto content = contentQueryTerms(phrase);
        terms.insert(content.begin(), content.end());
    }
};

struct ContextCounts
{
    std::array<std::unordered_map<std::string, size_t>, ContextFieldCount> fields;
    std::array<size_t, ContextFieldCount> lengths{};
    std::unordered_map<std::string, size_t> first_positions;

    explicit ContextCounts(const std::vector<ContextPart> &parts)
    {
        size_t position = 1;
        for (const auto &part : parts)
        {
            lengths[part.field] += part.words.size();
            for (size_t i = 0; i < part.words.size(); ++i)
            {
                ++fields[part.field][part.words[i]];
                first_positions.try_emplace(part.words[i], position + i);
            }
            position += part.words.size() + 2;
        }
    }

    size_t count(size_t field, const std::string &term) const
    {
        const auto found = fields[field].find(term);
        return found == fields[field].end() ? 0 : found->second;
    }

    size_t observations(ContextField field, const Terms &terms) const
    {
        size_t total = 0;
        for (const auto &term : terms)
            total += count(field, term);
        return total;
    }
};

struct Components
{
    double bm25 = 0;
    double flags = 0;
    double phrase = 0;
    double proximity = 0;
    double first = 0;
    double coverage = 0;
    double passes_all_terms = 0;
    double total = 0;
};

struct ComponentField
{
    std::string_view name;
    double Components::*member;
};
static constexpr std::array<ComponentField, 8> component_fields = {
    {ComponentField{"bm25", &Components::bm25},
     {"flags", &Components::flags},
     {"phrase", &Components::phrase},
     {"proximity", &Components::proximity},
     {"first", &Components::first},
     {"coverage", &Components::coverage},
     {"passes_all_terms", &Components::passes_all_terms},
     {"total", &Components::total}}};

struct LexicalEvidence
{
    double bm25 = 0;
    double flags = 0;
    size_t matched_terms = 0;
    size_t latest_first_match = 1;
};

static LexicalEvidence scoreContextTerms(const ContextQuery &query, const ContextCounts &counts,
                                         const Page &page, const CorpusStatistics &stats)
{
    constexpr std::array<double, ContextFieldCount> weights = {2.5, 1.25, 1., .2, .5, 1.5};
    const Url url(page.url, false);
    const auto domain = unique(context_terms(url.authority()));
    const auto path = unique(context_terms(unquote(url.path())));
    const size_t size =
        std::max<int64_t>(1, page.size ? page.size : static_cast<int64_t>(page.document.body.size()));
    LexicalEvidence result;
    for (const auto &term : query.terms)
    {
        double frequency = 0;
        for (size_t field = 0; field < ContextFieldCount; ++field)
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
        result.bm25 += idf * (frequency * 2.2) / (frequency + 1.2 * (.5 + .5 * size / 5000.));
        const double flags = (domain.count(term) ? 3.
                              : path.count(term) ? 1.
                                                 : 0.) +
                             (counts.count(TitleField, term) ? 1.5 : 0.);
        result.flags += .5 * idf * (flags * 2.2) / (flags + 1.2);
    }
    const double normalization = std::sqrt(result.matched_terms + 1.);
    result.bm25 /= normalization;
    result.flags /= normalization;
    return result;
}

struct PhraseEvidence
{
    double score = 0;
    std::array<bool, ContextFieldCount> matched_fields{};
};

static PhraseEvidence scoreContextPhrase(const Words &query, const std::vector<ContextPart> &parts)
{
    constexpr std::array<double, ContextFieldCount> weights = {3., 1.5, 1., .2, .75, 2.};
    constexpr std::array<double, ContextFieldCount> attenuation = {1., .5, .5, .3, 1., 1.};
    std::array<size_t, ContextFieldCount> hits{};
    size_t title_boundaries = 0;
    for (const auto &part : parts)
        for (size_t i = 0; i + query.size() <= part.words.size(); ++i)
            if (std::equal(query.begin(), query.end(), part.words.begin() + i))
            {
                ++hits[part.field];
                if (part.field == TitleField && (i == 0 || i + query.size() == part.words.size()))
                    ++title_boundaries;
            }
    PhraseEvidence result;
    for (size_t field = 0; field < ContextFieldCount; ++field)
        if (hits[field])
        {
            result.score +=
                weights[field] * query.size() * (1 + std::log1p(std::pow(hits[field], attenuation[field])));
            result.matched_fields[field] = true;
        }
    result.score += 1.5 * title_boundaries;
    return result;
}

static PhraseEvidence scoreContextWord(const std::string &term, const std::vector<ContextPart> &parts)
{
    PhraseEvidence result;
    size_t exact_headings = 0, boundary_headings = 0, exact_links = 0, partial_links = 0;
    for (const auto &part : parts)
    {
        const auto &words = part.words;
        if (std::find(words.begin(), words.end(), term) == words.end())
            continue;
        const bool boundary = words.front() == term || words.back() == term;
        switch (part.field)
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
        case IncomingField:
            exact_links += words.size() == 1;
            partial_links += words.size() != 1;
            result.matched_fields[IncomingField] = true;
            break;
        default:
            break;
        }
    }
    result.score += .75 * std::sqrt(exact_headings) + .75 * std::sqrt(boundary_headings) + 1.5 * exact_links +
                    .5 * std::sqrt(partial_links);
    return result;
}

static double contextWindowProximity(const Terms &terms, const Words &words)
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

static double scoreContextProximity(const Terms &terms, const std::vector<ContextPart> &parts,
                                    const ContextCounts &counts, const PhraseEvidence &phrase,
                                    size_t matched_terms)
{
    double proximity = 0;
    if (terms.size() > 2)
        for (const auto &part : parts)
            proximity = std::max(proximity, contextWindowProximity(terms, part.words));
    if (!phrase.matched_fields[TitleField] && matched_terms >= 2 &&
        counts.observations(TitleField, terms) == matched_terms)
        proximity += matched_terms * (2.5 + 2. / std::max<size_t>(1, counts.lengths[TitleField]));
    if (counts.lengths[HeadingField] < 64 && !phrase.matched_fields[HeadingField] && matched_terms &&
        counts.observations(HeadingField, terms) == matched_terms)
        proximity += matched_terms;
    return .5 * proximity;
}

static Components contextComponents(const ContextQuery &query, const std::vector<ContextPart> &parts,
                                    const Page &page, const CorpusStatistics &stats)
{
    const ContextCounts counts(parts);
    const auto lexical = scoreContextTerms(query, counts, page, stats);
    PhraseEvidence phrase;
    if (query.phrase.size() == 1)
        phrase = scoreContextWord(query.phrase.front(), parts);
    else if (query.phrase.size() > 1)
        phrase = scoreContextPhrase(query.phrase, parts);
    Components result;
    result.bm25 = lexical.bm25;
    result.flags = lexical.flags;
    result.phrase = phrase.score;
    result.proximity = scoreContextProximity(query.terms, parts, counts, phrase, lexical.matched_terms);
    result.first = lexical.matched_terms ? 2.5 / std::sqrt(lexical.latest_first_match) : 0.;
    result.coverage = double(lexical.matched_terms) / std::max<size_t>(1, query.terms.size());
    result.passes_all_terms = !query.terms.empty() && lexical.matched_terms == query.terms.size();
    result.total = result.bm25 + result.flags + result.phrase + result.proximity + result.first;
    return result;
}

static void appendContextParts(std::vector<ContextPart> &parts, ContextField field, const std::string &text)
{
    for (const auto &line : lines(text))
    {
        auto words = context_terms(line);
        if (!words.empty())
            parts.push_back({field, std::move(words)});
    }
}

static std::vector<ContextPart> localContextParts(const Page &page)
{
    std::vector<ContextPart> parts;
    const auto title = context_terms(page.title);
    if (page.document.has_explicit_title)
        appendContextParts(parts, TitleField, page.title);
    for (const auto &line : lines(page.document.headings))
        if (!page.document.has_explicit_title || context_terms(line) != title)
            appendContextParts(parts, HeadingField, line);
    appendContextParts(parts, BodyField, page.document.body);
    appendContextParts(parts, OutgoingField, page.document.link_text);
    const Url url(page.url, false);
    appendContextParts(parts, AddressField, url.authority() + " " + unquote(url.path()));
    return parts;
}

struct IncomingEvidence
{
    std::string text;
    size_t maximum_support = 0;
};

static IncomingEvidence appendIncomingParts(std::vector<ContextPart> &parts,
                                            const std::vector<IncomingContext> &incoming)
{
    IncomingEvidence result;
    for (const auto &context : incoming)
    {
        if (!result.text.empty())
            result.text += '\n';
        result.text += context.text;
        result.maximum_support = std::max(result.maximum_support, context.independent_sites);
        const auto repeats =
            std::clamp<size_t>(static_cast<size_t>(std::sqrt(context.independent_sites)), 1, 12);
        for (size_t i = 0; i < repeats; ++i)
            appendContextParts(parts, IncomingField, context.text);
    }
    return result;
}

using ContextValues = std::array<float, context_feature_names.size()>;
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

static constexpr auto base_context_columns = []() consteval
{
    std::array<size_t, feature_names.size()> columns{};
    for (size_t i = 0; i < columns.size(); ++i)
        columns[i] = contextFeatureIndex(feature_names[i]);
    return columns;
}();

static constexpr auto anchor_context_columns = []() consteval
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

template <FeaturePrefix Prefix, size_t Count = component_fields.size()>
static void storeComponents(ContextValues &values, const Components &components)
{
    static constexpr auto columns = []() consteval
    {
        std::array<size_t, Count> result{};
        for (size_t i = 0; i < Count; ++i)
            result[i] = contextFeatureIndex(Prefix, component_fields[i].name);
        return result;
    }();
    for (size_t i = 0; i < Count; ++i)
        values[columns[i]] = components.*component_fields[i].member;
}

static void storeAnchorFeatures(ContextValues &values, const ContextQuery &query,
                                const IncomingEvidence &evidence, size_t contexts)
{
    Values anchor{};
    field<"link_text">(anchor, evidence.text, query.anchor_phrase, query.anchor_terms);
    for (const auto &[source, destination] : anchor_context_columns)
        values[destination] = anchor[source];
    values[contextFeatureIndex("m_anchor_contexts_log")] = std::log1p(contexts);
    values[contextFeatureIndex("m_anchor_max_support_log")] = std::log1p(evidence.maximum_support);
}

static ContextValues contextFeatureRow(const ContextQuery &query, const Page &page,
                                       const std::vector<IncomingContext> &incoming,
                                       const CorpusStatistics &stats, std::span<const float> base)
{
    ContextValues values{};
    for (size_t i = 0; i < base.size(); ++i)
        values[base_context_columns[i]] = base[i];
    auto parts = localContextParts(page);
    const auto local = contextComponents(query, parts, page, stats);
    const auto evidence = appendIncomingParts(parts, incoming);
    const auto combined = contextComponents(query, parts, page, stats);
    Components delta;
    for (const auto &field : component_fields)
        delta.*field.member = combined.*field.member - local.*field.member;
    storeComponents<"m_local">(values, local);
    storeComponents<"m_incoming">(values, combined);
    // The feature contract includes deltas for every component except total.
    storeComponents<"m_delta", component_fields.size() - 1>(values, delta);
    storeAnchorFeatures(values, query, evidence, incoming.size());
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
        const auto values = contextFeatureRow(context_query, items[row], incoming[row], stats, base_row);
        result.insert(result.end(), values.begin(), values.end());
    }
    return result;
}
} // namespace tlgs::ranking
