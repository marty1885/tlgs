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
}

DROGON_TEST(BlockedPathTest)
{
    CHECK(tlgs::isPathBlocked("/", {"/"}) == true);
    CHECK(tlgs::isPathBlocked("/foo", {"/"}) == true);
    CHECK(tlgs::isPathBlocked("/bar", {"/foo"}) == false);
    CHECK(tlgs::isPathBlocked("/foo", {"/foobar"}) == false);
    CHECK(tlgs::isPathBlocked("/foo", {"/foo/"}) == false);
    CHECK(tlgs::isPathBlocked("/foo/", {"/foo"}) == true);
    CHECK(tlgs::isPathBlocked("/foo/bar/", {"/foo"}) == true);
    CHECK(tlgs::isPathBlocked("/foo/", {"/foo/bar"}) == false);
    CHECK(tlgs::isPathBlocked("/foo.txt", {"/foo"}) == false);
    CHECK(tlgs::isPathBlocked("/foo/bar.txt", {"/foo"}) == true);
}