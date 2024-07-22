#include <fmt/format.h>
#include <stdexcept>
#include <string_view>
#include "CommissionEmployee.h"
#include "Employee.h"

CommissionEmployee::CommissionEmployee(
    std::string_view name, double grossSales, double commissionRate)
    : Employee{name} {
    setGrossSales(grossSales);
    setCommissionRate(commissionRate);
}

void CommissionEmployee::setGrossSales(double grossSales) {
    if (grossSales < 0.0) {
        throw std::invalid_argument("Gross sales must be >= 0.0");
    }

    m_grossSales = grossSales;
}

double CommissionEmployee::getGrossSales() const {
    return m_grossSales;
}

void CommissionEmployee::setCommissionRate(double commissionRate) {
    if (commissionRate <= 0.0 || commissionRate >= 1) {
        throw std::invalid_argument("Commission rate must be > 0.0 and < 1.0");
    }

    m_commissionRate = commissionRate;
}

double CommissionEmployee::getCommissionRate() const {
    return m_commissionRate;
}

double CommissionEmployee::getPay() const {
    return getGrossSales() * getCommissionRate();
}

std::string CommissionEmployee::getString() const {
    return fmt::format("{}\n{}: ${:.2f}\n{}: {:.2f}", Employee::getString(),
        "gross sales", getGrossSales(), "commission rate", getCommissionRate());
}