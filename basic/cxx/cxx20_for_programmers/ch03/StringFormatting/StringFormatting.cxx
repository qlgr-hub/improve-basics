#include <iostream>
#include <fmt/format.h>
#include <string>

int main() {
    std::string student{"Pual"};
    int grade{87};

    std::cout << fmt::format("{}'s grade is {}\n", student, grade);
    return 0;
}