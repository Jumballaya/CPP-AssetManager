#include "AssetManager.hpp"

void AssetManager::initializeDefaults() {
  // 1. Geometry
  auto geo = createDefaultQuadGeometry();
  _defaultGeometryId = registerGeometry(geo);

  // 2. Texture
  auto tex = createDefaultTexture2D();
  _defaultTextureId = registerTexture(tex);

  // 3. Shader (load and inline)
  auto shader = AssetLoader::loadShader("assets/shaders/brdf/vertex.glsl",
                                        "assets/shaders/brdf/fragment.glsl");
  _defaultShaderId = registerShader(shader);

  // 4. Material
  auto mat = std::make_shared<Material>();
  mat->albedoTextureId = _defaultTextureId;
  mat->normalTextureId = _defaultTextureId;
  mat->metallicRoughnessTextureId = _defaultTextureId;
  mat->shaderId = _defaultShaderId;
  _defaultMaterialId = registerMaterial(mat);

  // 5. Mesh
  auto mesh = createDefaultMesh(_defaultGeometryId, _defaultMaterialId);
  _defaultMeshId = registerMesh(mesh);
}

std::shared_ptr<Geometry> AssetManager::createDefaultQuadGeometry() {
  auto geom = std::make_shared<Geometry>();

  geom->positions = {
      -1.0f,
      -1.0f,
      0.0f,
      1.0f,
      -1.0f,
      0.0f,
      1.0f,
      1.0f,
      0.0f,
      -1.0f,
      1.0f,
      0.0f,
  };

  geom->texCoords = {
      0.0f,
      0.0f,
      1.0f,
      0.0f,
      1.0f,
      1.0f,
      0.0f,
      1.0f,
  };

  geom->normals = {
      0.0f,
      0.0f,
      1.0f,
      0.0f,
      0.0f,
      1.0f,
      0.0f,
      0.0f,
      1.0f,
      0.0f,
      0.0f,
      1.0f,
  };

  geom->tangents = {
      1.0f,
      0.0f,
      0.0f,
      1.0f,
      1.0f,
      0.0f,
      0.0f,
      1.0f,
      1.0f,
      0.0f,
      0.0f,
      1.0f,
      1.0f,
      0.0f,
      0.0f,
      1.0f,
  };

  geom->indices = {0, 1, 2, 2, 3, 0};

  return geom;
}

std::shared_ptr<Texture> AssetManager::createDefaultTexture2D() {
  auto tex = std::make_shared<Texture>();

  tex->data = {
      0,
      0,
      0,
      255,
      0,
      0,
      0,
      255,
      0,
      0,
      0,
      255,
      0,
      0,
      0,
      255,
  };
  tex->channels = 4;
  tex->format = TextureFormat::RGBA8;
  tex->width = 2;
  tex->height = 2;
  tex->name = "default_texture";

  return tex;
}

std::shared_ptr<Material>
AssetManager::createDefaultMaterial(AssetHandle<Texture> tex) {
  auto mat = std::make_shared<Material>();
  mat->albedoTextureId = tex;
  mat->metallicRoughnessTextureId = tex;
  mat->normalTextureId = tex;
  return mat;
}

std::shared_ptr<Mesh>
AssetManager::createDefaultMesh(AssetHandle<Geometry> geo,
                                AssetHandle<Material> mat) {
  auto mesh = std::make_shared<Mesh>();
  mesh->geometryId = geo;
  mesh->materialId = mat;
  return mesh;
}

AssetHandle<Geometry>
AssetManager::registerGeometry(std::shared_ptr<Geometry> geo) {
  uint32_t nextId = _geoNextId++;
  AssetHandle<Geometry> handle(nextId);
  _geometries[handle] = std::move(geo);
  return handle;
}

AssetHandle<Texture>
AssetManager::registerTexture(std::shared_ptr<Texture> tex) {
  uint32_t nextId = _texNextId++;
  AssetHandle<Texture> handle(nextId);
  _textures[handle] = std::move(tex);
  return handle;
}

AssetHandle<Material>
AssetManager::registerMaterial(std::shared_ptr<Material> mat) {
  uint32_t nextId = _matNextId++;
  AssetHandle<Material> handle(nextId);
  _materials[handle] = std::move(mat);
  return handle;
}

AssetHandle<Mesh> AssetManager::registerMesh(std::shared_ptr<Mesh> mesh) {
  uint32_t nextId = _meshNextId++;
  AssetHandle<Mesh> handle(nextId);
  _meshes[handle] = std::move(mesh);
  return handle;
}

AssetHandle<Shader>
AssetManager::registerShader(std::shared_ptr<Shader> shader) {
  uint32_t nextId = _shaderNextId++;
  AssetHandle<Shader> handle(nextId);
  _shaders[handle] = std::move(shader);
  return handle;
}

std::shared_ptr<Geometry>
AssetManager::getGeometry(AssetHandle<Geometry> handle) const {
  auto it = _geometries.find(handle);
  return (it != _geometries.end())
             ? it->second
             : _geometries.find(defaultGeometry())->second;
  ;
}

std::shared_ptr<Texture>
AssetManager::getTexture(AssetHandle<Texture> handle) const {
  auto it = _textures.find(handle);
  return (it != _textures.end()) ? it->second
                                 : _textures.find(defaultTexture())->second;
  ;
}

std::shared_ptr<Material>
AssetManager::getMaterial(AssetHandle<Material> handle) const {
  auto it = _materials.find(handle);
  return (it != _materials.end()) ? it->second
                                  : _materials.find(defaultMaterial())->second;
  ;
}

std::shared_ptr<Mesh> AssetManager::getMesh(AssetHandle<Mesh> handle) const {
  auto it = _meshes.find(handle);
  return (it != _meshes.end()) ? it->second
                               : _meshes.find(defaultMesh())->second;
  ;
}

std::shared_ptr<Shader>
AssetManager::getShader(AssetHandle<Shader> handle) const {
  auto it = _shaders.find(handle);
  return (it != _shaders.end()) ? it->second
                                : _shaders.find(defaultShader())->second;
}
