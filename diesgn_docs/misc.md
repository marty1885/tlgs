# TLGS design doc

a.k.a. My rambling about why I made something someway

## PostgreSQL

The decition to use PostgreSQL instead of dedicated search engines like ElasticSarch is solely due to the complexity in deployment. Not that I can't deploy complicated applications. But it makes contributing (hopefully the project will have) to be hard. Setting Nextcloud for personal use is already annoning enough. I think people will be detured from contributing just because how long it takes to properly setup a development enviroment.

## Why HITS as raking algorithm

It is easier in the earlier development process. PageRank run on the entire network graph instead of a subset. Thus it scales less and requires more inital work to get going. HITS on the other hand runs on a subset of the graph. Making it easier to debug since I don't need to have a an entire database ready (this is from an early stage of development). The original idea was to use SALSA. But SALSA requires the text search algorithm to determine which nodes are the hubs. It turns out to be hard to do. Full text search returns the entire list of possible sites without any room for potential hubs in most cases. Crumblimg the algorithm.

~~Totally would want to switch to SALSA if I can. To avoid TKC problem.~~
**Update:** Ditched HITS. Now using SALSA. Turns out the original SALSA paper has a easy way to distingush hubs and auths.
