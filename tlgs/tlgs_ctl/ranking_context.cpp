#include "ranking_context.hpp"
#include <chrono>
#include <drogon/drogon.h>
#include <iostream>
#include <nlohmann/json.hpp>
#include <tlgsutils/ranking/context_features.hpp>
#include <unordered_map>

using namespace drogon;

Task<> rebuildRankingContext(bool dry_run, int *exit_status)
{
    struct TermHash
    {
        using is_transparent = void;
        size_t operator()(std::string_view term) const { return std::hash<std::string_view>{}(term); }
    };
    struct TermFrequency
    {
        size_t documents = 0;
        // Deduplicate across fields without allocating a separate set per page.
        size_t last_document = 0;
    };

    std::shared_ptr<orm::Transaction> transaction;
    try
    {
        transaction = co_await app().getDbClient()->newTransactionCoro();
        transaction->setTimeout(-1);
        co_await transaction->execSqlCoro("SET TRANSACTION ISOLATION LEVEL REPEATABLE READ");
        co_await transaction->execSqlCoro("SET LOCAL statement_timeout=0");
        const auto lock =
            co_await transaction->execSqlCoro("SELECT pg_try_advisory_xact_lock(1953261427) AS locked");
        if (!lock[0]["locked"].as<bool>())
            throw std::runtime_error("another ranking context refresh is running");
        const auto state = co_await transaction->execSqlCoro(R"sql(
            SELECT active_ruleset_id, transaction_timestamp()::text AS snapshot_at
            FROM site_identity_state WHERE singleton AND active_ruleset_id IS NOT NULL
        )sql");
        if (state.empty())
            throw std::runtime_error("no active site identity ruleset");
        const auto ruleset = state[0]["active_ruleset_id"].as<int64_t>();
        const auto snapshot = state[0]["snapshot_at"].as<std::string>();
        const auto context_started = std::chrono::steady_clock::now();
        // Keep incoming text in PostgreSQL and stream pages in bounded batches.
        // Each context is [qualifying_text, support, linkers]; linkers are up to 32
        // [site_key, out_hosts, standing] triples for the distinct expert sites behind
        // that text, most selective first:
        //   out_hosts = fewest distinct hosts any of the site's linking pages points to,
        //   standing  = distinct other hosts linking to the site's host.
        // Offline training reads this statement verbatim (between the markers).
        co_await transaction->execSqlCoro(
            // BEGIN ranking_context_build
            R"sql(
            CREATE TEMP TABLE ranking_context_build ON COMMIT DROP AS
            WITH edges AS (
                SELECT target_url, qualifying_text, expert_site, expert_url,
                    lower(split_part(split_part(expert_site,'/',3),':',1)) AS expert_host
                FROM hilltop_edges WHERE ruleset_id=$1 AND qualifying_text<>''
            ), out_hosts AS (
                SELECT l.url, count(DISTINCT lower(l.to_host)) AS hosts
                FROM links l WHERE l.is_cross_site
                  AND l.url IN (SELECT DISTINCT expert_url FROM edges)
                GROUP BY l.url
            ), standing AS (
                SELECT lower(l.to_host) AS host, count(DISTINCT lower(l.host)) AS sites
                FROM links l WHERE l.is_cross_site
                  AND lower(l.to_host) IN (SELECT DISTINCT expert_host FROM edges)
                GROUP BY lower(l.to_host)
            ), site_linkers AS (
                SELECT e.target_url, e.qualifying_text, e.expert_site,
                    min(coalesce(o.hosts,1)) AS out_hosts, max(coalesce(s.sites,0)) AS standing
                FROM edges e
                LEFT JOIN out_hosts o ON o.url=e.expert_url
                LEFT JOIN standing s ON s.host=e.expert_host
                GROUP BY e.target_url,e.qualifying_text,e.expert_site
            ), ordered_linkers AS (
                SELECT *, row_number() OVER (PARTITION BY target_url,qualifying_text
                    ORDER BY out_hosts,standing DESC,expert_site) AS linker_rank
                FROM site_linkers
            ), grouped AS (
                SELECT target_url, qualifying_text, count(*) AS support,
                    jsonb_agg(jsonb_build_array(hashtextextended(expert_site,0),out_hosts,standing)
                              ORDER BY linker_rank) FILTER (WHERE linker_rank<=32) AS linkers
                FROM ordered_linkers GROUP BY target_url,qualifying_text
            ), ranked AS (
                SELECT *, row_number() OVER (
                    PARTITION BY target_url ORDER BY support DESC,qualifying_text) AS rank
                FROM grouped
            )
            SELECT target_url AS url,
                jsonb_agg(jsonb_build_array(qualifying_text,support,linkers)
                          ORDER BY support DESC,qualifying_text) AS contexts,
                string_agg(qualifying_text,E'\n' ORDER BY support DESC,qualifying_text) AS search_text
            FROM ranked WHERE rank<=64 GROUP BY target_url
        )sql"
            // END ranking_context_build
            ,
            ruleset);
        co_await transaction->execSqlCoro("CREATE UNIQUE INDEX ON ranking_context_build(url)");
        const auto context_count =
            co_await transaction->execSqlCoro("SELECT count(*) AS count FROM ranking_context_build");
        const auto destinations = context_count[0]["count"].as<size_t>();
        co_await transaction->execSqlCoro(R"sql(
            DECLARE ranking_pages NO SCROLL CURSOR FOR
            SELECT p.url,CASE WHEN p.has_explicit_title THEN coalesce(p.title,'') ELSE '' END AS title,
                coalesce(p.search_headings,'') AS headings,
                coalesce(p.search_link_text,'') AS link_text,coalesce(p.content_body,'') AS body,
                coalesce(c.search_text,'') AS incoming_text
            FROM pages p LEFT JOIN ranking_context_build c ON c.url=p.url
        )sql");
        const auto scan_started = std::chrono::steady_clock::now();
        double fetch_seconds = 0;
        std::unordered_map<std::string, TermFrequency, TermHash, std::equal_to<>> frequency;
        size_t documents = 0;
        for (;;)
        {
            const auto fetch_started = std::chrono::steady_clock::now();
            const auto pages = co_await transaction->execSqlCoro("FETCH 256 FROM ranking_pages");
            fetch_seconds +=
                std::chrono::duration<double>(std::chrono::steady_clock::now() - fetch_started).count();
            if (pages.empty())
                break;
            for (const auto &page : pages)
            {
                const auto count = [&](std::string_view term)
                {
                    auto entry = frequency.find(term);
                    if (entry == frequency.end())
                        entry = frequency.emplace(term, TermFrequency{}).first;
                    auto &value = entry->second;
                    if (value.last_document != documents + 1)
                    {
                        ++value.documents;
                        value.last_document = documents + 1;
                    }
                };
                for (const auto *column : {"title", "headings", "link_text", "body", "incoming_text"})
                    tlgs::ranking::visit_context_terms(page[column].as<std::string>(), count);
                for (const auto &term : tlgs::ranking::context_url_terms(page["url"].as<std::string>()))
                    count(term);
                ++documents;
            }
            if (documents % 25600 == 0)
                std::cout << "Ranking context: scanned " << documents << " pages\n";
        }
        co_await transaction->execSqlCoro("CLOSE ranking_pages");
        const auto scan_finished = std::chrono::steady_clock::now();
        std::cout << "Ranking context timing: contexts "
                  << std::chrono::duration<double>(scan_started - context_started).count() << "s, scan "
                  << std::chrono::duration<double>(scan_finished - scan_started).count() << "s (fetch "
                  << fetch_seconds << "s)\n";
        if (!documents)
            throw std::runtime_error("cannot build ranking context for an empty corpus");
        if (dry_run)
        {
            transaction->setCommitCallback(
                [documents, terms = frequency.size(), destinations, exit_status](bool committed)
                {
                    if (committed)
                        std::cout << "Ranking context: " << documents << " pages, " << terms << " terms, "
                                  << destinations << " incoming destinations (not applied)\n";
                    else
                    {
                        *exit_status = 1;
                        std::cerr << "Failed to finish ranking context scan\n";
                    }
                    app().quit();
                });
            transaction.reset();
            co_return;
        }
        // A ruleset switched since the snapshot causes a serialization failure
        // here. Hold its row through publication so activation cannot race it.
        const auto active =
            co_await transaction->execSqlCoro("SELECT active_ruleset_id FROM site_identity_state "
                                              "WHERE singleton AND active_ruleset_id=$1 FOR SHARE",
                                              ruleset);
        if (active.empty())
            throw std::runtime_error("site rules changed; retry the refresh");
        co_await transaction->execSqlCoro(R"sql(
            CREATE TABLE IF NOT EXISTS ranking_context_state (
                singleton boolean PRIMARY KEY CHECK(singleton), ruleset_id bigint NOT NULL,
                documents bigint NOT NULL CHECK(documents>0), feature_version integer NOT NULL,
                refreshed_at timestamptz NOT NULL DEFAULT now(),
                snapshot_at timestamptz NOT NULL DEFAULT '-infinity')
        )sql");
        co_await transaction->execSqlCoro(R"sql(
            CREATE TABLE IF NOT EXISTS ranking_term_frequency (
                term text NOT NULL, documents bigint NOT NULL CHECK(documents>=0))
        )sql");
        co_await transaction->execSqlCoro(R"sql(
            CREATE TABLE IF NOT EXISTS ranking_incoming_context (
                url text PRIMARY KEY, contexts jsonb NOT NULL CHECK(jsonb_typeof(contexts)='array'))
        )sql");
        co_await transaction->execSqlCoro(R"sql(
            DO $ddl$ BEGIN
                IF NOT EXISTS (SELECT FROM pg_attribute
                    WHERE attrelid='ranking_context_state'::regclass
                      AND attname='snapshot_at' AND NOT attisdropped) THEN
                    ALTER TABLE ranking_context_state ADD COLUMN snapshot_at
                        timestamptz NOT NULL DEFAULT '-infinity';
                END IF;
            END $ddl$
        )sql");
        const auto newer = co_await transaction->execSqlCoro(
            "SELECT FROM ranking_context_state WHERE singleton AND snapshot_at>$1::timestamptz", snapshot);
        if (!newer.empty())
            throw std::runtime_error("a newer ranking snapshot is already installed");
        co_await transaction->execSqlCoro("DELETE FROM ranking_term_frequency");
        // Tokens can exceed B-tree's index-entry limit. Equality lookups use a
        // hash index instead; the frequency map supplies one row per full term.
        co_await transaction->execSqlCoro("ALTER TABLE ranking_term_frequency "
                                          "DROP CONSTRAINT IF EXISTS ranking_term_frequency_pkey");
        co_await transaction->execSqlCoro("CREATE INDEX IF NOT EXISTS ranking_term_frequency_term_hash "
                                          "ON ranking_term_frequency USING hash(term)");
        co_await transaction->execSqlCoro("DELETE FROM ranking_incoming_context");
        co_await transaction->execSqlCoro("DELETE FROM ranking_context_state");
        nlohmann::json batch = nlohmann::json::array();
        const auto insert = [&]() -> Task<>
        {
            co_await transaction->execSqlCoro(R"sql(
                INSERT INTO ranking_term_frequency(term,documents)
                SELECT term,documents FROM jsonb_to_recordset($1::jsonb)
                    AS f(term text,documents bigint)
            )sql",
                                              batch.dump());
            batch.clear();
        };
        for (const auto &[term, count] : frequency)
        {
            batch.push_back({{"term", term}, {"documents", count.documents}});
            if (batch.size() == 2000)
                co_await insert();
        }
        if (!batch.empty())
            co_await insert();
        co_await transaction->execSqlCoro("INSERT INTO ranking_incoming_context(url,contexts) SELECT "
                                          "url,contexts FROM ranking_context_build");
        // Publish usable planner statistics with the rebuilt cache, rather than
        // waiting for autovacuum while searches can choose full-table scans.
        co_await transaction->execSqlCoro("ANALYZE ranking_term_frequency");
        co_await transaction->execSqlCoro("ANALYZE ranking_incoming_context");
        co_await transaction->execSqlCoro(R"sql(
            INSERT INTO ranking_context_state(singleton,ruleset_id,documents,feature_version,snapshot_at)
            VALUES(TRUE,$1,$2,$3,$4::timestamptz)
        )sql",
                                          ruleset, documents, tlgs::ranking::context_feature_version,
                                          snapshot);
        transaction->setCommitCallback(
            [documents, terms = frequency.size(), destinations, exit_status](bool committed)
            {
                if (committed)
                    std::cout << "Built ranking context: " << documents << " pages, " << terms << " terms, "
                              << destinations << " incoming destinations\n";
                else
                {
                    *exit_status = 1;
                    std::cerr << "Failed to commit ranking context\n";
                }
                app().quit();
            });
        transaction.reset();
    }
    catch (const std::exception &error)
    {
        if (transaction)
            transaction->rollback();
        *exit_status = 1;
        std::cerr << "Cannot rebuild ranking context: " << error.what() << '\n';
        app().quit();
    }
}
