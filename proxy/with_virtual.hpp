#pragma once

#include "utilities/rule_of_five.hpp"

#include <memory>
#include <string>

class ComponentBase {
public:
  constexpr ComponentBase() = default;
  RULE_OF_FIVE_VIRTUAL_DESTRUCTOR_FOR_BASE(ComponentBase);

  [[nodiscard]] virtual auto action() const -> std::string = 0;
};

class Component : public ComponentBase {
public:
  constexpr Component() = default;
  RULE_OF_FIVE_VIRTUAL_DESTRUCTOR_FOR_OVERRIDE(Component);

  [[nodiscard]] auto action() const -> std::string override {
    return "Component action";
  }
};

class Proxy : public ComponentBase {
public:
  [[nodiscard]] auto action() const -> std::string override {
    return "Proxy action for: " + component->action();
  }

private:
  std::unique_ptr<ComponentBase> component{new Component{}};
};
