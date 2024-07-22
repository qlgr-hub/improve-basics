#include <fmt/format.h>
#include <iostream>
#include <array>

int main() {
    std::array items{1, 2, 3, 4, 5};

    std::cout << "items before modification: ";
    for (const int& item : items) {
        std::cout << fmt::format("{} ", item); 
    }                       

    for (int& item : items) {
        item *= 2;
    }

    std::cout << "\nitems after modification: ";
    for (const int& item : items) {
        std::cout << fmt::format("{} ", item);
    }

    std::cout << "\n\ncalculating a running total of items' values:\n";
    for (int runningTotal{0}; const int& item : items) {
        runningTotal += item;
        std::cout << fmt::format("item: {}; running total: {}\n",
            item, runningTotal);
    }

    return 0;
}
