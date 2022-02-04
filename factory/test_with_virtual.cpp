#include "with_virtual.hpp"

#include <gtest/gtest.h>

#include <type_traits>

TEST(ProductTest, Product_XIsAProduct) {
  static_assert(std::is_base_of_v<ProductBase, Product_X>,
                "The implemented class is required to be of this shape by the "
                "design pattern");
}

TEST(ProductTest, ConstructProduct_X) {
  const Product_X product{};
  EXPECT_STREQ(product.get_name().c_str(), "Product: X");
}

TEST(ProductTest, Product_YIsAProduct) {
  static_assert(std::is_base_of_v<ProductBase, Product_Y>,
                "The implemented class is required to be of this shape by the "
                "design pattern");
}

TEST(ProductTest, ConstructProduct_Y) {
  const Product_Y product{};
  EXPECT_STREQ(product.get_name().c_str(), "Product: Y");
}

TEST(FactoryTest, XFactoryIsAFactory) {
  static_assert(std::is_base_of_v<FactoryBase, XFactory>,
                "The implemented class is required to be of this shape by the "
                "design pattern");
}

TEST(FactoryTest, XFactory) {
  const XFactory factory{};
  EXPECT_STREQ(factory.create()->get_name().c_str(), "Product: X");
}

TEST(FactoryTest, YFactoryIsAFactory) {
  static_assert(std::is_base_of_v<FactoryBase, YFactory>,
                "The implemented class is required to be of this shape by the "
                "design pattern");
}

TEST(FactoryTest, YFactory) {
  const YFactory factory{};
  EXPECT_STREQ(factory.create()->get_name().c_str(), "Product: Y");
}
