#pragma once

#include <string>

template <typename TProduct>
concept CProductA = requires(TProduct t) {
  TProduct{};
  t.get_name();
};

template <typename TProduct>
concept CProductB = requires(TProduct t) {
  TProduct{std::string{}};
  t.get_value();
};

class ProductA_X {
public:
  [[nodiscard]] auto get_name() const -> std::string { return "ProductA: X"; }
};

class ProductA_Y {
public:
  [[nodiscard]] auto get_name() const -> std::string { return "ProductA: Y"; }
};

class ProductB_X {
public:
  explicit(true) ProductB_X(std::string input_value)
      : value_x{std::move(input_value)} {}
  [[nodiscard]] auto get_value() const -> std::string {
    return "ProductB_X: " + value_x;
  }

private:
  std::string value_x{};
};

class ProductB_Y {
public:
  explicit(true) ProductB_Y(std::string input_value)
      : value_y{std::move(input_value)} {}
  [[nodiscard]] auto get_value() const -> std::string {
    return "ProductB_Y: " + value_y;
  }

private:
  std::string value_y{};
};

template <CProductA TProductA, CProductB TProductB> class Factory {
public:
  [[nodiscard]] auto create_ProductA() const -> TProductA {
    return TProductA{};
  }
  [[nodiscard]] auto create_ProductB(std::string input_value) const
      -> TProductB {
    return TProductB{std::move(input_value)};
  }
};

using XFactory = Factory<ProductA_X, ProductB_X>;
using YFactory = Factory<ProductA_Y, ProductB_Y>;
