#include "proxy.hpp"

namespace cache_proxy {

Proxy::Proxy(const userver::components::ComponentConfig& config,
             const userver::components::ComponentContext& context)
    : HttpHandlerJsonBase(config, context),
      regular_lru_(context.FindComponent<RegularLruCacheComponent>(
          "regular-lru-cache")) {}

userver::formats::json::Value Proxy::HandleRequestJsonThrow(
    const userver::server::http::HttpRequest& request,
    const userver::formats::json::Value&,
    userver::server::request::RequestContext&) const {
  userver::formats::json::ValueBuilder builder;
  builder["page_id"] = regular_lru_.DoGetByKey(request.GetArg("url"));
  return builder.ExtractValue();
}

void AppendProxy(userver::components::ComponentList& component_list) {
  component_list.Append<Proxy>();
}

}  // namespace cache_proxy
