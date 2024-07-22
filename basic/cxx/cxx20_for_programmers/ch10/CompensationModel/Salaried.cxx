#include <fmt/format.h>
#include <stdexcept>
#include "Salaried.h"

Salaried::Salaried(double salary) : m_salary{salary} {
    if (m_salary < 0.0) {
        throw std::invalid_argument("Weekly salary must be >= 0.0");
    }
}

double Salaried::earnings() const {
    return m_salary;
}

std::string Salaried::toString() const {
    return fmt::format("salary: ${:.2f}", m_salary);
}