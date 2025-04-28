#pragma once

#include <memory>
#include <string>

#include "Geometry.hpp"
#include "Shader.hpp"
#include "Texture.hpp"

class AssetManager;

class AssetLoader {
 public:
  static std::shared_ptr<Geometry> createCubeGeometry();
  static std::shared_ptr<Texture> loadTexture(const std::string &path);
  static std::shared_ptr<Shader> loadShader(const std::string &vertexPath,
                                            const std::string &fragmentPath,
                                            const std::string &basePath);
};
