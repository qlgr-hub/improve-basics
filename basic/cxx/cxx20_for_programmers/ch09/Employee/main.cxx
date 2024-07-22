#include <fmt/format.h>
#include <iostream>
#include "Employee.h"

int main() {
    std::cout << fmt::format("Initial employee cout: {}\n",
        Employee::getCount());

    {
        const Employee e1{"Susan", "Baker"};
        const Employee e2{"Robert", "Jones"};

        std::cout << fmt::format("Employee count after creating objects: {}\n",
            Employee::getCount());

        std::cout << fmt::format("Employee 1: {} {}\nEmployee 2: {} {}\n\n",
            e1.getFirstName(), e1.getLastName(),
            e2.getFirstName(), e2.getLastName());
    }

    std::cout << fmt::format("Employee count after objects are deleted: {}\n",
        Employee::getCount());
    return 0;
}