cmake_minimum_required(VERSION 3.1)

set(CMAKE_C_COMPILER clang-16)
set(CMAKE_CXX_COMPILER clang++-16)

project(WhileLoop)

add_executable(WhileLoop WhileLoop.cxx)
