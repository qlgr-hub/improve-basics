#include <fmt/format.h>
#include <iostream>
#include "Employee.h"

int main() {
    const Date birth{1987, 7, 24};
    const Date hire{2018, 3, 12};
    const Employee manager{"Sue", "Green", birth, hire};

    std::cout << fmt::format("\n{}\n\n", manager.toString());
    return 0;
}