cmake_minimum_required(VERSION 3.1)

set(CMAKE_C_COMPILE clang-16)
set(CMAKE_CXX_COMPILE clang++-16)

project(NewThrowBadAlloc)

set(CMAKE_CXX_STANDARD 20)
link_libraries(libfmt.a)
add_executable(NewThrowBadAlloc NewThrowBadAlloc.cxx)
add_executable(SetNewHandler SetNewHandler.cxx)
