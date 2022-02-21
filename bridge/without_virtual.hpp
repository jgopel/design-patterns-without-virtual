#pragma once

#include <string>

template <typename TImplementation>
concept CImplementation = requires(TImplementation implementation) {
  typename TImplementation::value_t{};
  implementation.action(typename TImplementation::value_t{});
};

template <typename TAbstraction>
concept CAbstraction = requires(TAbstraction abstraction) {
  typename TAbstraction::implementation_t{};
  abstraction.base_function();
};

namespace detail {
  using value_t = int;
}

class Implementation1 {
public:
  using value_t = detail::value_t;

  [[nodiscard]] auto action(value_t value) const -> std::string {
    return "Implementation 1 called with value '" + std::to_string(value) + "'";
  }
};

class Implementation2 {
public:
  using value_t = detail::value_t;

  [[nodiscard]] auto action(value_t value) const -> std::string {
    return "Implementation 2 called with value '" + std::to_string(value) + "'";
  }
};

template <CImplementation TImplementation> class Abstraction {
public:
  using implementation_t = TImplementation;

  Abstraction(const TImplementation &impl,
              const typename TImplementation::value_t val)
      : implementation{impl}, value{val} {}

  [[nodiscard]] auto base_function() const -> std::string {
    return "Abstraction called Implementation action and got '" +
           implementation.action(value) + "'";
  }

  [[nodiscard]] auto abstraction_function() const -> std::string {
    return "Abstraction called its own function";
  }

private:
  TImplementation implementation{};
  typename TImplementation::value_t value{};
};
