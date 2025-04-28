#pragma once

#include <string>

#include "AssetHandle.hpp"
#include "Geometry.hpp"
#include "Material.hpp"

struct Mesh {
  AssetHandle<Geometry> geometryId;
  AssetHandle<Material> materialId;
};