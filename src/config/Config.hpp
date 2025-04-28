#pragma once

#include <memory>
#include <optional>
#include <string>
#include <unordered_map>

#include "ConfigValue.hpp"

class Config {
 public:
  Config() = default;
  ~Config() = default;

  template <typename T>
  T get(const std::string& key) const {
    auto it = _entries.find(key);
    if (it == _entries.end()) {
      throw std::runtime_error("Config key not found: " + key);
    }
    return it->second.get<T>();
  }

  template <typename T>
  std::optional<T> getOptional(const std::string& key) const {
    auto it = _entries.find(key);
    if (it == _entries.end()) return std::nullopt;
    if (!it->second.is<T>()) return std::nullopt;
    return it->second.get<T>();
  }

  void set(const std::string& key, ConfigValue value) {
    _entries[key] = std::move(value);
  }

 private:
  std::unordered_map<std::string, ConfigValue> _entries;
};