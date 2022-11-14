#include "proxy.hpp"

namespace cache_proxy {

Proxy::Proxy(const userver::components::ComponentConfig& config,
                   const userver::components::ComponentContext& context)
    : HttpHandlerBase(config, context),
      http_client_(context.FindComponent<userver::components::HttpClient>()
                       .GetHttpClient()),
      upstream_(config["upstream"].As<std::string>()) {}

std::string Proxy::HandleRequestThrow(
    const userver::server::http::HttpRequest& request,
    userver::server::request::RequestContext&) const {
  auto resp = ForwardRequest(request);
  request.GetHttpResponse().SetStatus(
      static_cast<userver::server::http::HttpStatus>(resp->status_code()));
  return resp->body();
}


std::shared_ptr<userver::clients::http::Response> Proxy::ForwardRequest(
    const userver::server::http::HttpRequest& request) const {
  auto response = http_client_.CreateRequest()
                      ->get(BuildUrl(request))
                      ->retry(1)
                      ->timeout(std::chrono::seconds{1})
                      ->perform();
  return response;
}

std::string
Proxy::BuildUrl(const userver::server::http::HttpRequest& request) const {
  return fmt::format("{0}/wiki/{1}", upstream_, request.GetArg("id"));
}


void AppendProxy(userver::components::ComponentList& component_list) {
  component_list.Append<Proxy>();
}

}  // namespace cache_proxy
