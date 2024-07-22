#include <iostream>
#include <exception>

void throwException() {
    try {
        std::cout << " Function throwException throws an exception\n";
        throw std::exception{};
    }
    catch (const std::exception&) {
        std::cout << " Exception handled in function throwException"
            << "\n Fucntion throwException rethrows exception";
        throw; // rethrows it
    }

    std::cout << "This should not print\n";
}

int main() {
    try {
        std::cout << "main invokes function throwException\n";
        throwException();
        std::cout << "This should not print\n";
    }
    catch (const std::exception&) {
        std::cout << "\n\nException handled in main\n";
    }

    std::cout << "Program control continues after catch in main\n";
    return 0;
}