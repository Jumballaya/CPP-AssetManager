#pragma once

#include <string>

#include "../config/ConfigValue.hpp"
#include "../config/Serializable.hpp"

struct Shader : public Serializable {
  std::string vertexPath;
  std::string fragmentPath;
  std::string vertexSource;
  std::string fragmentSource;

  void serialize(Config& out) const override {
    out.set("vertexPath", ConfigValue{vertexPath});
    out.set("fragmentPath", ConfigValue{fragmentPath});
    out.set("vertexSource", ConfigValue{vertexSource});
    out.set("fragmentSource", ConfigValue{fragmentSource});
  }

  void deserialize(const Config& in) override {
    vertexPath = in.get<std::string>("vertexPath");
    fragmentPath = in.get<std::string>("fragmentPath");
    if (auto vSource = in.getOptional<std::string>("vertexSource")) {
      vertexSource = *vSource;
    }
    if (auto fSource = in.getOptional<std::string>("fragmentSource")) {
      fragmentSource = *fSource;
    }
  }
};