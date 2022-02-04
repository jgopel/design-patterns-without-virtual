#include "without_virtual.hpp"

#include <gtest/gtest.h>

TEST(ProductTest, Product_XIsAProduct) {
  static_assert(CProduct<Product_X>,
                "Product_X is not classified as a Product");
}

TEST(ProductTest, ConstructProduct_X) {
  const Product_X product{};
  EXPECT_STREQ(product.get_name().c_str(), "Product: X");
}

TEST(ProductTest, Product_YIsAProduct) {
  static_assert(CProduct<Product_Y>,
                "Product_Y is not classified as a Product");
}

TEST(ProductTest, ConstructProduct_Y) {
  const Product_Y product{};
  EXPECT_STREQ(product.get_name().c_str(), "Product: Y");
}

TEST(FactoryTest, XFactory) {
  const XFactory factory{};
  EXPECT_STREQ(factory.create().get_name().c_str(), "Product: X");
}

TEST(FactoryTest, YFactory) {
  const YFactory factory{};
  EXPECT_STREQ(factory.create().get_name().c_str(), "Product: Y");
}
