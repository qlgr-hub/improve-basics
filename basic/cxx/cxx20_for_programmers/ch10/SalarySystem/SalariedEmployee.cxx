#include <fmt/format.h>
#include <stdexcept>
#include <string_view>
#include "Employee.h"
#include "SalariedEmployee.h"

SalariedEmployee::SalariedEmployee(std::string_view name, double salary)
    : Employee{name} {
    setSalary(salary);
}

void SalariedEmployee::setSalary(double salary) {
    if (salary < 0.0) {
        throw std::invalid_argument("Salary must be >= 0.0");
    }

    m_salary = salary;
}

double SalariedEmployee::getSalary() const {
    return m_salary;
}

double SalariedEmployee::earnings() const {
    return getSalary();
}

std::string SalariedEmployee::toString() const {
    return fmt::format("{}\n{}: {}: ${:.2f}", Employee::toString(),
        getName(), "salary", getSalary());
}