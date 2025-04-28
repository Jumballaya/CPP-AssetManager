#include <iostream>
#include <string>
#include <vector>

#include "config/ConfigParser.hpp"

int main() {
  Config config = ConfigParser::loadFromFile("material.json");

  auto albedo = config.get<std::vector<float>>("albedoColor");
  auto roughness = config.get<float>("roughness");
  auto isTransparent = config.get<bool>("useAlphaBlend");

  if (auto materialName = config.getOptional<std::string>("materialName")) {
    std::cout << "Material: " << *materialName << '\n';
  }
  auto c = config.get<std::string>("nested.b.c");

  std::cout << "nested.b.c: " << c << std::endl;
}