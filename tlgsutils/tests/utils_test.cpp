#include <tlgsutils/utils.hpp>
#include <drogon/drogon_test.h>

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
    CHECK(tlgs::linkCompose(url, path).str() == "gemini://localhost/asd/dir");

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
}

DROGON_TEST(NonUriActionTest)
{
  CHECK(tlgs::isNonUriAction("javascript:void(2)") == true);
  CHECK(tlgs::isNonUriAction("mailto:tom@example.com") == true);
  CHECK(tlgs::isNonUriAction("gemini://localhost") == false);
}
