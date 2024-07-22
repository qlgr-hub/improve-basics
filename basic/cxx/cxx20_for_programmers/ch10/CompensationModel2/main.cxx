#include <fmt/format.h>
#include <iostream>
#include <vector>
#include "Employee.h"
#include "Salaried.h"
#include "Commission.h"

int main() {
    Employee salariedEmployee{"John Smith", Salaried{800.0}};
    Employee commissionEmployee{"Sue Jones", Commission{10000.0, .06}};

    std::vector employees{salariedEmployee, commissionEmployee};
    for (const auto& employee : employees) {
        std::cout << fmt::format("{}\nearned ${:.2f}\n\n",
            employee.toString(), employee.earnings());
    }

    return 0;
}