#include "hello.hpp"

#include <userver/utest/utest.hpp>

UTEST(SayHelloTo, Basic) {
  EXPECT_EQ(cache_proxy::SayHelloTo("Developer"), "Hello, Developer!\n");
  EXPECT_EQ(cache_proxy::SayHelloTo({}), "Hello, unknown user!\n");
}
