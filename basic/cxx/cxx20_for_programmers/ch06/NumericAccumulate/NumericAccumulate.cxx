#include <array>
#include <fmt/format.h>
#include <iostream>
#include <numeric>


int main() {
    constexpr std::array integers{10, 20, 30, 40};
    std::cout << fmt::format("Product of array elements: {}\n",
        std::accumulate(std::begin(integers), std::end(integers), 0));
    
    return 0;
}