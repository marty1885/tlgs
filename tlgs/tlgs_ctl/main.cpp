#include <drogon/drogon.h>
#include <drogon/utils/coroutine.h>
#include <tlgsutils/site_identity.hpp>
#include <nlohmann/json.hpp>
using namespace drogon;

#include <algorithm>
#include <chrono>
#include <cmath>
#include <filesystem>
#include <iomanip>
#include <iostream>
#include <memory>
#include <numeric>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "CLI/App.hpp"
#include "CLI/Formatter.hpp"
#include "CLI/Config.hpp"

Task<> createDb()
{
	auto db = app().getDbClient();
	co_await db->execSqlCoro(R"(
		CREATE TABLE IF NOT EXISTS public.pages (
			url text NOT NULL,
			domain_name text NOT NULL,
			port integer NOT NULL,
			content_type text,
			charset text,
			lang text,
			title text,
			content_body text,
			feed_type TEXT,
			size bigint DEFAULT 0 NOT NULL,
			last_indexed_at timestamp without time zone,
			last_crawled_at timestamp without time zone,
			last_crawl_success_at timestamp without time zone,
			last_status integer,
			last_meta text,
			first_seen_at timestamp without time zone NOT NULL,
			search_vector tsvector,
			cross_site_links json,
			internal_links json,
			title_vector tsvector,
			english_search_vector tsvector,
			has_explicit_title boolean NOT NULL DEFAULT false,
			search_headings text NOT NULL DEFAULT '',
			search_link_text text NOT NULL DEFAULT '',
			search_schema_version smallint NOT NULL DEFAULT 0,
			last_queued_at timestamp without time zone,
			indexed_content_hash text NOT NULL default '',
			raw_content_hash text NOT NULL default '',
			PRIMARY KEY (url)
		);
	)");
	co_await db->execSqlCoro("CREATE INDEX IF NOT EXISTS last_crawled_index ON public.pages USING btree (last_crawled_at DESC);");
	co_await db->execSqlCoro("ALTER TABLE public.pages ADD COLUMN IF NOT EXISTS english_search_vector tsvector;");
	co_await db->execSqlCoro("ALTER TABLE public.pages ADD COLUMN IF NOT EXISTS feed_type text;");
	co_await db->execSqlCoro("ALTER TABLE public.pages ADD COLUMN IF NOT EXISTS has_explicit_title boolean NOT NULL DEFAULT false;");
	co_await db->execSqlCoro("ALTER TABLE public.pages ADD COLUMN IF NOT EXISTS search_headings text NOT NULL DEFAULT '';");
	co_await db->execSqlCoro("ALTER TABLE public.pages ADD COLUMN IF NOT EXISTS search_link_text text NOT NULL DEFAULT '';");
	co_await db->execSqlCoro("ALTER TABLE public.pages ADD COLUMN IF NOT EXISTS search_schema_version smallint NOT NULL DEFAULT 0;");
	co_await db->execSqlCoro("CREATE INDEX IF NOT EXISTS search_vector_index ON public.pages USING gin (search_vector);");
	co_await db->execSqlCoro("CREATE INDEX IF NOT EXISTS english_search_vector_index ON public.pages USING gin (english_search_vector);");
	co_await db->execSqlCoro(R"sql(
		CREATE OR REPLACE FUNCTION public.tlgs_bounded_search_vector(
			config regconfig,
			title_text text,
			headings_text text,
			url_text text,
			link_text text,
			body_text text,
			reduced_headings text,
			reduced_link_text text,
			reduced_body text,
			minimal_headings text,
			minimal_link_text text,
			minimal_body text
		) RETURNS tsvector
		LANGUAGE plpgsql IMMUTABLE PARALLEL SAFE AS $$
		DECLARE
			result tsvector;
		BEGIN
			result :=
				setweight(to_tsvector(config, coalesce(title_text, '')), 'A') ||
				setweight(to_tsvector(config, coalesce(headings_text, '')), 'B') ||
				setweight(to_tsvector(config, coalesce(url_text, '') || ' ' || coalesce(link_text, '')), 'C') ||
				setweight(to_tsvector(config, coalesce(body_text, '')), 'D');
			IF pg_column_size(result) <= 49152 THEN
				RETURN result;
			END IF;

			result :=
				setweight(to_tsvector(config, coalesce(title_text, '')), 'A') ||
				setweight(to_tsvector(config, coalesce(reduced_headings, '')), 'B') ||
				setweight(to_tsvector(config, coalesce(url_text, '') || ' ' || coalesce(reduced_link_text, '')), 'C') ||
				setweight(to_tsvector(config, coalesce(reduced_body, '')), 'D');
			IF pg_column_size(result) <= 49152 THEN
				RETURN result;
			END IF;

			result :=
				setweight(to_tsvector(config, coalesce(title_text, '')), 'A') ||
				setweight(to_tsvector(config, coalesce(minimal_headings, '')), 'B') ||
				setweight(to_tsvector(config, coalesce(url_text, '') || ' ' || coalesce(minimal_link_text, '')), 'C') ||
				setweight(to_tsvector(config, coalesce(minimal_body, '')), 'D');
			IF pg_column_size(result) <= 49152 THEN
				RETURN result;
			END IF;

			-- The title and normalized URL are independently bounded by the crawler.
			RETURN
				setweight(to_tsvector(config, coalesce(title_text, '')), 'A') ||
				setweight(to_tsvector(config, coalesce(url_text, '')), 'C');
		END;
		$$
	)sql");
	co_await db->execSqlCoro(R"sql(
		DO $$
		BEGIN
			IF NOT EXISTS (
				SELECT 1 FROM pg_constraint
				WHERE conrelid='public.pages'::regclass
				  AND conname='pages_search_vector_size'
			) THEN
				ALTER TABLE public.pages ADD CONSTRAINT pages_search_vector_size
					CHECK (search_vector IS NULL OR pg_column_size(search_vector) <= 49152)
					NOT VALID;
			END IF;
			IF NOT EXISTS (
				SELECT 1 FROM pg_constraint
				WHERE conrelid='public.pages'::regclass
				  AND conname='pages_english_search_vector_size'
			) THEN
				ALTER TABLE public.pages ADD CONSTRAINT pages_english_search_vector_size
					CHECK (english_search_vector IS NULL OR pg_column_size(english_search_vector) <= 49152)
					NOT VALID;
			END IF;
		END
		$$
	)sql");

	co_await db->execSqlCoro(R"(
		CREATE TABLE IF NOT EXISTS public.links (
			url text NOT NULL,
			host text NOT NULL,
			port integer NOT NULL,
			to_url text NOT NULL,
			to_host text NOT NULL,
			to_port integer NOT NULL,
			is_cross_site boolean NOT NULL,
			qualifying_text text NOT NULL DEFAULT '',
			qualifying_vector tsvector
		);
	)");
	co_await db->execSqlCoro("ALTER TABLE public.links ADD COLUMN IF NOT EXISTS qualifying_text text NOT NULL DEFAULT ''; ");
	co_await db->execSqlCoro("ALTER TABLE public.links ADD COLUMN IF NOT EXISTS qualifying_vector tsvector;");
	co_await db->execSqlCoro("CREATE INDEX IF NOT EXISTS is_cross_site_index ON public.links USING btree (is_cross_site);");
	co_await db->execSqlCoro("CREATE INDEX IF NOT EXISTS source_url_index ON public.links USING btree (url);");
	co_await db->execSqlCoro("CREATE INDEX IF NOT EXISTS to_url_index ON public.links USING btree (to_url);");
	co_await db->execSqlCoro("CREATE INDEX IF NOT EXISTS links_qualifying_vector_idx ON public.links USING gin (qualifying_vector);");

	co_await db->execSqlCoro(R"(
		CREATE TABLE IF NOT EXISTS public.robot_policies (
			host text NOT NULL,
			port integer NOT NULL,
			disallowed text NOT NULL
		);
	)");
	co_await db->execSqlCoro("CREATE INDEX IF NOT EXISTS host_port_index ON public.robot_policies USING btree (host, port);");

	co_await db->execSqlCoro(R"(
		CREATE TABLE IF NOT EXISTS public.robot_policies_status (
			host text NOT NULL,
			port integer NOT NULL,
			last_crawled_at timestamp without time zone NOT NULL,
			have_policy boolean NOT NULL,
			PRIMARY KEY (host, port)
		);
	)");

	co_await db->execSqlCoro(R"(
		CREATE TABLE IF NOT EXISTS public.perma_redirects (
			from_url text NOT NULL,
			to_url text NOT NULL,
			PRIMARY KEY (from_url)
		);
	)");
	co_await db->execSqlCoro(R"(
		CREATE INDEX IF NOT EXISTS pages_crawl_queue_idx ON pages (last_queued_at, last_crawled_at) WHERE last_crawled_at IS NULL OR last_queued_at IS NULL;
	)");

	co_await db->execSqlCoro(R"(
		CREATE TABLE IF NOT EXISTS public.site_identity_rulesets (
			id bigserial PRIMARY KEY,
			rules_hash text NOT NULL,
			rules_toml text NOT NULL,
			created_at timestamp without time zone NOT NULL DEFAULT CURRENT_TIMESTAMP,
			activated_at timestamp without time zone
		);
	)");
	co_await db->execSqlCoro("CREATE INDEX IF NOT EXISTS site_identity_rulesets_hash_idx ON site_identity_rulesets(rules_hash);");
	co_await db->execSqlCoro(R"(
		CREATE TABLE IF NOT EXISTS public.site_identity_state (
			singleton boolean PRIMARY KEY DEFAULT TRUE CHECK (singleton),
			active_ruleset_id bigint REFERENCES site_identity_rulesets(id)
		);
	)");
	co_await db->execSqlCoro("INSERT INTO site_identity_state(singleton) VALUES(TRUE) ON CONFLICT(singleton) DO NOTHING;");
	co_await db->execSqlCoro(R"(
		CREATE TABLE IF NOT EXISTS public.url_site_map (
			ruleset_id bigint NOT NULL REFERENCES site_identity_rulesets(id) ON DELETE CASCADE,
			url text NOT NULL,
			site_key text NOT NULL,
			matched_rule text,
			PRIMARY KEY (ruleset_id, url)
		);
	)");
	co_await db->execSqlCoro("CREATE INDEX IF NOT EXISTS url_site_map_site_idx ON url_site_map(ruleset_id, site_key);");

	co_await db->execSqlCoro(R"(
		CREATE TABLE IF NOT EXISTS public.hilltop_edges (
			ruleset_id bigint NOT NULL REFERENCES site_identity_rulesets(id) ON DELETE CASCADE,
			expert_url text NOT NULL,
			expert_site text NOT NULL,
			target_url text NOT NULL,
			target_site text NOT NULL,
			qualifying_text text NOT NULL,
			qualifying_vector tsvector NOT NULL,
			PRIMARY KEY (ruleset_id, expert_url, target_url)
		);
	)");
	co_await db->execSqlCoro("CREATE INDEX IF NOT EXISTS hilltop_edges_qualifier_idx ON hilltop_edges USING gin (qualifying_vector);");
	co_await db->execSqlCoro("CREATE INDEX IF NOT EXISTS hilltop_edges_target_idx ON hilltop_edges(ruleset_id, target_url);");
	co_await db->execSqlCoro("CREATE INDEX IF NOT EXISTS hilltop_edges_expert_idx ON hilltop_edges(ruleset_id, expert_url);");
	app().quit();
}

Task<> purgePage(std::string url)
{
	auto db = app().getDbClient();
	auto page = co_await db->execSqlCoro("DELETE FROM pages WHERE url like $1;", url);
	co_await db->execSqlCoro("DELETE FROM links WHERE url like $1;", url);
	co_await db->execSqlCoro("DELETE FROM links WHERE to_url like $1;", url);
	std::cout << "Deleted " << page.affectedRows() << " pages from index" << std::endl;
	app().quit();
}

Task<> indexStatus()
{
	auto db = app().getDbClient();
	auto domain_pages = co_await db->execSqlCoro("SELECT COUNT(DISTINCT LOWER(domain_name)) AS domain_count, COUNT(*) AS count "
		"FROM pages WHERE content_body IS NOT NULL");
	auto pages_need_update = co_await db->execSqlCoro("SELECT COUNT(*) AS count FROM pages WHERE "
		"last_crawled_at < CURRENT_TIMESTAMP - INTERVAL '3' DAY OR last_crawled_at IS NULL");
	std::cout << domain_pages[0]["domain_count"].as<size_t>() << " domains in index\n";
	std::cout << domain_pages[0]["count"].as<size_t>() << " pages in index\n";
	std::cout << pages_need_update[0]["count"].as<size_t>() << " pages need update\n";
	app().quit();
}

namespace
{

constexpr size_t identity_batch_size = 5000;

const char* siteIdentityCursorSql = R"sql(
DECLARE site_identity_urls NO SCROLL CURSOR FOR
WITH all_urls AS MATERIALIZED (
    SELECT url FROM pages
    UNION
    SELECT url FROM links
    UNION
    SELECT to_url AS url FROM links
)
SELECT all_urls.url, url_site_map.site_key
FROM all_urls
LEFT JOIN site_identity_state ON site_identity_state.singleton = TRUE
LEFT JOIN url_site_map
  ON url_site_map.ruleset_id = site_identity_state.active_ruleset_id
 AND url_site_map.url = all_urls.url
ORDER BY all_urls.url
)sql";

const char* allSiteIdentityUrlsCursorSql = R"sql(
DECLARE site_identity_urls NO SCROLL CURSOR FOR
SELECT url FROM (
    SELECT url FROM pages
    UNION
    SELECT url FROM links
    UNION
    SELECT to_url AS url FROM links
) AS all_urls
ORDER BY url
)sql";

const char* missingSiteIdentityCursorSql = R"sql(
DECLARE site_identity_urls NO SCROLL CURSOR FOR
WITH all_urls AS MATERIALIZED (
    SELECT url FROM pages
    UNION
    SELECT url FROM links
    UNION
    SELECT to_url AS url FROM links
)
SELECT all_urls.url
FROM all_urls
JOIN site_identity_state ON site_identity_state.singleton = TRUE
LEFT JOIN url_site_map
  ON url_site_map.ruleset_id = site_identity_state.active_ruleset_id
 AND url_site_map.url = all_urls.url
WHERE url_site_map.url IS NULL
ORDER BY all_urls.url
)sql";

std::string jsonRows(const Json::Value& rows)
{
    Json::StreamWriterBuilder writer;
    writer["indentation"] = "";
    return Json::writeString(writer, rows);
}

Task<> planSiteRules(std::shared_ptr<const tlgs::SiteIdentityRules> rules)
{
    std::shared_ptr<orm::Transaction> transaction;
    try {
        auto db = app().getDbClient();
        transaction = co_await db->newTransactionCoro();
        transaction->setTimeout(-1);
        co_await transaction->execSqlCoro(siteIdentityCursorSql);

        size_t total = 0;
        size_t changed = 0;
        size_t unmapped = 0;
        size_t invalid = 0;
        std::unordered_set<std::string> old_sites;
        std::unordered_set<std::string> new_sites;
        std::unordered_map<std::string, std::unordered_set<std::string>> old_to_new;
        std::unordered_map<std::string, std::unordered_set<std::string>> new_to_old;
        std::unordered_map<std::string, size_t> rule_matches;
        std::vector<std::string> examples;

        while(true) {
            const auto batch = co_await transaction->execSqlCoro("FETCH FORWARD 5000 FROM site_identity_urls");
            if(batch.empty())
                break;
            for(const auto& row : batch) {
                ++total;
                const auto url = row["url"].as<std::string>();
                try {
                    const auto identity = rules->classify(url);
                    const auto old_key = row["site_key"].isNull() ? std::string{} : row["site_key"].as<std::string>();
                    if(old_key.empty())
                        ++unmapped;
                    else {
                        old_sites.emplace(old_key);
                        old_to_new[old_key].emplace(identity.site_key);
                        new_to_old[identity.site_key].emplace(old_key);
                    }
                    new_sites.emplace(identity.site_key);
                    rule_matches[identity.matched_rule.empty() ? "<origin fallback>" : identity.matched_rule]++;
                    if(old_key != identity.site_key) {
                        ++changed;
                        if(examples.size() < 20)
                            examples.push_back((old_key.empty() ? "<unmapped>" : old_key) + " -> " +
                                               identity.site_key + "  [" + url + "]");
                    }
                }
                catch(const std::exception& error) {
                    ++invalid;
                    if(examples.size() < 20)
                        examples.push_back(std::string("ERROR: ") + error.what());
                }
            }
        }

        size_t splits = 0;
        size_t merges = 0;
        for(const auto& [_, sites] : old_to_new)
            splits += sites.size() > 1;
        for(const auto& [_, sites] : new_to_old)
            merges += sites.size() > 1;

        std::cout << "Rules hash: " << rules->hash() << '\n'
                  << "URLs: " << total << '\n'
                  << "Changed mappings: " << changed << '\n'
                  << "Currently unmapped: " << unmapped << '\n'
                  << "Invalid/oversized URLs: " << invalid << '\n'
                  << "Current logical sites: " << old_sites.size() << '\n'
                  << "Proposed logical sites: " << new_sites.size() << '\n'
                  << "Sites split: " << splits << '\n'
                  << "Sites merged: " << merges << "\n\nRule matches:\n";
        std::vector<std::pair<std::string, size_t>> matches(rule_matches.begin(), rule_matches.end());
        std::ranges::sort(matches, {}, &std::pair<std::string, size_t>::second);
        for(auto it = matches.rbegin(); it != matches.rend(); ++it)
            std::cout << "  " << it->first << ": " << it->second << '\n';
        if(!examples.empty()) {
            std::cout << "\nExamples:\n";
            for(const auto& example : examples)
                std::cout << "  " << example << '\n';
        }
        transaction->rollback();
    }
    catch(const std::exception& error) {
        if(transaction)
            transaction->rollback();
        std::cerr << "Cannot plan site identity rules: " << error.what() << '\n';
    }
    app().quit();
}

Task<> applySiteRules(std::shared_ptr<const tlgs::SiteIdentityRules> rules)
{
    std::shared_ptr<orm::Transaction> transaction;
    try {
        auto db = app().getDbClient();
        transaction = co_await db->newTransactionCoro();
        transaction->setTimeout(-1);

        const auto inserted = co_await transaction->execSqlCoro(
            "INSERT INTO site_identity_rulesets(rules_hash, rules_toml) VALUES($1, $2) RETURNING id",
            rules->hash(), rules->sourceToml());
        const auto ruleset_id = inserted[0]["id"].as<int64_t>();
        co_await transaction->execSqlCoro(allSiteIdentityUrlsCursorSql);

        size_t total = 0;
        while(true) {
            const auto urls = co_await transaction->execSqlCoro("FETCH FORWARD 5000 FROM site_identity_urls");
            if(urls.empty())
                break;

            Json::Value rows(Json::arrayValue);
            for(const auto& url_row : urls) {
                const auto url = url_row["url"].as<std::string>();
                const auto identity = rules->classify(url);
                Json::Value row;
                row["url"] = url;
                row["site_key"] = identity.site_key;
                row["matched_rule"] = identity.matched_rule;
                rows.append(std::move(row));
            }
            co_await transaction->execSqlCoro(R"sql(
                INSERT INTO url_site_map(ruleset_id, url, site_key, matched_rule)
                SELECT $1, row.url, row.site_key, NULLIF(row.matched_rule, '')
                FROM jsonb_to_recordset($2::jsonb)
                  AS row(url text, site_key text, matched_rule text)
            )sql", ruleset_id, jsonRows(rows));
            total += urls.size();
            if(total % 50000 < identity_batch_size)
                std::cout << "Classified " << total << " URLs\n";
        }

        const auto mapped = co_await transaction->execSqlCoro(
            "SELECT count(*) AS count FROM url_site_map WHERE ruleset_id=$1", ruleset_id);
        const auto mapped_count = mapped[0]["count"].as<size_t>();
        if(mapped_count != total)
            throw std::runtime_error("mapping row count mismatch: expected " + std::to_string(total) +
                                     ", got " + std::to_string(mapped_count));

        co_await transaction->execSqlCoro(R"sql(
            WITH activated AS (
                UPDATE site_identity_rulesets
                SET activated_at=CURRENT_TIMESTAMP
                WHERE id=$1
                RETURNING id
            )
            INSERT INTO site_identity_state(singleton, active_ruleset_id)
            SELECT TRUE, id FROM activated
            ON CONFLICT(singleton) DO UPDATE
            SET active_ruleset_id=EXCLUDED.active_ruleset_id
        )sql", ruleset_id);

        transaction->setCommitCallback([ruleset_id, total](bool committed) {
            if(committed)
                std::cout << "Activated site identity ruleset " << ruleset_id
                          << " with " << total << " URL mappings\n";
            else
                std::cerr << "Failed to commit site identity ruleset " << ruleset_id << '\n';
            app().quit();
        });
        transaction.reset();
        co_return;
    }
    catch(const std::exception& error) {
        if(transaction)
            transaction->rollback();
        std::cerr << "Cannot apply site identity rules: " << error.what() << '\n';
        app().quit();
    }
}

Task<> siteRulesStatus()
{
    try {
        const auto rows = co_await app().getDbClient()->execSqlCoro(R"sql(
            SELECT rulesets.id, rulesets.rules_hash, rulesets.rules_toml, rulesets.created_at,
                   rulesets.activated_at, count(mapping.url) AS mappings,
                   COALESCE(rulesets.id=state.active_ruleset_id, FALSE) AS active
            FROM site_identity_rulesets rulesets
            LEFT JOIN url_site_map mapping ON mapping.ruleset_id=rulesets.id
            LEFT JOIN site_identity_state state ON state.singleton=TRUE
            GROUP BY rulesets.id, state.active_ruleset_id
            ORDER BY rulesets.id DESC
        )sql");
        if(rows.empty())
            std::cout << "No site identity rulesets have been applied\n";
        bool printed_history_header = false;
        for(const auto& row : rows) {
            if(row["active"].as<bool>()) {
                std::cout << "Active site identity ruleset " << row["id"].as<int64_t>() << '\n'
                          << "Mappings: " << row["mappings"].as<size_t>() << '\n'
                          << "Created: " << row["created_at"].as<std::string>() << '\n'
                          << "Hash: " << row["rules_hash"].as<std::string>() << "\n\n"
                          << row["rules_toml"].as<std::string>();
                if(!row["rules_toml"].as<std::string>().ends_with('\n'))
                    std::cout << '\n';
                continue;
            }
            if(!printed_history_header) {
                std::cout << "\nInactive rulesets available for rollback:\n";
                printed_history_header = true;
            }
            std::cout << "  " << row["id"].as<int64_t>() << "  "
                      << row["mappings"].as<size_t>() << " mappings  created "
                      << row["created_at"].as<std::string>() << '\n';
        }
    }
    catch(const std::exception& error) {
        std::cerr << "Cannot read site identity status: " << error.what() << '\n';
    }
    app().quit();
}

Task<> syncSiteRules()
{
    std::shared_ptr<orm::Transaction> transaction;
    try {
        auto db = app().getDbClient();
        transaction = co_await db->newTransactionCoro();
        transaction->setTimeout(-1);
        const auto active = co_await transaction->execSqlCoro(R"sql(
            SELECT rulesets.id, rulesets.rules_toml
            FROM site_identity_state state
            JOIN site_identity_rulesets rulesets ON rulesets.id=state.active_ruleset_id
            WHERE state.singleton=TRUE
            FOR SHARE OF state, rulesets
        )sql");
        if(active.empty())
            throw std::runtime_error("no active site identity ruleset");

        const auto ruleset_id = active[0]["id"].as<int64_t>();
        const auto source = active[0]["rules_toml"].as<std::string>();
        const auto rules = tlgs::SiteIdentityRules::fromToml(
            toml::parse_str(source, toml::spec::v(1, 0, 0)), source);
        co_await transaction->execSqlCoro(missingSiteIdentityCursorSql);

        size_t total = 0;
        while(true) {
            const auto urls = co_await transaction->execSqlCoro("FETCH FORWARD 5000 FROM site_identity_urls");
            if(urls.empty())
                break;
            Json::Value rows(Json::arrayValue);
            for(const auto& url_row : urls) {
                const auto url = url_row["url"].as<std::string>();
                const auto identity = rules.classify(url);
                Json::Value row;
                row["url"] = url;
                row["site_key"] = identity.site_key;
                row["matched_rule"] = identity.matched_rule;
                rows.append(std::move(row));
            }
            co_await transaction->execSqlCoro(R"sql(
                INSERT INTO url_site_map(ruleset_id, url, site_key, matched_rule)
                SELECT $1, row.url, row.site_key, NULLIF(row.matched_rule, '')
                FROM jsonb_to_recordset($2::jsonb)
                  AS row(url text, site_key text, matched_rule text)
                ON CONFLICT DO NOTHING
            )sql", ruleset_id, jsonRows(rows));
            total += urls.size();
            if(total % 50000 < identity_batch_size)
                std::cout << "Classified " << total << " new URLs\n";
        }

        transaction->setCommitCallback([ruleset_id, total](bool committed) {
            if(committed)
                std::cout << "Synchronized " << total << " new URLs into active ruleset "
                          << ruleset_id << '\n';
            else
                std::cerr << "Failed to synchronize active site identity ruleset\n";
            app().quit();
        });
        transaction.reset();
        co_return;
    }
    catch(const std::exception& error) {
        if(transaction)
            transaction->rollback();
        std::cerr << "Cannot synchronize site identity rules: " << error.what() << '\n';
        app().quit();
    }
}

Task<> rollbackSiteRules(int64_t ruleset_id)
{
    try {
        const auto result = co_await app().getDbClient()->execSqlCoro(R"sql(
            WITH candidate AS (
                SELECT rulesets.id
                FROM site_identity_rulesets rulesets
                WHERE rulesets.id=$1
                  AND EXISTS (SELECT 1 FROM url_site_map WHERE ruleset_id=rulesets.id)
            ), activated AS (
                UPDATE site_identity_rulesets
                SET activated_at=CURRENT_TIMESTAMP
                WHERE id IN (SELECT id FROM candidate)
                RETURNING id
            )
            INSERT INTO site_identity_state(singleton, active_ruleset_id)
            SELECT TRUE, id FROM activated
            ON CONFLICT(singleton) DO UPDATE
            SET active_ruleset_id=EXCLUDED.active_ruleset_id
            RETURNING active_ruleset_id
        )sql", ruleset_id);
        if(result.empty())
            std::cerr << "Ruleset " << ruleset_id << " does not exist or has no completed mapping\n";
        else
            std::cout << "Activated site identity ruleset " << ruleset_id << '\n';
    }
    catch(const std::exception& error) {
        std::cerr << "Cannot roll back site identity rules: " << error.what() << '\n';
    }
    app().quit();
}

Task<> rebuildHilltop(bool rebuild_text_search)
{
    std::shared_ptr<orm::Transaction> transaction;
    try {
        transaction = co_await app().getDbClient()->newTransactionCoro();
        transaction->setTimeout(-1);
        co_await transaction->execSqlCoro("SET LOCAL client_min_messages TO WARNING");
        size_t text_pages = 0;
        if(rebuild_text_search) {
            const auto rebuilt = co_await transaction->execSqlCoro(R"sql(
                WITH source AS MATERIALIZED (
                    SELECT url, content_type, title, content_body, lang,
                           search_headings, search_link_text, search_schema_version,
                           CASE WHEN search_schema_version >= 2 THEN has_explicit_title
                                ELSE content_type='text/gemini' AND title IS NOT NULL
                                     AND title <> '' AND title <> url END AS real_title,
                           replace(replace(replace(url, '_', ' '), '-', ' '), '~', ' ') AS index_url
                    FROM pages
                    WHERE last_indexed_at IS NOT NULL AND search_schema_version < 1
                )
                UPDATE pages
                SET has_explicit_title=source.real_title,
                    title_vector=to_tsvector('simple',
                        CASE WHEN source.real_title THEN coalesce(source.title, '') ELSE '' END),
                    search_vector=
                        setweight(to_tsvector('simple', CASE WHEN source.real_title THEN coalesce(source.title, '') ELSE '' END), 'A') ||
                        setweight(to_tsvector('simple', source.search_headings), 'B') ||
                        setweight(to_tsvector('simple', source.index_url || ' ' || source.search_link_text), 'C') ||
                        setweight(to_tsvector('simple', coalesce(source.content_body, '')), 'D'),
                    english_search_vector=CASE
                        WHEN source.lang IS NULL OR lower(split_part(source.lang, ',', 1)) ~ '^en([_-]|$)' THEN
                            setweight(to_tsvector('english', CASE WHEN source.real_title THEN coalesce(source.title, '') ELSE '' END), 'A') ||
                            setweight(to_tsvector('english', source.search_headings), 'B') ||
                            setweight(to_tsvector('english', source.index_url || ' ' || source.search_link_text), 'C') ||
                            setweight(to_tsvector('english', coalesce(source.content_body, '')), 'D')
                        ELSE NULL END,
                    search_schema_version=greatest(source.search_schema_version, 1)
                FROM source
                WHERE pages.url=source.url
            )sql");
            text_pages = rebuilt.affectedRows();
        }
        const auto active = co_await transaction->execSqlCoro(R"sql(
            SELECT active_ruleset_id AS id
            FROM site_identity_state
            WHERE singleton=TRUE AND active_ruleset_id IS NOT NULL
            FOR SHARE
        )sql");
        if(active.empty())
            throw std::runtime_error("no active site identity ruleset");
        const auto ruleset_id = active[0]["id"].as<int64_t>();

        co_await transaction->execSqlCoro("DELETE FROM hilltop_edges WHERE ruleset_id=$1", ruleset_id);
        const auto inserted = co_await transaction->execSqlCoro(R"sql(
            WITH mapped AS MATERIALIZED (
                SELECT links.url AS expert_url,
                       source_map.site_key AS expert_site,
                       links.to_url AS target_url,
                       target_map.site_key AS target_site,
                       links.qualifying_text
                FROM links
                JOIN url_site_map source_map
                  ON source_map.ruleset_id=$1 AND source_map.url=links.url
                JOIN url_site_map target_map
                  ON target_map.ruleset_id=$1 AND target_map.url=links.to_url
                WHERE source_map.site_key <> target_map.site_key
            ), experts AS MATERIALIZED (
                SELECT expert_url
                FROM mapped
                GROUP BY expert_url
                HAVING count(DISTINCT target_site) >= 5
            ), collapsed AS (
                SELECT mapped.expert_url,
                       mapped.expert_site,
                       mapped.target_url,
                       mapped.target_site,
                       left(string_agg(DISTINCT mapped.qualifying_text, E'\n'), 16384) AS qualifying_text
                FROM mapped
                JOIN experts USING (expert_url)
                WHERE mapped.qualifying_text <> ''
                GROUP BY mapped.expert_url, mapped.expert_site,
                         mapped.target_url, mapped.target_site
            )
            INSERT INTO hilltop_edges(
                ruleset_id, expert_url, expert_site, target_url, target_site,
                qualifying_text, qualifying_vector)
            SELECT $1, expert_url, expert_site, target_url, target_site,
                   qualifying_text, to_tsvector('simple', qualifying_text)
            FROM collapsed
        )sql", ruleset_id);

        const auto edge_count = inserted.affectedRows();
        transaction->setCommitCallback([ruleset_id, edge_count, text_pages, rebuild_text_search](bool committed) {
            if(committed) {
                if(rebuild_text_search)
                    std::cout << "Built structured FTS vectors for " << text_pages << " pages\n";
                std::cout << "Built authority (Hilltop) index for ruleset " << ruleset_id
                          << " with " << edge_count << " expert recommendations\n";
            }
            else
                std::cerr << "Failed to commit authority index\n";
            app().quit();
        });
        transaction.reset();
        co_return;
    }
    catch(const std::exception& error) {
        if(transaction)
            transaction->rollback();
        std::cerr << "Cannot rebuild authority index: " << error.what() << '\n';
        app().quit();
    }
}

Task<> hilltopStatus(bool include_text_search)
{
    try {
        if(include_text_search) {
            const auto fts = co_await app().getDbClient()->execSqlCoro(R"sql(
                SELECT count(*) FILTER (WHERE last_indexed_at IS NOT NULL) AS indexed_pages,
                       count(*) FILTER (WHERE search_schema_version >= 1) AS structured_vectors,
                       count(*) FILTER (WHERE search_schema_version >= 2) AS parsed_fields,
                       count(*) FILTER (WHERE search_schema_version >= 3) AS bounded_vectors,
                       count(*) FILTER (WHERE english_search_vector IS NOT NULL) AS english_vectors,
                       count(*) FILTER (WHERE pg_column_size(search_vector) > 49152) AS oversized_simple,
                       count(*) FILTER (WHERE pg_column_size(english_search_vector) > 49152) AS oversized_english
                FROM pages
            )sql");
            std::cout << "Text search index\n"
                      << "Indexed pages: " << fts[0]["indexed_pages"].as<size_t>() << '\n'
                      << "Structured vectors: " << fts[0]["structured_vectors"].as<size_t>() << '\n'
                      << "Parsed field vectors: " << fts[0]["parsed_fields"].as<size_t>() << '\n'
                      << "Bounded vectors: " << fts[0]["bounded_vectors"].as<size_t>() << '\n'
                      << "English stemming vectors: " << fts[0]["english_vectors"].as<size_t>() << '\n'
                      << "Oversized simple vectors: " << fts[0]["oversized_simple"].as<size_t>() << '\n'
                      << "Oversized English vectors: " << fts[0]["oversized_english"].as<size_t>() << "\n\n";
        }
        const auto rows = co_await app().getDbClient()->execSqlCoro(R"sql(
            SELECT state.active_ruleset_id AS ruleset_id,
                   count(edges.target_url) AS recommendations,
                   count(DISTINCT edges.expert_url) AS expert_pages,
                   count(DISTINCT edges.expert_site) AS expert_sites,
                   count(DISTINCT edges.target_url) AS targets
            FROM site_identity_state state
            LEFT JOIN hilltop_edges edges
              ON edges.ruleset_id=state.active_ruleset_id
            WHERE state.singleton=TRUE
            GROUP BY state.active_ruleset_id
        )sql");
        if(rows.empty() || rows[0]["ruleset_id"].isNull())
            std::cout << "No active site identity ruleset\n";
        else
            std::cout << "Authority (Hilltop) index for ruleset " << rows[0]["ruleset_id"].as<int64_t>() << '\n'
                      << "Expert pages: " << rows[0]["expert_pages"].as<size_t>() << '\n'
                      << "Expert sites: " << rows[0]["expert_sites"].as<size_t>() << '\n'
                      << "Recommendations: " << rows[0]["recommendations"].as<size_t>() << '\n'
                      << "Targets: " << rows[0]["targets"].as<size_t>() << '\n';
    }
    catch(const std::exception& error) {
        std::cerr << "Cannot read authority index status: " << error.what() << '\n';
    }
    app().quit();
}

Task<> queryHilltop(std::string query)
{
    try {
        const auto started = std::chrono::steady_clock::now();
        const auto rows = co_await app().getDbClient()->execSqlCoro(R"sql(
            WITH query AS (
                SELECT websearch_to_tsquery('simple', $1) AS simple,
                       websearch_to_tsquery('english', $1) AS english,
                       phraseto_tsquery('simple', $1) AS simple_phrase,
                       phraseto_tsquery('english', $1) AS english_phrase
            ), active AS (
                SELECT active_ruleset_id AS ruleset_id
                FROM site_identity_state
                WHERE singleton=TRUE
            ), candidates AS MATERIALIZED (
                SELECT pages.url AS target_url,
                       pages.title,
                       (CASE WHEN pages.search_vector @@ query.simple THEN
                           CASE WHEN pages.title_vector @@ query.simple THEN 1.0 ELSE 0.0 END +
                           CASE WHEN pages.title_vector @@ query.simple_phrase THEN 0.5 ELSE 0.0 END +
                           CASE WHEN pages.search_vector @@ query.simple_phrase THEN 0.25 ELSE 0.0 END +
                           least(ts_rank_cd(ARRAY[0.05, 0.15, 0.4, 0.0]::real[], pages.search_vector, query.simple, 1), 0.5)
                        ELSE 0.8 * (
                           CASE WHEN ts_filter(pages.english_search_vector, '{A}') @@ query.english THEN 1.0 ELSE 0.0 END +
                           CASE WHEN ts_filter(pages.english_search_vector, '{A}') @@ query.english_phrase THEN 0.5 ELSE 0.0 END +
                           CASE WHEN pages.english_search_vector @@ query.english_phrase THEN 0.25 ELSE 0.0 END +
                           least(ts_rank_cd(ARRAY[0.05, 0.15, 0.4, 0.0]::real[], pages.english_search_vector, query.english, 1), 0.5)
                        ) END)::double precision AS text_rank
                FROM pages
                CROSS JOIN query
                WHERE pages.search_vector @@ query.simple
                   OR pages.english_search_vector @@ query.english
                ORDER BY text_rank DESC
                LIMIT 1000
            ), site_votes AS MATERIALIZED (
                SELECT candidates.target_url,
                       edges.expert_site,
                       max(CASE WHEN edges.qualifying_vector @@ query.simple
                                THEN 2.0 ELSE 1.0 END) AS vote
                FROM candidates
                JOIN hilltop_edges edges
                  ON edges.target_url=candidates.target_url
                JOIN active ON active.ruleset_id=edges.ruleset_id
                CROSS JOIN query
                GROUP BY candidates.target_url, edges.expert_site
            ), authority AS (
                SELECT target_url,
                       sum(vote) AS raw_authority,
                       count(*) AS independent_experts
                FROM site_votes
                GROUP BY target_url
            )
            SELECT candidates.target_url,
                   candidates.title,
                   candidates.text_rank,
                   CASE WHEN coalesce(authority.independent_experts, 0) >= 2
                        THEN 2.0 * ln(1.0 + authority.raw_authority)
                        ELSE 0.0 END AS authority,
                   coalesce(authority.independent_experts, 0) AS independent_experts,
                   candidates.text_rank +
                       CASE WHEN coalesce(authority.independent_experts, 0) >= 2
                            THEN 2.0 * ln(1.0 + authority.raw_authority)
                            ELSE 0.0 END AS final_score
            FROM candidates
            LEFT JOIN authority USING (target_url)
            ORDER BY final_score DESC, candidates.text_rank DESC
            LIMIT 50
        )sql", query);
        const auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::steady_clock::now() - started);

        std::cout << rows.size() << " lexical + Hilltop results in "
                  << elapsed.count() << " ms\n";
        for(const auto& row : rows) {
            std::cout << std::fixed << std::setprecision(5)
                      << row["final_score"].as<double>() << '\t'
                      << row["text_rank"].as<double>() << '\t'
                      << row["authority"].as<double>() << '\t'
                      << row["independent_experts"].as<size_t>() << '\t'
                      << row["target_url"].as<std::string>() << '\t'
                      << row["title"].as<std::string>() << '\n';
        }
    }
    catch(const std::exception& error) {
        std::cerr << "Cannot query Hilltop index: " << error.what() << '\n';
    }
    app().quit();
}

struct ExperimentResult
{
    std::string url;
    std::string title;
    double fts = 0;
    double salsa = 0;
    double hilltop = 0;
    size_t salsa_sites = 0;
    size_t hilltop_sites = 0;
};

class DisjointSet
{
  public:
    explicit DisjointSet(const size_t size) : parent_(size), rank_(size, 0)
    {
        std::iota(parent_.begin(), parent_.end(), 0);
    }

    size_t add()
    {
        const auto id = parent_.size();
        parent_.push_back(id);
        rank_.push_back(0);
        return id;
    }

    size_t find(const size_t value)
    {
        if(parent_[value] != value)
            parent_[value] = find(parent_[value]);
        return parent_[value];
    }

    void unite(size_t lhs, size_t rhs)
    {
        lhs = find(lhs);
        rhs = find(rhs);
        if(lhs == rhs)
            return;
        if(rank_[lhs] < rank_[rhs])
            std::swap(lhs, rhs);
        parent_[rhs] = lhs;
        if(rank_[lhs] == rank_[rhs])
            ++rank_[lhs];
    }

  private:
    std::vector<size_t> parent_;
    std::vector<unsigned char> rank_;
};

std::string singleLine(std::string text)
{
    std::replace(text.begin(), text.end(), '\n', ' ');
    std::replace(text.begin(), text.end(), '\r', ' ');
    std::replace(text.begin(), text.end(), '\t', ' ');
    return text;
}

Task<> compareRankings(std::string query)
{
    constexpr size_t candidate_limit = 1000;
    constexpr size_t display_limit = 20;

    try {
        const auto total_started = std::chrono::steady_clock::now();
        auto db = app().getDbClient();

        const auto fts_started = std::chrono::steady_clock::now();
        const auto candidate_rows = co_await db->execSqlCoro(R"sql(
            WITH query AS (
                SELECT websearch_to_tsquery('simple', $1) AS simple,
                       websearch_to_tsquery('english', $1) AS english,
                       phraseto_tsquery('simple', $1) AS simple_phrase,
                       phraseto_tsquery('english', $1) AS english_phrase
            )
            SELECT pages.url, pages.title,
                   (CASE WHEN pages.search_vector @@ query.simple THEN
                       CASE WHEN pages.title_vector @@ query.simple THEN 1.0 ELSE 0.0 END +
                       CASE WHEN pages.title_vector @@ query.simple_phrase THEN 0.5 ELSE 0.0 END +
                       CASE WHEN pages.search_vector @@ query.simple_phrase THEN 0.25 ELSE 0.0 END +
                       least(ts_rank_cd(ARRAY[0.05, 0.15, 0.4, 0.0]::real[], pages.search_vector, query.simple, 1), 0.5)
                    ELSE 0.8 * (
                       CASE WHEN ts_filter(pages.english_search_vector, '{A}') @@ query.english THEN 1.0 ELSE 0.0 END +
                       CASE WHEN ts_filter(pages.english_search_vector, '{A}') @@ query.english_phrase THEN 0.5 ELSE 0.0 END +
                       CASE WHEN pages.english_search_vector @@ query.english_phrase THEN 0.25 ELSE 0.0 END +
                       least(ts_rank_cd(ARRAY[0.05, 0.15, 0.4, 0.0]::real[], pages.english_search_vector, query.english, 1), 0.5)
                    ) END)::double precision AS fts
            FROM pages
            CROSS JOIN query
            WHERE pages.search_vector @@ query.simple
               OR pages.english_search_vector @@ query.english
            ORDER BY fts DESC
            LIMIT $2
        )sql", query, candidate_limit);
        const auto fts_finished = std::chrono::steady_clock::now();

        std::vector<ExperimentResult> results;
        results.reserve(candidate_rows.size());
        std::unordered_map<std::string, size_t> result_by_url;
        result_by_url.reserve(candidate_rows.size());
        nlohmann::json candidate_urls = nlohmann::json::array();
        for(const auto& row : candidate_rows) {
            ExperimentResult result;
            result.url = row["url"].as<std::string>();
            if(!row["title"].isNull())
                result.title = singleLine(row["title"].as<std::string>());
            result.fts = row["fts"].as<double>();
            result_by_url.emplace(result.url, results.size());
            candidate_urls.push_back(result.url);
            results.emplace_back(std::move(result));
        }

        if(results.empty()) {
            std::cout << "No FTS candidates for '" << query << "'\n";
            app().quit();
            co_return;
        }

        const auto salsa_started = std::chrono::steady_clock::now();
        const auto salsa_rows = co_await db->execSqlCoro(R"sql(
            WITH active AS (
                SELECT active_ruleset_id AS ruleset_id
                FROM site_identity_state
                WHERE singleton=TRUE
            ), candidates AS MATERIALIZED (
                SELECT value AS target_url
                FROM jsonb_array_elements_text($1::jsonb)
            )
            SELECT DISTINCT links.to_url AS target_url,
                            source_map.site_key AS source_site
            FROM candidates
            JOIN links ON links.to_url=candidates.target_url
            CROSS JOIN active
            JOIN url_site_map source_map
              ON source_map.ruleset_id=active.ruleset_id
             AND source_map.url=links.url
            JOIN url_site_map target_map
              ON target_map.ruleset_id=active.ruleset_id
             AND target_map.url=links.to_url
            WHERE source_map.site_key <> target_map.site_key
        )sql", candidate_urls.dump());

        DisjointSet components(results.size());
        std::unordered_map<std::string, size_t> hub_nodes;
        hub_nodes.reserve(salsa_rows.size());
        for(const auto& row : salsa_rows) {
            const auto target = result_by_url.find(row["target_url"].as<std::string>());
            if(target == result_by_url.end())
                continue;
            const auto source_site = row["source_site"].as<std::string>();
            auto [hub, inserted] = hub_nodes.emplace(source_site, 0);
            if(inserted)
                hub->second = components.add();
            components.unite(target->second, hub->second);
            ++results[target->second].salsa_sites;
        }

        struct ComponentStats
        {
            size_t authorities = 0;
            size_t edges = 0;
        };
        std::unordered_map<size_t, ComponentStats> component_stats;
        size_t linked_authorities = 0;
        for(size_t i = 0; i < results.size(); ++i) {
            if(results[i].salsa_sites == 0)
                continue;
            auto& stats = component_stats[components.find(i)];
            ++stats.authorities;
            stats.edges += results[i].salsa_sites;
            ++linked_authorities;
        }
        if(linked_authorities != 0) {
            for(size_t i = 0; i < results.size(); ++i) {
                if(results[i].salsa_sites == 0)
                    continue;
                const auto& stats = component_stats.at(components.find(i));
                results[i].salsa =
                    (static_cast<double>(stats.authorities) / linked_authorities) *
                    (static_cast<double>(results[i].salsa_sites) / stats.edges);
            }
        }
        const auto salsa_finished = std::chrono::steady_clock::now();

        const auto hilltop_started = std::chrono::steady_clock::now();
        const auto hilltop_rows = co_await db->execSqlCoro(R"sql(
            WITH query AS (
                SELECT websearch_to_tsquery('simple', $2) AS value
            ), active AS (
                SELECT active_ruleset_id AS ruleset_id
                FROM site_identity_state
                WHERE singleton=TRUE
            ), candidates AS MATERIALIZED (
                SELECT value AS target_url
                FROM jsonb_array_elements_text($1::jsonb)
            )
            SELECT edges.target_url,
                   edges.expert_site,
                   bool_or(edges.qualifying_vector @@ query.value) AS context_match
            FROM candidates
            JOIN hilltop_edges edges
              ON edges.target_url=candidates.target_url
            JOIN active ON active.ruleset_id=edges.ruleset_id
            CROSS JOIN query
            GROUP BY edges.target_url, edges.expert_site
        )sql", candidate_urls.dump(), query);

        std::vector<double> hilltop_raw(results.size(), 0);
        for(const auto& row : hilltop_rows) {
            const auto target = result_by_url.find(row["target_url"].as<std::string>());
            if(target == result_by_url.end())
                continue;
            ++results[target->second].hilltop_sites;
            hilltop_raw[target->second] += row["context_match"].as<bool>() ? 2.0 : 1.0;
        }
        size_t hilltop_consensus_targets = 0;
        for(size_t i = 0; i < results.size(); ++i) {
            if(results[i].hilltop_sites < 2)
                continue;
            results[i].hilltop = std::log1p(hilltop_raw[i]);
            ++hilltop_consensus_targets;
        }
        const auto hilltop_finished = std::chrono::steady_clock::now();

        auto ranked = [&](auto score) {
            std::vector<size_t> order(results.size());
            std::iota(order.begin(), order.end(), 0);
            std::stable_sort(order.begin(), order.end(), [&](const size_t lhs, const size_t rhs) {
                const auto lhs_score = score(results[lhs]);
                const auto rhs_score = score(results[rhs]);
                if(lhs_score != rhs_score)
                    return lhs_score > rhs_score;
                return results[lhs].fts > results[rhs].fts;
            });
            return order;
        };
        const auto fts_order = ranked([](const ExperimentResult& result) { return result.fts; });
        const auto salsa_order = ranked([](const ExperimentResult& result) { return result.salsa; });
        const auto hilltop_order = ranked([](const ExperimentResult& result) { return result.hilltop; });

        auto overlap = [&](const std::vector<size_t>& lhs, const std::vector<size_t>& rhs) {
            std::unordered_set<size_t> top;
            const auto count = std::min({display_limit, lhs.size(), rhs.size()});
            for(size_t i = 0; i < count; ++i)
                top.insert(lhs[i]);
            size_t common = 0;
            for(size_t i = 0; i < count; ++i)
                common += top.contains(rhs[i]);
            return common;
        };

        const auto milliseconds = [](const auto begin, const auto end) {
            return std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();
        };
        std::cout << "Ranking experiment for '" << query << "'\n"
                  << "Candidates: " << results.size() << '/' << candidate_limit << '\n'
                  << "FTS: " << milliseconds(fts_started, fts_finished) << " ms\n"
                  << "Optimized SALSA: " << milliseconds(salsa_started, salsa_finished)
                  << " ms, " << salsa_rows.size() << " affiliation edges, "
                  << hub_nodes.size() << " hubs, " << component_stats.size() << " components\n"
                  << "Hilltop: " << milliseconds(hilltop_started, hilltop_finished)
                  << " ms, " << hilltop_rows.size() << " affiliation votes, "
                  << hilltop_consensus_targets << " targets with independent consensus\n"
                  << "Total: " << milliseconds(total_started, hilltop_finished) << " ms\n"
                  << "Top-" << display_limit << " overlap: FTS/SALSA "
                  << overlap(fts_order, salsa_order) << ", FTS/Hilltop "
                  << overlap(fts_order, hilltop_order) << ", SALSA/Hilltop "
                  << overlap(salsa_order, hilltop_order) << "\n";

        auto printRanking = [&](const std::string_view name, const std::vector<size_t>& order,
                                auto score) {
            std::cout << "\n[" << name << "]\n"
                      << "rank\tscore\tfts\tsalsa-sites\thilltop-sites\turl\ttitle\n";
            const auto count = std::min(display_limit, order.size());
            for(size_t rank = 0; rank < count; ++rank) {
                const auto& result = results[order[rank]];
                std::cout << rank + 1 << '\t' << std::fixed << std::setprecision(8)
                          << score(result) << '\t' << result.fts << '\t'
                          << result.salsa_sites << '\t' << result.hilltop_sites << '\t'
                          << result.url << '\t' << result.title << '\n';
            }
        };
        printRanking("FTS", fts_order, [](const ExperimentResult& result) { return result.fts; });
        printRanking("OPTIMIZED SALSA", salsa_order,
                     [](const ExperimentResult& result) { return result.salsa; });
        printRanking("HILLTOP", hilltop_order,
                     [](const ExperimentResult& result) { return result.hilltop; });
    }
    catch(const std::exception& error) {
        std::cerr << "Cannot run ranking experiment: " << error.what() << '\n';
    }
    app().quit();
}

} // namespace

int main(int argc, char** argv)
{
	std::string config_file = "/etc/tlgs/config.json";
	CLI::App cli{"TLGS Utiltity"};
	
	CLI::App& populate_schema = *cli.add_subcommand("populate_schema", "Populate/update database schema");

	CLI::App& purge = *cli.add_subcommand("purge", "Remove page from database");
	std::string url;
	purge.add_option("purge_url", url, "URL to purge (SQL wildcards allowed)");

	CLI::App& index_status = *cli.add_subcommand("indexstatus", "Show status of the index");

	CLI::App& site_rules = *cli.add_subcommand("site-rules", "Manage logical site identity rules");
	site_rules.require_subcommand(1);
	CLI::App& validate_site_rules = *site_rules.add_subcommand("validate", "Validate a TOML rules file and its tests");
	CLI::App& plan_site_rules = *site_rules.add_subcommand("plan", "Show how a TOML rules file changes existing URLs");
	CLI::App& apply_site_rules = *site_rules.add_subcommand("apply", "Build and atomically activate a TOML rules file");
	CLI::App& site_rules_status = *site_rules.add_subcommand("status", "List installed rulesets");
	CLI::App& sync_site_rules = *site_rules.add_subcommand("sync", "Classify URLs added since the active ruleset was applied");
	CLI::App& rollback_site_rules = *site_rules.add_subcommand("rollback", "Activate a previous completed ruleset");
	std::string site_rules_file;
	int64_t rollback_ruleset_id = 0;
	validate_site_rules.add_option("rules_file", site_rules_file, "TOML site identity rules")->required();
	plan_site_rules.add_option("rules_file", site_rules_file, "TOML site identity rules")->required();
	apply_site_rules.add_option("rules_file", site_rules_file, "TOML site identity rules")->required();
	rollback_site_rules.add_option("ruleset_id", rollback_ruleset_id, "Ruleset ID to activate")->required();

	CLI::App& search_index = *cli.add_subcommand(
		"search-index", "Build and inspect the FTS and authority indexes used by default search");
	search_index.require_subcommand(1);
	CLI::App& rebuild_search_index = *search_index.add_subcommand(
		"rebuild", "Migrate missing structured FTS vectors and rebuild authority recommendations");
	CLI::App& search_index_status = *search_index.add_subcommand(
		"status", "Show FTS and authority index statistics");

	CLI::App& hilltop = *cli.add_subcommand("hilltop", "Hilltop experiments and compatibility commands");
	hilltop.require_subcommand(1);
	CLI::App& rebuild_hilltop = *hilltop.add_subcommand("rebuild", "Rebuild expert recommendations for the active site ruleset");
	CLI::App& hilltop_status = *hilltop.add_subcommand("status", "Show Hilltop index statistics");
	CLI::App& query_hilltop = *hilltop.add_subcommand("query", "Run lexical retrieval with a conservative Hilltop boost");
	std::string hilltop_query;
	query_hilltop.add_option("query", hilltop_query, "Search query")->required();

	CLI::App& ranking_experiment = *cli.add_subcommand(
		"ranking-experiment", "Compare FTS, closed-form SALSA, and Hilltop rankings");
	std::string experiment_query;
	ranking_experiment.add_option("query", experiment_query, "Search query")->required();

	cli.add_option("config_file", config_file, "Path to TLGS config file");
	CLI11_PARSE(cli, argc, argv);
	if(validate_site_rules) {
		try {
			const auto rules = tlgs::SiteIdentityRules::fromFile(site_rules_file);
			std::cout << "Valid site identity rules: " << rules.ruleCount() << " rules, "
			          << rules.tests().size() << " tests, hash " << rules.hash() << '\n';
			return 0;
		}
		catch(const std::exception& error) {
			std::cerr << "Invalid site identity rules: " << error.what() << '\n';
			return 1;
		}
	}

	app().loadConfigFile(config_file);

	if(populate_schema) {
		app().getLoop()->queueInLoop(async_func(createDb));
	}
	else if(purge) {
		app().getLoop()->queueInLoop(async_func(std::bind(purgePage, url)));
	}
	else if(index_status) {
		app().getLoop()->queueInLoop(async_func(indexStatus));
	}
	else if(plan_site_rules || apply_site_rules) {
		try {
			auto rules = std::make_shared<const tlgs::SiteIdentityRules>(
				tlgs::SiteIdentityRules::fromFile(site_rules_file));
			if(plan_site_rules)
				app().getLoop()->queueInLoop(async_func([rules]() { return planSiteRules(rules); }));
			else
				app().getLoop()->queueInLoop(async_func([rules]() { return applySiteRules(rules); }));
		}
		catch(const std::exception& error) {
			std::cerr << "Invalid site identity rules: " << error.what() << '\n';
			return 1;
		}
	}
	else if(site_rules_status) {
		app().getLoop()->queueInLoop(async_func(siteRulesStatus));
	}
	else if(sync_site_rules) {
		app().getLoop()->queueInLoop(async_func(syncSiteRules));
	}
	else if(rollback_site_rules) {
		app().getLoop()->queueInLoop(async_func(std::bind(rollbackSiteRules, rollback_ruleset_id)));
	}
	else if(rebuild_search_index || rebuild_hilltop) {
		app().getLoop()->queueInLoop(async_func(std::bind(rebuildHilltop, bool(rebuild_search_index))));
	}
	else if(search_index_status || hilltop_status) {
		app().getLoop()->queueInLoop(async_func(std::bind(hilltopStatus, bool(search_index_status))));
	}
	else if(query_hilltop) {
		app().getLoop()->queueInLoop(async_func(std::bind(queryHilltop, hilltop_query)));
	}
	else if(ranking_experiment) {
		app().getLoop()->queueInLoop(async_func(std::bind(compareRankings, experiment_query)));
	}
	else {
		std::cout << cli.help();
		return 0;
	}

	app().run();
}
