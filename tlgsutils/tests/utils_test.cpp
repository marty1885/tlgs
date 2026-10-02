#include <tlgsutils/utils.hpp>
#include <tlgsutils/counter.hpp>
#include <drogon/drogon_test.h>

DROGON_TEST(CounterTracksRemainingCrawls)
{
    std::atomic<size_t> active{0};
    tlgs::Counter first(active);
    tlgs::Counter second(active);
    CHECK(active == 2);
    CHECK(first.release() == 1);
    CHECK(active == 1);
    tlgs::Counter moved(std::move(second));
    CHECK(active == 1);
    CHECK(moved.release() == 0);
    CHECK(active == 0);
}

DROGON_TEST(AsciiArtDetectorTest)
{
    std::string s = R"(
 .-----------------.
| .---------------. |
| |   _________   | |
| |  |___   ___|  | |
| |      | |      | |
| |      | |      | |
| |     _| |_     | |
| |    |_____|    | |
| |               | |
| '---------------' |
 '-----------------')";

    CHECK(tlgs::isAsciiArt(s) == true);

    s = R"|(
 .       .  .   . .   .   . .    +  .
   .  :     .    .. :. .___---------___.
  .  .   .    .  :.:. _".^ .^ ^.  '.. :"-_. .
  :       .  .  .:../:            . .^  :.:\.
   .   . :: +. :.:/: .   .    .        . . .:\
    .     . _ :::/:               .  ^ .  . .:\
. .   . - : :.:./.                        .  .:\
   . . . ::. ::\(                           . :)|
.     : . : .:.|. ######              .#######::/
 .  :-  : .:  ::|.#######           ..########:|
  .  ..  .  .. :\ ########          :######## :/
      .+ :: : -.:\ ########       . ########.:/
  .+   . . . . :.:\. #######       #######..:/
 :: . . . . ::.:..:.\           .   .   ..:/
  .   .  .. :  -::::.\.       | |     . .:/
 .  :  .  .  .-:.":.::.\             ..:/
   -.   . . . .: .:::.:.\.           .:/
   .  :      : ....::_:..:\   ___.  :/
  .  .   .:. .. .  .: :.:.:\       :/
+   .   .   : . ::. :.:. .:.|\  .:/|
.         +   .  .  ...:: ..|  --.:|
  . . .   .  .  . ... :..:.."(  ..)"
.       .      :  .   .: ::/  .  .::\
    )|";
    CHECK(tlgs::isAsciiArt(s) == true);

    s = R"(
        __   
.-----.|__|.-----.-----.
|  _  ||  ||     |  _  |
|   __||__||__|__|___  | 
|__|   station   |_____|
    )";
    CHECK(tlgs::isAsciiArt(s) == true);

    s = R"(
███████████████████▎██████▎▅████████████████▅
███████████████████▎██████▎███▎▎    █████████ ▎
█████▎━━━━━━███████▎██████▎▀████████████████▀ ▎
█████▎▎     ███████▎██████▎▅▅▅▅▅▅▅▅▅▅▅▅▅▅▅▅▅▅
█████▎▎mieum███████▎██████▎██████████████████ ▎
███████████████████▎██████▎▅▅▅▅▅▅▅▅▅▅▅▅▅▅▅▅▅▅
███████████████████▎██████▎██████████████████ ▎
███████████████████▎██████▎█████████▎▎     ██ ▎
███████████████████▎██████▎██████████████████ ▎
 ━━━━━━━━━━━━━━━━━━━ ━━━━━━ ━━━━━━━━━━━━━━━━━━
    )";
    CHECK(tlgs::isAsciiArt(s) == true);
}

DROGON_TEST(LinkCompositionTest)
{
    auto url = tlgs::Url("gemini://localhost/");
    std::string path = "/dir";
    CHECK(tlgs::linkCompose(url, path).str() == "gemini://localhost/dir");

    url = tlgs::Url("gemini://localhost/asd");
    path = "/dir";
    CHECK(tlgs::linkCompose(url, path).str() == "gemini://localhost/dir");

    url = tlgs::Url("gemini://localhost/asd");
    path = "dir";
    CHECK(tlgs::linkCompose(url, path).str() == "gemini://localhost/dir");

    url = tlgs::Url("gemini://localhost/asd/");
    path = "dir";
    CHECK(tlgs::linkCompose(url, path).str() == "gemini://localhost/asd/dir");

    url = tlgs::Url("gemini://localhost/asd/");
    path = "dir/";
    CHECK(tlgs::linkCompose(url, path).str() == "gemini://localhost/asd/dir/");

    url = tlgs::Url("gemini://localhost/asd#123456");
    path = "dir/";
    CHECK(tlgs::linkCompose(url, path).str() == "gemini://localhost/dir/");

    url = tlgs::Url("gemini://localhost/asd#123456");
    path = "dir#789";
    CHECK(tlgs::linkCompose(url, path).str() == "gemini://localhost/dir#789");

    url = tlgs::Url("gemini://localhost/asd/zxc");
    path = "../dir";
    CHECK(tlgs::linkCompose(url, path).str() == "gemini://localhost/dir");

    url = tlgs::Url("gemini://localhost/asd?123");
    path = "dir";
    CHECK(tlgs::linkCompose(url, path).str() == "gemini://localhost/dir");

    url = tlgs::Url("gemini://localhost/asd");
    path = "dir?123";
    CHECK(tlgs::linkCompose(url, path).str() == "gemini://localhost/dir?123");

    url = tlgs::Url("gemini://localhost/asd#123");
    path = "dir?789";
    CHECK(tlgs::linkCompose(url, path).str() == "gemini://localhost/dir?789");

    url = tlgs::Url("gemini://127.0.0.1/asd#123");
    path = "dir?789";
    CHECK(tlgs::linkCompose(url, path).str() == "gemini://127.0.0.1/dir?789");

    url = tlgs::Url("gemini://localhost/test/one.gmi");
    path = "../two.gmi";
    CHECK(tlgs::linkCompose(url, path).str() == "gemini://localhost/two.gmi");

    url = tlgs::Url("gemini://dhammapada.michaelnordmeyer.com/chapter-3/33.gmi");
    path = "../chapter-2/32.gmi";
    CHECK(tlgs::linkCompose(url, path).str() == "gemini://dhammapada.michaelnordmeyer.com/chapter-2/32.gmi");
}

DROGON_TEST(NonUriActionTest)
{
  CHECK(tlgs::isNonUriAction("javascript:void(2)") == true);
  CHECK(tlgs::isNonUriAction("mailto:tom@example.com") == true);
  CHECK(tlgs::isNonUriAction("gemini://localhost") == false);
  CHECK(tlgs::isNonUriAction("relative/page.gmi") == false);
  CHECK(tlgs::isNonUriAction("/absolute/page.gmi") == false);
}

DROGON_TEST(PgSQLEscape)
{
  CHECK(tlgs::pgSQLRealEscape("test") == "test");
  CHECK(tlgs::pgSQLRealEscape("test'") == "test''");
  CHECK(tlgs::pgSQLRealEscape("test''") == "test''''");
  CHECK(tlgs::pgSQLRealEscape("\n") == "\\n");
}

DROGON_TEST(XXHashTest)
{
  // xxHash64 hex-encodes the hash in host (little-endian) byte order rather
  // than canonical XXH64 order (C49AACF8080FE47F). Stored hashes depend on it.
  CHECK(tlgs::xxHash64("Hello, World!") == "7FE40F08F8AC9AC4");
}

DROGON_TEST(GeminiLineTextTest)
{
    CHECK(tlgs::geminiLineText("plain title") == "plain title");
    CHECK(tlgs::geminiLineText("a\n=> gemini://evil x") == "a => gemini://evil x");
    CHECK(tlgs::geminiLineText("a\r\nb\tc\x7f") == "a  b c ");
    CHECK(tlgs::geminiLineText("日本語") == "日本語");
}

DROGON_TEST(GeminiLinkTargetTest)
{
    CHECK(tlgs::geminiLinkTarget("gemini://example.com/a?b") == "gemini://example.com/a?b");
    CHECK(tlgs::geminiLinkTarget("gemini://example.com/a\n=> x") == "gemini://example.com/a%0A=>%20x");
    CHECK(tlgs::geminiLinkTarget("gemini://example.com/\r\t") == "gemini://example.com/%0D%09");
}
