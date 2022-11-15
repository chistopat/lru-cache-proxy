#pragma once

#include <userver/clients/http/component.hpp>
#include <userver/components/component_list.hpp>
#include <userver/components/loggable_component_base.hpp>

namespace cache_proxy {

class WikiBenchClient final
    : public userver::components::LoggableComponentBase {
 public:
  static constexpr std::string_view kName = "wiki-bench-client";

  WikiBenchClient(const userver::components::ComponentConfig& config,
                  const userver::components::ComponentContext& context);

  ~WikiBenchClient() final;

  std::optional<int64_t> GetPageID(const std::string& url) const;

 private:
  userver::clients::http::Client& http_client_;
  const std::string upstream_;
};

void AppendWikiBenchClient(userver::components::ComponentList& component_list);

}  // namespace cache_proxy