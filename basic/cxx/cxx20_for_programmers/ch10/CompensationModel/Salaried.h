#pragma once
#include <string>
#include "CompensationModel.h"

class Salaried final : public CompensationModel {
public:
    explicit Salaried(double salary);
    double earnings() const override;
    std::string toString() const override;
private:
    double m_salary{0.0};
};
