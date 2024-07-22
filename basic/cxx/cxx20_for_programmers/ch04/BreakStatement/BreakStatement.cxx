#include <iostream>

int main() {
    int count{1};
    for (; count <= 10; ++count) {
        if (count == 5) {
            break;
        }

        std::cout << count << " ";
    }

    std::cout << "\nBroke out of loop at count = " << count << "\n";
    return 0;
}