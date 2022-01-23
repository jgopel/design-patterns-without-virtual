#pragma once

#include <string>

class ProductABase {
public:
  ProductABase() = default;
  virtual ~ProductABase() = default;
  ProductABase(const ProductABase &) = default;
  ProductABase(ProductABase &&) = default;
  ProductABase &operator=(const ProductABase &) = default;
  ProductABase &operator=(ProductABase &&) = default;

  [[nodiscard]] virtual auto get_name() const -> std::string = 0;
};

class ProductA_X : public ProductABase {
public:
  ProductA_X() = default;
  virtual ~ProductA_X() = default;
  ProductA_X(const ProductA_X &) = default;
  ProductA_X(ProductA_X &&) = default;
  ProductA_X &operator=(const ProductA_X &) = default;
  ProductA_X &operator=(ProductA_X &&) = default;

  [[nodiscard]] auto get_name() const -> std::string override {
    return "ProductA: X";
  }
};

class ProductA_Y : public ProductABase {
public:
  ProductA_Y() = default;
  virtual ~ProductA_Y() = default;
  ProductA_Y(const ProductA_Y &) = default;
  ProductA_Y(ProductA_Y &&) = default;
  ProductA_Y &operator=(const ProductA_Y &) = default;
  ProductA_Y &operator=(ProductA_Y &&) = default;

  [[nodiscard]] auto get_name() const -> std::string override {
    return "ProductA: Y";
  }
};

class ProductBBase {
public:
  ProductBBase() = default;
  virtual ~ProductBBase() = default;
  ProductBBase(const ProductBBase &) = default;
  ProductBBase(ProductBBase &&) = default;
  ProductBBase &operator=(const ProductBBase &) = default;
  ProductBBase &operator=(ProductBBase &&) = default;

  [[nodiscard]] virtual auto get_value() const -> std::string = 0;
};

class ProductB_X : public ProductBBase {
public:
  explicit(true) ProductB_X(std::string input_value)
      : value_x{std::move(input_value)} {}
  virtual ~ProductB_X() = default;
  ProductB_X(const ProductB_X &) = default;
  ProductB_X(ProductB_X &&) = default;
  ProductB_X &operator=(const ProductB_X &) = default;
  ProductB_X &operator=(ProductB_X &&) = default;

  [[nodiscard]] auto get_value() const -> std::string override {
    return "ProductB_X: " + value_x;
  }

private:
  std::string value_x{};
};

class ProductB_Y : public ProductBBase {
public:
  explicit(true) ProductB_Y(std::string input_value)
      : value_y{std::move(input_value)} {}
  virtual ~ProductB_Y() = default;
  ProductB_Y(const ProductB_Y &) = default;
  ProductB_Y(ProductB_Y &&) = default;
  ProductB_Y &operator=(const ProductB_Y &) = default;
  ProductB_Y &operator=(ProductB_Y &&) = default;

  [[nodiscard]] auto get_value() const -> std::string override {
    return "ProductB_Y: " + value_y;
  }

private:
  std::string value_y{};
};
