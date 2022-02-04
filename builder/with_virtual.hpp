#pragma once

#include "common.hpp"

#include "utilities/rule_of_five.hpp"

#include <memory>

class BuilderBase {
public:
  BuilderBase() = default;
  RULE_OF_FIVE_VIRTUAL_DESTRUCTOR_FOR_BASE(BuilderBase);

  constexpr virtual auto set_color() -> void = 0;
  constexpr virtual auto set_size() -> void = 0;
  constexpr virtual auto set_model() -> void = 0;

  [[nodiscard]] virtual auto build() const -> Product = 0;
};

class IndependentBuilder : public BuilderBase {
public:
  IndependentBuilder() = default;
  RULE_OF_FIVE_VIRTUAL_DESTRUCTOR_FOR_OVERRIDE(IndependentBuilder);

  constexpr auto set_color() -> void override { product.color = Color::Green; }
  constexpr auto set_size() -> void override { product.size = 42; }
  constexpr auto set_model() -> void override { product.model = "Independent"; }

  [[nodiscard]] auto build() const -> Product override { return product; }

private:
  Product product{};
};

class DependentBuilder : public BuilderBase {
public:
  DependentBuilder() = default;
  RULE_OF_FIVE_VIRTUAL_DESTRUCTOR_FOR_OVERRIDE(DependentBuilder);

  constexpr auto set_color() -> void override { product.color = Color::Blue; }
  constexpr auto set_size() -> void override { product.size = 101; }
  constexpr auto set_model() -> void override {
    product.model = "Dependent - size " + std::to_string(product.size.value());
  }

  [[nodiscard]] auto build() const -> Product override { return product; }

private:
  Product product{};
};

class Director {
public:
  Director(std::unique_ptr<BuilderBase> concrete_builder) {
    set_builder(std::move(concrete_builder));
  }

  auto set_builder(std::unique_ptr<BuilderBase> concrete_builder) -> void {
    builder = std::move(concrete_builder);
    builder->set_color();
    builder->set_size();
    builder->set_model();
  }

  [[nodiscard]] auto build() const -> Product { return builder->build(); }

private:
  std::unique_ptr<BuilderBase> builder{};
};
