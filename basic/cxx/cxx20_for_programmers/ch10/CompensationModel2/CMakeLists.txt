cmake_minimum_required(VERSION 3.1)

set(CMAKE_C_COMPILE clang-16)
set(CMAKE_CXX_COMPILE clang++-16)

project(CompensationModel)

set(CMAKE_CXX_STANDARD 20)
link_libraries(libfmt.a)
add_executable(CompensationModel Employee.cxx Salaried.cxx Commission.cxx main.cxx)
