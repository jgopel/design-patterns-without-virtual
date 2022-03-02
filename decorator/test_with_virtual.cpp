#include "with_virtual.hpp"

#include <gtest/gtest.h>

#include <memory>

TEST(ComponentTest, ComponentIsAComponent) {
  static_assert(std::is_base_of_v<ComponentBase, Component>);
}

TEST(ComponentTest, ComponentActionIsCorrect) {
  const Component component{};
  EXPECT_STREQ(component.action().c_str(), "Component action");
}

TEST(DecoratorTest, DecoratorIsAComponent) {
  static_assert(std::is_base_of_v<ComponentBase, Decorator>);
}

TEST(DecoratorTest, DecoratorActionHasComponentActionAndValue) {
  const Decorator decorator{std::make_unique<Component>(), 42};
  EXPECT_STREQ(decorator.action().c_str(), "Component action with value 42");
}

TEST(DecoratorTest, DecoratorCanNest) {
  const Decorator decorator{
      std::make_unique<Decorator>(std::make_unique<Component>(), 42), 101};
  EXPECT_STREQ(decorator.action().c_str(),
               "Component action with value 42 with value 101");
}
