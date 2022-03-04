#pragma once

#include <string>

template <typename TComponent>
concept CComponent = requires(TComponent component) {
  component.action();
};

namespace detail {
  template <CComponent TComponent> class ProxyImpl {
  public:
    [[nodiscard]] auto action() const -> std::string {
      return "Proxy action for: " + component.action();
    }

  private:
    TComponent component{};
  };
} // namespace detail

class Component {
public:
  [[nodiscard]] auto action() const -> std::string {
    return "Component action";
  }
};

using Proxy = detail::ProxyImpl<Component>;
