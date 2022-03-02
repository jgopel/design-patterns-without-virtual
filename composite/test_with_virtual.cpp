#include "with_virtual.hpp"

#include <gtest/gtest.h>

#include <memory>
#include <type_traits>

TEST(LeafTest, LeafIsAComponent) {
  static_assert(std::is_base_of_v<ComponentBase, Leaf>);
}

TEST(LeafTest, LeafActionHasExpectedReturn) {
  const Leaf leaf{};
  EXPECT_STREQ(leaf.action().c_str(), "Leaf action");
}

TEST(CompositeTest, CompositeIsAComponent) {
  static_assert(std::is_base_of_v<ComponentBase, Composite>);
}

TEST(CompsiteTest, ActionForEmptyCompositeOnlyRunsItsOwnAction) {
  const Composite composite;
  EXPECT_STREQ(composite.action().c_str(), "Composite action");
}

TEST(CompositeTest, LeafsCanBeAddedToComposites) {
  Composite composite{};
  composite.add(std::make_unique<Leaf>());
}

TEST(CompositeTest, CompositesCanBeAddedToComposites) {
  Composite composite{};
  composite.add(std::make_unique<Composite>());
}

TEST(CompositeTest, ActionForPopulatedCompositeOutputsChildActions) {
  {
    Composite composite{};
    composite.add(std::make_unique<Leaf>());
    composite.add(std::make_unique<Leaf>());

    EXPECT_STREQ(composite.action().c_str(),
                 "Composite action, Leaf action, Leaf action");
  }
  {
    auto inner_composite = std::make_unique<Composite>();
    inner_composite->add(std::make_unique<Leaf>());
    inner_composite->add(std::make_unique<Composite>());

    Composite composite{};
    composite.add(std::make_unique<Leaf>());
    composite.add(std::move(inner_composite));

    EXPECT_STREQ(composite.action().c_str(),
                 "Composite action, Leaf action, Composite action, Leaf "
                 "action, Composite action");
  }
}
