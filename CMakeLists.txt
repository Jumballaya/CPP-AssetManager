cmake_minimum_required(VERSION 3.16)
project(asset_manager)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(FetchContent)

# ------------------------------
# stb_image (via FetchContent)
# ------------------------------
FetchContent_Declare(
  stb_image
  GIT_REPOSITORY https://github.com/nothings/stb.git
  GIT_TAG master
)
FetchContent_MakeAvailable(stb_image)

add_executable(asset_manager src/main.cpp)

target_include_directories(asset_manager PRIVATE
  src/
  ${stb_image_SOURCE_DIR}
)