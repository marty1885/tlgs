#include <drogon/drogon_test.h>
#include <tlgsutils/url_blacklist.hpp>

DROGON_TEST(BlacklistTest)
{
	tlgs::UrlBlacklist blacklist;
	blacklist.add("gemini://example.com/");
	CHECK(blacklist.isBlocked("gemini://") == false);
	CHECK(blacklist.isBlocked("gemini://example.com/") == true);
	CHECK(blacklist.isBlocked("gemini://example.com/index.gmi") == true);
	CHECK(blacklist.isBlocked("gemini://example.com") == true);
	CHECK(blacklist.isBlocked("gemini://example.org/") == false);

	blacklist.add("gemini://example.org/");
	CHECK(blacklist.isBlocked("gemini://example.org/") == true);
	CHECK(blacklist.isBlocked("gemini://example.org/index.gmi") == true);

	blacklist.add("gemini://example.net/cgi-bin");
	CHECK(blacklist.isBlocked("gemini://example.net/cgi-bin/get-data?123456") == true);
	CHECK(blacklist.isBlocked("gemini://example.net/cgi-bin") == true);
	CHECK(blacklist.isBlocked("gemini://example.net/data/cgi-bin") == false);

	CHECK(blacklist.isBlocked("gemini://example.online/") == false);
	CHECK(blacklist.isBlocked("gemini://example") == false);
	CHECK(blacklist.isBlocked("http://example.com") == false);

	blacklist.add("gemini://example.gov/data/");
	CHECK(blacklist.isBlocked("gemini://example.gov/data") == false);
}
