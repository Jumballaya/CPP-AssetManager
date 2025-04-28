#pragma once

#include <string>
#include <vector>

#include "AssetHandle.hpp"

struct Geometry {
  std::vector<float> positions;
  std::vector<float> normals;
  std::vector<float> texCoords;
  std::vector<float> tangents;
  std::vector<uint32_t> indices;
};