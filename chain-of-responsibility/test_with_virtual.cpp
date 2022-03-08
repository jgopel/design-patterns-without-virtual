#include "with_virtual.hpp"

#include "gtest/gtest.h"

#include <memory>
#include <type_traits>

TEST(ComponentTest, Component1IsAComponent) {
  static_assert(std::is_base_of_v<ComponentBase, Component1>);
}

TEST(ComponentTest, Component1HandlesRequestsWithoutSuccessor) {
  Component1 component{};
  EXPECT_STREQ(component.handle_request().c_str(), "Component1 action");
}

TEST(ComponentTest, Component1HandlesRequestsWithSuccessor) {
  auto inner_component = std::make_unique<Component1>();
  Component1 component{std::move(inner_component)};
  EXPECT_STREQ(component.handle_request().c_str(),
               "Component1 action, Component1 action");
}

TEST(ComponentTest, Component2IsAComponent) {
  static_assert(std::is_base_of_v<ComponentBase, Component2>);
}

TEST(ComponentTest, Component2HandlesRequestsWithoutSuccessor) {
  Component2 component{};
  EXPECT_STREQ(component.handle_request().c_str(), "Component2 action");
}

TEST(ComponentTest, Component2HandlesRequestsWithSuccessor) {
  auto inner_component = std::make_unique<Component2>();
  Component2 component{std::move(inner_component)};
  EXPECT_STREQ(component.handle_request().c_str(),
               "Component2 action, Component2 action");
}

TEST(ComponentTest, Component1AndComponent2Compose) {
  auto inner_component = std::make_unique<Component2>();
  Component1 component{std::move(inner_component)};
  EXPECT_STREQ(component.handle_request().c_str(),
               "Component1 action, Component2 action");
}
