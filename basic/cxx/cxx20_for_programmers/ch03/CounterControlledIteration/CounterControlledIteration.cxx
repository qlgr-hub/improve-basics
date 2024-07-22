#include <iostream>

int main() {
    int total{0};
    int gradeCounter{1};

    while (gradeCounter <= 10) {
        std::cout << "Enter grade: ";
        int grade;
        std::cin >> grade;
        total += grade;
        ++gradeCounter;
    }

    int average{total / 10};

    std::cout << "\nTotal of all grades is " << total;
    std::cout << "\nClass average is " << average << "\n";

    return 0;
}