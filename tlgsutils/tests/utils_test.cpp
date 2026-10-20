#include <tlgsutils/utils.hpp>
#include <tlgsutils/counter.hpp>
#include <drogon/drogon_test.h>

DROGON_TEST(HighlightQueryKeepsPositiveTermsAndPhrases)
{
    CHECK(tlgs::highlightQuery("gemini search engines") == "gemini OR search OR engines");
    CHECK(tlgs::highlightQuery("  gemini\tOR\nspartan ") == "gemini OR spartan");
    CHECK(tlgs::highlightQuery("gemini -http -\"web browsers\" protocol") == "gemini OR protocol");
    CHECK(tlgs::highlightQuery("\"client certificates\" gemini") == "\"client certificates\" OR gemini");
    CHECK(tlgs::highlightQuery("gemini \"unfinished phrase") == "gemini OR \"unfinished phrase\"");
    CHECK(tlgs::highlightQuery("中文 café O'Reilly") == "中文 OR café OR O'Reilly");
    CHECK(tlgs::highlightQuery(" -http -\"web browsers\" OR ").empty());
    CHECK(tlgs::highlightQuery("").empty());
}

DROGON_TEST(HighlightSnippetFindsDistinctTermsAndKeepsContext)
{
    const auto mark = [](std::string_view word) {
        return std::string(1, '\x1e') + std::string(word) + '\x1f';
    };
    std::string document;
    for(size_t i = 0; i < 60; ++i)
        document += "intro ";
    document += "You can use " + mark("client") + " " + mark("certificates")
        + " for authentication in " + mark("Gemini") + " browsers. More context follows.";
    const auto snippet = tlgs::highlightSnippet(document);
    CHECK(snippet.find("[client] [certificates]") != std::string::npos);
    CHECK(snippet.find("[Gemini]") != std::string::npos);
    CHECK(snippet.starts_with("... "));
    CHECK(snippet.find('\x1e') == std::string::npos);
    CHECK(snippet.find('\x1f') == std::string::npos);
    CHECK(snippet.size() < document.size());

    // Repetition of one term must not beat a passage explaining several terms.
    document.clear();
    for(size_t i = 0; i < 50; ++i)
        document += mark("gemini") + " ";
    for(size_t i = 0; i < 40; ++i)
        document += "background ";
    document += mark("Gemini") + " uses " + mark("TLS") + " " + mark("certificates");
    const auto diverse = tlgs::highlightSnippet(document);
    CHECK(diverse.find("[TLS] [certificates]") != std::string::npos);
}

DROGON_TEST(HighlightSnippetHandlesPlainTextAndUnicode)
{
    CHECK(tlgs::highlightSnippet("").empty());
    CHECK(tlgs::highlightSnippet(" \n\t ").empty());
    CHECK(tlgs::highlightSnippet("Literal [brackets]\nremain intact.") == "Literal [brackets] remain intact.");
    const auto marked = std::string("日本語 ") + '\x1e' + "café" + '\x1f' + " and "
        + '\x1e' + "O'Reilly" + '\x1f' + ".";
    CHECK(tlgs::highlightSnippet(marked) == "日本語 [café] and [O'Reilly].");
    CHECK(tlgs::highlightSnippet(std::string(1, '\x1e') + "several words" + '\x1f') == "[several] [words]");

    std::string plain;
    for(size_t i = 0; i < 60; ++i)
        plain += "word ";
    const auto opening = tlgs::highlightSnippet(plain);
    CHECK(opening.ends_with(" ..."));
    CHECK(std::count(opening.begin(), opening.end(), ' ') == 23);
}

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

DROGON_TEST(LogTextTest)
{
    CHECK(tlgs::logText("ordinary 日本語") == "ordinary 日本語");
    CHECK(tlgs::logText("a\r\nforged\t\x1b[31m\x7f") == "a\\x0D\\x0Aforged\\x09\\x1B[31m\\x7F");
    CHECK(tlgs::logText(std::string("a\0b", 3)) == "a\\x00b");
    CHECK(tlgs::logText("\\x0A") == "\\\\x0A");
}

DROGON_TEST(UntrustedInventoryFieldsStayOnOneLine)
{
    const std::string url = "gemini://example.test\r\n=> gemini://evil.test/.well-known/security.txt";
    const auto target = tlgs::geminiLinkTarget(url);
    const auto label = tlgs::geminiLineText("example.test\r\n=> forged\tlabel");
    const auto line = "=> " + target + " " + label;
    CHECK(line.find_first_of("\r\n\t") == std::string::npos);
    CHECK(target.find("%0D%0A") != std::string::npos);
    CHECK(target.find(' ') == std::string::npos);
}

DROGON_TEST(LogTextEscapesEveryAsciiControl)
{
    for(unsigned int ch = 0; ch <= 0x7f; ++ch) {
        if(ch >= 0x20 && ch != 0x7f)
            continue;
        const auto escaped = tlgs::logText(std::string(1, static_cast<char>(ch)));
        CHECK(escaped.size() == 4);
        CHECK(escaped.substr(0, 2) == "\\x");
        CHECK(escaped.find(static_cast<char>(ch)) == std::string::npos);
    }
}
