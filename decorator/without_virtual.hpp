#pragma once

#include <string>

template <typename TComponent>
concept CComponent = requires(TComponent component) {
  component.action();
};

class Component {
public:
  [[nodiscard]] auto action() const -> std::string {
    return "Component action";
  }
};

template <CComponent TComponent> class Decorator {
public:
  Decorator(TComponent comp, const int val) : component{comp}, value{val} {}
  [[nodiscard]] auto action() const -> std::string {
    return component.action() + " with value " + std::to_string(value);
  };

private:
  TComponent component{};
  int value{};
};
