#include <userver/clients/http/component.hpp>
#include <userver/components/minimal_server_component_list.hpp>
#include <userver/server/handlers/ping.hpp>
#include <userver/server/handlers/server_monitor.hpp>
#include <userver/server/handlers/tests_control.hpp>
#include <userver/testsuite/testsuite_support.hpp>
#include <userver/utils/daemon_run.hpp>

#include "proxy.hpp"
#include "regular_cache.hpp"
#include "wikibench.hpp"

int main(int argc, char* argv[]) {
  auto component_list = userver::components::MinimalServerComponentList()
                            .Append<userver::server::handlers::Ping>()
                            .Append<userver::components::TestsuiteSupport>()
                            .Append<userver::components::HttpClient>()
                            .Append<userver::server::handlers::TestsControl>()
                            .Append<userver::server::handlers::ServerMonitor>();

  cache_proxy::AppendProxy(component_list);
  cache_proxy::AppendRegularLruCache(component_list);
  cache_proxy::AppendWikiBenchClient(component_list);

  return userver::utils::DaemonMain(argc, argv, component_list);
}
