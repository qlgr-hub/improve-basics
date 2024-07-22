#pragma once
#include "Commission.h"
#include "Salaried.h"
#include <string>
#include <string_view>
#include <variant>

using CompensationModel = std::variant<Commission, Salaried>;

class Employee final {
public:
    explicit Employee(std::string_view name, CompensationModel model);
    void setCompensationModel(CompensationModel model);

    double earnings() const;
    std::string toString() const;
private:
    std::string m_name{};
    CompensationModel m_model;
};