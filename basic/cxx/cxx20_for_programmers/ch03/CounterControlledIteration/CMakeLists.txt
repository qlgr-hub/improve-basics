cmake_minimum_required(VERSION 3.1)

set(CMAKE_C_COMPILER clang-16)
set(CMAKE_CXX_COMPILER clang++-16)

project(CounterControlledIteration)

add_executable(CounterControlledIteration CounterControlledIteration.cxx)
