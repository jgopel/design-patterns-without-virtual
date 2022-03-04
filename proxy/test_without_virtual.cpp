#include "without_virtual.hpp"

#include "gtest/gtest.h"

TEST(ComponentTest, ComponentIsAComponent) {
  static_assert(CComponent<Component>);
}

TEST(ComponentTest, ComponentActionIsCorrect) {
  const Component component{};
  EXPECT_STREQ(component.action().c_str(), "Component action");
}

TEST(ProxyTest, ProxyIsAComponent) { static_assert(CComponent<Proxy>); }

TEST(ProxyTest, ProxyActionIsCorrect) {
  const Proxy proxy{};
  EXPECT_STREQ(proxy.action().c_str(), "Proxy action for: Component action");
}
