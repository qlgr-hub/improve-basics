#include <fmt/format.h>
#include <iostream>
#include <array>

int main() {
    constexpr size_t arraySize{5};

    std::array<int, arraySize> values{};

    for (size_t i{0}; i < values.size(); ++i) {
        values.at(i) = 2 + 2 * i;
    }

    for (const int& value : values) {
        std::cout << fmt::format("{} ", value);
    }

    std::cout << "\n";
    return 0;
}