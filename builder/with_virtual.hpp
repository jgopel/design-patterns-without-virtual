#pragma once

#include <optional>
#include <string>

enum class Color {
  Red,
  Blue,
  Green,
};

class Product {
public:
  std::optional<Color> color{};
  std::optional<int> size{};
  std::optional<std::string> model{};
};
