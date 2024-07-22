#pragma once
#include <string>

class Salaried {
public:
    explicit Salaried(double salary);
    double earnings() const;
    std::string toString() const;
private:
    double m_salary{0.0};
};
