#include <iostream>

int main() {
    int number1{0}, number2{0};

    std::cout << "Enter two integer to compare: ";
    std::cin >> number1 >> number2;

    if (number1 == number2) {
        std::cout << number1 << " == " << number2 << "\n";
    }

    if (number1 != number2) {
        std::cout << number1 << " != " << number2 << "\n";
    }

    if (number1 < number2) {
        std::cout << number1 << " < " << number2 << "\n";
    }

    if (number1 > number2) {
        std::cout << number1 << " > " << number2 << "\n";
    }

    if (number1 <= number2) {
        std::cout << number1 << " <= " << number2 << "\n";
    }

    if (number1 >= number2) {
        std::cout << number1 << " >= " << number2 << "\n";
    }

    return 0;
}