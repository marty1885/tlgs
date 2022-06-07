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
    CHECK(url.param() == "");
    CHECK(url.fragment() == "");
    CHECK(url.str() == "gemini://localhost/aaa");

    url = tlgs::Url("gemini://localhost/aaa#123");
    CHECK(url.good() == true);
    CHECK(url.path() == "/aaa");
    CHECK(url.fragment() == "123");
    CHECK(url.str() == "gemini://localhost/aaa#123");

    url = tlgs::Url("gemini://localhost/aaa?456#123");
    CHECK(url.good() == true);
    CHECK(url.path() == "/aaa");
    CHECK(url.param() == "456");
    CHECK(url.fragment() == "123");
    CHECK(url.str() == "gemini://localhost/aaa?456#123");

    url = tlgs::Url("gemini://.smol.pub/");
    CHECK(url.good() == false);

    // no protocol, i.e. use the same protocol as the current page
    url = tlgs::Url("//smol.pub/");
    CHECK(url.good() == true);
    CHECK(url.protocol() == "");
    CHECK(url.host() == "smol.pub");
    CHECK(url.path() == "/");
    CHECK(url.str() == "//smol.pub/");

    url = tlgs::Url("//smol.pub/123456");
    CHECK(url.good() == true);
    CHECK(url.protocol() == "");
    CHECK(url.host() == "smol.pub");
    CHECK(url.path() == "/123456");
    CHECK(url.str() == "//smol.pub/123456");

    url = tlgs::Url("://");
    CHECK(url.good() == false);

    url = tlgs::Url("geini://example.com:65536/");
    CHECK(url.good() == false);

    url = tlgs::Url("geini://example.com:-1/");
    CHECK(url.good() == false);

    url = tlgs::Url("geini://example.com:0/");
    CHECK(url.good() == false);
}