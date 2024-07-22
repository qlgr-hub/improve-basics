cmake_minimum_required(VERSION 3.1)

set(CMAKE_C_COMPILE clang-16)
set(CMAKE_CXX_COMPILE clang++-16)

project(ReadWriteZipFile)

add_executable(ReadWriteZipFile ReadWriteZipFile.cxx)
