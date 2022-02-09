#include "without_virtual.hpp"

#include <gtest/gtest.h>

TEST(ProviderTest, StringProviderGetsString) {
  EXPECT_STREQ(StringProvider{}.get_string().c_str(), "foo");
}

TEST(FormatterTest, NullFormatterDoesntFormatString) {
  EXPECT_STREQ(NullFormatter{}.format("a string").c_str(), "a string");
}

TEST(FormatterTest, DebugFormatterFormatsAString) {
  EXPECT_STREQ(DebugFormatter{}.format("a string").c_str(),
               "the string is: a string");
}

TEST(AdapterTest, NullAdapterCombinesStringProviderAndFormatter) {
  EXPECT_STREQ(NullFormatterAdapter{}.get_formatted_string().c_str(), "foo");
}

TEST(AdapterTest, DebugAdapterCombinesStringProviderAndFormatter) {
  EXPECT_STREQ(DebugFormatterAdapter{}.get_formatted_string().c_str(),
               "the string is: foo");
}
