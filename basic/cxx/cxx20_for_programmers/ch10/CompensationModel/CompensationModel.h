#pragma once
#include <string>

class CompensationModel {
public:
    virtual ~CompensationModel() = default;
    virtual double earnings() const = 0;
    virtual std::string toString() const = 0;
};
