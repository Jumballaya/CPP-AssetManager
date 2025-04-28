#pragma once

#include <string>

#include "AssetHandle.hpp"
#include "Shader.hpp"
#include "Texture.hpp"

struct Material {
  AssetHandle<Shader> shaderId;

  float baseColor[4] = {1.0f, 1.0f, 1.0f, 1.0f};
  float metallic = 0.0f;
  float roughness = 1.0f;

  AssetHandle<Texture> albedoTextureId;
  AssetHandle<Texture> normalTextureId;
  AssetHandle<Texture> metallicRoughnessTextureId;
};