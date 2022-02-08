#include "without_virtual.hpp"

#include "gtest/gtest.h"

#include <type_traits>

TEST(PrototypeTest, ConcreteClass1IsAPrototype) {
  static_assert(std::is_copy_constructible_v<ConcreteClass1>);
}

TEST(PrototypeTest, ConcreteClass1CanClone) {
  const ConcreteClass1 original{
      .value = 42,
  };
  const auto clone = original;
  EXPECT_EQ(original.value, clone.value);
}

TEST(PrototypeTest, ConcreteClass1ClonesAreNotTiedToOriginal) {
  ConcreteClass1 original{
      .value = 42,
  };
  const auto clone = original;
  original.value = 101;
  EXPECT_NE(original.value, clone.value);
}

TEST(PrototypeTest, ConcreteClass2IsAPrototype) {
  static_assert(std::is_copy_constructible_v<ConcreteClass2>);
}

TEST(PrototypeTest, ConcreteClass2CanClone) {
  const ConcreteClass2 original{
      .stored_value = 42,
  };
  const auto clone = original;
  EXPECT_EQ(original.stored_value, clone.stored_value);
}

TEST(PrototypeTest, ConcreteClass2ClonesAreNotTiedToOriginal) {
  ConcreteClass2 original{
      .stored_value = 42,
  };
  const auto clone = original;
  original.stored_value = 101;
  EXPECT_NE(original.stored_value, clone.stored_value);
}
