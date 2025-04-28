#include <iostream>
#include <vector>

#include "ConfigParser.hpp"

int main() {
  Config config = ConfigParser::loadFromFile("material.json");

  auto albedo = config.get<std::vector<float>>("albedoColor");
  auto roughness = config.get<float>("roughness");
  auto isTransparent = config.get<bool>("useAlphaBlend");

  if (auto materialName = config.getOptional<std::string>("materialName")) {
    std::cout << "Material: " << *materialName << '\n';
  }
}