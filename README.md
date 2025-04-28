# Simple JSON Parser

## Usage

material.json:

```json
{
  "albedoColor": [1.0, 0.5, 0.2],
  "roughness": 0.7,
  "metallic": 0.1,
  "materialName": "Leather",
  "useAlphaBlend": true,
  "nested": {
    "a": "apple",
    "b": {
      "c": "clack"
    }
  }
}
```

```c++
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
```

## Building

```bash
mkdir -p build && cd ./build
cmake ..
cd .. && cmake --build build
./build/serial
```
