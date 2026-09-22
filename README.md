# TLGS - Totally Legit Gemini Search

## Overview

TLGS is a search engine for Gemini. It's slightly overengineered for what it currently is and uses weird tech. And I'm proud of that. The current code base is kinda messy - I promise to clean them up. The main features/characteristics are as follows:

* Using the state of the art C++20
* Parses and indexes textual contents on Gemninispace
* Highly concurrent and asynchronous
* Stores index on PostgreSQL
* Developed for Linux. But should work on Windows, OpenBSD, HaikuOS, macOS, etc..
* Only fetch headers for files it can't index to save bandwith and time
* Handles all kinds of source encoding

As of now, indexing of news sites, RFCs, documentations are mostly disabled. But likely be enabled once I have the mean and resources to scale the setup.

## Using this project

### Requirments

* [drogon](https://github.com/an-tao/drogon)
* [nlohmann-json](https://github.com/nlohmann/json)
* [CLI11](https://github.com/CLIUtils/CLI11)
* [libfmt](https://github.com/fmtlib/fmt)
* [TBB](https://github.com/oneapi-src/oneTBB)
* [xxHash](https://github.com/Cyan4973/xxHash)
* [toml11](https://github.com/ToruNiina/toml11)
* iconv
* PostgreSQL

### Building and running the project

To build the project. You'll need a fully C++20 capable compiler. The following compilers should work as of writing this README

* GCC >= 11.2
* MSVC >= 16.25

Install all dependencies. And run the commands:

```bash
mkdir build
cd build
cmake ..
make -j
```

### Creating and maintaining the index

TLGS imports the [TARDIS](gemini://tardis.northwire.xyz) incremental update feed. Configure the registered client certificate and key in `config.json` under `tardis`. `change_mime_types` controls the inventory of changed pages returned by TARDIS (`"*"` includes all MIME types), while `body_mime_types` controls which of those pages include bodies in the batch WARC; the sample fetches only the text MIME types TLGS indexes. Omitted `body_mime_types` defaults to `change_mime_types`. The crawler automatically stores its completed full-sync timestamp and an in-progress stable feed window in PostgreSQL, so it resumes an interrupted daily run from the server-provided paging token.

To create the initial index:

1. Initialize the database `./tlgs/tlgs_ctl/tlgs_ctl ../tlgs/config.json populate_schema`
2. In the build folder, run `./tlgs/crawler/tlgs_crawler ../tlgs/config.json`

To import later updates, run:

```bash
./tlgs/crawler/tlgs_crawler ../tlgs/config.json
```

### Logical site identity

Shared hosts can contain independent Gemini capsules below paths such as `/~alice/` or `/user/alice/`. TLGS classifies URLs into logical sites using the ordered rules in `tlgs/site_identity_rules.toml`. The matcher DOES NOT speak regex to suruve potential Regex DoS

Rules can be checked and applied to an already-ingested database without a recrawl:

```bash
./tlgs/tlgs_ctl/tlgs_ctl ../tlgs/config.json site-rules validate ../tlgs/site_identity_rules.toml
./tlgs/tlgs_ctl/tlgs_ctl ../tlgs/config.json site-rules plan ../tlgs/site_identity_rules.toml
./tlgs/tlgs_ctl/tlgs_ctl ../tlgs/config.json site-rules apply ../tlgs/site_identity_rules.toml
./tlgs/tlgs_ctl/tlgs_ctl ../tlgs/config.json site-rules status
./tlgs/tlgs_ctl/tlgs_ctl ../tlgs/config.json site-rules sync
```

`apply` builds a versioned URL mapping and switches the active ruleset only after the complete mapping has been verified. During TARDIS ingestion, the crawler incrementally adds captured URLs and their parsed link targets to the ruleset that was active when the sync began. `sync` remains available to backfill URLs from a previous crawl or repair an incomplete mapping, without creating a new ruleset version.

A previous mapping can be reactivated atomically:

```bash
./tlgs/tlgs_ctl/tlgs_ctl ../tlgs/config.json site-rules rollback RULESET_ID
```

After ingesting or replacing a dataset, build the derived search data:

```bash
./tlgs/tlgs_ctl/tlgs_ctl ../tlgs/config.json site-rules apply ../tlgs/site_identity_rules.toml
./tlgs/tlgs_ctl/tlgs_ctl ../tlgs/config.json search-index rebuild
./tlgs/tlgs_ctl/tlgs_ctl ../tlgs/config.json search-index status
```

### Running the capsule

```bash
openssl req -new -subj "/CN=my.host.name.space" -x509 -newkey ec -pkeyopt ec_paramgen_curve:prime256v1 -days 36500 -nodes -out cert.pem -keyout key.pem
cd tlgs/server
./tlgs_server ../../../tlgs/server_config.json
```

### Via systemd

```bash
sudo systemctl start tlgs_server
sudo systemctl start tlgs_crawler
```

### Via OpenBSD rc.d

On OpenBSD, installation places `rc.d(8)` scripts at `/etc/rc.d/tlgs_server` and `/etc/rc.d/tlgs_crawler`. Create the service account and runtime directories, install TLGS, then enable the server:

```sh
doas useradd -c "TLGS service account" -d /var/empty -s /sbin/nologin _tlgs
doas install -d -o _tlgs -g _tlgs -m 0750 /var/tlgs
doas install -d -o _tlgs -g _tlgs -m 0750 /var/tlgs/uploads
doas cmake --install build
doas rcctl enable tlgs_server
doas rcctl start tlgs_server
```
The service runs as `_tlgs`, changes directory to the writable runtime directory `/var/tlgs`, and sends its output to syslog with the `daemon.info` priority. Static content lives in  `/etc/tlgs/contents` and Drogon's upload scratch pad is `/var/tlgs/uploads`. Otherwise the framework may refuse to initialize.

Standard commands available through `rcctl`:

```sh
doas rcctl check tlgs_server
doas rcctl restart tlgs_server
doas rcctl stop tlgs_server
```

Edit `/etc/tlgs/server_config.json` before the first start. The `_tlgs` user must be able to read the configured TLS certificate and key and connect to the
configured PostgreSQL database.

The crawler is a finite job. Its rc.d wrapper changes directory to `/var/tlgs`, runs as `_tlgs`, passes `/etc/tlgs/config.json` as its default argument, and logs through syslog. It may be started or stopped with `rcctl`:

```sh
doas rcctl start tlgs_crawler
doas rcctl check tlgs_crawler
doas rcctl stop tlgs_crawler
```

Extra crawler arguments belong in `daemon_flags`; for example, this limits a controlled run to 100 TARDIS update pages:

```sh
doas rcctl set tlgs_crawler flags '/etc/tlgs/config.json --max-pages 100'
```

For normal production use, leave the default flags in place. Schedule the job from `/etc/daily.local` (which must be executable) with:

```sh
#!/bin/ksh
/etc/rc.d/tlgs_crawler start
```

Alternatively, use root's crontab for a fixed time, for example 00:15 daily:

```cron
15 0 * * * /etc/rc.d/tlgs_crawler start
```

The wrapper creates `/var/tlgs/tlgs_crawler.lock` atomically and records the crawler PID before it `exec`s the crawler. If a crawl takes more than a day, the next scheduled invocation logs a skip instead of starting a second crawl. A lock left by a completed or crashed crawler is identified as stale and removed on the next invocation. Do not enable `tlgs_crawler` with `rcctl enable`: it is intentionally started by the scheduler, not at boot.

## Server config

The `custom_config.tlgs` section in `search_config.json` (installed at `/etc/tlgs/server_config.json`) contains confgurations for TLGS server. Besides the usual [Drogon's config options](https://drogon.docsforge.com/master/configuration-file/). custom_config changes the property of TLGS itself. Current supported options are:

### ranking_algo
The ranking algorithm TLGS uses to rank pages in search results. Current supported values are `hits`, `salsa`, and `fusion`. It defaults to `fusion` if no value is provided. `hits` and `salsa` are retained for controlled comparisons but construct a query-time graph and are not recommended for normal serving.

`fusion` is a hand tuned FTS and Hilltop algorithm that imperically works and is much faster then SALSA/HITS + FTS but limited to 1000 results. The weight of FTS vs Hilltop defaults to `1.0` and can be adjusted in config. 

```json
"ranking_algo": "fusion",
"fusion_graph_weight": 1.0,
"fusion_site_decay": 0.5,
"fusion_max_site_results_per_page": 2
```

[hits]: http://www.cs.cornell.edu/home/kleinber/auth.pdf
[salsa]: https://citeseerx.ist.psu.edu/viewdoc/summary?doi=10.1.1.38.5859
[najork2007comparing]: https://www.ccs.neu.edu/home/vip/teach/IRcourse/4_webgraph/notes/najork05_HITS_vs_salsa.pdf
