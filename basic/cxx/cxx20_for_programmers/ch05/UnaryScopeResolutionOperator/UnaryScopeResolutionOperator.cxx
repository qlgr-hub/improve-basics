#include <iostream>

const int number{7};

int main() {
    const double number{10.5};

    std::cout << "Local double value of number = " << number
        << "\nGlobal int value of number = " << ::number << "\n";
    return 0;
}