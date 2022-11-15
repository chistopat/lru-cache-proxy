#include <userver/formats/json.hpp>
#include <userver/http/url.hpp>

#include "wikibench.hpp"

namespace cache_proxy {

WikiBenchClient::WikiBenchClient(
    const userver::components::ComponentConfig& config,
    const userver::components::ComponentContext& context)
    : LoggableComponentBase(config, context),
      http_client_(context.FindComponent<userver::components::HttpClient>()
                       .GetHttpClient()),
      upstream_(config["upstream"].As<std::string>()) {}

WikiBenchClient::~WikiBenchClient() = default;

std::optional<int64_t> WikiBenchClient::GetPageID(
    const std::string& url) const {
  auto response = http_client_.CreateRequest()
                      ->get(userver::http::MakeUrl(upstream_, {{"url", url}}))
                      ->retry(2)
                      ->timeout(std::chrono::seconds{3})
                      ->perform();
  response->raise_for_status();
  auto body = userver::formats::json::FromString(response->body_view());
  return body["id"].As<std::optional<int64_t>>();
}

void AppendWikiBenchClient(userver::components::ComponentList& component_list) {
  component_list.Append<WikiBenchClient>();
}

}  // namespace cache_proxy