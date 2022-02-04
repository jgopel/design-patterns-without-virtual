#pragma once

#include "utilities/rule_of_five.hpp"

#include <memory>
#include <string>

class ProductBase {
public:
  ProductBase() = default;
  RULE_OF_FIVE_VIRTUAL_DESTRUCTOR_FOR_BASE(ProductBase);

  [[nodiscard]] virtual auto get_name() const -> std::string = 0;
};

class Product_X : public ProductBase {
public:
  Product_X() = default;
  RULE_OF_FIVE_VIRTUAL_DESTRUCTOR_FOR_OVERRIDE(Product_X);

  [[nodiscard]] auto get_name() const -> std::string override {
    return "Product: X";
  }
};

class Product_Y : public ProductBase {
public:
  Product_Y() = default;
  RULE_OF_FIVE_VIRTUAL_DESTRUCTOR_FOR_OVERRIDE(Product_Y);

  [[nodiscard]] auto get_name() const -> std::string override {
    return "Product: Y";
  }
};

class FactoryBase {
public:
  FactoryBase() = default;
  RULE_OF_FIVE_VIRTUAL_DESTRUCTOR_FOR_BASE(FactoryBase);

  [[nodiscard]] virtual auto create() const -> std::unique_ptr<ProductBase> = 0;
};

class XFactory : public FactoryBase {
public:
  XFactory() = default;
  RULE_OF_FIVE_VIRTUAL_DESTRUCTOR_FOR_OVERRIDE(XFactory);

  [[nodiscard]] auto create() const -> std::unique_ptr<ProductBase> override {
    return std::make_unique<Product_X>();
  }
};

class YFactory : public FactoryBase {
public:
  YFactory() = default;
  RULE_OF_FIVE_VIRTUAL_DESTRUCTOR_FOR_OVERRIDE(YFactory);

  [[nodiscard]] auto create() const -> std::unique_ptr<ProductBase> override {
    return std::make_unique<Product_Y>();
  }
};
