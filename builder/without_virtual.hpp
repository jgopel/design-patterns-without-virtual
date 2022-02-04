#pragma once

#include "common.hpp"

template <typename TBuilder>
concept CBuilder = requires(TBuilder builder) {
  TBuilder{};
  builder.set_color();
  builder.set_size();
  builder.set_model();
};

class IndependentBuilder {
public:
  constexpr auto set_color() -> void { product.color = Color::Green; }
  constexpr auto set_size() -> void { product.size = 42; }
  constexpr auto set_model() -> void { product.model = "Independent"; }

  [[nodiscard]] auto build() const -> Product { return product; }

private:
  Product product{};
};

class DependentBuilder {
public:
  constexpr auto set_color() -> void { product.color = Color::Blue; }
  constexpr auto set_size() -> void { product.size = 101; }
  constexpr auto set_model() -> void {
    product.model = "Dependent - size " + std::to_string(product.size.value());
  }

  [[nodiscard]] auto build() const -> Product { return product; }

private:
  Product product{};
};
