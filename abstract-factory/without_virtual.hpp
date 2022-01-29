#pragma once

#include <string>

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
