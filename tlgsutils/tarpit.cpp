#include <tlgsutils/tarpit.hpp>

#include <tarpit.h>

#include <drogon/HttpResponse.h>
#include <drogon/HttpViewData.h>
#include <fmt/format.h>

#include <atomic>
#include <chrono>
#include <cerrno>
#include <cstdint>
#include <memory>
#include <string>
#include <string_view>
#include <utility>

namespace
{
using namespace drogon;

enum class Format
{
    Gemini,
    Http
};

struct GeneratedPage
{
    tarpit_page value{};
    ~GeneratedPage() { tarpit_page_free(&value); }
};

constexpr uint64_t corpusSeed = 0x476d5e4b7a21d9c3ULL;

tarpit_generator* generator()
{
    static const std::unique_ptr<tarpit_generator, decltype(&tarpit_close)> instance{
        [] {
            auto options = tarpit_default_options();
            // Keep generated HTTP pages below Spartoi's 64 KiB response limit.
            options.excerpt_bytes = 512;
            return tarpit_open_embedded(corpusSeed, &options);
        }(),
        &tarpit_close};
    return instance.get();
}

uint64_t requestNonce()
{
    static std::atomic<uint64_t> sequence{0};
    const auto ticks = std::chrono::steady_clock::now().time_since_epoch().count();
    return static_cast<uint64_t>(ticks) ^ sequence.fetch_add(1, std::memory_order_relaxed);
}

HttpResponsePtr response(int status, Format format, std::string body)
{
    auto result = HttpResponse::newHttpResponse();
    result->setStatusCode(static_cast<HttpStatusCode>(status));
    result->setContentTypeCodeAndCustomString(
        CT_CUSTOM, format == Format::Http ? "text/html; charset=utf-8" : "text/gemini");
    result->setBody(std::move(body));
    result->addHeader("cache-control", "no-store");
    return result;
}

HttpResponsePtr errorResponse(int status, Format format, std::string_view message)
{
    if(format == Format::Http)
        return response(status, format,
                        fmt::format("<!doctype html><html lang=\"en\"><body><h1>{}</h1></body></html>",
                                    HttpViewData::htmlTranslate(message)));
    return response(status, format, fmt::format("# {}\n", message));
}

std::string geminiPassage(const tarpit_page& page)
{
    return fmt::format("# The Tarpit\n\n{}\n=> /tarpit/{} {}\n=> / Exit the tarpit\n",
                       page.text, page.next_token, page.link_label);
}

std::string httpPassage(const tarpit_page& page)
{
    return fmt::format(R"HTML(<!doctype html>
<html lang="en"><head><meta charset="utf-8"><title>The Tarpit</title></head>
<body><h1>The Tarpit</h1><pre>{}</pre>
<p><a href="/tarpt/{}">{}</a> · <a href="/">Exit the tarpit</a></p>
</body></html>)HTML",
                       HttpViewData::htmlTranslate(std::string_view{page.text}),
                       page.next_token,
                       HttpViewData::htmlTranslate(std::string_view{page.link_label}));
}

HttpResponsePtr warning(Format format)
{
    if(format == Format::Http)
        return response(200, format, R"HTML(<!doctype html>
<html lang="en"><head><meta charset="utf-8"><title>The Tarpit</title></head>
<body><h1>The Tarpit</h1><p>This is an endless chain of pages intended to catch crawlers.
Following it will consume your time. You have been warned.</p>
<p><a href="/tarpt/0">Descend into the tarpit</a> · <a href="/">Exit the tarpit</a></p>
</body></html>)HTML");
    return response(200, format, "# The Tarpit\n\n"
           "This is an endless chain of links intended to catch bad crawlers. "
           "Following it will consume your time and resource. You have been warned.\n\n"
           "=> /tarpit/0 Descend into the tarpit\n"
           "=> / Exit the tarpit\n");
}

tlgs::TarpitResponse passage(std::string_view token, Format format)
{
    auto* source = generator();
    if(!source)
        return {errorResponse(503, format, "Tarpit unavailable")};

    const std::string component(token);
    GeneratedPage page;
    if(tarpit_generate(source, component.c_str(), requestNonce(), &page.value) != 0)
    {
        const int status = errno == EINVAL || errno == EOVERFLOW ? 404 : 503;
        return {errorResponse(status, format, "Page unavailable")};
    }

    auto body = format == Format::Http ? httpPassage(page.value) : geminiPassage(page.value);
    const auto delay = page.value.delay_ms;
    return {response(200, format, std::move(body)), delay};
}
}

namespace tlgs
{
drogon::HttpResponsePtr geminiTarpitWarning()
{
    return warning(Format::Gemini);
}

TarpitResponse geminiTarpitPassage(std::string_view token)
{
    return passage(token, Format::Gemini);
}

drogon::HttpResponsePtr httpTarpitWarning()
{
    return warning(Format::Http);
}

drogon::HttpResponsePtr httpTarpitPassage(std::string_view token)
{
    return passage(token, Format::Http).response;
}
}
