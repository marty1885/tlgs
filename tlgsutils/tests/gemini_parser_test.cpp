#include <drogon/drogon_test.h>
#include <dremini/GeminiParser.hpp>
#include <tlgsutils/gemini_parser.hpp>
using namespace dremini;

DROGON_TEST(GeminiParserBasics)
{
    auto nodes = dremini::parseGemini("# Heading");
    REQUIRE(nodes.size() == 1);
    CHECK(nodes[0].text == "Heading");
    CHECK(nodes[0].type == "heading1");
    CHECK(nodes[0].orig_text == "# Heading");
    CHECK(nodes[0].meta == "");

    nodes = dremini::parseGemini("## Heading2");
    REQUIRE(nodes.size() == 1);
    CHECK(nodes[0].text == "Heading2");
    CHECK(nodes[0].type == "heading2");
    CHECK(nodes[0].orig_text == "## Heading2");
    CHECK(nodes[0].meta == "");

    nodes = dremini::parseGemini("### Heading3");
    REQUIRE(nodes.size() == 1);
    CHECK(nodes[0].text == "Heading3");
    CHECK(nodes[0].type == "heading3");
    CHECK(nodes[0].orig_text == "### Heading3");
    CHECK(nodes[0].meta == "");

    nodes = dremini::parseGemini("=> gemini://example.com Example Link");
    REQUIRE(nodes.size() == 1);
    CHECK(nodes[0].text == "Example Link");
    CHECK(nodes[0].type == "link");
    CHECK(nodes[0].meta == "gemini://example.com");

    nodes = dremini::parseGemini("=> gemini://example.com");
    REQUIRE(nodes.size() == 1);
    CHECK(nodes[0].text == "");
    CHECK(nodes[0].type == "link");
    CHECK(nodes[0].meta == "gemini://example.com");

    nodes = dremini::parseGemini("=>gemini://example.com");
    REQUIRE(nodes.size() == 1);
    CHECK(nodes[0].text == "");
    CHECK(nodes[0].type == "link");
    CHECK(nodes[0].meta == "gemini://example.com");

    nodes = dremini::parseGemini("Hello World");
    REQUIRE(nodes.size() == 1);
    CHECK(nodes[0].text == "Hello World");
    CHECK(nodes[0].type == "text");
    CHECK(nodes[0].meta == "");

    nodes = dremini::parseGemini("```\nHello World\n```");
    REQUIRE(nodes.size() == 1);
    CHECK(nodes[0].text == "Hello World\n");
    CHECK(nodes[0].type == "preformatted_text");
    CHECK(nodes[0].meta == "");

    nodes = dremini::parseGemini("\n\n");
    REQUIRE(nodes.size() == 2);
    CHECK(nodes[0].type == "text");
    CHECK(nodes[1].type == "text");
    CHECK(nodes[0].text == "");
    CHECK(nodes[1].text == "");
}

DROGON_TEST(GeminiParserLink)
{
    auto nodes = dremini::parseGemini("=>gemini://example.com Example Link");
    REQUIRE(nodes.size() == 1);
    CHECK(nodes[0].text == "Example Link");
    CHECK(nodes[0].type == "link");
    CHECK(nodes[0].meta == "gemini://example.com");

    nodes = dremini::parseGemini("=>               gemini://example.com Example Link");
    REQUIRE(nodes.size() == 1);
    CHECK(nodes[0].text == "Example Link");
    CHECK(nodes[0].type == "link");
    CHECK(nodes[0].meta == "gemini://example.com");

    nodes = dremini::parseGemini("=>               gemini://example.com         Example Link");
    REQUIRE(nodes.size() == 1);
    CHECK(nodes[0].text == "Example Link");
    CHECK(nodes[0].type == "link");
    CHECK(nodes[0].meta == "gemini://example.com");

    nodes = dremini::parseGemini("=>gemini://example.com");
    REQUIRE(nodes.size() == 1);
    CHECK(nodes[0].text == "");
    CHECK(nodes[0].type == "link");
    CHECK(nodes[0].meta == "gemini://example.com");

    nodes = dremini::parseGemini("=>\tgemini://example.com");
    REQUIRE(nodes.size() == 1);
    CHECK(nodes[0].text == "");
    CHECK(nodes[0].type == "link");
    CHECK(nodes[0].meta == "gemini://example.com");

    nodes = dremini::parseGemini("=>\tgemini://example.com\t\tHello");
    REQUIRE(nodes.size() == 1);
    CHECK(nodes[0].text == "Hello");
    CHECK(nodes[0].type == "link");
    CHECK(nodes[0].meta == "gemini://example.com");

    nodes = dremini::parseGemini("=>\tgemini://example.com\t\tHello    ");
    REQUIRE(nodes.size() == 1);
    CHECK(nodes[0].text == "Hello");
    CHECK(nodes[0].type == "link");
    CHECK(nodes[0].meta == "gemini://example.com");
}

DROGON_TEST(GeminiParserArticle)
{
    auto art1 = 
        "# This is a sample article\n"
        "Hello world\n"
        "* list\n"
        "\n";
    auto nodes = dremini::parseGemini(art1);
    REQUIRE(nodes.size() == 4);

}

DROGON_TEST(IsGemsub)
{
    // gemlog index
    auto nodes = dremini::parseGemini(R"(
# This is a sample article
Hello world

=> /index1.gmi 2022-01-01 First article
=> /index2.gmi 2022-01-02 Second article
=> /index2.gmi 2022-01-03 Third article
)");
    CHECK(tlgs::isGemsub(nodes) == true);

    // Random text
    nodes = dremini::parseGemini(R"(
# First First
Hello world
)");
    CHECK(tlgs::isGemsub(nodes) == false);

    // index, but not gemlog index
    nodes = dremini::parseGemini(R"(
# First First
Hello world

=> / home
=> /food food
=> /cars cars
)");
    CHECK(tlgs::isGemsub(nodes) == false);

    // index, but not to gemini. Sttll considered gemsub
    nodes = dremini::parseGemini(R"(
# First First
Hello world

=> https://example.com/test1.html 2022-01-01 First article
=> https://example.com/test2.html 2022-01-02 Second article
=> https://example.com/test3.html 2022-01-03 Third article
)");
    CHECK(tlgs::isGemsub(nodes) == true);

    // index, relative links
    nodes = dremini::parseGemini(R"(
# First First
Hello world

=> /test1.html 2022-01-01 First article
=> /test2.html 2022-01-02 Second article
=> /test3.html 2022-01-03 Third article
)");
    CHECK(tlgs::isGemsub(nodes) == true);


    // index, but now we card about if the file is hosted on the same host
    nodes = dremini::parseGemini(R"(
# First First
Hello world

=> https://example.com/test1.html 2022-01-01 First article
=> https://example.com/test2.html 2022-01-02 Second article
=> https://example.com/test3.html 2022-01-03 Third article
)");
    CHECK(tlgs::isGemsub(nodes, tlgs::Url("https://example.org")) == false);

    // require gemini feed
    nodes = dremini::parseGemini(R"(
# First First
Hello world

=> https://example.com/test1.html 2022-01-01 First article
=> https://example.com/test2.html 2022-01-02 Second article
=> https://example.com/test3.html 2022-01-03 Third article
)");
    CHECK(tlgs::isGemsub(nodes, tlgs::Url("https://example.org"), "gemini") == false);

        // require gemini feed
    nodes = dremini::parseGemini(R"(
# First First
Hello world

=> gemini://example.com/test1.html 2022-01-01 First article
=> gemini://example.com/test2.html 2022-01-02 Second article
=> gemini://example.com/test3.html 2022-01-03 Third article
)");
    CHECK(tlgs::isGemsub(nodes, tlgs::Url("https://example.com"), "gemini") == true);

        // index, links on same host
    nodes = dremini::parseGemini(R"(
# First First
Hello world

=> /test1.html 2022-01-01 First article
=> /test2.html 2022-01-02 Second article
=> /test3.html 2022-01-03 Third article
)");
    CHECK(tlgs::isGemsub(nodes, tlgs::Url("https://example.com"), "gemini") == true);
    
    // index, relative links
    nodes = dremini::parseGemini(R"(
# First First
Hello world

=> test1.html 2022-01-01 First article
=> test2.html 2022-01-02 Second article
=> test3.html 2022-01-03 Third article
)");
    CHECK(tlgs::isGemsub(nodes, tlgs::Url("https://example.com"), "gemini") == true);
}
