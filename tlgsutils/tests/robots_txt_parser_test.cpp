#include <robots_txt_parser.hpp>
#include <drogon/drogon_test.h>

DROGON_TEST(RobotTextTest)
{
    std::string robots = 
        "User-agent: *\n"
        "Disallow: /\n";

    auto disallowed = tlgs::parseRobotsTxt(robots, {"*"});
    REQUIRE(disallowed.size() == 1);
    CHECK(disallowed[0] == "/");

    robots = 
        "User-agent: gus\n"
        "Disallow: /\n";
    disallowed = tlgs::parseRobotsTxt(robots, {"tlgs"});
    REQUIRE(disallowed.size() == 0);

    robots = 
        "User-agent: gus\n"
        "Disallow: /\n"
        "\n"
        "User-agent: tlgs\n"
        "Disallow: /mydir";
    disallowed = tlgs::parseRobotsTxt(robots, {"tlgs"});
    REQUIRE(disallowed.size() == 1);
    CHECK(disallowed[0] == "/mydir");

    robots = 
        "User-agent: gus\n"
        "User-agent: tlgs\n"
        "Disallow: /\n";
    disallowed = tlgs::parseRobotsTxt(robots, {"tlgs"});
    REQUIRE(disallowed.size() == 1);
    CHECK(disallowed[0] == "/");
    disallowed = tlgs::parseRobotsTxt(robots, {"gus"});
    REQUIRE(disallowed.size() == 1);
    CHECK(disallowed[0] == "/");

    robots = 
        "User-agent: *\n"
        "Disallow: /\n"
        "\n"
        "User-agent: tlgs\n"
        "Disallow: \n";
    disallowed = tlgs::parseRobotsTxt(robots, {"tlgs", "*"});
    REQUIRE(disallowed.size() == 0);
    disallowed = tlgs::parseRobotsTxt(robots, {"*"});
    REQUIRE(disallowed.size() == 1);
    CHECK(disallowed[0] == "/");

    robots = 
        "User-agent: *\n"
        "Disallow: /\n"
        "\n"
        "User-agent: tlgs\n"
        "Disallow: \n";
    disallowed = tlgs::parseRobotsTxt(robots, {"tlgs", "*"});
    REQUIRE(disallowed.size() == 0);

    robots = "";
    disallowed = tlgs::parseRobotsTxt(robots, {"tlgs", "*"});
    REQUIRE(disallowed.size() == 0);

    robots =
        "User-agent: indexer\n"
        "Disallow: /test\n"
        "User-agent: researcher\n"
        "Disallow: /\n";
    disallowed = tlgs::parseRobotsTxt(robots, {"indexer", "*"});
    REQUIRE(disallowed.size() == 1);

    // Test support for lowercase user-agent
    robots =
        "user-agent: indexer\n"
        "Disallow: /test\n";
    disallowed = tlgs::parseRobotsTxt(robots, {"indexer", "*"});
    REQUIRE(disallowed.size() == 1);

    // Test support for lowercase disallow
    robots =
        "User-agent: indexer\n"
        "disallow: /test\n";
    disallowed = tlgs::parseRobotsTxt(robots, {"indexer", "*"});
    REQUIRE(disallowed.size() == 1);

    // Test support for weird cases
    robots =
        "User-AGEnT: indexer\n"
        "disalloW: /test\n";
    disallowed = tlgs::parseRobotsTxt(robots, {"indexer", "*"});
    REQUIRE(disallowed.size() == 1);

    // Test handling of leading whitespace in value
    robots =
        "User-agent: \tindexer\n"
        "Disallow:         /test\n";
    disallowed = tlgs::parseRobotsTxt(robots, {"indexer", "*"});
    REQUIRE(disallowed.size() == 1);
    REQUIRE(disallowed[0] == "/test");

    // Test handling of leading whitespace in key
    robots =
        "        User-agent: indexer\n"
        "        Disallow: /test\n";
    disallowed = tlgs::parseRobotsTxt(robots, {"indexer", "*"});
    REQUIRE(disallowed.size() == 1);
    REQUIRE(disallowed[0] == "/test");

    // Test CRLF line endings
    robots =
        "User-agent: indexer\r\n"
        "Disallow: /test\r\n";
    disallowed = tlgs::parseRobotsTxt(robots, {"indexer", "*"});
    REQUIRE(disallowed.size() == 1);
    REQUIRE(disallowed[0] == "/test");
}

DROGON_TEST(BlockedPathTest)
{
    CHECK(tlgs::isPathBlocked("/", "/") == true);
    CHECK(tlgs::isPathBlocked("/foo", "/") == true);
    CHECK(tlgs::isPathBlocked("/bar", "/foo") == false);
    CHECK(tlgs::isPathBlocked("/foo", "/foobar") == false);
    CHECK(tlgs::isPathBlocked("/foo", "/foo/") == false);
    CHECK(tlgs::isPathBlocked("/foo/", "/foo") == true);
    CHECK(tlgs::isPathBlocked("/foo/bar/", "/foo") == true);
    CHECK(tlgs::isPathBlocked("/foo/", "/foo/bar") == false);
    CHECK(tlgs::isPathBlocked("/foo.txt", "/foo") == false);
    CHECK(tlgs::isPathBlocked("/foo/bar.txt", "/foo") == true);
    CHECK(tlgs::isPathBlocked("/foo/bar.txt", "/foo/*") == true);
    CHECK(tlgs::isPathBlocked("/foo/bar.txt", "*.txt") == true);
    CHECK(tlgs::isPathBlocked("/foo/bar.txt", "*.ogg") == false);
    CHECK(tlgs::isPathBlocked("/foo/dir1/bar.txt", "*.txt") == true);
    CHECK(tlgs::isPathBlocked("/foo/dir1/bar.txt", "*.txt$") == true);
    CHECK(tlgs::isPathBlocked("/foo/some_dir/bar.txt", "*some_dir*") == true);
    CHECK(tlgs::isPathBlocked("/foo/other_dir/bar.txt", "*some_dir*") == false);
    CHECK(tlgs::isPathBlocked("/foo/other_dir/baz/bar.txt", "/foo/*/baz") == true);
    CHECK(tlgs::isPathBlocked("/~testuser/gci-bin/test.txt", "/~*/cgi-bin/") == true);
    CHECK(tlgs::isPathBlocked("/foo/123/bar/456/baz", "/foo/*/bar/*/baz") == true);
    CHECK(tlgs::isPathBlocked("/foo/123/bar/baz", "/foo/*/bar/*/baz") == false);
    CHECK(tlgs::isPathBlocked("/foo/123/bar/baz", "/foo/*/bar/*") == true);
    CHECK(tlgs::isPathBlocked("/foo", "/***") == true);

    // Check special regex characters are escaped
    CHECK(tlgs::isPathBlocked("/foo/(", "/foo/(") == true);
    CHECK(tlgs::isPathBlocked("/*/asd/*/.mp3", "/foo/asd/bar/1mp3") == false);
    CHECK(tlgs::isPathBlocked("/foo/\\*", "/foo/*") == true);
}
