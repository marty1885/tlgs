-- Run with:
--   psql "$DATABASE_URL" -v term='representative search term' -f search_explain.sql
--
-- The base-set query is intentionally EXPLAIN-only because it can return a
-- very large graph for common terms. Uncomment its ANALYZE version only after
-- reviewing the estimated row count.

\if :{?term}
\else
\set term 'gemini'
\endif

SET statement_timeout = '30s';
SET plan_cache_mode = force_custom_plan;

\echo 'Root-set query'
EXPLAIN (ANALYZE, BUFFERS, SETTINGS)
SELECT
    url AS source_url,
    cross_site_links,
    content_type,
    size,
    indexed_content_hash AS content_hash,
    ts_rank_cd(title_vector, plainto_tsquery(:'term')) * 50 +
    ts_rank_cd(search_vector, plainto_tsquery(:'term')) AS rank
FROM pages
WHERE search_vector @@ plainto_tsquery(:'term')
ORDER BY rank DESC
LIMIT 5000;

\echo 'Base-set query estimate'
EXPLAIN (BUFFERS, SETTINGS)
SELECT
    links.to_url AS dest_url,
    links.url AS source_url,
    content_type,
    size,
    indexed_content_hash AS content_hash,
    0 AS rank
FROM pages
JOIN links ON pages.url = links.to_url
WHERE links.is_cross_site = TRUE
  AND pages.search_vector @@ plainto_tsquery(:'term');

-- EXPLAIN (ANALYZE, BUFFERS, SETTINGS)
-- SELECT
--     links.to_url AS dest_url,
--     links.url AS source_url,
--     content_type,
--     size,
--     indexed_content_hash AS content_hash,
--     0 AS rank
-- FROM pages
-- JOIN links ON pages.url = links.to_url
-- WHERE links.is_cross_site = TRUE
--   AND pages.search_vector @@ plainto_tsquery(:'term');

\echo 'Table statistics'
SELECT
    relname,
    n_live_tup,
    n_dead_tup,
    last_analyze,
    last_autoanalyze
FROM pg_stat_user_tables
WHERE relname IN ('pages', 'links');

\echo 'Index statistics'
SELECT
    indexrelname,
    idx_scan,
    idx_tup_read,
    idx_tup_fetch
FROM pg_stat_user_indexes
WHERE relname IN ('pages', 'links');
