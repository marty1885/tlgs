#include "ranking_context.hpp"
#include <drogon/drogon.h>
#include <iostream>
#include <nlohmann/json.hpp>
#include <tlgsutils/ranking/context_features.hpp>
#include <unordered_map>
#include <unordered_set>

using namespace drogon;

Task<> rebuildRankingContext(bool dry_run, int *exit_status)
{
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
        // Keep incoming text in PostgreSQL and stream pages in bounded batches.
        co_await transaction->execSqlCoro(R"sql(
            CREATE TEMP TABLE ranking_context_build ON COMMIT DROP AS
            WITH grouped AS (
                SELECT target_url, qualifying_text, count(DISTINCT expert_site) AS support
                FROM hilltop_edges WHERE ruleset_id=$1 AND qualifying_text<>''
                GROUP BY target_url,qualifying_text
            ), ranked AS (
                SELECT *, row_number() OVER (
                    PARTITION BY target_url ORDER BY support DESC,qualifying_text) AS rank
                FROM grouped
            )
            SELECT target_url AS url,
                jsonb_agg(jsonb_build_array(qualifying_text,support)
                          ORDER BY support DESC,qualifying_text) AS contexts
            FROM ranked WHERE rank<=64 GROUP BY target_url
        )sql",
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
                coalesce(c.contexts,'[]'::jsonb)::text AS contexts
            FROM pages p LEFT JOIN ranking_context_build c ON c.url=p.url
        )sql");
        std::unordered_map<std::string, size_t> frequency;
        size_t documents = 0;
        for (;;)
        {
            const auto pages = co_await transaction->execSqlCoro("FETCH 256 FROM ranking_pages");
            if (pages.empty())
                break;
            for (const auto &page : pages)
            {
                std::unordered_set<std::string> terms;
                const auto add = [&](const std::string &text)
                {
                    for (auto &term : tlgs::ranking::context_terms(text))
                        terms.insert(std::move(term));
                };
                for (const auto *column : {"title", "headings", "link_text", "body"})
                    add(page[column].as<std::string>());
                for (auto &term : tlgs::ranking::context_url_terms(page["url"].as<std::string>()))
                    terms.insert(std::move(term));
                const auto contexts = nlohmann::json::parse(page["contexts"].as<std::string>());
                for (const auto &context : contexts)
                    add(context.at(0).get<std::string>());
                for (const auto &term : terms)
                    ++frequency[term];
                ++documents;
            }
            if (documents % 25600 == 0)
                std::cout << "Ranking context: scanned " << documents << " pages\n";
        }
        co_await transaction->execSqlCoro("CLOSE ranking_pages");
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
                term text PRIMARY KEY, documents bigint NOT NULL CHECK(documents>=0))
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
            batch.push_back({{"term", term}, {"documents", count}});
            if (batch.size() == 2000)
                co_await insert();
        }
        if (!batch.empty())
            co_await insert();
        co_await transaction->execSqlCoro("INSERT INTO ranking_incoming_context(url,contexts) SELECT "
                                          "url,contexts FROM ranking_context_build");
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
