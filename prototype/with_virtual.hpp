#pragma once

#include "utilities/rule_of_five.hpp"

#include <memory>

class Prototype {
public:
  constexpr Prototype() = default;
  RULE_OF_FIVE_VIRTUAL_DESTRUCTOR_FOR_BASE(Prototype);

  [[nodiscard]] virtual auto clone() const -> std::unique_ptr<Prototype> = 0;
};

class ConcreteClass1 : public Prototype {
public:
  constexpr explicit(true) ConcreteClass1(const int starting_value)
      : value{starting_value} {}
  RULE_OF_FIVE_VIRTUAL_DESTRUCTOR_FOR_OVERRIDE(ConcreteClass1);

  [[nodiscard]] auto clone() const -> std::unique_ptr<Prototype> override {
    return std::make_unique<ConcreteClass1>(value);
  };

  int value{};
};

class ConcreteClass2 : public Prototype {
public:
  constexpr explicit(true) ConcreteClass2(const int starting_value)
      : stored_value{starting_value} {}
  RULE_OF_FIVE_VIRTUAL_DESTRUCTOR_FOR_OVERRIDE(ConcreteClass2);

  [[nodiscard]] auto clone() const -> std::unique_ptr<Prototype> override {
    return std::make_unique<ConcreteClass2>(stored_value);
  };

  int stored_value{};
};
