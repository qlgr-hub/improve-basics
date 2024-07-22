#include <ios>
#include <iostream>
#include <iomanip>

int main() {
    int total{0};
    int gradeCounter{0};
    
    std::cout << "Enter grade or -1 to quit: ";
    int grade;
    std::cin >> grade;

    while (grade != -1) {
        total += grade;
        ++gradeCounter;

        std::cout << "Enter grade or -1 to quit: ";
        std::cin >> grade;
    }

    if (gradeCounter != 0) {
        double average{static_cast<double>(total) / gradeCounter};

        std::cout << "\nTotal of the " << gradeCounter << " grades entered is " << total;
        std::cout << std::setprecision(2) << std::fixed;
        std::cout << "\nClass average is " << average << "\n";
    }
    else {
        std::cout << "No grades were entered!\n";
    }

    return 0;
}