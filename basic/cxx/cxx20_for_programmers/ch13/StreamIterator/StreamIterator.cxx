#include <iostream>
#include <iterator>

int main() {
    std::cout << "Enter two integers: ";

    std::istream_iterator<int> inputInt{std::cin};

    const int number1{*inputInt};
    ++inputInt;
    const int number2{*inputInt};

    std::ostream_iterator<int> outputInt{std::cout};

    std::cout << "The sum is: ";
    *outputInt = number1 + number2;
    std::cout << "\n";

    return 0;
}