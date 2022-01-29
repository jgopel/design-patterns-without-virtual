#include "without_virtual.hpp"

#include <gtest/gtest.h>

TEST(ProductTest, ProductA_XIsAProductA) {
  static_assert(CProductA<ProductA_X>,
                "ProductA_X is not classified as a ProductA");
}

TEST(ProductTest, ConstructProductA_X) {
  const ProductA_X product{};
  EXPECT_STREQ(product.get_name().c_str(), "ProductA: X");
}

TEST(ProductTest, ProductA_YIsAProductA) {
  static_assert(CProductA<ProductA_Y>,
                "ProductA_Y is not classified as a ProductA");
}

TEST(ProductTest, ConstructProductA_Y) {
  const ProductA_Y product{};
  EXPECT_STREQ(product.get_name().c_str(), "ProductA: Y");
}

TEST(ProductTest, ProductB_XIsAProductB) {
  static_assert(CProductB<ProductB_X>,
                "ProductB_X is not classified as a ProductB");
}

TEST(ProductTest, ConstructProductB_X) {
  const ProductB_X product{"foo"};
  EXPECT_STREQ(product.get_value().c_str(), "ProductB_X: foo");
}

TEST(ProductTest, ProductB_YIsAProductB) {
  static_assert(CProductB<ProductB_Y>,
                "ProductB_Y is not classified as a ProductB");
}

TEST(ProductTest, ConstructProductB_Y) {
  const ProductB_Y product{"bar"};
  EXPECT_STREQ(product.get_value().c_str(), "ProductB_Y: bar");
}

TEST(FactoryTest, XFactory) {
  const XFactory factory{};
  EXPECT_STREQ(factory.create_ProductA().get_name().c_str(), "ProductA: X");
  EXPECT_STREQ(factory.create_ProductB("foo").get_value().c_str(),
               "ProductB_X: foo");
}

TEST(FactoryTest, YFactory) {
  const YFactory factory{};
  EXPECT_STREQ(factory.create_ProductA().get_name().c_str(), "ProductA: Y");
  EXPECT_STREQ(factory.create_ProductB("foo").get_value().c_str(),
               "ProductB_Y: foo");
}
