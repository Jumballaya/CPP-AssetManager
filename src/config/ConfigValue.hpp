#pragma once

#include <cstddef>
#include <ostream>
#include <string>
#include <variant>
#include <vector>

using ValueVariant = std::variant<
    int,
    float,
    bool,
    uint32_t,
    std::string,
    std::vector<float>>;

class ConfigValue {
 public:
  ConfigValue() = default;
  ConfigValue(ValueVariant v) : _value(std::move(v)) {}

  template <typename T>
  const T& get() const {
    return std::get<T>(_value);
  }

  template <typename T>
  bool is() const {
    return std::holds_alternative<T>(_value);
  }

 private:
  ValueVariant _value;
};