#include <drogon/HttpAppFramework.h>
#include <drogon/HttpController.h>
#include <drogon/utils/coroutine.h>
#include <tlgsutils/tarpit.hpp>

using namespace drogon;

struct TarpitController : public HttpController<TarpitController>
{
    Task<HttpResponsePtr> warning(HttpRequestPtr);
    Task<HttpResponsePtr> passage(HttpRequestPtr, std::string token);

    METHOD_LIST_BEGIN
    ADD_METHOD_TO(TarpitController::warning, "/tarpit", {Get, Head});
    ADD_METHOD_TO(TarpitController::warning, "/tarpit/", {Get, Head});
    ADD_METHOD_TO(TarpitController::passage, "/tarpit/{token}", {Get, Head});
    METHOD_LIST_END
};

Task<HttpResponsePtr> TarpitController::warning(HttpRequestPtr)
{
    co_return tlgs::geminiTarpitWarning();
}

Task<HttpResponsePtr> TarpitController::passage(HttpRequestPtr, std::string token)
{
    auto generated = tlgs::geminiTarpitPassage(token);
    if(generated.delayMs != 0)
        co_await sleepCoro(app().getLoop(), generated.delayMs / 1000.0);
    co_return generated.response;
}
