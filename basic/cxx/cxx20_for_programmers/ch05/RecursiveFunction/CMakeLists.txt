cmake_minimum_required(VERSION 3.1)

set(CMAKE_C_COMPILE clang-16)
set(CMAKE_CXX_COMPILE clang++-16)

project(RecursiveFunction)

link_libraries(libfmt.a)
add_executable(RecursiveFactorial RecursiveFactorial.cxx)
add_executable(IterativeFactorial IterativeFactorial.cxx)
add_executable(RecursiveFibonacci RecursiveFibonacci.cxx)
