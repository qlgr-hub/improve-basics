#include <iostream>
#include <string>
#include <list>
#include <algorithm>
#include <concepts>

template<typename T>
T multiply1(T first, T second) {return first * second;}

template<typename T>
    requires std::integral<T> || std::floating_point<T>
T multiply(T first, T second) {return first * second;}

int main() {
    std::cout << "Product of 5 and 3: " << multiply1(5, 3)
        << "\nProduct of 7.25 and 2.0: " << multiply1(7.25, 2.0) << "\n";

    // std::string s1{"hi"};
    // std::string s2{"bye"};
    // auto result{multiply(s1, s2)};
    //
    // std::list integers{10, 2, 33, 4, 7, 1, 80};
    // std::sort(integers.begin(), integers.end());

    std::cout << "Product of 5 and 3: " << multiply1(5, 3)
        << "\nProduct of 7.25 and 2.0: " << multiply1(7.25, 2.0) << "\n";

    // std::string s1{"hi"};
    // std::string s2{"bye"};
    // auto result{multiply(s1, s2)};

    return 0;
}