#include "without_virtual.hpp"

#include <gtest/gtest.h>

TEST(LeafTest, LeafIsAComponent) { static_assert(CComponent<Leaf>); }

TEST(LeafTest, LeafActionHasExpectedReturn) {
  const Leaf leaf{};
  EXPECT_STREQ(leaf.action().c_str(), "Leaf action");
}

TEST(CompositeTest, CompositeIsAComponent) {
  static_assert(CComponent<Composite>);
}

TEST(CompsiteTest, ActionForEmptyCompositeOnlyRunsItsOwnAction) {
  const Composite composite;
  EXPECT_STREQ(composite.action().c_str(), "Composite action");
}

TEST(CompositeTest, LeafsCanBeAddedToComposites) {
  Composite composite{};
  composite.add(Leaf{});
}

TEST(CompositeTest, CompositesCanBeAddedToComposites) {
  Composite composite{};
  composite.add(Composite{});
}

TEST(CompositeTest, ActionForPopulatedCompositeOutputsChildActions) {
  {
    Composite composite{};
    composite.add(Leaf{});
    composite.add(Leaf{});

    EXPECT_STREQ(composite.action().c_str(),
                 "Composite action, Leaf action, Leaf action");
  }
  {
    Composite inner_composite{};
    inner_composite.add(Leaf{});
    inner_composite.add(Composite{});

    Composite composite{};
    composite.add(Leaf{});
    composite.add(std::move(inner_composite));

    EXPECT_STREQ(composite.action().c_str(),
                 "Composite action, Leaf action, Composite action, Leaf "
                 "action, Composite action");
  }
}

TEST(CompositeTest, CompositeActionAlwaysOutputsLeavesFirst) {
  Composite composite{};
  composite.add(Composite{});
  composite.add(Leaf{});
  composite.add(Leaf{});

  EXPECT_STREQ(composite.action().c_str(),
               "Composite action, Leaf action, Leaf action, Composite action");
}
