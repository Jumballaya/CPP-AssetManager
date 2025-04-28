#include <iostream>
#include <string>
#include <vector>

#include "assets/Material.hpp"
#include "config/ConfigParser.hpp"

int main() {
  Config config = ConfigParser::loadFromFile("material.json");
  Material mat;
  mat.deserialize(config);
  std::cout << "Metallic: " << mat.metallic << std::endl;
}