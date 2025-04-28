#pragma once

#include <string>
#include <vector>

#include "../config/ConfigValue.hpp"
#include "../config/Serializable.hpp"
#include "AssetHandle.hpp"

struct Geometry : public Serializable {
  std::vector<float> positions;
  std::vector<float> normals;
  std::vector<float> texCoords;
  std::vector<float> tangents;
  std::vector<uint32_t> indices;

  void serialize(Config& out) const override {
    out.set("positions", ConfigValue{positions});
    out.set("normals", ConfigValue{normals});
    out.set("texCoords", ConfigValue{texCoords});
    out.set("tangents", ConfigValue{tangents});
    out.set("indices", ConfigValue{indices});
  }

  void deserialize(const Config& in) override {
  }
};