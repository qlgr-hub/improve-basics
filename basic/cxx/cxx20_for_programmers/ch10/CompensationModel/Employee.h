#pragma once
#include <string>
#include <string_view>
#include "CompensationModel.h"

class Employee final {
public:
    explicit Employee(std::string_view name, CompensationModel* modelPtr);
    void setCompensationModel(CompensationModel* modelPtr);

    double earnings() const;
    std::string toString() const;
private:
    std::string m_name{};
    CompensationModel* m_modelPtr;
};