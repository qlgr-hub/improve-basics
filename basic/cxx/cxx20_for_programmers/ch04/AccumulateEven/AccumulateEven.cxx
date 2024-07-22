#include <iostream>

int main() {
    int total{0};

    for (int counter{2}; counter <= 20; counter += 2) {
        total += counter;
    }

    std::cout << "Sum is: " << total << "\n";
    return 0;
}