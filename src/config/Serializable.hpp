#pragma once

#include "Config.hpp"

class Serializable {
 public:
  virtual void serialize(Config& out) const = 0;
  virtual void deserialize(const Config& in) = 0;
  virtual ~Serializable() = default;
};