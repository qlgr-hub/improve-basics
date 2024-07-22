#include <array>
#include <fmt/format.h>
#include <iostream>
#include <memory>
#include <new>
#include <cstdlib>

void customNewHandler() {
    std::cerr << "customNewHandler was called\n";
    std::exit(EXIT_FAILURE);
}


int main() {
    std::array<std::unique_ptr<double[]>, 1000> items{};

    std::set_new_handler(customNewHandler);

    for (int i{0}; auto& item : items) {
        item = std::make_unique<double[]>(500'000'000);
        std::cout << fmt::format(
            "items[{}] points to 500,000,000 doubles\n", i++);
    }

    return 0;
}