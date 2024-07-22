#include <fmt/format.h>
#include <iostream>
#include <array>

int main() {
    std::array items{10, 20, 30, 40};
    int total{0};

    for (const int& item : items) {
        total += item;
    }

    std::cout << fmt::format("Total of array elements: {}\n", total);
    return 0;
}