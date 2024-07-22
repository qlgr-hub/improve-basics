#pragma once
#include <string>
#include <string_view>
#include "Employee.h"

class SalariedEmployee final : public Employee {
public:
    SalariedEmployee(std::string_view name, double salary);
    virtual ~SalariedEmployee() = default;

    void setSalary(double salary);
    double getSalary() const;

    virtual double earnings() const override;
    virtual std::string toString() const override;

private:
    double m_salary{0.0};
};