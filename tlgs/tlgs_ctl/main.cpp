#include <drogon/drogon.h>
#include <drogon/utils/coroutine.h>
using namespace drogon;

#include "CLI/App.hpp"
#include "CLI/Formatter.hpp"
#include "CLI/Config.hpp"

Task<> createDb()
{
	auto db = app().getDbClient();
	co_await db->execSqlCoro("CREATE EXTENSION IF NOT EXISTS pgroonga;");
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
			size bigint DEFAULT 0 NOT NULL,
			last_indexed_at timestamp without time zone,
			last_crawled_at timestamp without time zone,
			last_crawl_success_at timestamp without time zone,
			last_status integer,
			last_meta text,
			first_seen_at timestamp without time zone NOT NULL,
			cross_site_links json,
			internal_links json,
			title_vector tsvector,
			last_queued_at timestamp without time zone,
			indexed_content_hash text NOT NULL default '',
			raw_content_hash text NOT NULL default '',
			PRIMARY KEY (url)
		);
	)");
	co_await db->execSqlCoro("CREATE INDEX IF NOT EXISTS last_crawled_index ON public.pages USING btree (last_crawled_at DESC);");
	co_await db->execSqlCoro("CREATE INDEX IF NOT EXISTS search_vector_index ON public.pages USING pgroonga (content_body);");

	co_await db->execSqlCoro(R"(
		CREATE TABLE IF NOT EXISTS public.links (
			url text NOT NULL,
			host text NOT NULL,
			port integer NOT NULL,
			to_url text NOT NULL,
			to_host text NOT NULL,
			to_port integer NOT NULL,
			is_cross_site boolean NOT NULL
		);
	)");
	co_await db->execSqlCoro("CREATE INDEX IF NOT EXISTS is_cross_site_index ON public.links USING btree (is_cross_site);");
	co_await db->execSqlCoro("CREATE INDEX source_url_index ON public.links USING btree (url);");
	co_await db->execSqlCoro("CREATE INDEX to_url_index ON public.links USING btree (to_url);");

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

int main(int argc, char** argv)
{
	std::string config_file = "/etc/tlgs/config.json";
	CLI::App cli{"TLGS Utiltity"};
	
	CLI::App& populate_schema = *cli.add_subcommand("populate_schema", "Populate/update database schema");

	CLI::App& purge = *cli.add_subcommand("purge", "Remove page from database");
	std::string url;
	purge.add_option("purge_url", url, "URL to purge (SQL wildcards allowed)");

	CLI::App& index_status = *cli.add_subcommand("indexstatus", "Show status of the index");

	cli.add_option("config_file", config_file, "Path to TLGS config file");
	CLI11_PARSE(cli, argc, argv);

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
	else {
		std::cout << cli.help();
		return 0;
	}

	app().run();
}