#pragma once

#include "utilities/rule_of_five.hpp"

#include <memory>
#include <string>

class ProductABase {
public:
  ProductABase() = default;
  RULE_OF_FIVE_VIRTUAL_DESTRUCTOR_FOR_BASE(ProductABase);

  [[nodiscard]] virtual auto get_name() const -> std::string = 0;
};

class ProductA_X : public ProductABase {
public:
  ProductA_X() = default;
  RULE_OF_FIVE_VIRTUAL_DESTRUCTOR_FOR_OVERRIDE(ProductA_X);

  [[nodiscard]] auto get_name() const -> std::string override {
    return "ProductA: X";
  }
};

class ProductA_Y : public ProductABase {
public:
  ProductA_Y() = default;
  RULE_OF_FIVE_VIRTUAL_DESTRUCTOR_FOR_OVERRIDE(ProductA_Y);

  [[nodiscard]] auto get_name() const -> std::string override {
    return "ProductA: Y";
  }
};

class ProductBBase {
public:
  ProductBBase() = default;
  RULE_OF_FIVE_VIRTUAL_DESTRUCTOR_FOR_BASE(ProductBBase);

  [[nodiscard]] virtual auto get_value() const -> std::string = 0;
};

class ProductB_X : public ProductBBase {
public:
  explicit(true) ProductB_X(std::string input_value)
      : value_x{std::move(input_value)} {}
  RULE_OF_FIVE_VIRTUAL_DESTRUCTOR_FOR_OVERRIDE(ProductB_X);

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
  RULE_OF_FIVE_VIRTUAL_DESTRUCTOR_FOR_OVERRIDE(ProductB_Y);

  [[nodiscard]] auto get_value() const -> std::string override {
    return "ProductB_Y: " + value_y;
  }

private:
  std::string value_y{};
};

class AbstractFactoryBase {
public:
  AbstractFactoryBase() = default;
  RULE_OF_FIVE_VIRTUAL_DESTRUCTOR_FOR_BASE(AbstractFactoryBase);

  [[nodiscard]] virtual auto create_ProductA() const
      -> std::unique_ptr<ProductABase> = 0;
  [[nodiscard]] virtual auto create_ProductB(std::string) const
      -> std::unique_ptr<ProductBBase> = 0;
};

class XFactory : public AbstractFactoryBase {
public:
  XFactory() = default;
  RULE_OF_FIVE_VIRTUAL_DESTRUCTOR_FOR_OVERRIDE(XFactory);

  [[nodiscard]] auto create_ProductA() const
      -> std::unique_ptr<ProductABase> override {
    return std::make_unique<ProductA_X>();
  }
  [[nodiscard]] auto create_ProductB(std::string input_value) const
      -> std::unique_ptr<ProductBBase> override {
    return std::make_unique<ProductB_X>(std::move(input_value));
  }
};

class YFactory : public AbstractFactoryBase {
public:
  YFactory() = default;
  RULE_OF_FIVE_VIRTUAL_DESTRUCTOR_FOR_OVERRIDE(YFactory);

  [[nodiscard]] auto create_ProductA() const
      -> std::unique_ptr<ProductABase> override {
    return std::make_unique<ProductA_Y>();
  }
  [[nodiscard]] auto create_ProductB(std::string input_value) const
      -> std::unique_ptr<ProductBBase> override {
    return std::make_unique<ProductB_Y>(std::move(input_value));
  }
};
