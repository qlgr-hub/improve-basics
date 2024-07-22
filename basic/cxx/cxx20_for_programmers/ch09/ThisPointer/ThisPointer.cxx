#include <fmt/format.h>
#include <iostream>

class Test {
public:
    explicit Test(int value);
    void print() const;
private:
    int m_x{0};
};

Test::Test(int value) : m_x(value) {}

void Test::print() const {
    std::cout << fmt::format("        m_x = {}\n", m_x);
    std::cout << fmt::format("  this->m_x = {}\n", this->m_x);
    std::cout << fmt::format("(*this).m_x = {}\n", (*this).m_x);
}

int main() {
    const Test testObject{12};
    testObject.print();
    return 0;
}