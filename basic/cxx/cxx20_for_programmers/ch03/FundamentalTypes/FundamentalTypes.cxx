#include <iostream>
#include "bignumber.h"

int main() {
    const long long value1{9'223'372'036'854'775'807LL};
    std::cout << "long long value1: " << value1 << "\nvalue1 - 1 = " << value1 - 1
            << "\nvalue1 + 1 = " << value1 + 1;

    const BigNumber value2{value1};
    std::cout << "\nBigNumber value2: " << value2 << "\nvalue2 - 1 = " << value2 - 1
            << "\nvalue2 + 1 = " << value2 + 1;

    long long value3{100'000'000};
    std::cout << "\n\nvalue3: " << value3;

    int counter{2};

    while (counter <= 5) {
        value3 *= 100'000'000;
        std::cout << "\nvalue3 to power " << counter << ": " << value3;
        ++counter;
    }

    BigNumber value4{100'000'000};
    counter = 2;

    while (counter <= 5) {
        value4 *= 100'000'000;
        std::cout << "\nvalue4 to power " << counter << ": " << value4;
        ++counter;
    }

    std::cout << "\n";
    return 0;
}