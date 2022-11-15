#include "regular_cache.hpp"

namespace cache_proxy {

RegularLruCacheComponent::RegularLruCacheComponent(
    const userver::components::ComponentConfig& config,
    const userver::components::ComponentContext& context)
    : userver::cache::LruCacheComponent<Key, Value>(config, context),
      wiki_bench_client_(
          context.FindComponent<WikiBenchClient>("wiki-bench-client")) {}

Value RegularLruCacheComponent::GetValueForExpiredKeyFromRemote(
    const Key& key) {
  auto data = GetCache().GetOptional(key);
  if (data.has_value()) {
    return data.value();
  }
  data = wiki_bench_client_.GetPageID(key);
  GetCache().GetCache()->Put(key, data.value());
  return data.value();
}

Value RegularLruCacheComponent::DoGetByKey(const Key& key) {
  return GetValueForExpiredKeyFromRemote(key);
}

void AppendRegularLruCache(userver::components::ComponentList& component_list) {
  component_list.Append<RegularLruCacheComponent>();
}

}  // namespace cache_proxy
