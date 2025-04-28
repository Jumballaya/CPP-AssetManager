#include <iostream>
#include <memory>

#include "assets/Geometry.hpp"
#include "assets/Material.hpp"
#include "assets/Mesh.hpp"
#include "assets/Shader.hpp"
#include "assets/Texture.hpp"
#include "config/ConfigParser.hpp"

int main() {
  try {
    // --- Load Shader ---
    std::cout << "Loading Shader..." << std::endl;
    Config shaderConfig = ConfigParser::loadFromFile("assets/shader.json");
    Shader shader;
    shader.deserialize(shaderConfig);

    // --- Load Texture ---
    Config textureConfig = ConfigParser::loadFromFile("assets/texture.json");
    std::cout << "Loading Texture..." << std::endl;
    Texture texture;
    texture.deserialize(textureConfig);

    // --- Load Geometry ---
    Config geometryConfig = ConfigParser::loadFromFile("assets/geometry.json");
    std::cout << "Loading Geometry..." << std::endl;
    Geometry geometry;
    geometry.deserialize(geometryConfig);

    // --- Load Material ---
    Config materialConfig = ConfigParser::loadFromFile("assets/material.json");
    std::cout << "Loading Material..." << std::endl;
    Material material;
    material.deserialize(materialConfig);

    // --- Create Mesh (link Geometry + Material) ---
    std::cout << "Creating Mesh..." << std::endl;
    Mesh mesh;
    mesh.geometryId = AssetHandle<Geometry>(1);  // assuming geometry ID 1
    mesh.materialId = AssetHandle<Material>(2);  // assuming material ID 2

    // --- Print out verification ---
    std::cout << "\n--- Loaded Assets ---" << std::endl;
    std::cout << "Shader vertex path: " << shader.vertexPath << std::endl;
    std::cout << "Texture size: " << texture.width << "x" << texture.height << ", channels: " << texture.channels << std::endl;
    std::cout << "Geometry vertices: " << geometry.positions.size() / 3 << " (assuming 3 floats per position)" << std::endl;
    std::cout << "Material metallic: " << material.metallic << ", roughness: " << material.roughness << std::endl;
    std::cout << "Mesh links Geometry ID: " << mesh.geometryId.id() << ", Material ID: " << mesh.materialId.id() << std::endl;
  } catch (const std::exception& ex) {
    std::cerr << "Fatal error: " << ex.what() << std::endl;
    return 1;
  }

  return 0;
}