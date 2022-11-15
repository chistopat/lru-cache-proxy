#pragma once

#include <userver/cache/lru_cache_component_base.hpp>
#include <userver/components/component_list.hpp>

#include "wikibench.hpp"

namespace cache_proxy {

using Key = std::string;
using Value = int64_t;

class RegularLruCacheComponent final
    : public userver::cache::LruCacheComponent<Key, Value> {
 public:
  static constexpr auto kName = "regular-lru-cache";

  RegularLruCacheComponent(
      const userver::components::ComponentConfig& config,
      const userver::components::ComponentContext& context);

  Value DoGetByKey(const Key& key) override;

 private:
  Value GetValueForExpiredKeyFromRemote(const Key& key);

  WikiBenchClient& wiki_bench_client_;
};

void AppendRegularLruCache(userver::components::ComponentList& component_list);

}  // namespace cache_proxy