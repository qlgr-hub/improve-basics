#include <fmt/format.h>
#include <iostream>
#include <vector>
#include "Employee.h"
#include "Salaried.h"
#include "Commission.h"

int main() {
    Salaried salaried{800.0};
    Employee salariedEmployee{"John Smith", &salaried};

    Commission commission{10000.0, .06};
    Employee commissionEmployee{"Sue Jones", &commission};

    std::vector employees{salariedEmployee, commissionEmployee};
    for (const auto& employee : employees) {
        std::cout << fmt::format("{}\nearned ${:.2f}\n\n",
            employee.toString(), employee.earnings());
    }

    return 0;
}