#pragma once

#include <userver/clients/http/component.hpp>
#include <userver/components/component.hpp>
#include <userver/components/component_list.hpp>
#include <userver/engine/mutex.hpp>
#include <userver/server/handlers/http_handler_base.hpp>
#include <userver/server/http/http_status.hpp>
#include <userver/utils/assert.hpp>

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
  std::shared_ptr<userver::clients::http::Response> ForwardRequest(
      const userver::server::http::HttpRequest& request) const;

 private:
  userver::clients::http::Client& http_client_;
  const std::string upstream_;
};

void AppendProxy(userver::components::ComponentList& component_list);

}  // namespace cache_proxy