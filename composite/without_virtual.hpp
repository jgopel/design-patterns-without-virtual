#pragma once

#include <numeric>
#include <string>
#include <vector>

template <typename TComponent>
concept CComponent = requires(TComponent component) {
  component.action();
};

class Leaf {
public:
  [[nodiscard]] auto action() const -> std::string { return "Leaf action"; }
};

class Composite {
public:
  [[nodiscard]] auto action() const -> std::string {
    return std::apply(
        [](auto &&...components_of_type) {
          return "Composite action" +
                 (... +
                  std::accumulate(std::cbegin(components_of_type),
                                  std::cend(components_of_type), std::string{},
                                  [](const auto &acc, const auto &component) {
                                    return acc + ", " + component.action();
                                  }));
        },
        components);
  }

  template <CComponent TComponent>
  auto add(const TComponent component) -> void {
    std::get<std::vector<TComponent>>(components)
        .push_back(std::move(component));
  }

private:
  std::tuple<std::vector<Leaf>, std::vector<Composite>> components;
};
