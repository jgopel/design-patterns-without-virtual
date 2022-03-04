#pragma once

#include "utilities/rule_of_five.hpp"

#include <memory>
#include <string>

class ComponentBase {
public:
  ComponentBase() = default;
  RULE_OF_FIVE_VIRTUAL_DESTRUCTOR_FOR_BASE(ComponentBase);

  [[nodiscard]] virtual auto handle_request() -> std::string = 0;
};

class Component1 : public ComponentBase {
public:
  Component1() = default;
  explicit(true) Component1(std::unique_ptr<ComponentBase> successor)
      : successor{std::move(successor)} {}
  RULE_OF_FIVE_VIRTUAL_DESTRUCTOR_FOR_UNMOVABLE_OVERRIDE(Component1);

  [[nodiscard]] auto handle_request() -> std::string override {
    static const std::string ACTION = "Component1 action";

    if (not successor) {
      return ACTION;
    }

    return ACTION + ", " + successor->handle_request();
  }

private:
  std::unique_ptr<ComponentBase> successor{nullptr};
};

class Component2 : public ComponentBase {
public:
  Component2() = default;
  explicit(true) Component2(std::unique_ptr<ComponentBase> successor)
      : successor{std::move(successor)} {}
  RULE_OF_FIVE_VIRTUAL_DESTRUCTOR_FOR_UNMOVABLE_OVERRIDE(Component2);

  [[nodiscard]] auto handle_request() -> std::string override {
    static const std::string ACTION = "Component2 action";

    if (not successor) {
      return ACTION;
    }

    return ACTION + ", " + successor->handle_request();
  }

private:
  std::unique_ptr<ComponentBase> successor{nullptr};
};
