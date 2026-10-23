#pragma once

#include <cstddef>
#include <cstdint>
#include <optional>
#include <string>

namespace tlgs::ranking
{
struct RetrievalScore
{
    size_t rank = 0;
    double score = 0;
};

struct AuthorityScore : RetrievalScore
{
    size_t independent_sites = 0;
};

struct RetrievalSignals
{
    std::optional<RetrievalScore> bm25;
    std::optional<AuthorityScore> hilltop;
};

struct TruncatedFields
{
    bool title = false;
    bool headings = false;
    bool body = false;
    bool link_text = false;
    bool external_links = false;
    bool internal_links = false;
};

struct Document
{
    std::string raw_content_hash;
    std::string indexed_content_hash;
    std::string language;
    std::string headings;
    std::string body;
    std::string link_text;
    bool has_explicit_title = false;
    TruncatedFields truncated;
    size_t external_link_count = 0;
    size_t internal_link_count = 0;
};

struct Page
{
    std::string url;
    std::string site;
    std::string title;
    int64_t size = 0;
    Document document;
    RetrievalSignals retrieval;
};
} // namespace tlgs::ranking
