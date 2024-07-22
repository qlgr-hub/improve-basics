#pragma once
#include <string>
#include <string_view>
#include "SalariedEmployee.h"

class CommissionEmployee final : public Employee {
public:
    CommissionEmployee(std::string_view name, double grossSales,
        double commissionRate);
    virtual ~CommissionEmployee() = default;
    
    void setGrossSales(double grossSales);
    double getGrossSales() const;

    void setCommissionRate(double commissionRate);
    double getCommissionRate() const;

private:
    double m_grossSales{0.0};
    double m_commissionRate{0.0};

    double getPay() const override;
    std::string getString() const override;
};
