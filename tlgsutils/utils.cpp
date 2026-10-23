#include "utils.hpp"
#include <regex>
#include <filesystem>
#include <iostream>
#include <cctype>
#include <unordered_map>
#include <xxhash.h>
#include <unicode/utf8.h>
#include <drogon/utils/Utilities.h>

bool tlgs::constantTimeStringCompare(std::string_view lhs, std::string_view rhs)
{
    if(lhs.size() != rhs.size())
        return false;
    volatile unsigned char difference = 0;
    for(size_t i = 0; i < lhs.size(); ++i)
        difference = difference | static_cast<unsigned char>(lhs[i] ^ rhs[i]);
    return difference == 0;
}

bool tlgs::isValidUtf8(std::string_view text)
{
    size_t position = 0;
    while(position < text.size()) {
        UChar32 codepoint;
        U8_NEXT(text.data(), position, text.size(), codepoint);
        if(codepoint < 0)
            return false;
    }
    return true;
}

static std::string charToHex(char c)
{
    std::string result;
    char first, second;

    first = (c & 0xF0) / 16;
    first += first > 9 ? 'A' - 10 : '0';
    second = c & 0x0F;
    second += second > 9 ? 'A' - 10 : '0';

    result.append(1, first);
    result.append(1, second);

    return result;
}

std::string tlgs::highlightQuery(const std::string_view query)
{
    std::string result;
    const std::string_view whitespace = " \t\r\n\f\v";
    size_t position = 0;
    while(position < query.size()) {
        position = query.find_first_not_of(whitespace, position);
        if(position == std::string_view::npos)
            break;
        const auto start = position;
        bool quoted = false;
        while(position < query.size()) {
            const auto ch = query[position];
            if(ch == '"')
                quoted = !quoted;
            if(!quoted && whitespace.find(ch) != std::string_view::npos)
                break;
            ++position;
        }
        const auto term = query.substr(start, position - start);
        const bool is_or = term.size() == 2
            && (term[0] == 'o' || term[0] == 'O')
            && (term[1] == 'r' || term[1] == 'R');
        if(term.front() == '-' || is_or)
            continue;
        if(!result.empty())
            result += " OR ";
        result += term;
        // websearch accepts an unfinished phrase; close it before adding OR.
        if(quoted)
            result.push_back('"');
    }
    return result;
}

std::string tlgs::highlightSnippet(const std::string_view marked_text)
{
    constexpr size_t min_words = 23;
    constexpr size_t max_words = 37;
    constexpr size_t context_words = 5;
    struct Word {
        std::string text;
        std::vector<size_t> terms;
    };
    std::vector<Word> words;
    std::unordered_map<std::string, size_t> term_ids;
    Word word;
    std::string match;
    bool highlighting = false;
    const auto finish_match = [&] {
        if(match.empty())
            return;
        word.text += '[' + match + ']';
        auto normalized = match;
        for(auto& ch : normalized) {
            if(ch >= 'A' && ch <= 'Z')
                ch += 'a' - 'A';
        }
        const auto id = term_ids.try_emplace(std::move(normalized), term_ids.size()).first->second;
        word.terms.push_back(id);
        match.clear();
    };
    const auto finish_word = [&] {
        finish_match();
        if(!word.text.empty()) {
            words.emplace_back(std::move(word));
            word = Word{};
        }
    };
    for(const auto ch : marked_text) {
        if(ch == '\x1e') {
            finish_match();
            highlighting = true;
        }
        else if(ch == '\x1f') {
            finish_match();
            highlighting = false;
        }
        else if(std::string_view{" \t\r\n\f\v"}.find(ch) != std::string_view::npos)
            finish_word();
        else if(highlighting)
            match += ch;
        else
            word.text += ch;
    }
    finish_word();

    // A fixed-size sliding window rewards distinct terms before repetition.
    // Only short windows are inspected; document length cannot make this quadratic.
    std::vector<size_t> frequency(term_ids.size());
    size_t distinct = 0, hits = 0;
    size_t best_distinct = 0, best_hits = 0;
    size_t best_first = 0, best_last = 0, best_span = max_words + 1;
    for(size_t right = 0; right < words.size(); ++right) {
        for(const auto id : words[right].terms) {
            if(frequency[id]++ == 0)
                ++distinct;
            ++hits;
        }
        const auto left = right >= max_words ? right - max_words + 1 : 0;
        if(right >= max_words) {
            for(const auto id : words[left - 1].terms) {
                if(--frequency[id] == 0)
                    --distinct;
                --hits;
            }
        }
        if(hits == 0 || distinct < best_distinct
            || (distinct == best_distinct && hits < best_hits))
            continue;
        auto first = left;
        auto last = right;
        while(words[first].terms.empty())
            ++first;
        while(words[last].terms.empty())
            --last;
        const auto span = last - first + 1;
        if(distinct > best_distinct || hits > best_hits || span < best_span) {
            best_distinct = distinct;
            best_hits = hits;
            best_first = first;
            best_last = last;
            best_span = span;
        }
    }

    size_t begin = 0, end = std::min(min_words, words.size());
    if(best_hits != 0) {
        begin = best_first > context_words ? best_first - context_words : 0;
        if(best_last - begin >= max_words)
            begin = best_last - max_words + 1;
        end = std::min(words.size(), std::min(begin + max_words,
            std::max(begin + min_words, best_last + context_words + 1)));
    }
    std::string result = begin == 0 ? "" : "... ";
    for(auto i = begin; i < end; ++i) {
        if(i != begin)
            result += ' ';
        result += words[i].text;
    }
    if(end < words.size())
        result += " ...";
    return result;
}

bool tlgs::isAsciiArt(const std::string& str)
{
    // detection algorithm 2.A from https://www.w3.org/WAI/ER/IG/ert/AsciiArt.htm
    size_t count = 0;
    char last_ch = 0;
    for(auto ch : str) {
        if(ch == last_ch)
            count++;
        else {
            count = 1;
            last_ch = ch;
        }

        if(count >= 4 && ch != ' ' && ch != '\t')
            return true;
    }

    // Characters I'm sure is not used in code
    if(str.find("☆") != std::string::npos
    || str.find("★") != std::string::npos
    || str.find("░") != std::string::npos
    || str.find("█") != std::string::npos
    || str.find("⣿") != std::string::npos
    || str.find("⡇") != std::string::npos
    || str.find("⢀") != std::string::npos
    || str.find("┼") != std::string::npos
    || str.find("╭") != std::string::npos)
        return true;

    // patterns that's definatelly not normal text
    if(str.find("(_-<") != std::string::npos ||
        str.find("_ _ _ _") != std::string::npos)
        return true;

    return false;
}

std::string tlgs::urlEncode(const std::string_view src)
{
    std::string result;
    result.reserve(src.size() + 8);  // Some sane amount to reduce allocation
    // Unserved symbols. See RFC 3986
    constexpr std::string_view symbols = "-_.~";

    for (char ch : src)
    {
        if (std::isalnum(static_cast<unsigned char>(ch)) || symbols.find(ch) != std::string_view::npos)
            result.append(1, ch);
        else
        {
            result.append(1, '%');
            result.append(charToHex(ch));
        }
    }

    return result;
}

std::string tlgs::logText(const std::string_view str)
{
    std::string result;
    result.reserve(str.size());
    for(const unsigned char ch : str) {
        if(ch == '\\')
            result += "\\\\";
        else if(ch < 0x20 || ch == 0x7f) {
            result += "\\x";
            result += charToHex(static_cast<char>(ch));
        }
        else
            result.push_back(static_cast<char>(ch));
    }
    return result;
}

std::string tlgs::geminiLineText(const std::string_view str)
{
    std::string result(str);
    for(auto& ch : result) {
        if((unsigned char)ch < 0x20 || ch == 0x7f)
            ch = ' ';
    }
    return result;
}

std::string tlgs::geminiLinkTarget(const std::string_view url)
{
    std::string result;
    result.reserve(url.size());
    for(char ch : url) {
        if((unsigned char)ch <= 0x20 || ch == 0x7f) {
            result.append(1, '%');
            result.append(charToHex(ch));
        }
        else
            result.append(1, ch);
    }
    return result;
}

tlgs::Url tlgs::linkCompose(const tlgs::Url& url, const std::string& path)
{
    if(path.empty())
        return tlgs::Url("");
    tlgs::Url link_url;
    if(path[0] == '/') {
        tlgs::Url dummy = tlgs::Url("gemini://localhost"+path);
        link_url = tlgs::Url(url).withPath(dummy.path()).withParam(dummy.param()).withFragment(dummy.fragment());
    }
    else {
        tlgs::Url dummy = tlgs::Url("gemini://localhost/"+path, false);
        auto link_path = std::filesystem::path(dummy.path().substr(1));
        auto current_path = std::filesystem::path(url.path());

        if(url.path().back() == '/') // we are visiting a directory  
            link_url = tlgs::Url(url).withPath((current_path/link_path).generic_string());
        else
            link_url = tlgs::Url(url).withPath((current_path.parent_path()/link_path).generic_string());
        link_url.withParam(dummy.param()).withFragment(dummy.fragment());
    }
    return link_url;
}

bool tlgs::isNonUriAction(const std::string& str)
{
    // detects if the string is of the form [scheme]:[other_stuff]
    size_t n = str.find("://");
    if(n != std::string::npos)
        return false;
    n = str.find(":");
    if(n == std::string::npos)
        return false;
    for(size_t i = 0; i < n; i++) {
        if(std::isalpha(static_cast<unsigned char>(str[i])) == false)
            return false;
    }
    return true;
}

std::string tlgs::xxHash64(const std::string_view str)
{
    auto hash = XXH64(str.data(), str.size(), 0);
    return drogon::utils::binaryStringToHex((unsigned char*)&hash, sizeof(hash));
}

std::optional<unsigned long long> tlgs::try_strtoull(const std::string& str)
{
    char* endptr;
    unsigned long long result = strtoull(str.c_str(), &endptr, 10);
    if(endptr == str.c_str() || *endptr != '\0')
        return std::nullopt;
    return result;
}

std::string tlgs::indexFriendly(const tlgs::Url& url)
{
    std::string result = url.str();
    drogon::utils::replaceAll(result, "_", " ");
    drogon::utils::replaceAll(result, "-", " ");
    drogon::utils::replaceAll(result, "~", " ");

    return result;
}

std::string tlgs::pgSQLRealEscape(std::string str)
{
    drogon::utils::replaceAll(str, "\\", "\\\\");
    drogon::utils::replaceAll(str, std::string(1, '\0'), "\\0");
    drogon::utils::replaceAll(str, "\n", "\\n");
    drogon::utils::replaceAll(str, "\r", "\\r");
    drogon::utils::replaceAll(str, "'", "''");
    drogon::utils::replaceAll(str, "\"", "\\\"");
    drogon::utils::replaceAll(str, "\x1a", "\\Z");
    return str;
}
