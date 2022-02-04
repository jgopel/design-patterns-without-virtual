#pragma once

#include <string>

template <typename TProduct>
concept CProduct = requires(TProduct t) {
  TProduct{};
  t.get_name();
};

class Product_X {
public:
  [[nodiscard]] auto get_name() const -> std::string { return "Product: X"; }
};

class Product_Y {
public:
  [[nodiscard]] auto get_name() const -> std::string { return "Product: Y"; }
};

template <CProduct TProduct> class Factory {
public:
  [[nodiscard]] auto create() const -> TProduct { return TProduct{}; }
};

using XFactory = Factory<Product_X>;
using YFactory = Factory<Product_Y>;
