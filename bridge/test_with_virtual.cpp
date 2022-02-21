#include "with_virtual.hpp"

#include <gtest/gtest.h>

#include <type_traits>

TEST(ImplementationTest, Implementation1IsAnImplementation) {
  static_assert(std::is_base_of_v<ImplementationBase, Implementation1>);
}

TEST(ImplementationTest, Implementation1ActionIsValid) {
  Implementation1 impl{};
  EXPECT_STREQ(impl.action(42).c_str(),
               "Implementation 1 called with value '42'");
}

TEST(ImplementationTest, Implementation2IsAnImplementation) {
  static_assert(std::is_base_of_v<ImplementationBase, Implementation2>);
}

TEST(ImplementationTest, Implementation2ActionIsValid) {
  Implementation2 impl{};
  EXPECT_STREQ(impl.action(42).c_str(),
               "Implementation 2 called with value '42'");
}

TEST(AbstractionTest, AbstractionIsAnAbstraction) {
  static_assert(std::is_base_of_v<AbstractionBase, Abstraction>);
}

TEST(AbstractionTest, AbstractionCallsImplementation) {
  const Abstraction abstraction{std::make_unique<Implementation1>(), 42};
  EXPECT_STREQ(abstraction.base_function().c_str(),
               "Abstraction called Implementation action and got "
               "'Implementation 1 called with value '42''");
}

TEST(AbstractionTest, AbstractionIsntJustAnInterface) {
  const Abstraction abstraction{std::make_unique<Implementation1>(), 42};
  EXPECT_STREQ(abstraction.abstraction_function().c_str(),
               "Abstraction called its own function");
}
