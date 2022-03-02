#include "without_virtual.hpp"

#include <gtest/gtest.h>

TEST(ComponentTest, ComponentAActionIsCorrect) {
  const ComponentA component{};
  EXPECT_STREQ(component.action().c_str(), "ComponentA action");
}

TEST(ComponentTest, ComponentBActionIsCorrect) {
  const ComponentB component{};
  EXPECT_STREQ(component.action().c_str(), "ComponentB action");
}

TEST(ComponentTest, ComponentCActionIsCorrect) {
  const ComponentC component{};
  EXPECT_STREQ(component.action().c_str(), "ComponentC action");
}

TEST(FacadeTest, FacadeActionIsCorrect) {
  const Facade facade{};
  EXPECT_STREQ(facade.action().c_str(),
               "ComponentA action and ComponentB action and ComponentC action");
}
