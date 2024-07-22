#include <array>
#include <iostream>
#include <string>
#include <vector>

template<typename T>
void printContainer1(const T& items) {
    for (const auto& item : items) {
        std::cout << item << " ";
    }
    std::cout << "\n";
}

void printContainer(const auto& items) {
    for (const auto& item : items) {
        std::cout << item << " ";
    }
    std::cout << "\n";
}

int main() {
    using namespace std::string_literals;

    std::array ints{1, 2, 3, 4, 5};
    std::vector strings{"red"s, "green"s, "blue"s};

    std::cout << "ints: ";
    printContainer1(ints);
    std::cout << "strings: ";
    printContainer(strings);

    auto sumSquare1{[](auto total, auto value) {return total + value * value;}};
    auto sumSquare2{[]<typename T>(T total, T value) {return total + value * value;}};

    std::cout << sumSquare1(33, 4) << "\n";
    std::cout << sumSquare2(33.1, 3.0) << "\n";

    return 0;
}