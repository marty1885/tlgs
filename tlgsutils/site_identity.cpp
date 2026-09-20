#include "site_identity.hpp"

#include <algorithm>
#include <cstdint>
#include <fstream>
#include <sstream>
#include <stdexcept>

#include "url_parser.hpp"
#include "utils.hpp"

namespace
{
std::string lower(std::string value)
{
    std::transform(value.begin(), value.end(), value.begin(), [](unsigned char ch) {
        return static_cast<char>(std::tolower(ch));
    });
    return value;
}

std::string originOf(const tlgs::Url& input)
{
    auto origin = input;
    origin.withPath("/").withParam("").withFragment("");
    auto result = origin.str();
    if(result.ends_with('/'))
        result.pop_back();
    return result;
}

constexpr size_t max_rules_file_size = 1024 * 1024;
constexpr size_t max_url_size = 16 * 1024;
constexpr size_t max_path_size = 8 * 1024;
constexpr size_t max_segment_size = 512;
constexpr size_t max_rule_name_size = 128;
constexpr size_t max_rule_field_size = 1024;

std::string expandTemplate(const std::string& input, const std::string& origin,
                           const std::string_view segment)
{
    std::string output;
    output.reserve(input.size() + origin.size());
    for(size_t index = 0; index < input.size();) {
        if(input.compare(index, 8, "{origin}") == 0) {
            output += origin;
            index += 8;
            continue;
        }
        if(input.compare(index, 9, "{segment}") == 0) {
            output += segment;
            index += 9;
            continue;
        }
        output += input[index++];
    }
    return output;
}

std::string requireString(const toml::value& object, const char* key,
                          const std::string& context)
{
    if(!object.contains(key))
        throw std::runtime_error(context + " requires a non-empty string `" + key + "`");
    const auto value = toml::find<std::string>(object, key);
    if(value.empty())
        throw std::runtime_error(context + " requires a non-empty string `" + key + "`");
    return value;
}
} // namespace

tlgs::SiteIdentityRules tlgs::SiteIdentityRules::fromToml(const toml::value& document,
                                                          std::string source)
{
    if(!document.is_table() || !document.contains("format") ||
       toml::find<std::int64_t>(document, "format") != 1)
        throw std::runtime_error("site identity rules require format version 1");
    if(!document.contains("rules") || !document.at("rules").is_array())
        throw std::runtime_error("site identity rules require a `rules` array");

    SiteIdentityRules result;
    std::unordered_set<std::string> names;
    const auto rule_values = toml::find<std::vector<toml::value>>(document, "rules");
    if(rule_values.size() > 1024)
        throw std::runtime_error("site identity rules file contains more than 1024 rules");
    for(const auto& value : rule_values) {
        if(!value.is_table())
            throw std::runtime_error("each site identity rule must be a table");

        Rule rule;
        rule.name = requireString(value, "name", "site identity rule");
        if(rule.name.size() > max_rule_name_size)
            throw std::runtime_error("site identity rule name is too long: " + rule.name);
        if(!names.emplace(rule.name).second)
            throw std::runtime_error("duplicate site identity rule name: " + rule.name);
        if(!value.contains("hosts") || !value.at("hosts").is_array())
            throw std::runtime_error("site identity rule `" + rule.name + "` requires hosts");
        const auto hosts = toml::find<std::vector<std::string>>(value, "hosts");
        if(hosts.empty() || hosts.size() > 1024)
            throw std::runtime_error("site identity rule `" + rule.name + "` requires hosts");
        for(const auto& host : hosts) {
            if(host.empty() || host.size() > 253)
                throw std::runtime_error("site identity rule `" + rule.name + "` has an invalid host");
            rule.hosts.emplace(lower(host));
        }

        rule.path_prefix = requireString(value, "path_prefix", "site identity rule `" + rule.name + "`");
        if(!rule.path_prefix.starts_with('/') || rule.path_prefix.size() > max_rule_field_size)
            throw std::runtime_error("site identity rule `" + rule.name + "` has an invalid path_prefix");
        rule.site_key_template = requireString(value, "site_key", "site identity rule `" + rule.name + "`");
        if(rule.site_key_template.size() > max_rule_field_size ||
           rule.site_key_template.find("{origin}") == std::string::npos ||
           rule.site_key_template.find("{segment}") == std::string::npos)
            throw std::runtime_error("site identity rule `" + rule.name +
                                     "` must include {origin} and {segment} in site_key");
        result.rules_.push_back(std::move(rule));
    }

    if(document.contains("tests")) {
        if(!document.at("tests").is_array())
            throw std::runtime_error("site identity `tests` must be an array");
        const auto test_values = toml::find<std::vector<toml::value>>(document, "tests");
        if(test_values.size() > 4096)
            throw std::runtime_error("site identity rules file contains more than 4096 tests");
        for(const auto& value : test_values) {
            SiteIdentityTest test;
            test.url = requireString(value, "url", "site identity test");
            test.expected_site_key = requireString(value, "site_key", "site identity test");
            result.tests_.push_back(std::move(test));
        }
    }

    result.source_toml_ = source.empty() ? toml::format(document) : std::move(source);
    if(result.source_toml_.size() > max_rules_file_size)
        throw std::runtime_error("site identity rules file exceeds 1 MiB");
    result.hash_ = tlgs::xxHash64(result.source_toml_);
    result.runTests();
    return result;
}

tlgs::SiteIdentityRules tlgs::SiteIdentityRules::fromFile(const std::filesystem::path& path)
{
    std::ifstream input(path);
    if(!input)
        throw std::runtime_error("cannot open site identity rules: " + path.string());
    std::ostringstream source;
    source << input.rdbuf();
    if(source.str().size() > max_rules_file_size)
        throw std::runtime_error("site identity rules file exceeds 1 MiB");
    return fromToml(toml::parse_str(source.str(), toml::spec::v(1, 0, 0)), source.str());
}

tlgs::SiteIdentity tlgs::SiteIdentityRules::classify(const std::string& url_string) const
{
    if(url_string.size() > max_url_size)
        throw std::runtime_error("cannot classify URL longer than 16 KiB");
    const Url url(url_string);
    if(!url.good())
        throw std::runtime_error("cannot classify invalid URL: " + url_string);
    if(url.path().size() > max_path_size)
        throw std::runtime_error("cannot classify URL path longer than 8 KiB: " + url_string);

    const auto origin = originOf(url);
    for(const auto& rule : rules_) {
        if(!rule.hosts.contains("*") && !rule.hosts.contains(lower(url.host())))
            continue;
        if(!url.path().starts_with(rule.path_prefix))
            continue;
        const auto segment_begin = rule.path_prefix.size();
        const auto segment_end = url.path().find('/', segment_begin);
        const auto segment = std::string_view(url.path()).substr(
            segment_begin, segment_end == std::string::npos ? std::string::npos
                                                            : segment_end - segment_begin);
        if(segment.empty())
            continue;
        if(segment.size() > max_segment_size)
            throw std::runtime_error("site identity segment exceeds 512 bytes: " + url_string);
        const auto key = expandTemplate(rule.site_key_template, origin, segment);
        if(key.empty())
            throw std::runtime_error("site identity rule `" + rule.name + "` produced an empty key");
        return {.site_key = key, .matched_rule = rule.name};
    }
    return {.site_key = origin, .matched_rule = ""};
}

void tlgs::SiteIdentityRules::runTests() const
{
    for(const auto& test : tests_) {
        const auto actual = classify(test.url).site_key;
        if(actual != test.expected_site_key)
            throw std::runtime_error("site identity test failed for " + test.url +
                                     ": expected `" + test.expected_site_key +
                                     "`, got `" + actual + "`");
    }
}
