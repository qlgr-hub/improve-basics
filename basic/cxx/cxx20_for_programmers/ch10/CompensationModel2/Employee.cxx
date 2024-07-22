#include <fmt/format.h>
#include <variant>
#include "Employee.h"

Employee::Employee(std::string_view name, CompensationModel model)
    : m_name{name}, m_model{model} {}

void Employee::setCompensationModel(CompensationModel model) {
    m_model = model;
}

double Employee::earnings() const {
    auto getEarnings{[](const auto& model){return model.earnings();}};
    return std::visit(getEarnings, m_model);
}

std::string Employee::toString() const {
    auto getString{[](const auto& model){return model.toString();}};
    return fmt::format("{}\n{}", m_name, std::visit(getString, m_model));
}