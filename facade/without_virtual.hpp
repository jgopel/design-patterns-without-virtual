#pragma once

#include <string>

class ComponentA {
public:
  [[nodiscard]] auto action() const -> std::string {
    return "ComponentA action";
  }
};

class ComponentB {
public:
  [[nodiscard]] auto action() const -> std::string {
    return "ComponentB action";
  }
};

class ComponentC {
public:
  [[nodiscard]] auto action() const -> std::string {
    return "ComponentC action";
  }
};

class Facade {
public:
  [[nodiscard]] auto action() const -> std::string {
    return comp_a.action() + " and " + comp_b.action() + " and " +
           comp_c.action();
  };

private:
  ComponentA comp_a{};
  ComponentB comp_b{};
  ComponentC comp_c{};
};
