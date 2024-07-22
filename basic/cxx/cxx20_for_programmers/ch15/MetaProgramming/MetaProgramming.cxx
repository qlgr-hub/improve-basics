#include <array>
#include <cstddef>
#include <iterator>
#include <iostream>
#include <list>
#include <type_traits>
#include <fmt/format.h>

template <int N>
struct Factorial
{
    static constexpr long long value{N * Factorial<N - 1>::value};
};

template <>
struct Factorial<0>
{
    static constexpr long long value{1};
};

constexpr long long recursiveFactorial(int number) {
    if (number <= 1) {
        return 1;
    }
    else {
        return number * recursiveFactorial(number - 1);
    }
}

constexpr long long iteractiveFactorial(int number) {
    long long factorial{1};

    for (long long i{2}; i <= number; ++i) {
        factorial *= i;
    }

    return factorial;
}

template <std::input_iterator Iterator>
auto customDistance(Iterator begin, Iterator end) {
    if constexpr (std::is_base_of_v<std::random_access_iterator_tag, 
        typename Iterator::iterator_category>) {
        std::cout << "customDistance with random-access iterators\n";
        return end - begin;
    }
    else {
        std::cout << "customDistance with non-random-access iterators\n";
        std::ptrdiff_t count{0};

        for (auto iter{begin}; iter != end; ++iter) {
            ++count;
        }

        return count;
    }
}

template <typename T>
struct my_add_const {
    using type = const T;
};

template <typename T>
struct my_remove_ptr {
    using type = T;
};

template <typename T>
struct my_remove_ptr<T*> {
    using type = T;
};

int main() {
    std::cout << "CALCULATING FACTORIALS AT COMPILE TIME "
        << "WITH A RECURSIVE METAFUNCTION"
        << "\nFactorial(0): " << Factorial<0>::value
        << "\nFactorial(1): " << Factorial<1>::value
        << "\nFactorial(2): " << Factorial<2>::value
        << "\nFactorial(3): " << Factorial<3>::value
        << "\nFactorial(4): " << Factorial<4>::value
        << "\nFactorial(5): " << Factorial<5>::value;

    std::cout << "\n\nCALCULATING FACTORIALS AT COMPILE TIME "
        << "WITH A RECURSIVE CONSTEXPR FUNCTION"
        << "\nrecursiveFactorial(0): " << recursiveFactorial(0)
        << "\nrecursiveFactorial(1): " << recursiveFactorial(1)
        << "\nrecursiveFactorial(2): " << recursiveFactorial(2)
        << "\nrecursiveFactorial(3): " << recursiveFactorial(3)
        << "\nrecursiveFactorial(4): " << recursiveFactorial(4)
        << "\nrecursiveFactorial(5): " << recursiveFactorial(5);

    std::cout << "\n\nCALCULATING FACTORIALS AT COMPILE TIME "
        << "WITH A ITERATIVE CONSTEXPR FUNCTION"
        << "\niteractiveFactorial(0): " << iteractiveFactorial(0)
        << "\niteractiveFactorial(1): " << iteractiveFactorial(1)
        << "\niteractiveFactorial(2): " << iteractiveFactorial(2)
        << "\niteractiveFactorial(3): " << iteractiveFactorial(3)
        << "\niteractiveFactorial(4): " << iteractiveFactorial(4)
        << "\niteractiveFactorial(5): " << iteractiveFactorial(5);

    std::cout << "\n";

    std::array ints1{1, 2, 3, 4, 5};
    std::list ints2{1, 2, 3};

    // clang g++ 使用指针作为迭代器 所以没法使用这个版本的 distance
    // auto result1{customDistance(ints1.begin(), ints1.end())};
    // std::cout << "\nints1 number of elements: " << result1 << "\n";
    auto result2{customDistance(ints2.begin(), ints2.end())};
    std::cout << "ints2 number of elements: " << result2 << "\n";

    std::cout << fmt::format("\n{}\n{}{}\n{}{}\n\n",
        "ADD CONST TO A TYPE VIA A CUSTOM TYPE METAFUNCTION",
        "std::is_same_v<const int, my_add_const<int>::type>: ",
        std::is_same_v<const int, my_add_const<int>::type>,
        "std::is_same_v<int* const, my_add_const<int*>::type>: ",
        std::is_same_v<int* const, my_add_const<int*>::type>);

    std::cout << fmt::format("\n{}\n{}{}\n{}{}\n\n",
        "REMOVE POINTER FROM TYPE VIA A CUSTOM TYPE METAFUNCTION",
        "std::is_same_v<int, my_remove_ptr<int>::type>: ",
        std::is_same_v<int, my_remove_ptr<int>::type>,
        "std::is_same_v<int, my_remove_ptr<int*>::type>: ",
        std::is_same_v<int, my_remove_ptr<int*>::type>);

    std::cout << fmt::format("\n{}\n{}{}\n{}{}\n\n",
        "ADD REFERENCES TO TYPES USING STANDARD TYPE TRAITS",
        "std::is_same_v<int&, std::add_lvalue_reference<int>::type>: ",
        std::is_same_v<int&, std::add_lvalue_reference<int>::type>,
        "std::is_same_v<int&&, std::add_rvalue_reference<int>::type>: ",
        std::is_same_v<int&&, std::add_rvalue_reference<int>::type>);
    
    std::cout << fmt::format("\n{}\n{}{}\n{}{}\n{}{}\n\n",
        "REMOVE REFERENCES FROM TYPES USING STANDARD TYPE TRAITS",
        "std::is_same_v<int, std::remove_reference<int>::type>: ",
        std::is_same_v<int, std::remove_reference<int>::type>,
        "std::is_same_v<int, std::remove_reference<int&>::type>: ",
        std::is_same_v<int, std::remove_reference<int&>::type>,
        "std::is_same_v<int, std::remove_reference<int&&>::type>: ",
        std::is_same_v<int, std::remove_reference<int&&>::type>);
    
    return 0;
}