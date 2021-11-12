#include <url_parser.hpp>
#include <drogon/drogon_test.h>

DROGON_TEST(UrlParserTest)
{
    auto url = tlgs::Url("http://example.com");
    CHECK(url.good() == true);
    CHECK(url.protocol() == "http");
    CHECK(url.host() == "example.com");
    CHECK(url.port() == 80); // guessed from the protocol tring
    CHECK(url.path() == "/");
    CHECK(url.param() == "");

    url = tlgs::Url("http:/example.com");
    CHECK(url.good() == false);

    url = tlgs::Url("$!@://example.com");
    CHECK(url.good() == false);

    url = tlgs::Url("./example.com");
    CHECK(url.good() == false);

    url = tlgs::Url("http://example.com:ababababa");
    CHECK(url.good() == false);

    url = tlgs::Url("http://example.com:/");
    CHECK(url.good() == false);

    url = tlgs::Url("://example.com");
    CHECK(url.good() == false);

    url = tlgs::Url("");
    CHECK(url.good() == false);

    url = tlgs::Url("gemini://localhost/index.gmi?15");
    CHECK(url.good() == true);
    CHECK(url.protocol() == "gemini");
    CHECK(url.host() == "localhost");
    CHECK(url.port() == 1965);
    CHECK(url.path() == "/index.gmi");
    CHECK(url.param() == "15");
    CHECK(url.str() == "gemini://localhost/index.gmi?15");

    url = tlgs::Url("gemini://localhost:1965/index.gmi?15");
    CHECK(url.good() == true);
    CHECK(url.str() == "gemini://localhost/index.gmi?15");

    url = tlgs::Url("gemini://localhost:1966");
    CHECK(url.good() == true);
    CHECK(url.port() == 1966);
    CHECK(url.path() == "/");
    CHECK(url.str() == "gemini://localhost:1966/");

    url = tlgs::Url("GEMINI://localhost");
    CHECK(url.good() == true);
    CHECK(url.protocol() == "gemini");

    url = tlgs::Url("gemini://localhost/a/../b");
    CHECK(url.good() == true);
    CHECK(url.path() == "/b");

    url = tlgs::Url("gemini://localhost:1965/aaa");
    CHECK(url.good() == true);
    CHECK(url.path() == "/aaa");
    CHECK(url.str() == "gemini://localhost/aaa");
}