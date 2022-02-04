#include "common.hpp"

#include <gtest/gtest.h>

#include <optional>

TEST(ProductTest, ConstructProductWithAllArgs) {
  const Product product{Color::Red, 42, "Excalibur"};
  EXPECT_EQ(product.color, Color::Red);
  EXPECT_EQ(product.size, 42);
  EXPECT_STREQ(product.model.value().c_str(), "Excalibur");
}

TEST(ProductTest, ConstructProductWithSomeArgs) {
  const Product product{Color::Red, std::nullopt, "Excalibur"};
  EXPECT_EQ(product.color, Color::Red);
  EXPECT_EQ(product.size, std::nullopt);
  EXPECT_STREQ(product.model.value().c_str(), "Excalibur");
}
