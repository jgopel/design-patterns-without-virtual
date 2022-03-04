#include "with_virtual.hpp"

#include "gtest/gtest.h"

#include <type_traits>

TEST(ComponentTest, ComponentIsAComponent) {
  static_assert(std::is_base_of_v<ComponentBase, Component>);
}

TEST(ComponentTest, ComponentActionIsCorrect) {
  const Component component{};
  EXPECT_STREQ(component.action().c_str(), "Component action");
}

TEST(ProxyTest, ProxyIsAComponent) {
  static_assert(std::is_base_of_v<ComponentBase, Proxy>);
}

TEST(ProxyTest, ProxyActionIsCorrect) {
  const Proxy proxy{};
  EXPECT_STREQ(proxy.action().c_str(), "Proxy action for: Component action");
}
