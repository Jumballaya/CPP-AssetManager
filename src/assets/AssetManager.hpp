#pragma once

#include <memory>
#include <string>
#include <unordered_map>

#include "AssetHandle.hpp"
#include "AssetLoader.hpp"
#include "Geometry.hpp"
#include "Material.hpp"
#include "Mesh.hpp"
#include "Shader.hpp"
#include "Texture.hpp"

class AssetManager {
 public:
  AssetHandle<Geometry> registerGeometry(std::shared_ptr<Geometry> geo);
  AssetHandle<Texture> registerTexture(std::shared_ptr<Texture> tex);
  AssetHandle<Material> registerMaterial(std::shared_ptr<Material> mat);
  AssetHandle<Mesh> registerMesh(std::shared_ptr<Mesh> mesh);
  AssetHandle<Shader> registerShader(std::shared_ptr<Shader> shader);

  std::shared_ptr<Geometry> getGeometry(AssetHandle<Geometry> id) const;
  std::shared_ptr<Texture> getTexture(AssetHandle<Texture> id) const;
  std::shared_ptr<Material> getMaterial(AssetHandle<Material> id) const;
  std::shared_ptr<Mesh> getMesh(AssetHandle<Mesh> id) const;
  std::shared_ptr<Shader> getShader(AssetHandle<Shader> id) const;

  Scene loadGLTF(const std::string &path) {
    return AssetLoader::loadGLTF(path, *this);
  }

  AssetHandle<Geometry> defaultGeometry() const { return _defaultGeometryId; }
  AssetHandle<Texture> defaultTexture() const { return _defaultTextureId; }
  AssetHandle<Material> defaultMaterial() const { return _defaultMaterialId; }
  AssetHandle<Mesh> defaultMesh() const { return _defaultMeshId; }
  AssetHandle<Shader> defaultShader() const { return _defaultShaderId; }

  void initializeDefaults();

 private:
  std::unordered_map<AssetHandle<Geometry>, std::shared_ptr<Geometry>>
      _geometries;
  std::unordered_map<AssetHandle<Texture>, std::shared_ptr<Texture>> _textures;
  std::unordered_map<AssetHandle<Material>, std::shared_ptr<Material>>
      _materials;
  std::unordered_map<AssetHandle<Mesh>, std::shared_ptr<Mesh>> _meshes;
  std::unordered_map<AssetHandle<Shader>, std::shared_ptr<Shader>> _shaders;

  uint32_t _geoNextId = 1;
  uint32_t _texNextId = 1;
  uint32_t _matNextId = 1;
  uint32_t _meshNextId = 1;
  uint32_t _shaderNextId = 1;

  // Fallbacks
  AssetHandle<Geometry> _defaultGeometryId;
  AssetHandle<Texture> _defaultTextureId;
  AssetHandle<Material> _defaultMaterialId;
  AssetHandle<Mesh> _defaultMeshId;
  AssetHandle<Shader> _defaultShaderId;

  std::shared_ptr<Geometry> createDefaultQuadGeometry();
  std::shared_ptr<Texture> createDefaultTexture2D();
  std::shared_ptr<Material> createDefaultMaterial(AssetHandle<Texture> tex);
  std::shared_ptr<Mesh> createDefaultMesh(AssetHandle<Geometry> geo,
                                          AssetHandle<Material> mat);
};