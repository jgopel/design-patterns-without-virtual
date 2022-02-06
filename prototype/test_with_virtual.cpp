#include "with_virtual.hpp"

#include "gtest/gtest.h"

#include <memory>
#include <type_traits>

TEST(PrototypeTest, ConcreteClass1IsAPrototype) {
  static_assert(std::is_base_of_v<Prototype, ConcreteClass1>);
}

TEST(PrototypeTest, ConcreteClass1CanClone) {
  const ConcreteClass1 original(42);
  const auto clone = original.clone();
  const auto concreteClone = dynamic_cast<ConcreteClass1 *>(clone.get());
  EXPECT_EQ(original.value, concreteClone->value);
}

TEST(PrototypeTest, ConcreteClass1ClonesAreNotTiedToOriginal) {
  ConcreteClass1 original(42);
  const auto clone = original.clone();
  const auto concreteClone = dynamic_cast<ConcreteClass1 *>(clone.get());
  original.value = 101;
  EXPECT_NE(original.value, concreteClone->value);
}

TEST(PrototypeTest, ConcreteClass2IsAPrototype) {
  static_assert(std::is_base_of_v<Prototype, ConcreteClass2>);
}

TEST(PrototypeTest, ConcreteClass2CanClone) {
  const ConcreteClass2 original(42);
  const auto clone = original.clone();
  const auto concreteClone = dynamic_cast<ConcreteClass2 *>(clone.get());
  EXPECT_EQ(original.stored_value, concreteClone->stored_value);
}

TEST(PrototypeTest, ConcreteClass2ClonesAreNotTiedToOriginal) {
  ConcreteClass2 original(42);
  const auto clone = original.clone();
  const auto concreteClone = dynamic_cast<ConcreteClass2 *>(clone.get());
  original.stored_value = 101;
  EXPECT_NE(original.stored_value, concreteClone->stored_value);
}
