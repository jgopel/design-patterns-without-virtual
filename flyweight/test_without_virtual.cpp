#include "without_virtual.hpp"

#include <gtest/gtest.h>

TEST(FlyweighTest, CanAddComponentToFlyweight) {
  Flyweight flyweight{};
  Component component{};
  flyweight.add_component(component);
}
