cmake_minimum_required(VERSION 3.25)

set(CMAKE_TOOLCHAIN_FILE "../toolchains/llvm.toolchain.cmake")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(demo)
add_executable(demo main.cxx)
