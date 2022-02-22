#include "with_virtual.hpp"

#include <gtest/gtest.h>

#include <type_traits>

TEST(ProductTest, ProductA_XIsAProductA) {
  static_assert(std::is_base_of_v<ProductABase, ProductA_X>,
                "The implemented class is required to be of this shape by the "
                "design pattern");
}

TEST(ProductTest, ConstructProductA_X) {
  const ProductA_X product{};
  EXPECT_STREQ(product.get_name().c_str(), "ProductA: X");
}

TEST(ProductTest, ProductA_YIsAProductA) {
  static_assert(std::is_base_of_v<ProductABase, ProductA_Y>,
                "The implemented class is required to be of this shape by the "
                "design pattern");
}

TEST(ProductTest, ConstructProductA_Y) {
  const ProductA_Y product{};
  EXPECT_STREQ(product.get_name().c_str(), "ProductA: Y");
}

TEST(ProductTest, ProductB_XIsAProductB) {
  static_assert(std::is_base_of_v<ProductBBase, ProductB_X>,
                "The implemented class is required to be of this shape by the "
                "design pattern");
}

TEST(ProductTest, ConstructProductB_X) {
  const ProductB_X product{"foo"};
  EXPECT_STREQ(product.get_value().c_str(), "ProductB_X: foo");
}

TEST(ProductTest, ProductB_YIsAProductB) {
  static_assert(std::is_base_of_v<ProductBBase, ProductB_Y>,
                "The implemented class is required to be of this shape by the "
                "design pattern");
}

TEST(ProductTest, ConstructProductB_Y) {
  const ProductB_Y product{"bar"};
  EXPECT_STREQ(product.get_value().c_str(), "ProductB_Y: bar");
}

TEST(FactoryTest, XFactoryIsAFactory) {
  static_assert(std::is_base_of_v<AbstractFactoryBase, XFactory>,
                "The implemented class is required to be of this shape by the "
                "design pattern");
}

TEST(FactoryTest, XFactory) {
  const XFactory factory{};
  EXPECT_STREQ(factory.create_ProductA()->get_name().c_str(), "ProductA: X");
  EXPECT_STREQ(factory.create_ProductB("foo")->get_value().c_str(),
               "ProductB_X: foo");
}

TEST(FactoryTest, YFactoryIsAFactory) {
  static_assert(std::is_base_of_v<AbstractFactoryBase, YFactory>,
                "The implemented class is required to be of this shape by the "
                "design pattern");
}

TEST(FactoryTest, YFactory) {
  const YFactory factory{};
  EXPECT_STREQ(factory.create_ProductA()->get_name().c_str(), "ProductA: Y");
  EXPECT_STREQ(factory.create_ProductB("foo")->get_value().c_str(),
               "ProductB_Y: foo");
}

TEST(FactoryTest, DefineCustomFactories) {
  class CustomFactory : public AbstractFactoryBase {
  public:
    CustomFactory() = default;
    RULE_OF_FIVE_VIRTUAL_DESTRUCTOR_FOR_OVERRIDE(CustomFactory);

    [[nodiscard]] auto create_ProductA() const
        -> std::unique_ptr<ProductABase> override {
      return std::make_unique<ProductA_X>();
    }

    [[nodiscard]] auto create_ProductB(std::string) const
        -> std::unique_ptr<ProductBBase> override {
      return std::make_unique<ProductB_Y>("foo");
    }
  };
  const CustomFactory factory{};
  EXPECT_STREQ(factory.create_ProductA()->get_name().c_str(), "ProductA: X");
  EXPECT_STREQ(factory.create_ProductB("foo")->get_value().c_str(),
               "ProductB_Y: foo");
}
