#pragma once
#include <iostream>
#include <string>
#include "Base1.h"
#include "Base2.h"

class Derived : public Base1, public Base2 {
public:
    Derived(int value, char letter, double real);
    double getReal() const;
    std::string toString() const;
private:
    double m_real;
};
