#pragma once

class Base2 {
public:
    explicit Base2(char letter) : m_letter{letter} {}
    char getData() const {return m_letter;}
private:
    char m_letter;
};