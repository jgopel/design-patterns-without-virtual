#pragma once

#include "utilities/rule_of_five.hpp"

#include <memory>
#include <string>

// Note: In a real implementation there woudl likely be multiple `Reciever`s
class Receiver {
public:
  [[nodiscard]] auto action() const -> std::string { return "Receiver action"; }
};

class CommandBase {
public:
  constexpr CommandBase() = default;
  RULE_OF_FIVE_VIRTUAL_DESTRUCTOR_FOR_BASE(CommandBase);

  [[nodiscard]] virtual auto execute() -> std::string = 0;
};

// Note: In a real implementation there would likely be multiple `Command`s
class Command final : public CommandBase {
public:
  constexpr Command() = default;
  RULE_OF_FIVE_VIRTUAL_DESTRUCTOR_FOR_OVERRIDE(Command);

  [[nodiscard]] auto execute() -> std::string override {
    return "Command executed: " + receiver.action();
  }

private:
  Receiver receiver{};
};

class Invoker {
public:
  Invoker(std::unique_ptr<CommandBase> command_)
      : command{std::move(command_)} {}

  [[nodiscard]] auto invoke() const -> std::string {
    if (not command) {
      return "";
    }
    return "Invoker invoked: " + command->execute();
  }

private:
  std::unique_ptr<CommandBase> command{};
};
