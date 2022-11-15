#include "proxy.hpp"

#include <userver/http/url.hpp>

namespace cache_proxy {

Proxy::Proxy(const userver::components::ComponentConfig& config,
             const userver::components::ComponentContext& context)
    : HttpHandlerBase(config, context),
      regular_lru_(context.FindComponent<RegularLruCacheComponent>("regular-lru-cache"))
      {}

std::string Proxy::HandleRequestThrow(
    const userver::server::http::HttpRequest& request,
    userver::server::request::RequestContext&) const {
  userver::formats::json::ValueBuilder builder;
  builder["page_id"] = regular_lru_.DoGetByKey(request.GetArg("url"));
  return builder.ExtractValue().As<std::string>();
}

void AppendProxy(userver::components::ComponentList& component_list) {
  component_list.Append<Proxy>();
}

}  // namespace cache_proxy
