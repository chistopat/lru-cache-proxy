#pragma once

#include <userver/components/component.hpp>
#include <userver/components/component_list.hpp>
#include <userver/server/handlers/http_handler_json_base.hpp>

#include "regular_cache.hpp"

namespace cache_proxy {

class Proxy final : public userver::server::handlers::HttpHandlerJsonBase {
 public:
  static constexpr std::string_view kName = "handler-proxy";

  Proxy(const userver::components::ComponentConfig& config,
        const userver::components::ComponentContext& context);

  userver::formats::json::Value HandleRequestJsonThrow(
      const userver::server::http::HttpRequest& request,
      const userver::formats::json::Value& request_json,
      userver::server::request::RequestContext&) const final;

 private:
  RegularLruCacheComponent& regular_lru_;
};

void AppendProxy(userver::components::ComponentList& component_list);

}  // namespace cache_proxy