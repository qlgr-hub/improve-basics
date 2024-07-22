cmake_minimum_required(VERSION 3.1)

set(CMAKE_C_COMPILE clang-16)
set(CMAKE_CXX_COMPILE clang++-16)

project(StdArray)

link_libraries(libfmt.a)
add_executable(StdArray StdArray.cxx)
