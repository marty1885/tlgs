#include <spartoi/SpartanServerPlugin.hpp>

#include <tlgsutils/tarpit.hpp>

#include <drogon/HttpRequest.h>
#include <drogon/HttpResponse.h>
#include <fmt/format.h>
#include <json/json.h>

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <mutex>
#include <optional>
#include <random>
#include <string>
#include <string_view>
#include <unordered_map>

namespace
{
using namespace drogon;
using Days = std::chrono::sys_days;

constexpr std::string_view homePage = R"HTML(<!doctype html>
<html lang="en"><head><meta charset="utf-8"><title>TLGS Index Console</title></head>
<body><h1>TLGS Index Console</h1><p>Index operations are available through the maintenance API.</p>
<nav><a href="/console/">Console</a> · <a href="/api/v1/status">API status</a></nav>
<p><a href="/tarpt/0">Crawler tarpit (endless)</a> · <a href="/tarpt">Read the warning</a></p>
<script src="/assets/console.js" defer></script></body></html>
)HTML";

constexpr std::string_view loginPage = R"HTML(<!doctype html>
<html lang="en"><head><meta charset="utf-8"><title>TLGS Index Console / Sign in</title></head>
<body><h1>Index Console</h1><p>Interactive sign-in is unavailable on this listener.</p>
<p>Existing maintenance clients can use the API. Check <a href="/api/v1/status">service status</a>
and <a href="/api/v1/index/jobs">recent jobs</a>.</p>
<p><a href="/tarpt/0">Crawler tarpit (endless)</a> · <a href="/tarpt">Read the warning</a></p>
</body></html>
)HTML";

constexpr std::string_view robotsPage = R"TXT(User-agent: *
Disallow: /console/maintenance/
Disallow: /internal/export/
Disallow: /tarpt
Disallow: /tarpt/
)TXT";

constexpr std::string_view consoleScript = R"JS(/* Legacy console bootstrap. The index view now reads from the API. */
const indexApi = "/api/v1/index";
const recentJobs = `${indexApi}/jobs`;
const leaseStatus = `${indexApi}/leases/current`;
// Replay requires an exclusive writer lease and a maintenance principal.
)JS";

struct IndexJob
{
    std::string id;
    std::string date;
    bool current;
};

using Clock = std::chrono::steady_clock;

struct Diagnostic
{
    std::string jobId;
    Clock::time_point started;
    int64_t expectedRevision;
};

constexpr auto diagnosticLifetime = std::chrono::minutes{20};
constexpr auto diagnosticRuntime = std::chrono::seconds{50};
constexpr size_t maxDiagnostics = 256;

class DiagnosticStore
{
  public:
    std::optional<std::string> start(const IndexJob& job, int64_t expectedRevision)
    {
        const auto now = Clock::now();
        std::lock_guard lock(mutex_);
        for(auto it = entries_.begin(); it != entries_.end();)
        {
            if(now - it->second.started >= diagnosticLifetime)
                it = entries_.erase(it);
            else
                ++it;
        }
        if(entries_.size() >= maxDiagnostics)
            return std::nullopt;

        std::string token;
        do
        {
            token = fmt::format("{:016x}{:016x}", tokens_(), tokens_());
        } while(entries_.contains(token));
        entries_.emplace(token, Diagnostic{job.id, now, expectedRevision});
        return token;
    }

    std::optional<Diagnostic> find(std::string_view token, std::string_view jobId)
    {
        std::lock_guard lock(mutex_);
        const auto it = entries_.find(std::string(token));
        if(it == entries_.end() || it->second.jobId != jobId)
            return std::nullopt;
        if(Clock::now() - it->second.started >= diagnosticLifetime)
        {
            entries_.erase(it);
            return std::nullopt;
        }
        return it->second;
    }

  private:
    std::mutex mutex_;
    std::unordered_map<std::string, Diagnostic> entries_;
    std::mt19937_64 tokens_{std::random_device{}()};
};

DiagnosticStore& diagnostics()
{
    static DiagnosticStore store;
    return store;
}

Days currentDay()
{
    return std::chrono::floor<std::chrono::days>(std::chrono::system_clock::now());
}

IndexJob jobFor(Days day, bool current)
{
    const std::chrono::year_month_day calendarDay{day};
    const auto date = fmt::format("{:04}-{:02}-{:02}",
                                  int(calendarDay.year()),
                                  unsigned(calendarDay.month()),
                                  unsigned(calendarDay.day()));
    const auto number = static_cast<uint64_t>(day.time_since_epoch().count());
    const auto suffix = (number * 2654435761ULL + 1013904223ULL) % 1000000;
    return {fmt::format("idx-{}-{:06}", date, suffix), date, current};
}

std::optional<IndexJob> findJob(std::string_view id, Days today)
{
    // Retain old links long enough for a returning scanner to find its history.
    for(int age = 0; age < 60; ++age)
    {
        auto job = jobFor(today - std::chrono::days{age}, age == 0);
        if(job.id == id)
            return job;
    }
    return std::nullopt;
}

std::string jobPath(const IndexJob& job)
{
    return "/api/v1/index/jobs/" + job.id;
}

std::string exportPath(const IndexJob& job)
{
    return "/internal/export/index-manifest-" + job.id + ".json";
}

Json::Value jobEntry(const IndexJob& job)
{
    Json::Value entry;
    entry["id"] = job.id;
    entry["day"] = job.date;
    entry["state"] = job.current ? "awaiting_lease" : "complete";
    entry["detail"] = jobPath(job);
    return entry;
}

HttpResponsePtr reply(int status, std::string_view contentType, std::string_view body)
{
    auto response = HttpResponse::newHttpResponse();
    response->setStatusCode(static_cast<HttpStatusCode>(status));
    response->setContentTypeCodeAndCustomString(CT_CUSTOM, std::string(contentType));
    response->setBody(std::string(body));
    response->addHeader("cache-control", "no-store");
    return response;
}

HttpResponsePtr jsonReply(int status, const Json::Value& body)
{
    auto response = HttpResponse::newHttpJsonResponse(body);
    response->setStatusCode(static_cast<HttpStatusCode>(status));
    response->addHeader("cache-control", "no-store");
    return response;
}

Json::Value errorBody(std::string_view code, std::string_view message = {})
{
    Json::Value body;
    body["error"] = std::string(code);
    if(!message.empty())
        body["message"] = std::string(message);
    return body;
}

HttpResponsePtr redirect(std::string_view target)
{
    auto response = reply(302, "text/plain; charset=utf-8", {});
    response->addHeader("location", std::string(target));
    return response;
}

HttpResponsePtr statusResponse(Days today)
{
    Json::Value body;
    body["service"] = "tlgs-index-console";
    body["api"] = "v1";
    body["console"] = "read-only";
    body["index_generation"] = jobFor(today - std::chrono::days{1}, false).date;
    body["index_writer"] = "lease-held";
    body["links"]["jobs"] = "/api/v1/index/jobs";
    body["links"]["lease"] = "/api/v1/index/leases/current";
    body["links"]["tarpit"] = "/tarpt/0";
    body["links"]["tarpit_warning"] = "/tarpt";
    return jsonReply(200, body);
}

HttpResponsePtr jobsResponse(Days today, int page)
{
    Json::Value body;
    Json::Value items(Json::arrayValue);
    const int firstAge = page == 1 ? 0 : 3;
    for(int age = firstAge; age < firstAge + 3; ++age)
        items.append(jobEntry(jobFor(today - std::chrono::days{age}, age == 0)));
    body["items"] = std::move(items);
    if(page == 1)
        body["next"] = "/api/v1/index/jobs/page/2";
    else
        body["next"] = Json::nullValue;
    return jsonReply(200, body);
}

HttpResponsePtr jobDetailResponse(const IndexJob& job)
{
    const auto base = jobPath(job);
    Json::Value body;
    body["id"] = job.id;
    body["day"] = job.date;
    body["state"] = job.current ? "awaiting_lease" : "complete";
    body["phase"] = "snapshot reconciliation";
    body["log"] = base + "/log";
    body["diagnostics"] = job.current ? Json::Value(base + "/diagnostics")
                                        : Json::Value(Json::nullValue);
    body["replay"] = base + "/replay";
    body["lease"] = "/api/v1/index/leases/current";
    return jsonReply(200, body);
}

HttpResponsePtr jobLogResponse(const IndexJob& job)
{
    const auto check = job.current
                     ? fmt::format("manifest revision check pending; run POST {}/diagnostics", jobPath(job))
                     : "manifest revision check passed";
    const auto log = fmt::format("[{}] snapshot reconciliation scheduled\n"
                                 "[{}] source manifest accepted\n"
                                 "[{}] snapshot staged at {}\n"
                                 "[{}] origin lease path /internal/index/leases/current {}\n"
                                 "[{}] {}\n"
                                 "[{}] {}\n",
                                 job.date, job.date, job.date, exportPath(job),
                                 job.date, job.current ? "held by reconciler" : "released",
                                 job.date, check,
                                 job.date, job.current ? "replay awaiting maintenance principal"
                                                       : "snapshot reconciliation complete");
    return reply(200, "text/plain; charset=utf-8", log);
}

HttpResponsePtr startDiagnosticResponse(const IndexJob& job, Days today)
{
    const auto token = diagnostics().start(job, today.time_since_epoch().count());
    if(!token)
        return jsonReply(503, errorBody("diagnostic_capacity_reached", "Try again later."));

    const auto resultPath = fmt::format("{}/diagnostics/{}", jobPath(job), *token);
    Json::Value body;
    body["id"] = *token;
    body["state"] = "running";
    body["result"] = resultPath;
    auto response = jsonReply(202, body);
    response->addHeader("location", resultPath);
    response->addHeader("retry-after", "20");
    return response;
}

HttpResponsePtr diagnosticResponse(const IndexJob& job, std::string_view token)
{
    const auto diagnostic = diagnostics().find(token, job.id);
    if(!diagnostic)
        return {};

    Json::Value body;
    body["id"] = std::string(token);
    body["job"] = job.id;
    if(Clock::now() - diagnostic->started < diagnosticRuntime)
    {
        body["state"] = "running";
        body["phase"] = "comparing origin lease revision";
        auto response = jsonReply(202, body);
        response->addHeader("retry-after", "20");
        return response;
    }

    body["state"] = "complete";
    body["checks"]["manifest"] = "passed";
    body["checks"]["snapshot"] = "staged";
    body["checks"]["origin_lease_revision"] = "mismatch";
    body["expected_revision"] = fmt::format("r{}", diagnostic->expectedRevision);
    body["observed_revision"] = fmt::format("r{}", diagnostic->expectedRevision - 1);
    body["origin_path"] = "/internal/index/leases/current";
    body["next_step"] = "Confirm the origin lease revision before replay.";
    return jsonReply(200, body);
}

HttpResponsePtr jobRoute(std::string_view path, HttpMethod method, Days today)
{
    constexpr std::string_view prefix = "/api/v1/index/jobs/";
    if(!path.starts_with(prefix))
        return {};

    auto tail = path.substr(prefix.size());
    std::string_view action;
    if(const auto slash = tail.find('/'); slash != std::string_view::npos)
    {
        action = tail.substr(slash);
        tail = tail.substr(0, slash);
    }
    const auto job = findJob(tail, today);
    if(!job)
        return {};

    const bool reading = method == Get || method == Head;
    if(reading && action.empty())
        return jobDetailResponse(*job);
    if(reading && action == "/log")
        return jobLogResponse(*job);
    if(method == Post && action == "/diagnostics" && job->current)
        return startDiagnosticResponse(*job, today);
    constexpr std::string_view diagnosticPrefix = "/diagnostics/";
    if(reading && action.starts_with(diagnosticPrefix))
        return diagnosticResponse(*job, action.substr(diagnosticPrefix.size()));
    if(method == Post && action == "/replay")
    {
        auto body = errorBody("maintenance_principal_required",
                              "Only a maintenance principal may replay an index job.");
        body["lease"] = "/api/v1/index/leases/current";
        return jsonReply(403, body);
    }
    return {};
}

HttpResponsePtr leaseResponse(Days today, const IndexJob& currentJob)
{
    const auto revision = fmt::format("r{}", today.time_since_epoch().count());
    Json::Value body;
    body["scope"] = "index-writer";
    body["holder"] = "reconciler";
    body["revision"] = revision;
    body["origin_path"] = "/internal/index/leases/current";
    body["release"] = "/api/v1/index/leases/current";
    body["replay"] = jobPath(currentJob) + "/replay";
    auto response = jsonReply(200, body);
    response->addHeader("etag", "\"" + revision + "\"");
    return response;
}

HttpResponsePtr decoyResponse(const HttpRequestPtr& request)
{
    const auto& path = request->path();
    const auto method = request->method();
    const bool reading = method == Get || method == Head;

    if(reading && (path == "/tarpt" || path == "/tarpt/"))
        return tlgs::httpTarpitWarning();
    constexpr std::string_view tarpitPrefix = "/tarpt/";
    if(reading && path.starts_with(tarpitPrefix))
        return tlgs::httpTarpitPassage(std::string_view(path).substr(tarpitPrefix.size()));

    if(reading && path == "/")
        return reply(200, "text/html; charset=utf-8", homePage);

    if(reading && path == "/robots.txt")
        return reply(200, "text/plain; charset=utf-8", robotsPage);

    if(reading && (path == "/console" || path == "/console/" || path == "/admin"))
        return redirect("/console/login");

    if(reading && path == "/console/login")
        return reply(200, "text/html; charset=utf-8", loginPage);

    if(reading && path == "/assets/console.js")
        return reply(200, "application/javascript; charset=utf-8", consoleScript);

    const auto today = currentDay();
    const auto currentJob = jobFor(today, true);

    if(reading && path == "/api/v1/status")
        return statusResponse(today);

    if(reading && (path == "/api/v1/index/jobs" || path == "/api/v1/index/jobs/"))
        return jobsResponse(today, 1);

    if(reading && path == "/api/v1/index/jobs/page/2")
        return jobsResponse(today, 2);

    if(auto response = jobRoute(path, method, today))
        return response;

    if(reading && path == "/api/v1/index/leases/current")
        return leaseResponse(today, currentJob);

    if(method == Delete && path == "/api/v1/index/leases/current")
        return jsonReply(403, errorBody("maintenance_principal_required",
                                        "Only a maintenance principal may release the writer lease."));

    if(reading && path.starts_with("/internal/export/index-manifest-"))
    {
        for(int age = 0; age < 60; ++age)
            if(path == exportPath(jobFor(today - std::chrono::days{age}, age == 0)))
                return jsonReply(403, errorBody("maintenance_principal_required",
                                                "Snapshot exports are restricted to maintenance clients."));
    }

    if(reading && path == "/internal/index/leases/current")
        return jsonReply(403, errorBody("maintenance_principal_required",
                                        "Origin lease inspection is restricted to maintenance clients."));

    if(reading && path == "/console/maintenance/")
        return redirect(exportPath(currentJob));

    if(reading && (path == "/.env" || path == "/config.json"))
        return reply(403, "text/plain; charset=utf-8", "Console configuration is not public.\n");

    auto notFound = errorBody("route_not_found");
    notFound["service"] = "tlgs-index-console";
    return jsonReply(404, notFound);
}
}

void registerDecoyHandler()
{
    spartoi::registerAccidentalHttpHandler(
        [](HttpRequestPtr&& request, spartoi::AccidentalHttpCallback&& callback) {
            callback(decoyResponse(request));
        });
}
