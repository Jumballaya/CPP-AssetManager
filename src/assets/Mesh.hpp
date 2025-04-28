#pragma once

#include <string>

#include "../config/ConfigValue.hpp"
#include "../config/Serializable.hpp"
#include "AssetHandle.hpp"
#include "Geometry.hpp"
#include "Material.hpp"

struct Mesh : public Serializable {
  AssetHandle<Geometry> geometryId;
  AssetHandle<Material> materialId;

  void serialize(Config& out) const override {
    out.set("geometryId", ConfigValue{geometryId.id()});
    out.set("materialId", ConfigValue{materialId.id()});
  }

  void deserialize(const Config& in) override {
    geometryId = AssetHandle<Geometry>(in.get<uint32_t>("geometryId"));
    materialId = AssetHandle<Material>(in.get<uint32_t>("materialId"));
  }
};