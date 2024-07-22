#include <fmt/format.h>
#include <stdexcept>
#include <string>
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

double Employee::earnings() const {
    return getPay();
}

std::string Employee::toString() const {
    return getString();
}

std::string Employee::getString() const {
    return fmt::format("name: {}", getName());
}