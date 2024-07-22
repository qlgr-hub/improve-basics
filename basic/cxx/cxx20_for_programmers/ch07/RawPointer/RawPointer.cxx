#include <iostream>
#include <fmt/format.h>

int cubeByValue(int n);
void cubeByReference(int* nPtr);

int main() {
    constexpr int a{7};
    const int* aPtr{&a};

    std::cout << "The address of a is " << &a
        << "\nThe value of aPtr is " << aPtr;
    
    std::cout << "\n\nThe value of a is " << a
        << "\nThe value of *aPtr is " << *aPtr << '\n';

    int number{5};
    std::cout << fmt::format("Original value of number is {}\n", number);
    number = cubeByValue(number);
    std::cout << fmt::format("New value of number is {}\n", number);

    int number1{5};
    std::cout << fmt::format("Original value of number1 is {}\n", number1);
    cubeByReference(&number1);
    std::cout << fmt::format("New value of number1 is {}\n", number1);

    return 0;
}

int cubeByValue(int n) {
   return n * n * n;
}

void cubeByReference(int* nPtr) {
   *nPtr = *nPtr * *nPtr * *nPtr;              
}