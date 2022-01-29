#include "without_virtual.hpp"

#include <gtest/gtest.h>

TEST(ProductTest, ConstructProductA_X) {
  const ProductA_X product{};
  EXPECT_STREQ(product.get_name().c_str(), "ProductA: X");
}

TEST(ProductTest, ConstructProductA_Y) {
  const ProductA_Y product{};
  EXPECT_STREQ(product.get_name().c_str(), "ProductA: Y");
}

TEST(ProductTest, ConstructProductB_X) {
  const ProductB_X product{"foo"};
  EXPECT_STREQ(product.get_value().c_str(), "ProductB_X: foo");
}

TEST(ProductTest, ConstructProductB_Y) {
  const ProductB_Y product{"bar"};
  EXPECT_STREQ(product.get_value().c_str(), "ProductB_Y: bar");
}
