#include <fmt/format.h>
#include <iostream>

class Count {
    friend void modifyX(Count& c, int value);
public:
    int getX() const { return m_x; }
private:
    int m_x{0};
};

void modifyX(Count& c, int value) {
    c.m_x = value;
}

int main() {
    Count counter{};

    std::cout << fmt::format("Initial counter.m_x: {}\n", counter.getX());
    modifyX(counter, 8);
    std::cout << fmt::format("counter.m_x after modifyX: {}\n", counter.getX());
    return 0;
}