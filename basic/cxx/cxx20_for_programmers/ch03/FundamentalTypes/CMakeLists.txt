cmake_minimum_required(VERSION 3.1)

set(CMAKE_C_COMPILER clang-16)
set(CMAKE_CXX_COMPILER clang++-16)

project(FundamentalTypes)

# link_directories(".")
# link_libraries(BigNumber)
add_executable(FundamentalTypes FundamentalTypes.cxx bignumber.cxx)
