#include <fmt/format.h>
#include <stdexcept>
#include "Commission.h"

Commission::Commission(double grossSales, double commissionRate) 
    : m_grossSales{grossSales}, m_commissionRate{commissionRate} {
    if (m_grossSales < 0.0) {
        throw std::invalid_argument("Gross sales must be >= 0.0");
    }

    if (m_commissionRate <= 0.0 || m_commissionRate >= 1.0) {
        throw std::invalid_argument(
            "Commission rate must be > 0.0 and < 1.0");
    }
}

double Commission::earnings() const {
    return m_grossSales * m_commissionRate;
}

std::string Commission::toString() const {
    return fmt::format("gross sales: ${:.2f}; commission rate: {:.2f}",
        m_grossSales, m_commissionRate);
}