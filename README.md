# TLGS - Totally Legit Gemini Search

## Overview

TLGS is a search engine for Gemini. It's slightly overengineered for what it currently is and uses weird tech. And I'm proud of that. The current code basse is kinda messy - I promise to clean them up. The main features/characteristics are as follows:

* Using the state of the art C++20
* Parses and indexes textual contents on Gemninispace
* Highly concurrent and asynchronous
* Stores index on PostgreSQL
* Developed for Linux. But should work on Windows, OpenBSD, HaikuOS, macOS, etc..
* Only fetch headers for files it can't index to save bandwith and time
* Handles all kinds of source encoding
* Link analysis using the HITS algorithm

As of now, indexing of news sites, RFCs, documentations are mostly disabled. But likely be enabled once I have the mean and resources to scale the setup.

## Using this project

### Requirments

* [drogon](https://github.com/an-tao/drogon)
* [nlohmann-json](https://github.com/nlohmann/json)
* [CLI11](https://github.com/CLIUtils/CLI11)
* [libfmt](https://github.com/fmtlib/fmt)
* [TBB](https://github.com/oneapi-src/oneTBB)
* [xxHash](https://github.com/Cyan4973/xxHash)
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

To create the inital index:

1. Initialize the database `./tlgs/tlgs_ctl/tlgs_ctl ../tlgs/config.json populate_schema`
2. Place the seed URLs into `seeds.text`
3. In the build folder, run `./tlgs/crawler/tlgs_crawler -s seeds.text -c 4 ../tlgs/config.json`

Now the crawler will start crawling the geminispace while also updating outdated indices (if any). To update an existing index. Run: 

```bash
./tlgs/crawler/tlgs_crawler -c 2 ../tlgs/config.json
# -c is the maximum concurrent connections the crawler will make
```

**NOTE:** TLGS's crawler is distributable. You can run multiple instances in parallel. But some intances may drop out early towards the end or crawling. Though it does not effect the result of crawling.

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

## Server config

The `custom_config.tlgs` section in `search_config.json` (installed at `/etc/tlgs/server_config.json`) contains confgurations for TLGS server. Besides the usual [Drogon's config options](https://drogon.docsforge.com/master/configuration-file/). custom_config changes the property of TLGS itself. Current supported options are:

### ranking_algo
The ranking algorithm TLGS uses to rank pages in search result. The ranking is then combined with the text match score to produce the final search rank. Current supported values are `hits` and `salsa`. Refering to the [HITS][hits] and [SALSA][salsa] ranking algorithm. It defaults to `hits` if no value is provided.

HITS runs faster than SALSA. Also while [literature][najork2007comparing] suggesres SALSA provides better result. From experience HITS is better at ranking Gemini.

```json
"ranking_algo": "hits"
```

## TODOs

- [ ] Code cleanup
- [ ] Randomize the order of crawling. Avoid bashing a single capsule
- [ ] Support parsing markdown
- [ ] Try indexing news sites
- [ ] Optimize the crawler even more
  - [x] Checks hash before updating index
  - [ ] Peoper UTF-8 handling in ASCII art detection
  - [x] Use a trie for blacklist URL match
- [x] ~~Link analysis using SALSA~~
  * SALSA is implemented. But it is slower with the same rank quality
  * Maybe Gemini is not complicated enough for HITS to fail
- [ ] BM25 for text scoring
- [x] Dedeuplicate search result
- [x] Impement Filters
- [ ] Proper(?) way to migrate schema

[hits]: http://www.cs.cornell.edu/home/kleinber/auth.pdf
[salsa]: https://citeseerx.ist.psu.edu/viewdoc/summary?doi=10.1.1.38.5859
[najork2007comparing]: https://www.ccs.neu.edu/home/vip/teach/IRcourse/4_webgraph/notes/najork05_HITS_vs_salsa.pdf