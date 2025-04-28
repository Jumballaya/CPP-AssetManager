#pragma once

#include <cstdint>
#include <string>
#include <vector>

#include "../config/Serializable.hpp"

enum class TextureFormat { Unknown = 0,
                           RGBA8,
                           RGB8,
                           GRAY8 };

struct Texture : public Serializable {
  std::string name;

  int width = 0;
  int height = 0;
  int channels = 0;
  TextureFormat format = TextureFormat::Unknown;

  std::vector<uint8_t> data;  // pixel data

  void serialize(Config& out) const override {
    out.set("width", ConfigValue{static_cast<uint32_t>(width)});
    out.set("height", ConfigValue{static_cast<uint32_t>(height)});
    out.set("channels", ConfigValue{static_cast<uint32_t>(channels)});
    out.set("format", ConfigValue{static_cast<uint32_t>(format)});
  }

  void deserialize(const Config& in) override {
  }
};