#include "without_virtual.hpp"

#include "gtest/gtest.h"

TEST(ComponentTest, Component1IsAComponent) {
  static_assert(CComponent<Component1<>>);
}

TEST(ComponentTest, Component1HandlesRequestsWithoutSuccessor) {
  Component1 component{};
  EXPECT_STREQ(component.handle_request().c_str(), "Component1 action");
}

TEST(ComponentTest, Component1HandlesRequestsWithSuccessor) {
  Component1 successor{};
  Component1 component{successor};
  EXPECT_STREQ(component.handle_request().c_str(),
               "Component1 action, Component1 action");
}

TEST(ComponentTest, Component2IsAComponent) {
  static_assert(CComponent<Component2<>>);
}

TEST(ComponentTest, Component2HandlesRequestsWithoutSuccessor) {
  Component2 component{};
  EXPECT_STREQ(component.handle_request().c_str(), "Component2 action");
}

TEST(ComponentTest, Component2HandlesRequestsWithSuccessor) {
  Component2 successor{};
  Component2 component{successor};
  EXPECT_STREQ(component.handle_request().c_str(),
               "Component2 action, Component2 action");
}

TEST(ComponentTest, Component1AndComponent2Compose) {
  Component1 successor{};
  Component2 component{successor};
  EXPECT_STREQ(component.handle_request().c_str(),
               "Component2 action, Component1 action");
}
