#include <fmt/format.h>
#include "Base1.h"
#include "Base2.h"
#include "Derived.h"

Derived::Derived(int value, char letter, double real)
    : Base1{value}, Base2{letter}, m_real{real} {}

double Derived::getReal() const {
    return m_real;
}

std::string Derived::toString() const {
    return fmt::format("int: {}; char: {}; double: {}",
        Base1::getData(), Base2::getData(), getReal());
}