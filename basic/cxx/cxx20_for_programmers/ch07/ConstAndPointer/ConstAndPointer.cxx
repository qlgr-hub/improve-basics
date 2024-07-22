#include <iostream>

int main() {
    // int y{0};
    // const int* yPtr{&y};
    // *yPtr = 100; // error: read-only variable is not assignable

    // int x, y;                               
    // int* const ptr{&x};
    // *ptr = 7;
    // ptr = &y; // error: cannot assign to variable 'ptr' with const-qualified type 'int *const'

    // int x{5}, y;
    // const int* const ptr{&x};
    // std::cout << *ptr << std::endl;
    // *ptr = 7; // error: read-only variable is not assignable
    // ptr = &y; // error: cannot assign to variable 'ptr' with const-qualified type 'const int *const'

    return 0;
}