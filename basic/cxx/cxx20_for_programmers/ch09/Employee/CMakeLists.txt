cmake_minimum_required(VERSION 3.1)

set(CMAKE_C_COMPILE clang-16)
set(CMAKE_CXX_COMPILE clang++-16)

project(Employee)

set(CMAKE_CXX_STANDARD 20)
link_libraries(libfmt.a)
add_executable(Employee Employee.cxx main.cxx)
