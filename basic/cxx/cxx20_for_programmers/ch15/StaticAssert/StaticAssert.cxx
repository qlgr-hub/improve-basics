#include <concepts>
#include <iostream>
#include <string>

template<typename T>
concept Numeric = std::integral<T> || std::floating_point<T>;

template<typename T>
auto multiply(T a, T b) {
    static_assert(Numeric<T>);
    return a * b;
}

int main() {
    using namespace std::string_literals;

    multiply(2, 5);
    multiply(2.5, 5.5);
    multiply("2"s, "5"s);
    return 0;
}