#include "without_virtual.hpp"

#include <gtest/gtest.h>

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
  static_assert(CBuilder<IndependentBuilder>);
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
  static_assert(CBuilder<DependentBuilder>);
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

TEST(FixedDirectorTest, BuildWithIndependentBuilder) {
  const FixedDirector director{IndependentBuilder{}};
  const auto product = director.build();
  EXPECT_EQ(product.color.value(), Color::Green);
  EXPECT_EQ(product.size.value(), 42);
  EXPECT_STREQ(product.model.value().c_str(), "Independent");
}

TEST(FixedDirectorTest, BuildWithDependentBuilder) {
  const FixedDirector director{DependentBuilder{}};
  {
    const auto product = director.build();
    EXPECT_EQ(product.color.value(), Color::Blue);
    EXPECT_EQ(product.size.value(), 101);
    EXPECT_STREQ(product.model.value().c_str(), "Dependent - size 101");
  }
  {
    const auto product = director.build();
    EXPECT_EQ(product.color.value(), Color::Blue);
    EXPECT_EQ(product.size.value(), 101);
    EXPECT_STREQ(product.model.value().c_str(), "Dependent - size 101");
  }
}

TEST(SwitchableDirectorTest, BuildWithIndependentBuilder) {
  const SwitchableDirector<IndependentBuilder> director{IndependentBuilder{}};
  const auto product = director.build();
  EXPECT_EQ(product.color.value(), Color::Green);
  EXPECT_EQ(product.size.value(), 42);
  EXPECT_STREQ(product.model.value().c_str(), "Independent");
}

TEST(SwitchableDirectorTest, BuildWithDependentBuilder) {
  const SwitchableDirector<DependentBuilder> director{DependentBuilder{}};
  {
    const auto product = director.build();
    EXPECT_EQ(product.color.value(), Color::Blue);
    EXPECT_EQ(product.size.value(), 101);
    EXPECT_STREQ(product.model.value().c_str(), "Dependent - size 101");
  }
  {
    const auto product = director.build();
    EXPECT_EQ(product.color.value(), Color::Blue);
    EXPECT_EQ(product.size.value(), 101);
    EXPECT_STREQ(product.model.value().c_str(), "Dependent - size 101");
  }
}

TEST(SwitchableDirectorTest, ChangeBuilderAfterBuilding) {
  SwitchableDirector<DependentBuilder, IndependentBuilder> director{
      DependentBuilder{}};
  {
    const auto product = director.build();
    EXPECT_EQ(product.color.value(), Color::Blue);
    EXPECT_EQ(product.size.value(), 101);
    EXPECT_STREQ(product.model.value().c_str(), "Dependent - size 101");
  }
  director.set_builder(IndependentBuilder{});
  {
    const auto product = director.build();
    EXPECT_EQ(product.color.value(), Color::Green);
    EXPECT_EQ(product.size.value(), 42);
    EXPECT_STREQ(product.model.value().c_str(), "Independent");
  }
}
