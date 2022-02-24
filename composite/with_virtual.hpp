#pragma once

#include "utilities/rule_of_five.hpp"

#include <memory>
#include <numeric>
#include <string>
#include <vector>

class ComponentBase {
public:
  constexpr ComponentBase() = default;
  RULE_OF_FIVE_VIRTUAL_DESTRUCTOR_FOR_BASE(ComponentBase);

  [[nodiscard]] virtual auto action() const -> std::string = 0;
};

class Leaf : public ComponentBase {
public:
  constexpr Leaf() = default;
  RULE_OF_FIVE_VIRTUAL_DESTRUCTOR_FOR_OVERRIDE(Leaf);

  [[nodiscard]] auto action() const -> std::string override {
    return "Leaf action";
  }
};

class Composite : public ComponentBase {
public:
  constexpr Composite() = default;
  RULE_OF_FIVE_VIRTUAL_DESTRUCTOR_FOR_OVERRIDE(Composite);

  auto add(std::unique_ptr<ComponentBase> component) -> void {
    children.push_back(std::move(component));
  }

  [[nodiscard]] auto action() const -> std::string override {
    return std::accumulate(
        std::cbegin(children), std::cend(children),
        std::string{"Composite action"},
        [](std::string acc, const std::unique_ptr<ComponentBase> &component) {
          acc += ", ";
          acc += component->action();
          return acc;
        });
  }

private:
  std::vector<std::unique_ptr<ComponentBase>> children{};
};
