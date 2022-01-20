#include <drogon/drogon_test.h>
#include <tlgsutils/trie.hpp>

DROGON_TEST(TrieTest)
{
	tlgs::trie_map<char, tlgs::SetCounter> trie;
	trie.insert("gemini://example.com/");
	CHECK(trie.containsPrefixOf("gemini://") == false);
	CHECK(trie.containsPrefixOf("gemini://example.com/") == true);
	CHECK(trie.containsPrefixOf("gemini://example.com/index.gmi") == true);
	CHECK(trie.containsPrefixOf("gemini://example.com") == false);
	CHECK(trie.containsPrefixOf("gemini://example.org/") == false);

	trie.insert("gemini://example.org/");
	CHECK(trie.containsPrefixOf("gemini://example.org/") == true);
	CHECK(trie.containsPrefixOf("gemini://example.org/index.gmi") == true);

	trie.insert("gemini://example.net/cgi-bin");
	CHECK(trie.containsPrefixOf("gemini://example.net/cgi-bin/get-data?123456") == true);
	CHECK(trie.containsPrefixOf("gemini://example.net/cgi-bin") == true);
	CHECK(trie.containsPrefixOf("gemini://example.net/data/cgi-bin") == false);

	CHECK(trie.containsPrefixOf("gemini://example.online/") == false);
	CHECK(trie.containsPrefixOf("gemini://example") == false);
	CHECK(trie.containsPrefixOf("http://example.com") == false);
}