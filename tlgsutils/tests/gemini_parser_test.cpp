#include <drogon/drogon_test.h>
#include <gemini_parser.hpp>
using namespace tlgs;

DROGON_TEST(GeminiParserBasics)
{
    auto nodes = parseGemini("# Heading");
    REQUIRE(nodes.size() == 1);
    CHECK(nodes[0].text == "Heading");
    CHECK(nodes[0].type == "heading1");
    CHECK(nodes[0].orig_text == "# Heading");
    CHECK(nodes[0].meta == "");

    nodes = parseGemini("## Heading2");
    REQUIRE(nodes.size() == 1);
    CHECK(nodes[0].text == "Heading2");
    CHECK(nodes[0].type == "heading2");
    CHECK(nodes[0].orig_text == "## Heading2");
    CHECK(nodes[0].meta == "");

    nodes = parseGemini("### Heading3");
    REQUIRE(nodes.size() == 1);
    CHECK(nodes[0].text == "Heading3");
    CHECK(nodes[0].type == "heading3");
    CHECK(nodes[0].orig_text == "### Heading3");
    CHECK(nodes[0].meta == "");

    nodes = parseGemini("=> gemini://example.com Example Link");
    REQUIRE(nodes.size() == 1);
    CHECK(nodes[0].text == "Example Link");
    CHECK(nodes[0].type == "link");
    CHECK(nodes[0].meta == "gemini://example.com");

    nodes = parseGemini("=> gemini://example.com");
    REQUIRE(nodes.size() == 1);
    CHECK(nodes[0].text == "");
    CHECK(nodes[0].type == "link");
    CHECK(nodes[0].meta == "gemini://example.com");

    nodes = parseGemini("Hello World");
    REQUIRE(nodes.size() == 1);
    CHECK(nodes[0].text == "Hello World");
    CHECK(nodes[0].type == "text");
    CHECK(nodes[0].meta == "");

    nodes = parseGemini("```\nHello World\n```");
    REQUIRE(nodes.size() == 1);
    CHECK(nodes[0].text == "Hello World\n");
    CHECK(nodes[0].type == "preformatted_text");
    CHECK(nodes[0].meta == "");
}

DROGON_TEST(GeminiParserLink)
{
    auto nodes = parseGemini("=>gemini://example.com Example Link");
    REQUIRE(nodes.size() == 1);
    CHECK(nodes[0].text == "Example Link");
    CHECK(nodes[0].type == "link");
    CHECK(nodes[0].meta == "gemini://example.com");

    nodes = parseGemini("=>               gemini://example.com Example Link");
    REQUIRE(nodes.size() == 1);
    CHECK(nodes[0].text == "Example Link");
    CHECK(nodes[0].type == "link");
    CHECK(nodes[0].meta == "gemini://example.com");

    nodes = parseGemini("=>               gemini://example.com         Example Link");
    REQUIRE(nodes.size() == 1);
    CHECK(nodes[0].text == "Example Link");
    CHECK(nodes[0].type == "link");
    CHECK(nodes[0].meta == "gemini://example.com");

    nodes = parseGemini("=>gemini://example.com");
    REQUIRE(nodes.size() == 1);
    CHECK(nodes[0].text == "");
    CHECK(nodes[0].type == "link");
    CHECK(nodes[0].meta == "gemini://example.com");

    nodes = parseGemini("=>\tgemini://example.com");
    REQUIRE(nodes.size() == 1);
    CHECK(nodes[0].text == "");
    CHECK(nodes[0].type == "link");
    CHECK(nodes[0].meta == "gemini://example.com");

    nodes = parseGemini("=>\tgemini://example.com\t\tHello");
    REQUIRE(nodes.size() == 1);
    CHECK(nodes[0].text == "Hello");
    CHECK(nodes[0].type == "link");
    CHECK(nodes[0].meta == "gemini://example.com");

    nodes = parseGemini("=>\tgemini://example.com\t\tHello    ");
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
    auto nodes = parseGemini(art1);
    REQUIRE(nodes.size() == 4);

}
