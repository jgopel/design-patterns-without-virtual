#include "with_virtual.hpp"

#include "gtest/gtest.h"

#include <memory>
#include <type_traits>

TEST(ReceiverTest, ReceiverActionIsCorrect) {
  Receiver receiver{};
  EXPECT_STREQ(receiver.action().c_str(), "Receiver action");
}

TEST(CommandTest, CommandIsACommand) {
  static_assert(std::is_base_of_v<CommandBase, Command>);
}

TEST(CommandTest, CommandExecuteIsCorrect) {
  Command command{};
  EXPECT_STREQ(command.execute().c_str(), "Command executed: Receiver action");
}

TEST(InvokerTest, InvokerHandlesEmptyCommand) {
  Invoker invoker{std::unique_ptr<Command>{}};
  EXPECT_STREQ(invoker.invoke().c_str(), "");
}

TEST(InvokerTest, InvokerHandlesPopulatedCommand) {
  Invoker invoker{std::make_unique<Command>()};
  EXPECT_STREQ(invoker.invoke().c_str(),
               "Invoker invoked: Command executed: Receiver action");
}
