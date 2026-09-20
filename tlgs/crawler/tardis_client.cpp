#include "tardis_client.hpp"

#include <stdexcept>
#include <string_view>
#include <unordered_map>

#include <zstd.h>
#include <nlohmann/json.hpp>
#include <dremini/GeminiClient.hpp>

using namespace drogon;

namespace
{
std::string encodePathSegment(std::string_view input)
{
    static constexpr char hex[] = "0123456789ABCDEF";
    std::string output;
    for(const unsigned char c : input) {
        if((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') ||
           (c >= '0' && c <= '9') || c == '-' || c == '_' || c == '.')
            output.push_back(static_cast<char>(c));
        else {
            output += '%'; output += hex[c >> 4]; output += hex[c & 15];
        }
    }
    return output;
}

std::string decompressZstd(std::string_view compressed)
{
    ZSTD_DStream *stream = ZSTD_createDStream();
    if(!stream)
        throw std::runtime_error("cannot create zstd decoder");
    const auto freeStream = std::unique_ptr<ZSTD_DStream, decltype(&ZSTD_freeDStream)>(stream, ZSTD_freeDStream);
    const auto initial = ZSTD_initDStream(stream);
    if(ZSTD_isError(initial))
        throw std::runtime_error("cannot initialize zstd decoder");
    ZSTD_inBuffer in{compressed.data(), compressed.size(), 0};
    std::string output;
    std::vector<char> buffer(ZSTD_DStreamOutSize());
    while(in.pos < in.size) {
        ZSTD_outBuffer out{buffer.data(), buffer.size(), 0};
        const auto result = ZSTD_decompressStream(stream, &out, &in);
        if(ZSTD_isError(result))
            throw std::runtime_error(std::string("invalid zstd batch from TARDIS: ") + ZSTD_getErrorName(result));
        output.append(buffer.data(), out.pos);
    }
    return output;
}

std::unordered_map<std::string, std::string> parseWarcResources(std::string_view warc)
{
    std::unordered_map<std::string, std::string> bodies;
    size_t position = 0;
    while(position < warc.size()) {
        const auto record = warc.find("WARC/1.0\r\n", position);
        if(record == std::string_view::npos)
            break;
        const auto headerEnd = warc.find("\r\n\r\n", record);
        if(headerEnd == std::string_view::npos)
            throw std::runtime_error("truncated WARC headers from TARDIS");
        std::string target;
        size_t contentLength = 0;
        for(size_t line = record; line < headerEnd;) {
            const auto end = warc.find("\r\n", line);
            const auto field = warc.substr(line, end - line);
            if(field.starts_with("WARC-Target-URI: "))
                target = field.substr(17);
            else if(field.starts_with("Content-Length: "))
                contentLength = std::stoull(std::string(field.substr(16)));
            line = end + 2;
        }
        const size_t body = headerEnd + 4;
        if(body + contentLength > warc.size())
            throw std::runtime_error("truncated WARC payload from TARDIS");
        if(!target.empty())
            bodies.emplace(std::move(target), std::string(warc.substr(body, contentLength)));
        position = body + contentLength;
        if(warc.substr(position, 4) == "\r\n\r\n")
            position += 4;
    }
    return bodies;
}
}

TardisClient::TardisClient(trantor::EventLoop *loop, std::string endpoint, std::string certificate,
                           std::string privateKey, std::string mode, size_t pageSize,
                           std::string changeMimeTypes, std::string bodyMimeTypes)
    : loop_(loop), endpoint_(std::move(endpoint)), certificate_(std::move(certificate)),
      privateKey_(std::move(privateKey)), mode_(std::move(mode)), pageSize_(pageSize),
      changeMimeTypes_(std::move(changeMimeTypes)),
      bodyMimeTypes_(std::move(bodyMimeTypes)) {}

Task<TardisPage> TardisClient::updates(int64_t since, int64_t till, const std::string &pageToken)
{
    auto policy = dremini::withClientCert(certificate_, privateKey_);
    std::string request = endpoint_ + "/api/v1/updates/" + mode_ + "/" + std::to_string(since) + "/" + std::to_string(till)
        + "/mime/" + encodePathSegment(changeMimeTypes_)
        + "/body-mime/" + encodePathSegment(bodyMimeTypes_);
    if(!pageToken.empty()) request += "/page/" + encodePathSegment(pageToken);
    request += "/limit/" + std::to_string(pageSize_);
    auto response = co_await dremini::sendRequestCoro(request, 30, loop_, 8 * 1024 * 1024, {}, 60, std::move(policy));
    if(response->getHeader("gemini-status") != "20")
        throw std::runtime_error("TARDIS updates returned " + response->getHeader("gemini-status") + " " + response->getHeader("meta"));
    const auto update = nlohmann::json::parse(response->body());
    TardisPage page{.hasMore = update.at("has_more").get<bool>(), .resumeToken = update.value("resume_token", ""), .till = update.at("till_unix_millis").get<int64_t>()};
    if(update.at("results").empty()) co_return page;
    std::string batch = update.at("batch_token").get<std::string>();
    std::unordered_map<std::string, std::string> bodies;
    while(!batch.empty()) {
        auto batchPolicy = dremini::withClientCert(certificate_, privateKey_);
        auto archive = co_await dremini::sendRequestCoro(endpoint_ + "/api/v1/batch/" + encodePathSegment(batch), 30, loop_, 80 * 1024 * 1024, {}, 120, std::move(batchPolicy));
        if(archive->getHeader("gemini-status") != "20") throw std::runtime_error("TARDIS batch request failed");
        auto resources = parseWarcResources(decompressZstd(archive->body()));
        auto manifestIt = resources.find("file://urn:tardis:batch:manifest");
        if(manifestIt == resources.end())
            manifestIt = resources.find("urn:tardis:batch:manifest");
        if(manifestIt == resources.end()) throw std::runtime_error("TARDIS batch has no manifest");
        const auto manifest = nlohmann::json::parse(manifestIt->second);
        for(const auto &entry : manifest.at("results")) {
            // The manifest covers every change, while WARC records are only
            // present for bodies selected by body-mime.  Do not mistake an
            // excluded body for an empty representation.
            if(entry.value("body_state", "unavailable") != "included") continue;
            if(!entry.contains("warc_target_uri"))
                throw std::runtime_error("TARDIS included batch body has no WARC target URI");
            const auto body = resources.find(entry.at("warc_target_uri").get<std::string>());
            if(body == resources.end()) throw std::runtime_error("TARDIS batch body is missing");
            bodies[entry.at("url").get<std::string>()] = body->second;
        }
        const auto nextBatch = manifest.find("next_batch_token");
        batch = nextBatch == manifest.end() || nextBatch->is_null() ? "" : nextBatch->get<std::string>();
    }
    for(const auto &entry : update.at("results")) {
        // A failed crawl can have no Gemini response at all.  TARDIS then
        // omits status_code and supplies only its failure metadata.  Preserve
        // that as status 0 so the crawler records the failure instead of
        // aborting the whole incremental-sync window.
        TardisCapture capture{.url = entry.at("url").get<std::string>(), .status = entry.value("status_code", 0), .meta = entry.value("meta", "")};
        if(const auto body = bodies.find(capture.url); body != bodies.end()) {
            capture.body = body->second;
            capture.hasBody = true;
        }
        page.captures.push_back(std::move(capture));
    }
    co_return page;
}
