#pragma once

#include <cstdint>
#include <string>
#include <vector>

enum class TextureFormat { Unknown = 0,
                           RGBA8,
                           RGB8,
                           GRAY8 };

struct Texture {
  std::string name;

  int width = 0;
  int height = 0;
  int channels = 0;
  TextureFormat format = TextureFormat::Unknown;

  std::vector<uint8_t> data;  // pixel data
};