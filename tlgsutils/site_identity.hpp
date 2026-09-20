#pragma once

#include <filesystem>
#include <string>
#include <unordered_set>
#include <vector>

#include <toml.hpp>

namespace tlgs
{

struct SiteIdentity
{
    std::string site_key;
    std::string matched_rule;
};

struct SiteIdentityTest
{
    std::string url;
    std::string expected_site_key;
};

class SiteIdentityRules
{
public:
    static SiteIdentityRules fromToml(const toml::value& document,
                                      std::string source = {});
    static SiteIdentityRules fromFile(const std::filesystem::path& path);

    SiteIdentity classify(const std::string& url) const;
    void runTests() const;

    const std::string& sourceToml() const { return source_toml_; }
    const std::string& hash() const { return hash_; }
    size_t ruleCount() const { return rules_.size(); }
    const std::vector<SiteIdentityTest>& tests() const { return tests_; }

private:
    struct Rule
    {
        std::string name;
        std::unordered_set<std::string> hosts;
        std::string path_prefix;
        std::string site_key_template;
    };

    std::vector<Rule> rules_;
    std::vector<SiteIdentityTest> tests_;
    std::string source_toml_;
    std::string hash_;
};

} // namespace tlgs
