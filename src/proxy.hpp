#pragma once

#include <userver/components/component.hpp>
#include <userver/components/component_list.hpp>
#include <userver/server/handlers/http_handler_base.hpp>

#include "regular_cache.hpp"

namespace cache_proxy {

class Proxy final : public userver::server::handlers::HttpHandlerBase {
 public:
  static constexpr std::string_view kName = "handler-proxy";

  Proxy(const userver::components::ComponentConfig& config,
        const userver::components::ComponentContext& context);

  std::string HandleRequestThrow(
      const userver::server::http::HttpRequest& request,
      userver::server::request::RequestContext&) const;

 private:
  RegularLruCacheComponent& regular_lru_;
};

void AppendProxy(userver::components::ComponentList& component_list);

}  // namespace cache_proxy