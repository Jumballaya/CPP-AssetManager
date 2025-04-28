#pragma once

#include <string>

#include "AssetHandle.hpp"
#include "Shader.hpp"
#include "Texture.hpp"
#include "config/Serializable.hpp"

struct Material : public Serializable {
  AssetHandle<Shader> shaderId;
  float baseColor[4];
  float metallic;
  float roughness;
  AssetHandle<Texture> albedoTextureId;
  AssetHandle<Texture> normalTextureId;
  AssetHandle<Texture> metallicRoughnessTextureId;

  void serialize(Config& out) const override {
    out.set("shaderId", shaderId.id());
    out.set("baseColor", baseColor);
    out.set("metallic", metallic);
    out.set("roughness", roughness);
    out.set("albedoTextureId", albedoTextureId.id());
    out.set("normalTextureId", normalTextureId.id());
    out.set("metallicRoughnessTextureId", metallicRoughnessTextureId.id());
  }

  void deserialize(const Config& in) override {
    shaderId = AssetHandle<Shader>(in.get<uint32_t>("shaderId"));
    baseColor = in.get<glm::vec4>("baseColor");
    metallic = in.get<float>("metallic");
    roughness = in.get<float>("roughness");
    albedoTextureId = AssetHandle<Texture>(in.get<uint32_t>("albedoTextureId"));
    normalTextureId = AssetHandle<Texture>(in.get<uint32_t>("normalTextureId"));
    metallicRoughnessTextureId = AssetHandle<Texture>(in.get<uint32_t>("metallicRoughnessTextureId"));
  }
};
