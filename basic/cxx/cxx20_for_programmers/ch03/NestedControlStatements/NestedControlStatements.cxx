#include <iostream>

int main() {
    int passes{0};
    int failures{0};
    int studentCounter{1};

    while (studentCounter <= 10) {
        std::cout << "Enter result (1 = pass, 2 = fail): ";
        int result;
        std::cin >> result;

        if (result == 1) {
            ++passes; 
        }
        else {
            ++failures;
        }

        ++studentCounter;
    }

    std::cout << "Passed: " << passes << "\nFailed: " << failures << "\n";

    if (passes > 8) {
        std::cout << "Bonus to instructor!\n";
    }

    return 0;
}