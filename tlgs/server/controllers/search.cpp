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
#include <ranges>
#include <fmt/core.h>

#include "search_result.hpp"

using namespace drogon;

struct RankedResult
{
    std::string url;
    std::string content_type;
    size_t size;
    uint64_t content_hash;
    float score;
};

struct SearchController : public HttpController<SearchController>
{
public:
    enum class RankingAlgorithm
    {
        HITS,
        SALSA
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


    Task<std::vector<RankedResult>> hitsSearch(const std::string& query_str);
    std::atomic<size_t> search_in_flight{0};
    RankingAlgorithm ranking_algorithm = RankingAlgorithm::HITS;
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
};

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
            if(key == "content_type" || key == "domain" || key == "size")
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
    return {search_query, filter};
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
    for(size_t i = 0; i < node_count; ++i) {
        is_auth[i] = in_neighbous[i].size() > out_neighbous[i].size();
        num_hubs += !is_auth[i];
        num_auths += is_auth[i];
    }
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

    // The SALSA algorithm
    size_t salsa_iter = 0;
    for(salsa_iter=0;salsa_iter<max_iter && score_delta > epsilon;salsa_iter++) {
        for(size_t i=0;i<node_count;i++) {
            if(is_auth[i]) {
                new_score[i] = std::accumulate(in_neighbous[i].begin(), in_neighbous[i].end(), 0.0, [&](double sum, size_t idx) {
                    return sum + 
                        std::accumulate(out_neighbous[idx].begin(), out_neighbous[idx].end(), 0.0, [&](double sum, size_t idx2) {
                            return sum + score[idx2] / std::max(in_neighbous[idx2].size(), size_t{1});
                        }) / std::max(out_neighbous[idx].size(), size_t{1});
                });
            }
            else {
                new_score[i] = std::accumulate(out_neighbous[i].begin(), out_neighbous[i].end(), 0.0, [&](double sum, size_t idx) {
                    return sum + 
                        std::accumulate(in_neighbous[idx].begin(), in_neighbous[idx].end(), 0.0, [&](double sum, size_t idx2) {
                            return sum + score[idx2] / std::max(out_neighbous[idx2].size(), size_t{1});
                        }) / std::max(in_neighbous[idx].size(), size_t{1});;
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

SearchController::SearchController()
{
    auto tlgs = app().getCustomConfig()["tlgs"];
    if(tlgs.isNull())
        return;

    auto ranking_algo = tlgs["ranking_algo"];
    if(!ranking_algo.isNull()) {
        auto algo = ranking_algo.asString();
        if(algo == "hits")
            ranking_algorithm = RankingAlgorithm::HITS;
        else if(algo == "salsa")
            ranking_algorithm = RankingAlgorithm::SALSA;
        else {
            LOG_WARN << "Unknown ranking algorithm: " << algo << ", use HITS instead";
            ranking_algorithm = RankingAlgorithm::HITS;
        }
    }
}

// Search with scoring using the HITS algorithm
Task<std::vector<RankedResult>> SearchController::hitsSearch(const std::string& query_str)
{
    auto db = app().getDbClient();
    auto nodes_of_intrest = co_await db->execSqlCoro("SELECT url as source_url, cross_site_links, content_type, size, "
        "indexed_content_hash AS content_hash, ts_rank_cd(pages.title_vector, "
        "plainto_tsquery($1))*50+ts_rank_cd(pages.search_vector, plainto_tsquery($1)) AS rank "
        "FROM pages WHERE pages.search_vector @@ plainto_tsquery($1) "
        "ORDER BY rank DESC LIMIT 50000;", query_str);
    auto links_to_node = co_await db->execSqlCoro("SELECT links.to_url AS dest_url, links.url AS source_url, content_type, size, "
        "indexed_content_hash AS content_hash, 0 AS rank FROM pages JOIN links ON pages.url=links.to_url "
        "WHERE links.is_cross_site = TRUE AND pages.search_vector @@ plainto_tsquery($1)"
        , query_str);
    if(nodes_of_intrest.size() == 0) {
        LOG_DEBUG << "DB returned no root set";
        co_return {};
    }

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

    std::vector<std::vector<size_t>> out_neighbous;
    std::vector<std::vector<size_t>> in_neighbous;
    out_neighbous.resize(nodes.size());
    in_neighbous.resize(nodes.size());

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
    // Combine the text score and the rank score. Really want to use BM25 as text score
    // XXX: This scoring function works. But it kinda sucks
    for(size_t i=0;i<nodes.size();i++) {
        auto& node = nodes[i];
        float boost = exp((score[i] / max_score)*6.5);
        float rank = text_rank[i];
        // discourage pages too large
        const size_t discourage_size = 48*1000; // 48KB
        if(node.size > discourage_size)
            rank *= 1/log(std::numbers::e+(node.size - discourage_size)/(1000*3));
        node.score = 2*(boost * rank) / (boost + rank);
    }

    // Deduplicate the search results using URL and hash. Currently it merges the results if the hash is the same
    // and one of the following is true:
    // 1. The two pages lives on the same host
    // 2. The two pages have the same path
    // 3. We can replace /~ with /users or /user and resulting URL is the same
    //
    // It works by storing using the hash as the key and looks up other nodes with the same hash. Then decide if 
    // we should merge or not.
    std::unordered_multimap<uint64_t,const RankedResult*> result_map;
    result_map.reserve(nodes.size());
    std::string buf(8, '\0');
    drogon::utils::secureRandomBytes(buf.data(), buf.size());
    std::string token = "/"+drogon::utils::binaryStringToHex((unsigned char*)buf.data(), buf.size());
    size_t num_root = 0;
    for(size_t i=0;i<nodes.size();i++) {
        auto& node = nodes[i];
        if(is_root[i] == false)
            continue;
        num_root++;
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
        std::string str = node.url;
        drogon::utils::replaceAll(str, "/~", token);
        drogon::utils::replaceAll(str, "/users", token);
        drogon::utils::replaceAll(str, "/user", token);
        bool replaced = false;
        for(auto& [_, stored] : std::ranges::subrange(begin, end)) {
            tlgs::Url stored_url(stored->url);
            stored_url.withHost(to_lower(stored_url.host()));
            std::string str2 = stored->url;
            drogon::utils::replaceAll(str2, "/~", token);
            drogon::utils::replaceAll(str2, "/users", token);
            drogon::utils::replaceAll(str2, "/user", token);

            if(node_url.host() == stored_url.host() ||
                node_url.path() == stored_url.path() ||
                stored->url.ends_with(node_url.host()+node_url.path()) ||
                str == str2) {
                if(stored->score < node.score)
                    stored = &node;
                replaced = true;
                break;
            }

            // Anti-spam/takeover protection. There are some archives on Geminispace. Commonly with the
            // URL gemini://example.com/<hostname>/<path....>/<filename> This prevents replacing the real
            // capsure link with the mirror/archive
            if(node.url.ends_with(stored_url.host()+stored_url.path())) {
                replaced = true;
                break;
            }
        }
        
        if(replaced == false)
            result_map.emplace(node.content_hash, &node);
    }
    LOG_DEBUG << "Deduplication removed " << num_root - result_map.size() << " results for search term `" << query_str <<"`";

    std::vector<RankedResult> search_result;
    search_result.reserve(result_map.size());
    for(auto& [_, item] : result_map)
        search_result.emplace_back(std::move(*item));

    std::sort(search_result.begin(), search_result.end(), [](const auto& a, const auto& b) {
        return a.score > b.score;
    });
    co_return search_result;
}

bool evalFilter(const std::string_view host, const std::string_view content_type, size_t size, const SearchFilter& filter)
{
    if(size == 0 && filter.size.size() != 0)
        return false;
    
    auto size_it = std::find_if(filter.size.begin(), filter.size.end(), [size](const auto& size_constrant){
        if(size_constrant.greater)
            return size > size_constrant.size;
        else
            return size < size_constrant.size;
    });
    if(!filter.size.empty() && size_it == filter.size.end())
        return false;
    
    auto domain_it = std::find_if(filter.domain.begin(), filter.domain.end(), [host](const auto& domain_constrant){
        return domain_constrant.negate ^ (host == domain_constrant.value);
    });
    if(!filter.domain.empty() && domain_it == filter.domain.end())
        return false;
    
    auto content_it = std::find_if(filter.content_type.begin(), filter.content_type.end(), [content_type](const auto& content_constrant){
        return content_constrant.negate ^ (content_type != "" && content_type.starts_with(content_constrant.value));
    });
    if(!filter.content_type.empty() && content_it == filter.content_type.end())
        return false;
    
    return true;
}

Task<HttpResponsePtr> SearchController::tlgs_search(HttpRequestPtr req)
{
    using namespace std::chrono;
    auto t1 = high_resolution_clock::now();
    // Prevent too many search requests piling up
    tlgs::Counter counter(search_in_flight);
    if(counter.count() > 120) {
        auto resp = HttpResponse::newHttpResponse();
        resp->addHeader("meta", "SlowDown");
        resp->setStatusCode((HttpStatusCode)44);
        co_return resp;
    }

    auto input = utils::urlDecode(req->getParameter("query"));
    auto [query_str, filter] = parseSearchQuery(input);
    std::transform(query_str.begin(), query_str.end(), query_str.begin(), ::tolower);

    if(query_str.empty())
    {
        auto resp = HttpResponse::newHttpResponse();
        resp->addHeader("meta", "Search for something");
        resp->setStatusCode((HttpStatusCode)10);
        co_return resp;
    }

    using RankedResults = std::vector<RankedResult>;

    static CacheMap<std::string, std::shared_ptr<RankedResults>> result_cache(app().getLoop(), 60);
    const static std::regex re(R"((?:\/v)?\/search\/([0-9]+))");
    std::smatch match;
    size_t current_page_idx = 0;
    if(std::regex_match(req->path(), match, re)) {
        std::string page_string = match[1];
        if(!page_string.empty()) {
            current_page_idx = std::stoull(page_string)-1;
        }
    }

    std::shared_ptr<RankedResults> ranked_result;
    bool cached = true;
    if(result_cache.findAndFetch(query_str, ranked_result) == false) {
        std::vector<RankedResult> result;
        result = co_await hitsSearch(query_str);
        ranked_result = std::make_shared<RankedResults>(std::move(result));
        result_cache.insert(query_str, ranked_result, 600);
        cached = false;
    }
    if(ranked_result == nullptr)
        throw std::runtime_error("search result is nullptr");
    // TODO: Maybe cache filtered results?
    std::shared_ptr<RankedResults> filtered_result = ranked_result;
    if(filter.content_type.size() != 0
        || filter.size.size() != 0
        || filter.domain.size() != 0) {
        filtered_result = std::make_shared<RankedResults>();
        for(const auto& item : *ranked_result) {
            if(evalFilter(tlgs::Url(item.url).host(), item.content_type, item.size, filter))
                filtered_result->push_back(item);
        }
    }
    size_t total_results = filtered_result->size();

    const size_t item_per_page = 10;
    auto begin = filtered_result->begin()+item_per_page*current_page_idx;
    auto end = filtered_result->begin()+std::min(item_per_page*(current_page_idx+1), filtered_result->size());
    if(begin > end)
        begin = end;
    // XXX: Drogon's raw SQL querys does not support arrays/sets 
    // Preperbally a bad idea to use string concat for SQL. But we do ignore bad strings
    std::string url_array;
    for(const auto& item : std::ranges::subrange(begin, end)) {
        if(item.url.find('\'') == std::string::npos)
            url_array += "'"+item.url+"', ";
    }
    if(url_array.size() != 0)
        url_array.resize(url_array.size()-2);

    std::vector<SearchResult> search_result;
    if(!url_array.empty()) {
        // HACK: Use the first 5K characters for highligh search. This is MUCH faster
        // without loosing too much accuracy
        auto db = app().getDbClient();
        auto page_data = co_await db->execSqlCoro("SELECT url, size, title, content_type, "
            "ts_headline(SUBSTRING(content_body, 0, 5000), plainto_tsquery($1), 'StartSel=\"\", "
                "StopSel=\"\", MinWords=23, MaxWords=37, MaxFragments=1, FragmentDelimiter=\" ... \"') AS preview, "
            "last_crawl_success_at FROM pages WHERE url IN ("+url_array+");", query_str);

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
                    .toCustomedFormattedString("%Y-%m-%d %H:%M:%S", false),
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
    data["total_results"] = total_results;
    data["current_page_idx"] = current_page_idx;
    data["item_per_page"] = item_per_page;
    data["search_query"] = input; 

    auto resp = HttpResponse::newHttpViewResponse("search_result", data);
    resp->setContentTypeCodeAndCustomString(CT_CUSTOM, "text/gemini");

    auto t2 = high_resolution_clock::now();
    double processing_time = duration_cast<duration<double>>(t2 - t1).count();
    LOG_DEBUG << fmt::format("Searching for '{}' took {} {} seconds."
        , input, (cached?"(cached) ":""), processing_time);
    co_return resp;
}

Task<HttpResponsePtr> SearchController::jump_search(HttpRequestPtr req, std::string search_term)
{
    auto input = utils::urlDecode(req->getParameter("query"));
    bool conversion_fail = false;
    size_t page = 0;
    try {
        if(!input.empty())
            page = std::stoull(input);
    }
    catch(...) {
        conversion_fail = true;
    }

    if(input.empty() || conversion_fail) {
        auto resp = HttpResponse::newHttpResponse();
        resp->addHeader("meta", "Go to page");
        resp->setStatusCode((HttpStatusCode)10);
        co_return resp;
    }

    bool verbose = req->path().starts_with("/v");
    std::string search_path = verbose ? "/v/search" : "/search";

    auto resp = HttpResponse::newHttpResponse();
    if(page != 1)
        resp->addHeader("meta", search_path+"/"+std::to_string(page)+"?"+search_term);
    else
        resp->addHeader("meta", search_path+"?"+search_term);
    resp->setStatusCode((HttpStatusCode)30);
    co_return resp;
}

Task<HttpResponsePtr> SearchController::backlinks(HttpRequestPtr req)
{
    auto input = utils::urlDecode(req->getParameter("query"));
    bool input_is_good = false;
    tlgs::Url url(input);
    if(!input.empty()) {
        input_is_good = url.good();
        if(!input_is_good) {
            url = tlgs::Url("gemini://"+input);
            input_is_good = url.good();
        }
    }

    if(!input_is_good) {
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
