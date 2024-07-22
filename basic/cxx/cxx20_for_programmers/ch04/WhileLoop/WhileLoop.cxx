#include <iostream>

int main() {
    int counter{1};

    while (counter <= 10) {
        std::cout << counter << " ";
        ++counter;
    }

    std::cout << "\n";
    return 0;
}