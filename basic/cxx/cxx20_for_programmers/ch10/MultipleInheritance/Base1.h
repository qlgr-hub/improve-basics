#pragma once

class Base1 {
public:
    explicit Base1(int value) : m_value{value} {}
    int getData() const {return m_value;}
private:
    int m_value;
};