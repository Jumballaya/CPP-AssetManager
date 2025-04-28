#pragma once

#include <string>
#include <vector>

#include "../config/Serializable.hpp"
#include "AssetHandle.hpp"
#include "Shader.hpp"
#include "Texture.hpp"

struct Material : public Serializable {
  AssetHandle<Shader> shaderId;
  std::array<float, 4> baseColor = {1.0f, 1.0f, 1.0f, 1.0f};
  float metallic;
  float roughness;
  AssetHandle<Texture> albedoTextureId;
  AssetHandle<Texture> normalTextureId;
  AssetHandle<Texture> metallicRoughnessTextureId;

  void serialize(Config& out) const override {
    out.set("shaderId", ConfigValue{shaderId.id()});

    std::vector<float> baseColorVec(baseColor.begin(), baseColor.end());
    out.set("baseColor", ConfigValue{baseColorVec});
    out.set("metallic", ConfigValue{metallic});
    out.set("roughness", ConfigValue{roughness});
    out.set("albedoTextureId", ConfigValue{albedoTextureId.id()});
    out.set("normalTextureId", ConfigValue{normalTextureId.id()});
    out.set("metallicRoughnessTextureId", ConfigValue{metallicRoughnessTextureId.id()});
  }

  void deserialize(const Config& in) override {
    shaderId = AssetHandle<Shader>(in.get<uint32_t>("shaderId"));
    auto tmp = in.get<std::vector<float>>("baseColor");
    if (tmp.size() != 4) {
      throw std::runtime_error("baseColor must have exactly 4 floats!");
    }

    std::copy(tmp.begin(), tmp.end(), baseColor.begin());
    metallic = in.get<float>("metallic");
    roughness = in.get<float>("roughness");
    albedoTextureId = AssetHandle<Texture>(in.get<uint32_t>("albedoTextureId"));
    normalTextureId = AssetHandle<Texture>(in.get<uint32_t>("normalTextureId"));
    metallicRoughnessTextureId = AssetHandle<Texture>(in.get<uint32_t>("metallicRoughnessTextureId"));
  }
};
