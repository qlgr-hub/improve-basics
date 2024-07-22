#pragma once
#include <string>

class Commission {
public:
    Commission(double grossSales, double commissionRate);
    double earnings() const;
    std::string toString() const;
private:
    double m_grossSales{0.0};
    double m_commissionRate{0.0};
};
