#include "AssetLoader.hpp"

#include <stb_image.h>

#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>

#include "AssetManager.hpp"
#include "Texture.hpp"

//**
// Helpers
//**

static std::string
readShaderWithIncludes(const std::string &path, const std::string &baseDir) {
  std::ifstream file(path);
  if (!file) {
    throw std::runtime_error("Failed to open shader file: " + path);
  }

  std::stringstream result;
  std::string line;
  while (std::getline(file, line)) {
    if (line.starts_with("#include")) {
      size_t start = line.find('"') + 1;
      size_t end = line.find_last_of('"');
      std::string includeFile = line.substr(start, end - start);
      std::string includePath = baseDir + includeFile;
      result << readShaderWithIncludes(includePath, baseDir);
    } else {
      result << line << '\n';
    }
  }

  return result.str();
}

//**
// AssetLoader
//**

std::shared_ptr<Geometry> AssetLoader::createCubeGeometry() {
  auto geom = std::make_shared<Geometry>();

  // 24 vertices (4 per face × 6 faces)
  geom->positions = {
      // Front face
      -1.0f,
      -1.0f,
      1.0f,
      1.0f,
      -1.0f,
      1.0f,
      1.0f,
      1.0f,
      1.0f,
      -1.0f,
      1.0f,
      1.0f,

      // Back face
      1.0f,
      -1.0f,
      -1.0f,
      -1.0f,
      -1.0f,
      -1.0f,
      -1.0f,
      1.0f,
      -1.0f,
      1.0f,
      1.0f,
      -1.0f,

      // Right face
      1.0f,
      -1.0f,
      1.0f,
      1.0f,
      -1.0f,
      -1.0f,
      1.0f,
      1.0f,
      -1.0f,
      1.0f,
      1.0f,
      1.0f,

      // Left face
      -1.0f,
      -1.0f,
      -1.0f,
      -1.0f,
      -1.0f,
      1.0f,
      -1.0f,
      1.0f,
      1.0f,
      -1.0f,
      1.0f,
      -1.0f,

      // Top face
      -1.0f,
      1.0f,
      1.0f,
      1.0f,
      1.0f,
      1.0f,
      1.0f,
      1.0f,
      -1.0f,
      -1.0f,
      1.0f,
      -1.0f,

      // Bottom face
      -1.0f,
      -1.0f,
      -1.0f,
      1.0f,
      -1.0f,
      -1.0f,
      1.0f,
      -1.0f,
      1.0f,
      -1.0f,
      -1.0f,
      1.0f,
  };

  geom->texCoords = {
      // Front
      0,
      0,
      1,
      0,
      1,
      1,
      0,
      1,
      // Back
      0,
      0,
      1,
      0,
      1,
      1,
      0,
      1,
      // Right
      0,
      0,
      1,
      0,
      1,
      1,
      0,
      1,
      // Left
      0,
      0,
      1,
      0,
      1,
      1,
      0,
      1,
      // Top
      0,
      0,
      1,
      0,
      1,
      1,
      0,
      1,
      // Bottom
      0,
      0,
      1,
      0,
      1,
      1,
      0,
      1,
  };

  geom->normals = {
      // Front
      0,
      0,
      1,
      0,
      0,
      1,
      0,
      0,
      1,
      0,
      0,
      1,
      // Back
      0,
      0,
      -1,
      0,
      0,
      -1,
      0,
      0,
      -1,
      0,
      0,
      -1,
      // Right
      1,
      0,
      0,
      1,
      0,
      0,
      1,
      0,
      0,
      1,
      0,
      0,
      // Left
      -1,
      0,
      0,
      -1,
      0,
      0,
      -1,
      0,
      0,
      -1,
      0,
      0,
      // Top
      0,
      1,
      0,
      0,
      1,
      0,
      0,
      1,
      0,
      0,
      1,
      0,
      // Bottom
      0,
      -1,
      0,
      0,
      -1,
      0,
      0,
      -1,
      0,
      0,
      -1,
      0,
  };

  geom->tangents = {
      // Front
      1,
      0,
      0,
      1,
      1,
      0,
      0,
      1,
      1,
      0,
      0,
      1,
      // Back
      -1,
      0,
      0,
      1,
      -1,
      0,
      0,
      1,
      -1,
      0,
      0,
      1,
      // Right
      0,
      0,
      -1,
      1,
      0,
      0,
      -1,
      1,
      0,
      0,
      -1,
      1,
      // Left
      0,
      0,
      1,
      1,
      0,
      0,
      1,
      1,
      0,
      0,
      1,
      1,
      // Top
      1,
      0,
      0,
      1,
      1,
      0,
      0,
      1,
      1,
      0,
      0,
      1,
      // Bottom
      1,
      0,
      0,
      1,
      1,
      0,
      0,
      1,
      1,
      0,
      0,
      1,
  };

  geom->indices = {
      // Front
      0,
      1,
      2,
      2,
      3,
      0,
      // Back
      4,
      5,
      6,
      6,
      7,
      4,
      // Right
      8,
      9,
      10,
      10,
      11,
      8,
      // Left
      12,
      13,
      14,
      14,
      15,
      12,
      // Top
      16,
      17,
      18,
      18,
      19,
      16,
      // Bottom
      20,
      21,
      22,
      22,
      23,
      20,
  };

  return geom;
}

std::shared_ptr<Texture> AssetLoader::loadTexture(const std::string &path) {
  int width, height, channels;
  stbi_uc *pixels =
      stbi_load(path.c_str(), &width, &height, &channels, STBI_rgb_alpha);
  if (!pixels)
    return nullptr;

  auto tex = std::make_shared<Texture>();
  tex->name = path;
  tex->width = width;
  tex->height = height;
  tex->channels = 4;
  tex->format = TextureFormat::RGBA8;
  tex->data.assign(pixels, pixels + width * height * 4);

  stbi_image_free(pixels);
  return tex;
}

std::shared_ptr<Shader>
AssetLoader::loadShader(const std::string &vertexPath,
                        const std::string &fragmentPath,
                        const std::string &basePath) {
  auto shader = std::make_shared<Shader>();
  shader->vertexPath = std::string(vertexPath);
  shader->fragmentPath = std::string(fragmentPath);
  shader->vertexSource = readShaderWithIncludes(vertexPath, basePath);
  shader->fragmentSource = readShaderWithIncludes(fragmentPath, basePath);

  return shader;
}
