#include "without_virtual.hpp"

#include <gtest/gtest.h>

TEST(ComponentTest, ComponentIsAComponent) {
  static_assert(CComponent<Component>);
}

TEST(ComponentTest, ComponentActionIsCorrect) {
  const Component component{};
  EXPECT_STREQ(component.action().c_str(), "Component action");
}

TEST(DecoratorTest, DecoratorIsAComponent) {
  static_assert(CComponent<Decorator<Component>>);
  static_assert(CComponent<Decorator<Decorator<Component>>>);
}

TEST(DecoratorTest, DecoratorActionHasComponentActionAndValue) {
  const Decorator decorator{Component{}, 42};
  EXPECT_STREQ(decorator.action().c_str(), "Component action with value 42");
}

TEST(DecoratorTest, DecoratorCanNest) {
  const Decorator decorator{Decorator{Component(), 42}, 101};
  EXPECT_STREQ(decorator.action().c_str(),
               "Component action with value 42 with value 101");
}
