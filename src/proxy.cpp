#include "proxy.hpp"

#include <userver/http/url.hpp>

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
  auto url =
      userver::http::MakeUrl(upstream_, {{"url", request.GetArg("url")}});
  auto response = http_client_.CreateRequest()
                      ->get(url)
                      ->retry(2)
                      ->timeout(std::chrono::seconds{3})
                      ->perform();
  return response;
}

void AppendProxy(userver::components::ComponentList& component_list) {
  component_list.Append<Proxy>();
}

}  // namespace cache_proxy
