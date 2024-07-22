#include <array>
#include <fmt/format.h>
#include <iostream>
#include <memory>
#include <new>

int main() {
    std::array<std::unique_ptr<double[]>, 1000> items{};

    try {
        for (int i{0}; auto& item : items) {
            item = std::make_unique<double[]>(500'000'000);
            std::cout << fmt::format(
                "items[{}] points to 500,000,000 doubles\n", i++);
        }
    }
    catch (const std::bad_alloc& memoryAllocationException) {
        std::cerr << fmt::format("Exception accurred: {}\n",
            memoryAllocationException.what());
    }

    return 0;
}