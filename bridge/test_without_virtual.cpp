#include "without_virtual.hpp"

#include <gtest/gtest.h>

TEST(ImplementationTest, Implementation1IsAnImplementation) {
  static_assert(CImplementation<Implementation1>);
}

TEST(ImplementationTest, Implementation1ActionIsValid) {
  Implementation1 impl{};
  EXPECT_STREQ(impl.action(42).c_str(),
               "Implementation 1 called with value '42'");
}

TEST(ImplementationTest, Implementation2IsAnImplementation) {
  static_assert(CImplementation<Implementation2>);
}

TEST(ImplementationTest, Implementation2ActionIsValid) {
  Implementation2 impl{};
  EXPECT_STREQ(impl.action(42).c_str(),
               "Implementation 2 called with value '42'");
}

TEST(AbstractionTest, AbstractionIsAnAbstraction) {
  static_assert(CAbstraction<Abstraction<Implementation1>>);
}

TEST(AbstractionTest, AbstractionCallsImplementation) {
  const Abstraction abstraction{Implementation1{}, 42};
  EXPECT_STREQ(abstraction.base_function().c_str(),
               "Abstraction called Implementation action and got "
               "'Implementation 1 called with value '42''");
}

TEST(AbstractionTest, AbstractionIsntJustAnInterface) {
  const Abstraction abstraction{Implementation1{}, 42};
  EXPECT_STREQ(abstraction.abstraction_function().c_str(),
               "Abstraction called its own function");
}
