#include <fmt/format.h>
#include <iostream>
#include "DivideByZeroException.h"

double quotient(double numerator, double denominator) {
    if (denominator == 0.0) {
        throw DivideByZeroException{};
    }

    return numerator / denominator;
}

int main() {
    int number1{0};
    int number2{0};

    std::cout << "Enter two integers (end-of-file to end): ";

    while (std::cin >> number1 >> number2) {
        try {
            double result{quotient(number1, number2)};
            std::cout << fmt::format("The quotient is: {}\n", result);
        }
        catch (const DivideByZeroException& ex) {
            std::cerr << fmt::format("Exception occurred: {}\n", ex.what());
        }

        std::cout << "Enter two integers (end-of-file to end): ";
    }

    std::cout << "\n";
    return 0;
}