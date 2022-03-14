#pragma once

#include <string>

template <typename TCommand>
concept CCommand = requires(TCommand command) {
  command.execute();
};

// Note: In a real implementation there woudl likely be multiple `Reciever`s
class Receiver {
public:
  [[nodiscard]] auto action() const -> std::string { return "Receiver action"; }
};

// Note: In a real implementation there would likely be multiple `Command`s
class Command {
public:
  [[nodiscard]] auto execute() const -> std::string {
    return "Command executed: " + receiver.action();
  }

private:
  Receiver receiver{};
};

template <CCommand TCommand> class Invoker {
public:
  Invoker(TCommand command_) : command{command_} {}
  [[nodiscard]] auto invoke() const -> std::string {
    return "Invoker invoked: " + command.execute();
  }

private:
  TCommand command{};
};
