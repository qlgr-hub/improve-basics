cmake_minimum_required(VERSION 3.1)

set(CMAKE_C_COMPILE clang-16)
set(CMAKE_CXX_COMPILE clang++-16)

project(JsonData)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 20)
include_directories(
    ./
    ./cereal/
    ./cereal/archives/
    ./cereal/details/
    ./cereal/external/
    ./cereal/external/rapidjson/
    ./cereal/external/rapidjson/error/
    ./cereal/external/rapidjson/internal/
    ./cereal/types/
)
link_libraries(libfmt.a)
add_executable(JsonData JsonData.cxx)
