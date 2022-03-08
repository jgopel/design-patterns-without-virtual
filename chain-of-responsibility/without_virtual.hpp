#pragma once

#include <optional>
#include <string>

template <typename TComponent>
concept CComponent = requires(TComponent component) {
  component.handle_request();
};

namespace detail {

  struct NullComponent {
    [[nodiscard]] auto handle_request() const -> std::string { return {}; };
  };
  static_assert(CComponent<NullComponent>,
                "The default component must satisfy the component concept");

} // namespace detail

template <typename TSuccessor = detail::NullComponent> class Component1 {
public:
  Component1() = default;
  explicit(true) Component1(const TSuccessor &successor_)
      // NOTE: This contraint should be on the class, but there is a compiler
      // bug in either gcc or clang and this is the first approach I found that
      // works on both - details here https://godbolt.org/z/hf6TM6Mb1
      requires CComponent<TSuccessor> : successor{successor_} {}

  [[nodiscard]] auto handle_request() -> std::string {
    static const std::string ACTION = "Component1 action";

    if (not successor.has_value()) {
      return ACTION;
    }

    return ACTION + ", " + successor->handle_request();
  };

private:
  std::optional<TSuccessor> successor{};
};

template <typename T> Component1(Component1<T>) -> Component1<Component1<T>>;

template <typename TSuccessor = detail::NullComponent> class Component2 {
public:
  Component2() = default;
  explicit(true) Component2(const TSuccessor &successor_)
      // NOTE: This contraint should be on the class, but there is a compiler
      // bug in either gcc or clang and this is the first approach I found that
      // works on both - details here https://godbolt.org/z/hf6TM6Mb1
      requires CComponent<TSuccessor> : successor{successor_} {}

  [[nodiscard]] auto handle_request() -> std::string {
    static const std::string ACTION = "Component2 action";

    if (not successor.has_value()) {
      return ACTION;
    }

    return ACTION + ", " + successor->handle_request();
  };

private:
  std::optional<TSuccessor> successor{};
};

template <typename T> Component2(Component2<T>) -> Component2<Component2<T>>;
