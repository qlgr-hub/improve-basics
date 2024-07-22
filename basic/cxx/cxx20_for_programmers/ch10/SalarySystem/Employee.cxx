#include <fmt/format.h>
#include <stdexcept>
#include <string_view>
#include "Employee.h"

Employee::Employee(std::string_view name)
    : m_name{name} {}

void Employee::setName(std::string_view name) {
    m_name = name;
}

std::string Employee::getName() const {
    return m_name;
}

std::string Employee::toString() const {
    return fmt::format("name: {}", getName());
}