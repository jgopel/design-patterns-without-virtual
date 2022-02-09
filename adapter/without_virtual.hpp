#pragma once

#include <string>

class StringProvider {
public:
  [[nodiscard]] static auto get_string() -> std::string { return "foo"; }
};

class NullFormatter {
public:
  [[nodiscard]] static auto format(const std::string &input) -> std::string {
    return input;
  }
};

class DebugFormatter {
public:
  [[nodiscard]] static auto format(const std::string &input) -> std::string {
    return "the string is: " + input;
  }
};

class NullFormatterAdapter : private StringProvider, private NullFormatter {
public:
  [[nodiscard]] auto get_formatted_string() -> std::string {
    return format(get_string());
  }
};

class DebugFormatterAdapter : private StringProvider, private DebugFormatter {
public:
  [[nodiscard]] auto get_formatted_string() -> std::string {
    return format(get_string());
  }
};
