#include "without_virtual.hpp"

#include "gtest/gtest.h"

TEST(ReceiverTest, ReceiverActionIsCorrect) {
  Receiver receiver{};
  EXPECT_STREQ(receiver.action().c_str(), "Receiver action");
}

TEST(CommandTest, CommandIsACommand) { static_assert(CCommand<Command>); }

TEST(CommandTest, CommandExecuteIsCorrect) {
  Command command{};
  EXPECT_STREQ(command.execute().c_str(), "Command executed: Receiver action");
}

TEST(InvokerTest, InvokerHandlesCommand) {
  Invoker invoker{Command{}};
  EXPECT_STREQ(invoker.invoke().c_str(),
               "Invoker invoked: Command executed: Receiver action");
}
