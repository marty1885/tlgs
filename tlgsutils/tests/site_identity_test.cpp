#include <drogon/drogon_test.h>

#include <tlgsutils/site_identity.hpp>

DROGON_TEST(SiteIdentityRules)
{
    const auto document = toml::parse_str(R"(
format = 1

[[rules]]
name = "tilde-users"
hosts = ["*"]
path_prefix = "/~"
site_key = "{origin}/~{segment}"

[[rules]]
name = "sdf-users"
hosts = ["sdf.org"]
path_prefix = "/"
site_key = "{origin}/{segment}"
)");

    const auto rules = tlgs::SiteIdentityRules::fromToml(document);
    CHECK(rules.classify("gemini://example.org/~alice/post.gmi").site_key ==
          "gemini://example.org/~alice");
    CHECK(rules.classify("gemini://example.org/docs/").site_key ==
          "gemini://example.org");
    CHECK(rules.classify("gemini://sdf.org/bob/log/").site_key ==
          "gemini://sdf.org/bob");
    CHECK(rules.classify("gemini://example.org:1966/~alice/").site_key ==
          "gemini://example.org:1966/~alice");
}

DROGON_TEST(SiteIdentityRulesRejectOversizedInput)
{
    const auto document = toml::parse_str(R"(
format = 1
[[rules]]
name = "users"
hosts = ["*"]
path_prefix = "/~"
site_key = "{origin}/~{segment}"
)");
    const auto rules = tlgs::SiteIdentityRules::fromToml(document);
    CHECK_THROWS(rules.classify("gemini://example.org/~" + std::string(17000, 'a')));
}
