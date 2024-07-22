#include <concepts>
#include <cstddef>
#include <iostream>
#include <iterator>
#include <array>
#include <list>

template<typename T>
concept Numeric = std::integral<T> || std::floating_point<T>;

auto multiply(Numeric auto first, Numeric auto second) {
    return first * second;
}

// 概念的使用方式 1
template<typename T>
    requires Numeric<T>
T multiply1(T first, T second) {
    return first * second;
}

// 概念的使用方式 2
template<typename T>
T multiply2(T first, T second) requires Numeric<T> {
    return first * second;
}

template<Numeric T>
T multiply3(T first, T second) {
    return first * second;
}

template<std::input_iterator Iterator>
auto customDistance(Iterator begin, Iterator end) {
    std::cout << "Called customDistance with input iterators\n";
    std::ptrdiff_t count{0};

    for (auto& iter{begin}; iter != end; ++iter) {
        ++count;
    }

    return count;
}

template<std::random_access_iterator Iterator>
auto customDistance(Iterator begin, Iterator end) {
    std::cout << "Called customDistance with random-access iterators\n";
    return end - begin;
}

int main() {
    std::cout << "Product of 5 and 3: " << multiply(5, 3)
        << "\nProduct of 7.25 and 2.0: " << multiply1(7.25, 2.)
        << "\nProduct of 5.0 and 7.25: " << multiply2(5., 7.25)
        << "\nProduct of 5 and 3: " << multiply3(5, 3) << "\n";

    std::array ints1{1, 2, 3, 4, 5};
    std::list ints2{1, 2, 3};

    auto result1{customDistance(ints1.begin(), ints1.end())};
    std::cout << "ints1 number of elements: " << result1 << "\n";
    auto result2{customDistance(ints2.begin(), ints2.end())};
    std::cout << "ints2 number of elements: " << result2 << "\n";

    return 0;
}