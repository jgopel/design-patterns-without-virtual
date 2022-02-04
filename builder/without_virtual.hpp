#pragma once

#include "common.hpp"

#include <type_traits>
#include <variant>

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

template <CBuilder TBuilder> class FixedDirector {
public:
  explicit(true) FixedDirector(const TBuilder &concrete_builder) {
    builder = concrete_builder;
    builder.set_color();
    builder.set_size();
    builder.set_model();
  }

  [[nodiscard]] auto build() const -> Product { return builder.build(); }

private:
  TBuilder builder{};
};

template <CBuilder... TBuilders> class SwitchableDirector {
public:
  explicit(true) SwitchableDirector(const CBuilder auto &concrete_builder) {
    set_builder(concrete_builder);
  }

  template <CBuilder TBuilder>
  auto set_builder(const TBuilder &concrete_builder) -> void {
    static_assert((... or std::is_same_v<TBuilder, TBuilders>),
                  "The provided builder must be in the builders provided to "
                  "the director");
    builder = concrete_builder;
    std::visit([](auto &b) { b.set_color(); }, builder);
    std::visit([](auto &b) { b.set_size(); }, builder);
    std::visit([](auto &b) { b.set_model(); }, builder);
  }

  [[nodiscard]] auto build() const -> Product {
    return std::visit([](auto &b) { return b.build(); }, builder);
  }

private:
  std::variant<TBuilders...> builder{};
};
