#pragma once

#include <functional>
#include <vector>

class Component {};

class Flyweight {
public:
  auto add_component(Component &component) -> void {
    components.push_back(component);
  }

private:
  std::vector<std::reference_wrapper<Component>> components{};
};
