#include <array>
#include <fmt/format.h>
#include <iostream>
#include <numeric>

int multiply(int x, int y) {
    return x * y;
}

int main() {
    constexpr std::array integers{10, 20, 30, 40};
    std::cout << fmt::format("Total of integers: {}\n",
        std::accumulate(std::begin(integers), std::end(integers), 1, multiply));

    std::cout << fmt::format("Total of integers with lambda: {}\n",
        std::accumulate(std::begin(integers), std::end(integers), 1,
            [](const auto& x, const auto& y){return x*y;}));
    
    return 0;
}