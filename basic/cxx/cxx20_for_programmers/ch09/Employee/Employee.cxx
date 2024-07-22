#include <fmt/format.h>
#include <iostream>
#include "Employee.h"

int Employee::getCount() { return m_count; }

Employee::Employee(std::string_view firstName, std::string_view lastName)
    : m_firstName{firstName}, m_lastName{lastName} {
    ++m_count;
    std::cout << fmt::format("Employee constructor called for {} {}\n",
        m_firstName, m_lastName);
}

Employee::~Employee() {
    std::cout << fmt::format("~Employee() called for {} {}\n",
        m_firstName, m_lastName);
    --m_count;
}

const std::string& Employee::getFirstName() const { return m_firstName; }
const std::string& Employee::getLastName() const { return m_lastName; }