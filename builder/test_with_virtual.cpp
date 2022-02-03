#include "with_virtual.hpp"

#include <gtest/gtest.h>

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

TEST(BuilderTest, CanBuildAProductWithAllArgs) {
  IndependentBuilder builder{};
  builder.set_color();
  builder.set_size();
  builder.set_model();
  const auto product = builder.build();
  EXPECT_EQ(product.color.value(), Color::Green);
  EXPECT_EQ(product.size.value(), 42);
  EXPECT_STREQ(product.model.value().c_str(), "Independent");
}

TEST(BuilderTest, CanBuildAProductWithSomeArgs) {
  IndependentBuilder builder{};
  builder.set_color();
  const auto product = builder.build();
  EXPECT_EQ(product.color.value(), Color::Green);
  EXPECT_FALSE(product.size.has_value());
  EXPECT_FALSE(product.model.has_value());
}

TEST(BuilderTest, CanBuildAProductWithNoArgs) {
  const IndependentBuilder builder{};
  const auto product = builder.build();
  EXPECT_FALSE(product.color.has_value());
  EXPECT_FALSE(product.size.has_value());
  EXPECT_FALSE(product.model.has_value());
}

TEST(BuilderTest, IndependentBuilderIsABuilder) {
  static_assert(std::is_base_of_v<BuilderBase, IndependentBuilder>);
}

TEST(BuilderTest, IndependentBuilderCanConstructInArbitraryOrder) {
  {
    IndependentBuilder builder{};
    builder.set_color();
    const auto product = builder.build();
    EXPECT_EQ(product.color.value(), Color::Green);
    EXPECT_FALSE(product.size.has_value());
    EXPECT_FALSE(product.model.has_value());
  }

  {
    IndependentBuilder builder{};
    builder.set_size();
    const auto product = builder.build();
    EXPECT_FALSE(product.color.has_value());
    EXPECT_EQ(product.size.value(), 42);
    EXPECT_FALSE(product.model.has_value());
  }

  {
    IndependentBuilder builder{};
    builder.set_model();
    const auto product = builder.build();
    EXPECT_FALSE(product.color.has_value());
    EXPECT_FALSE(product.size.has_value());
    EXPECT_STREQ(product.model.value().c_str(), "Independent");
  }
}

TEST(BuilderTest, DependentBuilderIsABuilder) {
  static_assert(std::is_base_of_v<BuilderBase, DependentBuilder>);
}

TEST(BuilderTest, DependentBuilderHasModelWithSize) {
  DependentBuilder builder{};
  builder.set_size();
  builder.set_model();
  const auto product = builder.build();
  EXPECT_FALSE(product.color.has_value());
  EXPECT_EQ(product.size.value(), 101);
  EXPECT_STREQ(product.model.value().c_str(), "Dependent - size 101");
}

TEST(BuilderTest, DependentBuilderHasNoModelWithoutSize) {
  DependentBuilder builder{};
  EXPECT_THROW((void)builder.set_model(), std::bad_optional_access);
}
