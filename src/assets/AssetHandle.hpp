#pragma once

template <typename T>
class AssetHandle {
 public:
  AssetHandle() = default;
  explicit AssetHandle(uint32_t id) : _id(id) {}

  uint32_t id() const { return _id; }
  bool isValid() const { return _id != 0; }

  bool operator==(const AssetHandle &other) const { return _id == other._id; }
  bool operator!=(const AssetHandle &other) const { return _id != other._id; }
  operator bool() const { return isValid(); }

 private:
  uint32_t _id = 0;
};

namespace std {
template <typename T>
struct hash<AssetHandle<T>> {
  std::size_t operator()(const AssetHandle<T> &h) const {
    return std::hash<uint32_t>()(h.id());
  }
};
}