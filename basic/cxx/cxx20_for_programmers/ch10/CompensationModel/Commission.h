#pragma once
#include <string>
#include "CompensationModel.h"

class Commission final : public CompensationModel {
public:
    Commission(double grossSales, double commissionRate);
    double earnings() const override;
    std::string toString() const override;
private:
    double m_grossSales{0.0};
    double m_commissionRate{0.0};
};
