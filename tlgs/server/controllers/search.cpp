#include <algorithm>
#include <drogon/HttpController.h>
#include <drogon/utils/coroutine.h>
#include <drogon/HttpAppFramework.h>
#include <tlgsutils/utils.hpp>
#include <tlgsutils/counter.hpp>
#include <tlgsutils/url_parser.hpp>
#include <nlohmann/json.hpp>
#include <ranges>
#include <atomic>
#include <regex>
#include <span>
#include <random>
#include <filesystem>
#include <fmt/format.h>

#include "search_result.hpp"

using namespace drogon;

namespace
{
constexpr size_t search_results_per_page = 10;
constexpr size_t fusion_candidate_limit = 1000;
constexpr size_t fusion_bm25_candidate_limit = 5000;
constexpr size_t fusion_title_candidate_limit = 1000;
constexpr size_t fusion_graph_candidate_limit = 250;
constexpr double fusion_rrf_constant = 60.0;

struct TimedSqlResult
{
    std::shared_ptr<orm::Result> rows;
    std::chrono::milliseconds duration{};
};

template<typename QueryFactory>
Task<TimedSqlResult> executeTimed(QueryFactory query_factory)
{
    const auto started = std::chrono::steady_clock::now();
    auto rows = co_await query_factory();
    co_return TimedSqlResult {
        .rows = std::make_shared<orm::Result>(std::move(rows)),
        .duration = std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::steady_clock::now() - started)
    };
}
}

struct RankedResult
{
    std::string url;
    std::string logical_site;
    std::string content_type;
    size_t size;
    uint64_t content_hash;
    double score;
};

struct SearchFilter;

struct SearchController : public HttpController<SearchController>
{
public:
    enum class RankingAlgorithm
    {
        HITS,
        SALSA,
        FUSION
    };

    SearchController();
    Task<HttpResponsePtr> tlgs_search(HttpRequestPtr req);
    Task<HttpResponsePtr> add_seed(HttpRequestPtr req);
    Task<HttpResponsePtr> jump_search(HttpRequestPtr req, std::string search_term);
    Task<HttpResponsePtr> backlinks(HttpRequestPtr req);

    METHOD_LIST_BEGIN
    ADD_METHOD_TO(SearchController::tlgs_search, "/search", {Get});
    ADD_METHOD_TO(SearchController::tlgs_search, "/search/{page}", {Get});
    ADD_METHOD_TO(SearchController::jump_search, "/search_jump/{search_term}", {Get});
    ADD_METHOD_TO(SearchController::tlgs_search, "/v/search", {Get});
    ADD_METHOD_TO(SearchController::tlgs_search, "/v/search/{page}", {Get});
    ADD_METHOD_TO(SearchController::jump_search, "/v/search_jump/{search_term}", {Get});
    ADD_METHOD_TO(SearchController::backlinks, "/backlinks", {Get});
    METHOD_LIST_END


    Task<std::vector<RankedResult>> pageSearch(
        const std::string& query_str, const SearchFilter& filter);
    Task<std::vector<RankedResult>> fusionSearch(
        const std::string& query_str, const SearchFilter& filter);
    std::atomic<size_t> search_in_flight{0};
    RankingAlgorithm ranking_algorithm = RankingAlgorithm::FUSION;
    double fusion_graph_weight = 1.0;
    double fusion_site_decay = 0.5;
    size_t fusion_max_site_results_per_page = 2;
};

auto sanitizeGemini(std::string preview) -> std::string {
    utils::replaceAll(preview, "\n", " ");
    utils::replaceAll(preview, "\t", " ");
    utils::replaceAll(preview, "```", " ");
    auto idx = preview.find_first_not_of("`*=>#");
    if(idx == std::string::npos)
        return preview;
    return preview.substr(idx);
}

enum class TokenType
{
    Text = 0,
    Filter,
    Logical,
};

struct FilterConstrant
{
    std::string value;
    bool negate;
};

struct SizeConstrant
{
    size_t size;
    bool greater;
};

struct SearchFilter
{
    std::vector<FilterConstrant> content_type;
    std::vector<FilterConstrant> domain;
    std::vector<SizeConstrant> size;
    std::vector<FilterConstrant> title;

    bool empty() const
    {
        return content_type.empty() && domain.empty() && size.empty() && title.empty();
    }
};

namespace std
{
template<>
struct hash<FilterConstrant>
{
    size_t operator()(const FilterConstrant& fc) const
    {
        return std::hash<std::string>{}(fc.value) + fc.negate;
    }
};

template<>
struct hash<SizeConstrant>
{
    size_t operator()(const SizeConstrant& sc) const
    {
        return std::hash<size_t>{}(sc.size) + sc.greater;
    }
};

template<>
struct hash<SearchFilter>
{
    size_t operator()(const SearchFilter& sf) const
    {
        size_t hash = 0;
        for(const auto& fc : sf.content_type)
            hash ^= std::hash<FilterConstrant>{}(fc);
        for(const auto& dc : sf.domain)
            hash ^= std::hash<FilterConstrant>{}(dc);
        for(const auto& sc : sf.size)
            hash ^= std::hash<SizeConstrant>{}(sc);
        for(const auto& tc : sf.title)
            hash ^= std::hash<FilterConstrant>{}(tc);
        return hash;
    }
};
}

std::optional<size_t> parseSizeUnits(std::string unit)
{
    std::transform(unit.begin(), unit.end(), unit.begin(), ::tolower);
    if(unit.size() > 1 && unit.back() == 'b')
        unit.pop_back();

    if(unit == "" || unit == "b" || unit == "byte")
        return 1;
    else if(unit == "k")
        return 1000;
    else if(unit == "ki")
        return 1024;
    else if(unit == "m")
        return 1000*1000;
    else if(unit == "mi")
        return 1024*1024;
    else if(unit == "g")
        return 1000*1000*1000;
    else if(unit == "gi")
        return 1024*1024*1024;
    else
        return {};
}

std::pair<std::string, SearchFilter> parseSearchQuery(const std::string& query)
{
    std::pair<std::string, std::string> result;
    auto words = utils::splitString(query, " ");
    std::string search_query = "";
    SearchFilter filter;
    std::vector<TokenType> token_type;

    for(const auto& token : words) {
        auto seperator = token.find(":");
        if(seperator != std::string::npos &&
            seperator+1 != token.size() &&
            seperator != 0) {
            auto key = token.substr(0, seperator);
            if(key == "content_type" || key == "domain" || key == "size" || key == "intitle")
                token_type.push_back(TokenType::Filter);
            else
                token_type.push_back(TokenType::Text);
        }
        else if(token == "NOT" || token == "not")
            token_type.push_back(TokenType::Logical);
        else
            token_type.push_back(TokenType::Text);
    }

    bool negate = false;
    for(size_t i=0;i<words.size();i++) {
        auto type = token_type[i];
        const auto& token = words[i];
        if(type == TokenType::Text)
            search_query += token + " ";
        else if(type == TokenType::Filter) {
            auto idx = token.find(':');
            auto key = token.substr(0, idx);
            auto value = token.substr(idx+1);
            if(key == "content_type")
                filter.content_type.push_back({std::string(value), negate});
            else if(key == "domain")
                filter.domain.push_back({std::string(value), negate});
            else if(key == "intitle")
                filter.title.push_back({std::string(value), negate});
            else if(key == "size") {
                static const std::regex re(R"(([><])([\.0-9]+)([GBKMibyte]+)?)", std::regex_constants::icase);
                std::smatch match;
                if(std::regex_match(value, match, re) == false) {
                    LOG_DEBUG << "Bad size filter: " << token;
                    negate = false;
                    continue;
                }
                bool greater = match[1] == ">";
                auto unit = parseSizeUnits(match[3].str());
                if(!unit.has_value()) {
                    LOG_DEBUG << "Bad size unit: " << match[3].str();
                    negate = false;
                    continue;
                }
                size_t size = std::stod(match[2])*unit.value();
                filter.size.push_back({size, bool(negate^greater)});
            }
            negate = false;
        }
        else {
            if(i != words.size() - 1 && token_type[i+1] == TokenType::Filter) {
                negate = true;
            }
            else
                search_query += token + " ";
        }
    }

    if(!search_query.empty())
        search_query.resize(search_query.size()-1);

    // A positive intitle term also supplies the lexical query for searches such
    // as "intitle:gemini". Negated title filters must not require the excluded
    // term to occur in the document.
    for(const auto& tc : filter.title) {
        if(!tc.negate) {
            if(!search_query.empty())
                search_query += ' ';
            search_query += tc.value;
        }
    }
    if(!search_query.empty() && search_query.back() == ' ')
        search_query.pop_back();
    return {search_query, filter};
}

nlohmann::json serializeSearchFilter(const SearchFilter& filter)
{
    nlohmann::json result = {
        {"content_type", nlohmann::json::array()},
        {"domain", nlohmann::json::array()},
        {"size", nlohmann::json::array()},
        {"title", nlohmann::json::array()}
    };
    for(const auto& item : filter.content_type)
        result["content_type"].push_back({{"value", item.value}, {"negate", item.negate}});
    for(const auto& item : filter.domain)
        result["domain"].push_back({{"value", item.value}, {"negate", item.negate}});
    for(const auto& item : filter.size)
        result["size"].push_back({{"size", item.size}, {"greater", item.greater}});
    for(const auto& item : filter.title)
        result["title"].push_back({{"value", item.value}, {"negate", item.negate}});
    return result;
}

/**
 * @brief Rnaks the network nodes using the HITS algorithm.
 *
 * @param in_neighbous vector of vector where in_neighbous[i] is all inbound links of node i
 * @param out_neighbous ector of vector where out_neighbous[i] is all outbound links of node i
 * @return std::vector<double> The score of each node
 */
std::vector<double> hitsRank(const std::vector<std::vector<size_t>>& in_neighbous, const std::vector<std::vector<size_t>>& out_neighbous)
{
    // The HITS algorithm
    size_t node_count = in_neighbous.size();
    assert(node_count == out_neighbous.size());
    float score_delta = std::numeric_limits<float>::max_digits10;
    constexpr float epsilon = 0.005;
    constexpr size_t max_iter = 300;
    std::vector<double> auth_score;
    std::vector<double> hub_score;
    std::vector<double> new_auth_score;
    std::vector<double> new_hub_score;
    auth_score.resize(node_count, 1.0/node_count);
    hub_score.resize(node_count, 1.0/node_count);
    new_auth_score.resize(node_count);
    new_hub_score.resize(node_count);
    size_t hits_iter = 0;
    for(hits_iter=0;hits_iter<max_iter && score_delta > epsilon;hits_iter++) {
        for(size_t i=0;i<node_count;i++) {
            new_auth_score[i] = auth_score[i];
            new_hub_score[i] = hub_score[i];
            float calc_auth_score = 0;
            float calc_hub_score = 0;
            for(auto neighbour_idx : in_neighbous[i])
                calc_auth_score += hub_score[neighbour_idx];
            for(auto neighbour_idx : out_neighbous[i])
                calc_hub_score += auth_score[neighbour_idx];

            if(calc_auth_score != 0)
                new_auth_score[i] = calc_auth_score;
            if(calc_hub_score != 0)
                new_hub_score[i] = calc_hub_score;
        }

        float auth_sum = std::max(std::accumulate(new_auth_score.begin(), new_auth_score.end(), 0.0), 1.0);
        float hub_sum = std::max(std::accumulate(new_hub_score.begin(), new_hub_score.end(), 0.0), 1.0);

        score_delta = 0;
        for(size_t i=0;i<node_count;i++) {
            score_delta += std::abs(auth_score[i] - new_auth_score[i] / auth_sum);
            score_delta += std::abs(hub_score[i] - new_hub_score[i] / hub_sum);
            auth_score[i] = new_auth_score[i] / auth_sum;
            hub_score[i] = new_hub_score[i] / hub_sum;

            // avoid denormals
            if(auth_score[i] < std::numeric_limits<float>::epsilon())
                auth_score[i] = 0;
            if(hub_score[i] < std::numeric_limits<float>::epsilon())
                hub_score[i] = 0;
        }
    }
    LOG_DEBUG << "HITS finished in " << hits_iter << " iterations";
    return auth_score;
}

/**
 * @brief Rnaks the network nodes using the SALSA algorithm.
 *
 * @param in_neighbous vector of vector where in_neighbous[i] is all inbound links of node i
 * @param out_neighbous ector of vector where out_neighbous[i] is all outbound links of node i
 * @return std::vector<double> The score of each node
 * @note in_neighbous and out_neighbous will be modified to become a biparte graph
 */
std::vector<double> salsaRank(std::vector<std::vector<size_t>>& in_neighbous, std::vector<std::vector<size_t>>& out_neighbous)
{
    size_t node_count = in_neighbous.size();
    assert(node_count == out_neighbous.size());
    std::vector<unsigned char> is_auth(node_count);
    size_t num_hubs = 0;
    size_t num_auths = 0;
    // Find the hubs and auths in the network. According to the SALSA paper, hubs are noes with more outbound links than inbound links.
    for(size_t i = 0; i < node_count; ++i) {
        is_auth[i] = in_neighbous[i].size() > out_neighbous[i].size();
        num_hubs += !is_auth[i];
        num_auths += is_auth[i];
    }
    // Turn the network into a biparte graph. For performance, we swap the link to be removed with the last link in the vector.
    // Then resize the vector at the very end.
    for(size_t i = 0; i < node_count; ++i) {
        size_t size = in_neighbous[i].size();
        for(size_t j = 0; j < size ; ++j) {
            auto idx = in_neighbous[i][j];
            if(is_auth[idx] == is_auth[i]) {
                if(j != size-1)
                    std::swap(in_neighbous[i][j], in_neighbous[i][size-1]);
                size--;
                j--;
            }
        }
        in_neighbous[i].resize(size);
        size = out_neighbous[i].size();
        for(size_t j = 0; j < size ; ++j) {
            auto idx = out_neighbous[i][j];
            if(is_auth[idx] == is_auth[i]) {
                if(j != size-1)
                    std::swap(out_neighbous[i][j], out_neighbous[i][size-1]);
                size--;
                j--;
            }
        }
        out_neighbous[i].resize(size);
    }

    float score_delta = std::numeric_limits<float>::max_digits10;
    constexpr float epsilon = 0.005*2;
    constexpr size_t max_iter = 300;
    std::vector<double> score;
    std::vector<double> new_score;
    score.resize(node_count);
    new_score.resize(node_count);
    for(size_t i=0;i<node_count;i++)
        score[i] = 1.0 / (is_auth[i] ? num_auths : num_hubs);

    // The SALSA ranking algorithm
    // Reference implementation: https://docs.oracle.com/cd/E56133_01/latest/reference/analytics/algorithms/salsa.html
    size_t salsa_iter = 0;
    std::vector<float> local_in_score(node_count);
    std::vector<float> local_out_score(node_count);
    for(salsa_iter=0;salsa_iter<max_iter && score_delta > epsilon;salsa_iter++) {
        for(size_t i=0;i<node_count;i++) {
            local_in_score[i] = -1;
            local_out_score[i] = -1;
        }
        for(size_t i=0;i<node_count;i++) {
            if(is_auth[i]) {
                new_score[i] = std::accumulate(in_neighbous[i].begin(), in_neighbous[i].end(), 0.0, [&](double sum, size_t idx) {
                    double neibour_score = local_out_score[idx];
                    if(neibour_score == -1) {
                        neibour_score = std::accumulate(out_neighbous[idx].begin(), out_neighbous[idx].end(), 0.0, [&](double sum, size_t idx2) {
                            return sum + score[idx2] / std::max(in_neighbous[idx2].size(), size_t{1});
                        }) / std::max(out_neighbous[idx].size(), size_t{1});
                        local_out_score[idx] = neibour_score;
                    }
                    return sum + neibour_score;
                });
            }
            else {
                new_score[i] = std::accumulate(out_neighbous[i].begin(), out_neighbous[i].end(), 0.0, [&](double sum, size_t idx) {
                    double neibour_score = local_in_score[idx];
                    if(neibour_score == -1) {
                        neibour_score = std::accumulate(in_neighbous[idx].begin(), in_neighbous[idx].end(), 0.0, [&](double sum, size_t idx2) {
                            return sum + score[idx2] / std::max(out_neighbous[idx2].size(), size_t{1});
                        }) / std::max(in_neighbous[idx].size(), size_t{1});
                        local_in_score[idx] = neibour_score;
                    }
                    return sum + neibour_score;
                });
            }
        }
        double sum = std::max(std::accumulate(score.begin(), score.end(), 0.0), 1.0);

        score_delta = 0.0;
        for(size_t i=0;i<node_count;i++) {
            score_delta += std::abs(new_score[i]/sum - score[i]);
            score[i] = new_score[i]/sum;
        }
    }
    LOG_DEBUG << "SALSA finished in " << salsa_iter << " iterations";
    return score;
}

std::vector<RankedResult> deduplicateRankedResults(
    std::vector<RankedResult>& nodes,
    const std::span<const unsigned char> roots,
    const std::string_view query)
{
    const auto started = std::chrono::high_resolution_clock::now();
    std::unordered_multimap<uint64_t, const RankedResult*> result_map;
    result_map.reserve(nodes.size());
    std::string buf(8, '\0');
    drogon::utils::secureRandomBytes(buf.data(), buf.size());
    const std::string token = "/" + drogon::utils::binaryStringToHex(
        reinterpret_cast<unsigned char*>(buf.data()), buf.size());
    size_t num_root = 0;
    for(size_t i = 0; i < nodes.size(); ++i) {
        auto& node = nodes[i];
        if(!roots.empty() && !roots[i])
            continue;
        ++num_root;
        auto [begin, end] = result_map.equal_range(node.content_hash);
        if(node.size == 0 || begin == end) {
            result_map.emplace(node.content_hash, &node);
            continue;
        }

        auto to_lower = [](const std::string& str) {
            std::string ret = str;
            std::transform(ret.begin(), ret.end(), ret.begin(), ::tolower);
            return ret;
        };
        tlgs::Url node_url(node.url);
        node_url.withHost(to_lower(node_url.host()));
        std::string normalized = node.url;
        drogon::utils::replaceAll(normalized, "/~", token);
        drogon::utils::replaceAll(normalized, "/users", token);
        drogon::utils::replaceAll(normalized, "/user", token);
        if(normalized.ends_with("/"))
            normalized.pop_back();
        bool replaced = false;
        for(auto& [_, stored] : std::ranges::subrange(begin, end)) {
            tlgs::Url stored_url(stored->url);
            stored_url.withHost(to_lower(stored_url.host()));
            std::string stored_normalized = stored->url;
            drogon::utils::replaceAll(stored_normalized, "/~", token);
            drogon::utils::replaceAll(stored_normalized, "/users", token);
            drogon::utils::replaceAll(stored_normalized, "/user", token);

            if(node_url.host() == stored_url.host() ||
               node_url.path() == stored_url.path() ||
               stored->url.ends_with(node_url.host() + node_url.path()) ||
               normalized == stored_normalized) {
                if(stored->score < node.score)
                    stored = &node;
                replaced = true;
                break;
            }

            if(node.url.ends_with(stored_url.host() + stored_url.path())) {
                replaced = true;
                break;
            }
        }
        if(!replaced)
            result_map.emplace(node.content_hash, &node);
    }

    std::vector<RankedResult> results;
    results.reserve(result_map.size());
    for(const auto& [_, item] : result_map)
        results.emplace_back(*item);
    std::sort(results.begin(), results.end(), [](const auto& lhs, const auto& rhs) {
        if(lhs.score != rhs.score)
            return lhs.score > rhs.score;
        return lhs.url < rhs.url;
    });

    const auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(
        std::chrono::high_resolution_clock::now() - started);
    LOG_DEBUG << "Deduplication removed " << num_root - result_map.size()
              << " results for search term `" << query << "` in "
              << elapsed.count() << "ms";
    return results;
}

std::vector<RankedResult> crowdResultPages(
    std::vector<RankedResult> pending,
    const size_t page_size,
    const size_t max_per_site)
{
    if(max_per_site == 0 || max_per_site >= page_size)
        return pending;

    std::vector<RankedResult> diversified;
    diversified.reserve(pending.size());
    while(!pending.empty()) {
        std::unordered_map<std::string, size_t> site_counts;
        std::vector<RankedResult> deferred;
        deferred.reserve(pending.size());
        size_t selected = 0;
        for(auto& result : pending) {
            const auto& site = result.logical_site.empty() ? result.url : result.logical_site;
            if(selected < page_size && site_counts[site] < max_per_site) {
                ++site_counts[site];
                ++selected;
                diversified.emplace_back(std::move(result));
            }
            else {
                deferred.emplace_back(std::move(result));
            }
        }

        // A narrow query may not have enough independent sites to fill a page.
        // Relax the cap only for the otherwise-empty slots; never drop results.
        const auto missing = std::min(page_size - selected, deferred.size());
        for(size_t i = 0; i < missing; ++i)
            diversified.emplace_back(std::move(deferred[i]));
        if(missing != 0)
            deferred.erase(deferred.begin(), deferred.begin() + missing);
        pending = std::move(deferred);
    }
    return diversified;
}

SearchController::SearchController()
{
    auto tlgs = app().getCustomConfig()["tlgs"];
    if(tlgs.isNull())
        return;

    auto ranking_algo = tlgs["ranking_algo"];
    if(!ranking_algo.isNull()) {
        if(!ranking_algo.isString()) {
            LOG_WARN << "ranking_algo must be a string; defaulting to fusion";
        }
        else {
            const auto algo = ranking_algo.asString();
            if(algo == "hits")
                ranking_algorithm = RankingAlgorithm::HITS;
            else if(algo == "salsa")
                ranking_algorithm = RankingAlgorithm::SALSA;
            else if(algo == "fusion")
                ranking_algorithm = RankingAlgorithm::FUSION;
            else
                LOG_WARN << "Unknown ranking algorithm: " << algo
                         << ", defaulting to fusion instead";
        }
    }

    auto graph_weight = tlgs["fusion_graph_weight"];
    if(!graph_weight.isNull()) {
        bool valid = false;
        if(graph_weight.isNumeric()) {
            const auto configured_weight = graph_weight.asDouble();
            if(configured_weight >= 0.0 && configured_weight <= 4.0) {
                fusion_graph_weight = configured_weight;
                valid = true;
            }
        }
        if(!valid)
            LOG_WARN << "fusion_graph_weight must be between 0 and 4; using 1.0";
    }

    auto site_decay = tlgs["fusion_site_decay"];
    if(!site_decay.isNull()) {
        bool valid = false;
        if(site_decay.isNumeric()) {
            const auto configured_decay = site_decay.asDouble();
            if(configured_decay >= 0.0 && configured_decay <= 4.0) {
                fusion_site_decay = configured_decay;
                valid = true;
            }
        }
        if(!valid)
            LOG_WARN << "fusion_site_decay must be between 0 and 4; using 0.5";
    }

    auto site_cap = tlgs["fusion_max_site_results_per_page"];
    if(!site_cap.isNull()) {
        bool valid = false;
        if(site_cap.isUInt()) {
            const auto configured_cap = site_cap.asUInt();
            if(configured_cap <= search_results_per_page) {
                fusion_max_site_results_per_page = configured_cap;
                valid = true;
            }
        }
        if(!valid)
            LOG_WARN << "fusion_max_site_results_per_page must be between 0 and 10; using 2";
    }

    if(ranking_algorithm == RankingAlgorithm::FUSION) {
        LOG_INFO << "Search ranking: fusion (graph weight " << fusion_graph_weight
                 << ", site decay " << fusion_site_decay
                 << ", per-page site cap " << fusion_max_site_results_per_page << ')';
    }
    else if(ranking_algorithm == RankingAlgorithm::SALSA) {
        LOG_WARN << "Search ranking: legacy query-time SALSA";
    }
    else {
        LOG_WARN << "Search ranking: legacy query-time HITS";
    }
}

Task<std::vector<RankedResult>> SearchController::fusionSearch(
    const std::string& query_str, const SearchFilter& filter)
{
    using Clock = std::chrono::steady_clock;
    const auto search_started = Clock::now();
    auto db = app().getDbClient();
    const auto filter_json = serializeSearchFilter(filter).dump();
    auto fts_task = executeTimed(
        [db, query_str, filter_json, filter_empty=filter.empty(),
         site_decay=fusion_site_decay]() -> Task<orm::Result> {
        // Keep BM25 as a top-level query. In a CTE PostgreSQL projects the
        // ORDER BY expression again, tokenizing every returned document.
        // Keep LIMIT literal: Drogon reuses prepared statements, and a generic
        // plan cannot push a parameterized LIMIT into pg_textsearch's top-K scan.
        const auto bm25_started = Clock::now();
        const auto bm25_rows = filter_empty
            ? co_await db->execSqlCoro(R"sql(
        SELECT pages.url, bm25_get_current_score() AS bm25_distance
        FROM pages
        ORDER BY public.tlgs_bm25_document(
                     pages.title, pages.search_headings, pages.search_link_text,
                     pages.url, pages.content_body) <@>
                 to_bm25query($1, 'pages_bm25_search_idx')
        LIMIT 5000
    )sql", query_str)
            : co_await db->execSqlCoro(R"sql(
        SELECT pages.url, bm25_get_current_score() AS bm25_distance
        FROM pages
        CROSS JOIN (SELECT $2::jsonb AS value) filters
        WHERE (jsonb_array_length(filters.value->'content_type')=0 OR (
            NOT EXISTS (
                SELECT 1 FROM jsonb_array_elements(filters.value->'content_type') item
                WHERE (item->>'negate')::boolean
                  AND coalesce(pages.content_type, '') LIKE item->>'value' || '%'
            )
            AND (
                NOT EXISTS (
                    SELECT 1 FROM jsonb_array_elements(filters.value->'content_type') item
                    WHERE NOT (item->>'negate')::boolean
                )
                OR EXISTS (
                    SELECT 1 FROM jsonb_array_elements(filters.value->'content_type') item
                    WHERE NOT (item->>'negate')::boolean
                      AND coalesce(pages.content_type, '') LIKE item->>'value' || '%'
                )
            )
          ))
          AND (jsonb_array_length(filters.value->'domain')=0 OR (
            NOT EXISTS (
                SELECT 1 FROM jsonb_array_elements(filters.value->'domain') item
                WHERE (item->>'negate')::boolean
                  AND lower(pages.domain_name)=lower(item->>'value')
            )
            AND (
                NOT EXISTS (
                    SELECT 1 FROM jsonb_array_elements(filters.value->'domain') item
                    WHERE NOT (item->>'negate')::boolean
                )
                OR EXISTS (
                    SELECT 1 FROM jsonb_array_elements(filters.value->'domain') item
                    WHERE NOT (item->>'negate')::boolean
                      AND lower(pages.domain_name)=lower(item->>'value')
                )
            )
          ))
          AND (
            jsonb_array_length(filters.value->'size')=0
            OR (pages.size > 0 AND NOT EXISTS (
                SELECT 1 FROM jsonb_array_elements(filters.value->'size') item
                WHERE CASE WHEN (item->>'greater')::boolean
                           THEN pages.size <= (item->>'size')::bigint
                           ELSE pages.size >= (item->>'size')::bigint END
            ))
          )
          AND (jsonb_array_length(filters.value->'title')=0 OR (
            NOT EXISTS (
                SELECT 1 FROM jsonb_array_elements(filters.value->'title') item
                WHERE (item->>'negate')::boolean
                  AND pages.title_vector @@ websearch_to_tsquery('simple', item->>'value')
            )
            AND NOT EXISTS (
                SELECT 1 FROM jsonb_array_elements(filters.value->'title') item
                WHERE NOT (item->>'negate')::boolean
                  AND NOT (pages.title_vector @@ websearch_to_tsquery('simple', item->>'value'))
            )
          ))
        ORDER BY public.tlgs_bm25_document(
                     pages.title, pages.search_headings, pages.search_link_text,
                     pages.url, pages.content_body) <@>
                 to_bm25query($1, 'pages_bm25_search_idx')
        LIMIT 5000
    )sql", query_str, filter_json);
        const auto bm25_finished = Clock::now();
        LOG_DEBUG << "BM25 retrieval for `" << query_str << "`: "
                  << std::chrono::duration_cast<std::chrono::milliseconds>(
                         bm25_finished - bm25_started).count()
                  << "ms (" << bm25_rows.size() << " candidates, filters "
                  << (filter_empty ? "empty" : "active") << ')';
        nlohmann::json bm25_candidates = nlohmann::json::array();
        for(const auto& row : bm25_rows)
            bm25_candidates.push_back({
                {"url", row["url"].as<std::string>()},
                {"bm25_distance", row["bm25_distance"].as<double>()}
            });
        auto ranked_rows = co_await db->execSqlCoro(R"sql(
        WITH query AS (
            SELECT websearch_to_tsquery('simple', $1) AS simple,
                   phraseto_tsquery('simple', $1) AS simple_phrase
        ), filters AS (
            SELECT $5::jsonb AS value
        ), active AS (
            SELECT (
                SELECT active_ruleset_id
                FROM site_identity_state
                WHERE singleton=TRUE
            ) AS ruleset_id
        ), eligible AS NOT MATERIALIZED (
            SELECT pages.*
            FROM pages
            CROSS JOIN filters
            WHERE (jsonb_array_length(filters.value->'content_type')=0 OR (
                NOT EXISTS (
                    SELECT 1 FROM jsonb_array_elements(filters.value->'content_type') item
                    WHERE (item->>'negate')::boolean
                      AND coalesce(pages.content_type, '') LIKE item->>'value' || '%'
                )
                AND (
                    NOT EXISTS (
                        SELECT 1 FROM jsonb_array_elements(filters.value->'content_type') item
                        WHERE NOT (item->>'negate')::boolean
                    )
                    OR EXISTS (
                        SELECT 1 FROM jsonb_array_elements(filters.value->'content_type') item
                        WHERE NOT (item->>'negate')::boolean
                          AND coalesce(pages.content_type, '') LIKE item->>'value' || '%'
                    )
                )
              ))
              AND (jsonb_array_length(filters.value->'domain')=0 OR (
                NOT EXISTS (
                    SELECT 1 FROM jsonb_array_elements(filters.value->'domain') item
                    WHERE (item->>'negate')::boolean
                      AND lower(pages.domain_name)=lower(item->>'value')
                )
                AND (
                    NOT EXISTS (
                        SELECT 1 FROM jsonb_array_elements(filters.value->'domain') item
                        WHERE NOT (item->>'negate')::boolean
                    )
                    OR EXISTS (
                        SELECT 1 FROM jsonb_array_elements(filters.value->'domain') item
                        WHERE NOT (item->>'negate')::boolean
                          AND lower(pages.domain_name)=lower(item->>'value')
                    )
                )
              ))
              AND (
                jsonb_array_length(filters.value->'size')=0
                OR (pages.size > 0 AND NOT EXISTS (
                    SELECT 1 FROM jsonb_array_elements(filters.value->'size') item
                    WHERE CASE WHEN (item->>'greater')::boolean
                               THEN pages.size <= (item->>'size')::bigint
                               ELSE pages.size >= (item->>'size')::bigint END
                ))
              )
              AND (jsonb_array_length(filters.value->'title')=0 OR (
                NOT EXISTS (
                    SELECT 1 FROM jsonb_array_elements(filters.value->'title') item
                    WHERE (item->>'negate')::boolean
                      AND pages.title_vector @@ websearch_to_tsquery('simple', item->>'value')
                )
                AND NOT EXISTS (
                    SELECT 1 FROM jsonb_array_elements(filters.value->'title') item
                    WHERE NOT (item->>'negate')::boolean
                      AND NOT (pages.title_vector @@ websearch_to_tsquery('simple', item->>'value'))
                )
              ))
        ), bm25_matches AS MATERIALIZED (
            SELECT url, bm25_distance
            FROM jsonb_to_recordset($7::jsonb)
                 AS bm25(url text, bm25_distance double precision)
        ), title_matches AS MATERIALIZED (
            SELECT pages.url
            FROM eligible pages
            CROSS JOIN query
            WHERE pages.title_vector @@ query.simple
            LIMIT $6
        ), retrieved AS MATERIALIZED (
            SELECT matches.url, min(matches.bm25_distance) AS bm25_distance
            FROM (
                SELECT url, bm25_distance FROM bm25_matches
                UNION ALL
                SELECT url, NULL::double precision FROM title_matches
            ) matches
            GROUP BY matches.url
        ), lexical_scored AS (
            SELECT pages.url, pages.content_type, pages.size,
                   pages.indexed_content_hash AS content_hash,
                   concat('gemini://', lower(pages.domain_name),
                          CASE WHEN pages.port = 1965 THEN ''
                               ELSE ':' || pages.port::text END) AS physical_site,
                   (CASE WHEN pages.title_vector @@ query.simple THEN 1.0 ELSE 0.0 END +
                    CASE WHEN pages.title_vector @@ query.simple_phrase THEN 0.5 ELSE 0.0 END +
                    CASE WHEN retrieved.bm25_distance < 0 THEN
                        0.5 * (-retrieved.bm25_distance) /
                        (1.0 - retrieved.bm25_distance)
                    ELSE 0.0 END)::double precision AS fts_score
            FROM retrieved
            JOIN pages ON pages.url=retrieved.url
            CROSS JOIN query
            WHERE retrieved.bm25_distance < 0
               OR pages.title_vector @@ query.simple
        ), lexical_pool AS MATERIALIZED (
            SELECT * FROM lexical_scored
            ORDER BY fts_score DESC, url
            LIMIT $2
        ), lexical_mapped AS MATERIALIZED (
            SELECT lexical_pool.*,
                   coalesce(target_map.site_key, lexical_pool.physical_site) AS target_site
            FROM lexical_pool
            CROSS JOIN active
            LEFT JOIN url_site_map target_map
              ON target_map.ruleset_id=active.ruleset_id
             AND target_map.url=lexical_pool.url
        ), lexical_site_ranked AS MATERIALIZED (
            SELECT lexical_mapped.*,
                   row_number() OVER (
                       PARTITION BY target_site
                       ORDER BY fts_score DESC, url
                   ) AS lexical_site_rank
            FROM lexical_mapped
        ), lexical AS MATERIALIZED (
            SELECT lexical_site_ranked.*,
                   (fts_score /
                    (1.0 + $4::double precision * (lexical_site_rank - 1)))::double precision
                       AS lexical_score
            FROM lexical_site_ranked
            ORDER BY lexical_score DESC, url
            LIMIT $3
        ), candidates AS MATERIALIZED (
            SELECT lexical.*,
                   row_number() OVER (ORDER BY lexical_score DESC, url) AS fts_rank
            FROM lexical
        )
        SELECT candidates.url, candidates.content_type, candidates.size,
               candidates.content_hash, candidates.target_site,
               candidates.fts_rank
        FROM candidates
        ORDER BY candidates.fts_rank
    )sql", query_str, fusion_bm25_candidate_limit, fusion_candidate_limit,
        site_decay, filter_json, fusion_title_candidate_limit,
        bm25_candidates.dump());
        const auto ranked_finished = Clock::now();
        LOG_DEBUG << "Lexical stages for `" << query_str << "`: BM25 "
                  << std::chrono::duration_cast<std::chrono::milliseconds>(
                         bm25_finished - bm25_started).count()
                  << "ms (" << bm25_rows.size() << " candidates), title/rerank "
                  << std::chrono::duration_cast<std::chrono::milliseconds>(
                         ranked_finished - bm25_finished).count() << "ms";
        co_return ranked_rows;
    });

    auto hilltop_task = executeTimed(
        [db, query_str, filter_json, filter_empty=filter.empty()]() {
        return db->execSqlCoro(R"sql(
        WITH query AS (
            SELECT websearch_to_tsquery('simple', $1) AS value
        ), filters AS (
            SELECT $3::jsonb AS value
        ), site_votes AS MATERIALIZED (
            SELECT edges.target_url,
                   edges.target_site,
                   edges.expert_site,
                   max(1.0 + least(
                       4.0 * ts_rank_cd(edges.qualifying_vector, query.value, 1),
                       1.0
                   )) AS vote
            FROM hilltop_edges edges
            CROSS JOIN query
            WHERE edges.ruleset_id=(
                SELECT active_ruleset_id
                FROM site_identity_state
                WHERE singleton=TRUE
            )
              AND edges.qualifying_vector @@ query.value
            GROUP BY edges.target_url, edges.target_site, edges.expert_site
        ), authority AS (
            SELECT target_url,
                   target_site,
                   sum(vote) AS authority_score,
                   count(*) AS independent_sites
            FROM site_votes
            GROUP BY target_url, target_site
            HAVING count(*) >= 2
        ), ranked AS (
            SELECT authority.*,
                   dense_rank() OVER (
                       ORDER BY authority_score DESC, independent_sites DESC
                   ) AS graph_rank
            FROM authority
        ), ranked_limited AS MATERIALIZED (
            SELECT *
            FROM ranked
            ORDER BY graph_rank, target_url
            LIMIT CASE WHEN $4::boolean THEN $2::bigint * 4 ELSE 2147483647::bigint END
        )
        SELECT ranked_limited.target_url,
               ranked_limited.target_site,
               ranked_limited.graph_rank,
               ranked_limited.authority_score,
               ranked_limited.independent_sites,
               pages.content_type,
               pages.size,
               pages.indexed_content_hash AS content_hash
        FROM ranked_limited
        JOIN pages ON pages.url=ranked_limited.target_url
        CROSS JOIN filters
        WHERE pages.last_indexed_at IS NOT NULL
          AND (jsonb_array_length(filters.value->'content_type')=0 OR (
            NOT EXISTS (
                SELECT 1 FROM jsonb_array_elements(filters.value->'content_type') item
                WHERE (item->>'negate')::boolean
                  AND coalesce(pages.content_type, '') LIKE item->>'value' || '%'
            )
            AND (
                NOT EXISTS (
                    SELECT 1 FROM jsonb_array_elements(filters.value->'content_type') item
                    WHERE NOT (item->>'negate')::boolean
                )
                OR EXISTS (
                    SELECT 1 FROM jsonb_array_elements(filters.value->'content_type') item
                    WHERE NOT (item->>'negate')::boolean
                      AND coalesce(pages.content_type, '') LIKE item->>'value' || '%'
                )
            )
          ))
          AND (jsonb_array_length(filters.value->'domain')=0 OR (
            NOT EXISTS (
                SELECT 1 FROM jsonb_array_elements(filters.value->'domain') item
                WHERE (item->>'negate')::boolean
                  AND lower(pages.domain_name)=lower(item->>'value')
            )
            AND (
                NOT EXISTS (
                    SELECT 1 FROM jsonb_array_elements(filters.value->'domain') item
                    WHERE NOT (item->>'negate')::boolean
                )
                OR EXISTS (
                    SELECT 1 FROM jsonb_array_elements(filters.value->'domain') item
                    WHERE NOT (item->>'negate')::boolean
                      AND lower(pages.domain_name)=lower(item->>'value')
                )
            )
          ))
          AND (
            jsonb_array_length(filters.value->'size')=0
            OR (pages.size > 0 AND NOT EXISTS (
                SELECT 1 FROM jsonb_array_elements(filters.value->'size') item
                WHERE CASE WHEN (item->>'greater')::boolean
                           THEN pages.size <= (item->>'size')::bigint
                           ELSE pages.size >= (item->>'size')::bigint END
            ))
          )
          AND (jsonb_array_length(filters.value->'title')=0 OR (
            NOT EXISTS (
                SELECT 1 FROM jsonb_array_elements(filters.value->'title') item
                WHERE (item->>'negate')::boolean
                  AND pages.title_vector @@ websearch_to_tsquery('simple', item->>'value')
            )
            AND NOT EXISTS (
                SELECT 1 FROM jsonb_array_elements(filters.value->'title') item
                WHERE NOT (item->>'negate')::boolean
                  AND NOT (pages.title_vector @@ websearch_to_tsquery('simple', item->>'value'))
            )
          ))
        ORDER BY ranked_limited.graph_rank, ranked_limited.target_url
        LIMIT $2
    )sql", query_str, fusion_graph_candidate_limit, filter_json, filter_empty);
    });

    auto fts_query = co_await std::move(fts_task);
    auto hilltop_query = co_await std::move(hilltop_task);
    const auto queries_finished = Clock::now();
    const auto& rows = *fts_query.rows;
    const auto& authority_rows = *hilltop_query.rows;

    struct FusionCandidate
    {
        RankedResult result;
        size_t fts_rank = 0;
        size_t graph_rank = 0;
        double fused_score = 0;
    };

    std::vector<FusionCandidate> candidates;
    candidates.reserve(rows.size() + authority_rows.size());
    std::unordered_map<std::string, size_t> candidate_indexes;
    candidate_indexes.reserve(rows.size() + authority_rows.size());
    for(const auto& row : rows) {
        FusionCandidate candidate;
        auto& result = candidate.result;
        result.url = row["url"].as<std::string>();
        result.logical_site = row["target_site"].as<std::string>();
        if(!row["content_type"].isNull())
            result.content_type = row["content_type"].as<std::string>();
        result.size = row["size"].as<int64_t>();
        std::string content_hash = row["content_hash"].as<std::string>();
        if(content_hash.empty())
            content_hash = "0";
        result.content_hash = std::stoull(content_hash, nullptr, 16);
        candidate.fts_rank = row["fts_rank"].as<int64_t>();
        candidate_indexes.emplace(result.url, candidates.size());
        candidates.emplace_back(std::move(candidate));
    }

    size_t graph_only_candidates = 0;
    for(const auto& row : authority_rows) {
        const auto url = row["target_url"].as<std::string>();
        const auto graph_rank = row["graph_rank"].as<int64_t>();
        if(const auto existing = candidate_indexes.find(url);
           existing != candidate_indexes.end()) {
            candidates[existing->second].graph_rank = graph_rank;
            continue;
        }

        FusionCandidate candidate;
        candidate.result.url = url;
        candidate.result.logical_site = row["target_site"].as<std::string>();
        if(!row["content_type"].isNull())
            candidate.result.content_type = row["content_type"].as<std::string>();
        candidate.result.size = row["size"].as<int64_t>();
        std::string content_hash = row["content_hash"].as<std::string>();
        if(content_hash.empty())
            content_hash = "0";
        candidate.result.content_hash = std::stoull(content_hash, nullptr, 16);
        candidate.graph_rank = graph_rank;
        candidate_indexes.emplace(candidate.result.url, candidates.size());
        candidates.emplace_back(std::move(candidate));
        ++graph_only_candidates;
    }

    for(auto& candidate : candidates) {
        if(candidate.fts_rank != 0)
            candidate.fused_score += 1.0 /
                (fusion_rrf_constant + candidate.fts_rank);
        if(candidate.graph_rank != 0)
            candidate.fused_score += fusion_graph_weight /
                (fusion_rrf_constant + candidate.graph_rank);
    }

    std::sort(candidates.begin(), candidates.end(), [](const auto& lhs, const auto& rhs) {
        if(lhs.fused_score != rhs.fused_score)
            return lhs.fused_score > rhs.fused_score;
        return lhs.fts_rank < rhs.fts_rank;
    });

    std::unordered_map<std::string, size_t> site_ranks;
    std::vector<RankedResult> results;
    results.reserve(candidates.size());
    for(auto& candidate : candidates) {
        const auto site_rank = ++site_ranks[candidate.result.logical_site];
        candidate.result.score = candidate.fused_score /
            (1.0 + fusion_site_decay * (site_rank - 1));
        results.emplace_back(std::move(candidate.result));
    }
    std::sort(results.begin(), results.end(), [](const auto& lhs, const auto& rhs) {
        if(lhs.score != rhs.score)
            return lhs.score > rhs.score;
        return lhs.url < rhs.url;
    });

    const auto fusion_finished = Clock::now();
    const auto milliseconds = [](const auto begin, const auto end) {
        return std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();
    };
    LOG_DEBUG << "Fusion search timings for `" << query_str << "`: FTS "
              << fts_query.duration.count() << "ms (" << rows.size()
              << " candidates), Hilltop " << hilltop_query.duration.count()
              << "ms (" << authority_rows.size() << " authority targets, "
              << graph_only_candidates << " graph-only) "
              << milliseconds(search_started, queries_finished) << "ms, fusion "
              << milliseconds(queries_finished, fusion_finished) << "ms";

    auto deduplicated = deduplicateRankedResults(
        results, std::span<const unsigned char>{}, query_str);
    co_return crowdResultPages(
        std::move(deduplicated), search_results_per_page, fusion_max_site_results_per_page);
}

Task<std::vector<RankedResult>> SearchController::pageSearch(
    const std::string& query_str, const SearchFilter& filter)
{
    if(ranking_algorithm == RankingAlgorithm::FUSION)
        co_return co_await fusionSearch(query_str, filter);
    auto sql_start = std::chrono::high_resolution_clock::now();
    auto db = app().getDbClient();
    constexpr size_t max_root_set_size = 1000;
    constexpr size_t max_rank_candidates = 5000;
    const auto bm25_rows = co_await db->execSqlCoro(R"sql(
        SELECT pages.url, bm25_get_current_score() AS distance
        FROM pages
        ORDER BY public.tlgs_bm25_document(
                     pages.title, pages.search_headings, pages.search_link_text,
                     pages.url, pages.content_body) <@>
                 to_bm25query($1, 'pages_bm25_search_idx')
        LIMIT 5000
    )sql", query_str);
    nlohmann::json bm25_candidates = nlohmann::json::array();
    for(const auto& row : bm25_rows)
        bm25_candidates.push_back({
            {"url", row["url"].as<std::string>()},
            {"distance", row["distance"].as<double>()}
        });
    auto nodes_of_intrest = co_await db->execSqlCoro(R"sql(
        WITH query AS (
            SELECT websearch_to_tsquery('simple', $1) AS simple,
                   phraseto_tsquery('simple', $1) AS phrase
        ), bm25 AS MATERIALIZED (
            SELECT url, distance
            FROM jsonb_to_recordset($4::jsonb)
                 AS bm25(url text, distance double precision)
        ), titles AS MATERIALIZED (
            SELECT pages.url
            FROM pages CROSS JOIN query
            WHERE pages.title_vector @@ query.simple
            LIMIT $3
        ), candidates AS MATERIALIZED (
            SELECT url, min(distance) AS distance
            FROM (
                SELECT url, distance FROM bm25
                UNION ALL
                SELECT url, NULL::double precision FROM titles
            ) matches
            GROUP BY url
        ), roots AS MATERIALIZED (
            SELECT pages.url,
                   (CASE WHEN pages.title_vector @@ query.simple THEN 1.0 ELSE 0.0 END +
                    CASE WHEN pages.title_vector @@ query.phrase THEN 0.5 ELSE 0.0 END +
                    CASE WHEN candidates.distance < 0 THEN
                        0.5 * (-candidates.distance) / (1.0 - candidates.distance)
                    ELSE 0.0 END) AS rank
            FROM candidates JOIN pages ON pages.url=candidates.url CROSS JOIN query
            ORDER BY rank DESC, pages.url
            LIMIT $3
        )
        SELECT roots.url AS source_url, pages.cross_site_links,
               pages.content_type, pages.size,
               pages.indexed_content_hash AS content_hash, roots.rank
        FROM roots JOIN pages ON pages.url=roots.url
        WHERE roots.rank > 0
        ORDER BY roots.rank DESC, roots.url
    )sql", query_str, max_rank_candidates, max_root_set_size,
        bm25_candidates.dump());
    if(nodes_of_intrest.size() == 0) {
        LOG_DEBUG << "DB returned no root set";
        co_return {};
    }

    nlohmann::json root_urls = nlohmann::json::array();
    for(const auto& node : nodes_of_intrest)
        root_urls.push_back(node["source_url"].as<std::string>());
    auto links_to_node = co_await db->execSqlCoro("SELECT links.to_url AS dest_url, links.url AS source_url, content_type, size, "
        "indexed_content_hash AS content_hash, 0 AS rank FROM pages JOIN links ON pages.url=links.to_url "
        "JOIN jsonb_array_elements_text($1::jsonb) AS roots(url) ON pages.url = roots.url "
        "WHERE links.is_cross_site = TRUE;", root_urls.dump());
    auto sql_end = std::chrono::high_resolution_clock::now();

    std::unordered_map<std::string, size_t> node_table;
    std::vector<RankedResult> nodes;
    std::vector<double> text_rank;
    std::vector<unsigned char> is_root;
    nodes.reserve(nodes_of_intrest.size());
    is_root.reserve(nodes_of_intrest.size());
    node_table.reserve(nodes_of_intrest.size());
    text_rank.reserve(nodes_of_intrest.size());
    // Add all nodes to our graph
    // TODO: Graph construction seems to be the slow part then a common term is being search. "Gemini", "capsule" are good examples.
    // Optimize it
    for(const auto& links : {nodes_of_intrest, links_to_node}) {
        for(const auto& link : links) {
            auto source_url = link["source_url"].as<std::string>();
            if(node_table.count(source_url) == 0) {
                std::string content_hash = link["content_hash"].as<std::string>();
                if(content_hash.empty())
                    content_hash = "0";
                RankedResult node;
                double rank = link["rank"].as<double>();
                node.url = source_url;
                node.size = link["size"].as<int64_t>();
                node.content_type = link["content_type"].as<std::string>();
                node.content_hash = std::stoull(content_hash, nullptr, 16);
                text_rank.emplace_back(rank);
                is_root.push_back(bool(rank != 0)); // Since the only reason for rank == 0 is it's in the base but not root
                nodes.emplace_back(std::move(node));
                node_table[source_url] = nodes.size()-1;
            }
        }
    }

    LOG_DEBUG << "DB returned " << nodes.size() << " pages";
    LOG_DEBUG << "Root set: " << nodes_of_intrest.size() << " pages";
    LOG_DEBUG << "Base set: " << nodes.size() - nodes_of_intrest.size() << " pages";

    std::vector<std::vector<size_t>> out_neighbous(nodes.size());
    std::vector<std::vector<size_t>> in_neighbous(nodes.size());

    // populate links between nodes
    auto getIfExists = [&](const std::string& name) -> size_t {
        auto it = node_table.find(name);
        if(it == node_table.end())
            return -1;
        return it->second;
    };
    for(const auto& page : nodes_of_intrest) {
        auto source_url = page["source_url"].as<std::string>();
        if(page["cross_site_links"].isNull())
            continue;
        auto links_str = page["cross_site_links"].as<std::string>();
        auto links = nlohmann::json::parse(std::move(links_str)).get<std::vector<std::string>>();
        auto source_node_idx = getIfExists(source_url);
        if(source_node_idx == -1) // Should not ever happen
            continue;
        out_neighbous[source_node_idx].reserve(links.size());
        for(const auto& link : links) {
            const auto& dest_url = link;
            auto dest_node_idx = getIfExists(dest_url);

            if(dest_node_idx == -1 || source_url == dest_url)
                continue;
            out_neighbous[source_node_idx].push_back(dest_node_idx);
            in_neighbous[dest_node_idx].push_back(source_node_idx);
        }
    }
    for(const auto& link : links_to_node) {
        const auto& source_url = link["source_url"].as<std::string>();
        const auto& dest_url = link["dest_url"].as<std::string>();
        if(source_url == dest_url)
            continue;

        auto source_node_idx = getIfExists(source_url);
        auto dest_node_idx = getIfExists(dest_url);
        if(dest_node_idx == -1 || source_node_idx == -1)
            continue;
        out_neighbous[source_node_idx].push_back(dest_node_idx);
        in_neighbous[dest_node_idx].push_back(source_node_idx);
    }

    std::vector<double> score;
    if(ranking_algorithm == RankingAlgorithm::HITS)
        score = hitsRank(in_neighbous, out_neighbous);
    else
        score = salsaRank(in_neighbous, out_neighbous);

    float max_score = *std::max_element(score.begin(), score.end());
    if(max_score == 0)
        max_score = 1;
    // Combine the bounded BM25/title text score with the graph score.
    // XXX: This scoring function works. But it kinda sucks
    for(size_t i=0;i<nodes.size();i++) {
        auto& node = nodes[i];
        float boost = exp((score[i] / max_score)*6.5);
        float rank = text_rank[i];
        // discourage pages too large
        const size_t discourage_size = 48*1000; // 48KB
        if(node.size > discourage_size) {
		rank *= 1.0 / std::log(
		    std::exp(1.0) +
		    (node.size - discourage_size) / 3000.0
		);
	}
        node.score = 2*(boost * rank) / (boost + rank);
    }

    auto sql_time = std::chrono::duration_cast<std::chrono::milliseconds>(sql_end - sql_start);
    LOG_DEBUG << "Legacy ranking SQL query time: " << sql_time.count() << "ms";
    co_return deduplicateRankedResults(nodes, is_root, query_str);
}

Task<HttpResponsePtr> SearchController::tlgs_search(HttpRequestPtr req)
{
    using namespace std::chrono;
    constexpr size_t cache_time = 600;

    // Hacky implementation of exponential backoff. We ask each request to wait
    // more and more until we processed something. Since we can't know how sent
    // which request
    tlgs::Counter counter(search_in_flight);
    static std::atomic<size_t> backup_count = 0;
    if(counter.count() > 64) {
        size_t count = backup_count++;
        size_t backoff = count > 9*64 ? 512 : std::pow(2, count/64.0);
        auto resp = HttpResponse::newHttpResponse();
        resp->addHeader("Retry-After", std::to_string(backoff));
        resp->setStatusCode(k429TooManyRequests);
        co_return resp;
    }
    backup_count = 0;

    auto t1 = high_resolution_clock::now();

    auto input = utils::urlDecode(req->getParameter("query"));
    if(input.size() > 1024) {
        auto resp = HttpResponse::newHttpResponse();
        resp->addHeader("meta", "Search query is too long");
        resp->setStatusCode(k400BadRequest);
        co_return resp;
    }
    auto [query_str, filter] = parseSearchQuery(input);
    std::transform(query_str.begin(), query_str.end(), query_str.begin(), ::tolower);

    if(query_str.empty()) {
        auto resp = HttpResponse::newHttpResponse();
        resp->addHeader("meta", "Search for something");
        resp->setStatusCode((HttpStatusCode)10);
        co_return resp;
    }

    using RankedResults = std::vector<RankedResult>;

    static CacheMap<std::string, std::shared_ptr<RankedResults>> result_cache(app().getLoop(), 60);
    const auto requested_page = tlgs::try_strtoull(
        std::filesystem::path(req->path()).filename().generic_string()).value_or(1);
    const size_t current_page_idx = std::max<uint64_t>(requested_page, 1) - 1;

    static const size_t fixed_random = std::random_device()();
    const auto hasher = std::hash<std::string>();
    const auto filter_hasher = std::hash<SearchFilter>();
    const auto query_hash = hasher(query_str)^fixed_random;
    const auto filter_hash = filter_hasher(filter)^fixed_random;
    const auto filtered_result_cache_key = query_str + "|" + std::to_string(query_hash)
        + "|" + std::to_string(filter_hash);
    std::string cache_status = "(fully cached)";

    std::shared_ptr<RankedResults> filtered_result;
    if(result_cache.findAndFetch(filtered_result_cache_key, filtered_result) == false) {
        filtered_result = std::make_shared<RankedResults>(
            co_await pageSearch(query_str, filter));
        cache_status = "";
        result_cache.insert(filtered_result_cache_key, filtered_result, cache_time);
    }

    if(filtered_result == nullptr)
        throw std::runtime_error("filtered search result is nullptr");

    const auto result_count = filtered_result->size();
    const size_t offset = current_page_idx > result_count / search_results_per_page
        ? result_count
        : std::min(current_page_idx * search_results_per_page, result_count);
    const size_t end_offset = std::min(offset + search_results_per_page, result_count);
    auto begin = filtered_result->begin() + offset;
    auto end = filtered_result->begin() + end_offset;

    nlohmann::json selected_urls = nlohmann::json::array();
    for(const auto& item : std::ranges::subrange(begin, end)) {
        selected_urls.push_back(item.url);
    }

    std::vector<SearchResult> search_result;
    if(!selected_urls.empty()) {
        // HACK: Use the first 5K characters for highligh search. This is MUCH faster
        // without loosing too much accuracy
        auto db = app().getDbClient();
        auto page_data = co_await db->execSqlCoro(R"sql(
            SELECT pages.url, pages.size, pages.title, pages.content_type,
                   CASE WHEN pages.english_search_vector IS NOT NULL
                        THEN ts_headline('english', SUBSTRING(pages.content_body, 0, 5000),
                                         websearch_to_tsquery('english', $1),
                                         'StartSel="[", StopSel="]", MinWords=23, MaxWords=37, '
                                         'MaxFragments=1, FragmentDelimiter=" ... "')
                        ELSE ts_headline('simple', SUBSTRING(pages.content_body, 0, 5000),
                                         websearch_to_tsquery('simple', $1),
                       'StartSel="[", StopSel="]", MinWords=23, MaxWords=37, '
                                         'MaxFragments=1, FragmentDelimiter=" ... "') END AS preview,
                   pages.last_crawl_success_at
            FROM pages
            JOIN jsonb_array_elements_text($2::jsonb) AS requested(url)
              ON requested.url=pages.url
        )sql", query_str, selected_urls.dump());

        std::unordered_map<std::string, size_t> result_idx;
        for(size_t i=0;i<page_data.size();i++) {
            const auto& page = page_data[i];
            result_idx[page["url"].as<std::string>()] = i;
        }

        for(const auto& item : std::ranges::subrange(begin, end)) {
            auto it = result_idx.find(item.url);
            if(it == result_idx.end()) {
                LOG_WARN << "Somehow found " << item.url << " in search. But that URL does not exist in DB";
                continue;
            }

            const auto& page = page_data[it->second];
            SearchResult res {
                .url = item.url,
                .title = page["title"].as<std::string>(),
                .content_type = page["content_type"].as<std::string>(),
                .preview = page["preview"].as<std::string>(),
                .last_crawled_at = trantor::Date::fromDbStringLocal(page["last_crawl_success_at"].as<std::string>())
                    .toCustomFormattedString("%Y-%m-%d %H:%M:%S", false),
                .size = page["size"].as<uint64_t>(),
                .score = item.score
            };
            if(res.preview.empty())
                res.preview = "No preview provided";
            search_result.emplace_back(std::move(res));
        }
    }

    HttpViewData data;
    std::string encoded_search_term = tlgs::urlEncode(input);
    data["search_result"] = std::move(search_result);
    data["title"] = sanitizeGemini(input) + " - TLGS Search";
    data["verbose"] = req->path().starts_with("/v/search");
    data["encoded_search_term"] = encoded_search_term;
    data["total_results"] = filtered_result->size();
    data["current_page_idx"] = current_page_idx;
    data["item_per_page"] = search_results_per_page;
    data["search_query"] = input;

    auto resp = HttpResponse::newHttpViewResponse("search_result", data);
    resp->setContentTypeCodeAndCustomString(CT_CUSTOM, "text/gemini");

    auto t2 = high_resolution_clock::now();
    double processing_time = duration_cast<duration<double>>(t2 - t1).count();
    LOG_DEBUG << fmt::format("Searching for '{}' took {} {} seconds."
        , input, cache_status, processing_time);
    co_return resp;
}

Task<HttpResponsePtr> SearchController::jump_search(HttpRequestPtr req, std::string search_term)
{
    auto input = utils::urlDecode(req->getParameter("query"));
    auto page = tlgs::try_strtoull(input);
    if(page.has_value() == false || page.value() == 0) {
        auto resp = HttpResponse::newHttpResponse();
        resp->addHeader("meta", "Go to page");
        resp->setStatusCode((HttpStatusCode)10);
        co_return resp;
    }

    bool verbose = req->path().starts_with("/v");
    const std::string_view search_path = verbose ? "/v/search" : "/search";

    auto resp = HttpResponse::newHttpResponse();
    std::string redirect_location;
    if(page.value() == 1)
        redirect_location = fmt::format("{}?{}", search_path, search_term);
    else
        redirect_location = fmt::format("{}/{}?{}", search_path, page.value(), search_term);

    resp->addHeader("location", redirect_location);
    resp->setStatusCode(k307TemporaryRedirect);
    co_return resp;
}

Task<HttpResponsePtr> SearchController::backlinks(HttpRequestPtr req)
{
    auto input = utils::urlDecode(req->getParameter("query"));
    tlgs::Url url(input);
    // try prepend gemini:// and see if it works
    if(url.good() == false)
        url = tlgs::Url("gemini://"+input);

    if(url.good() == false) {
        auto resp = HttpResponse::newHttpResponse();
        resp->addHeader("meta", "Enter URL to a page");
        resp->setStatusCode((HttpStatusCode)10);
        co_return resp;
    }

    auto db = app().getDbClient();
    auto backlinks = co_await db->execSqlCoro("SELECT url, is_cross_site FROM links WHERE links.to_url = $1 "
        , url.str());
    std::vector<std::string> internal_backlinks;
    std::vector<std::string> external_backlinks;
    for(const auto& link : backlinks) {
        std::string url = link["url"].as<std::string>();
        if(link["is_cross_site"].as<bool>())
            external_backlinks.push_back(url);
        else
            internal_backlinks.push_back(url);
    }
    HttpViewData data;
    data["title"] = "Backlinks to " + url.str() + " - TLGS Search";
    data["internal_backlinks"] = internal_backlinks;
    data["external_backlinks"] = external_backlinks;
    auto resp = HttpResponse::newHttpViewResponse("backlinks", data);
    resp->setContentTypeCodeAndCustomString(CT_CUSTOM, "text/gemini");
    co_return resp;
}
