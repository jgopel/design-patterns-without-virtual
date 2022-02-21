#pragma once

#include "utilities/rule_of_five.hpp"

#include <memory>
#include <string>
#include <utility>

class ImplementationBase {
public:
  using value_t = int;

  ImplementationBase() = default;
  RULE_OF_FIVE_VIRTUAL_DESTRUCTOR_FOR_BASE(ImplementationBase);

  [[nodiscard]] virtual auto action(value_t value) const -> std::string = 0;
};

class Implementation1 : public ImplementationBase {
public:
  Implementation1() = default;
  RULE_OF_FIVE_VIRTUAL_DESTRUCTOR_FOR_BASE(Implementation1);

  [[nodiscard]] auto action(value_t value) const -> std::string override {
    return "Implementation 1 called with value '" + std::to_string(value) + "'";
  }
};

class Implementation2 : public ImplementationBase {
public:
  Implementation2() = default;
  RULE_OF_FIVE_VIRTUAL_DESTRUCTOR_FOR_BASE(Implementation2);

  [[nodiscard]] auto action(value_t value) const -> std::string override {
    return "Implementation 2 called with value '" + std::to_string(value) + "'";
  }
};

class AbstractionBase {
public:
  [[nodiscard]] virtual auto base_function() const -> std::string = 0;
};

class Abstraction : public AbstractionBase {
public:
  Abstraction(std::unique_ptr<ImplementationBase> impl,
              const ImplementationBase::value_t val)
      : implementation{std::move(impl)}, value{val} {};

  [[nodiscard]] auto base_function() const -> std::string override {
    return "Abstraction called Implementation action and got '" +
           implementation->action(value) + "'";
  }

  [[nodiscard]] auto abstraction_function() const -> std::string {
    return "Abstraction called its own function";
  }

public:
  std::unique_ptr<ImplementationBase> implementation{};
  ImplementationBase::value_t value{};
};
