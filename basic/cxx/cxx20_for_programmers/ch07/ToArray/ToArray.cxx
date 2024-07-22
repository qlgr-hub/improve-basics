#include <fmt/format.h>
#include <iostream>
#include <array>

int main() {
    const auto display{
        [](const auto& items) {
            for (const auto& item : items) {
            std::cout << fmt::format("{} ", item);
            }
        }
    };

    const auto array1{std::array{"abc"}};
    std::cout << fmt::format("array1.size() = {}\narray1: ",
        array1.size());
    display(array1);

    const auto array2{std::to_array("C++20")};
    std::cout << fmt::format("\n\narray2.size() = {}\narray2: ",
        array2.size());
    display(array2);

    std::cout << '\n';
    return 0;
}