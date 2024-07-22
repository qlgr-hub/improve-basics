#include <fmt/format.h>
#include <iostream>
#include "Employee.h"

Employee::Employee(std::string_view firstName, std::string_view lastName,
    const Date& birthDate, const Date& hireDate)
    : m_firstName{firstName}, m_lastName{lastName},
    m_birthDate{birthDate}, m_hireDate{hireDate} {
    std::cout << fmt::format("Employee object constructor: {} {}\n",
        m_lastName, m_firstName);
}

std::string Employee::toString() const {
    return fmt::format("{}, {} Hired: {} Birthday: {}", m_lastName, m_firstName,
        m_hireDate.toString(), m_birthDate.toString());
}

Employee::~Employee() {
    std::cout << fmt::format("Employee object destructor: {}, {}\n",
        m_lastName, m_firstName);
}