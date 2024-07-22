#include <fmt/format.h>
#include <stdexcept>
#include <string_view>
#include "SalariedEmployee.h"

SalariedEmployee::SalariedEmployee(std::string_view name, double salary)
    : m_name{name} {
    setSalary(salary);
}

void SalariedEmployee::setName(std::string_view name) {
    m_name = name;
}

std::string SalariedEmployee::getName() const {
    return m_name;
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
    return fmt::format("name: {}\nsalary: ${:.2f}\n", getName(),
        getSalary());
}