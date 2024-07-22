#include <array>
#include <fmt/format.h>
#include <iostream>
#include <numeric>
#include <span>
#include <vector>

void displayArray(const int items[], size_t size) {
    for (size_t i{0}; i < size; ++i) {
        std::cout << fmt::format("{} ", items[i]);
    }
}

void displaySpan(std::span<const int> items) {
    for (const auto& item : items) {
        std::cout << fmt::format("{} ", item);
    }
}

void times2(std::span<int> items) {
    for (int& item : items) {
        item *= 2;
    }
}

int main() {
    int values1[]{1, 2, 3, 4, 5};
    std::array values2{6, 7, 8, 9, 10};
    std::vector values3{11, 12, 13, 14, 15};

    std::cout << "values1 via displayArray: ";
    displayArray(values1, 5);

    std::cout << "\nvalues1 via displaySpan: ";
    displaySpan(values1);

    std::cout << "\nvalues2 via displaySpan: ";
    displaySpan(values2);
    std::cout << "\nvalues3 via displaySpan: ";
    displaySpan(values3);

    times2(values1);
    std::cout << "\n\nvalues1 after times2 modifies its span argument: ";
    displaySpan(values1);

    std::span mySpan{values1};
    std::cout << "\n\nmySpan's first element: " << mySpan.front()
        << "\nmySpan's last element: " << mySpan.back();

    std::cout << "\n\nSum of mySpan's elements: "
        << std::accumulate(std::begin(mySpan), std::end(mySpan), 0);

    std::cout << "\n\nFirst three elements of mySpan: ";
    displaySpan(mySpan.first(3));
    std::cout << "\nLast three elements of mySpan: ";
    displaySpan(mySpan.last(3));
    std::cout << "\nMiddle three elements of mySpan: ";
    displaySpan(mySpan.subspan(1, 3));

    times2(mySpan.subspan(1, 3));
    std::cout << "\n\nvalues1 after modifying elements via span: ";
    displaySpan(values1);

    std::cout << "\n\nThe element at index 2 is: " << mySpan[2] << '\n';
    return 0;
}