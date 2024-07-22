cmake_minimum_required(VERSION 3.1)

set(CMAKE_C_COMPILE clang-16)
set(CMAKE_CXX_COMPILE clang++-16)

project(InlineFunction)

add_executable(InlineFunction InlineFunction.cxx)
