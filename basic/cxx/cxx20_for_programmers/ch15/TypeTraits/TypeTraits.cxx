#include <fmt/format.h>
#include <iostream>
#include <string>
#include <type_traits>

int main() {
    std::cout << fmt::format("{}\n{}{}\n{}{}\n{}{}\n{}{}\n{}{}\n\n",
        "CHECK WITH TYPE TRAITS WHETHER TYPES ARE INTEGERAL",
        "std::is_integeral<int>::value: ", std::is_integral<int>::value,
        "std::is_integral_v<int>: ", std::is_integral_v<int>,
        "std::is_integral_v<long>: ", std::is_integral_v<long>,
        "std::is_integral_v<float>: ", std::is_integral_v<float>,
        "std::is_integral_v<std::string>: ", std::is_integral_v<std::string>);

    std::cout << fmt::format("{}\n{}{}\n{}{}\n{}{}\n{}{}\n{}{}\n\n",
        "CHECK WITH TYPE TRAITS WHETHER TYPES ARE FLOATING POINT",
        "std::is_floating_point<float>::value: ", std::is_floating_point<float>::value,
        "std::is_floating_point_v<float>: ", std::is_floating_point_v<float>,
        "std::is_floating_point_v<double>: ", std::is_floating_point_v<double>,
        "std::is_floating_point_v<int>: ", std::is_floating_point_v<int>,
        "std::is_floating_point_v<std::string>: ", std::is_floating_point_v<std::string>);

    std::cout << fmt::format("{}\n{}{}\n{}{}\n{}{}\n{}{}\n\n",
        "CHECK WITH TYPE TRAITS WHETHER TYPES CAN BE USED IN ARITHMETIC",
        "std::is_arithmetic<int>::value: ", std::is_arithmetic<int>::value,
        "std::is_arithmetic_v<int>: ", std::is_arithmetic_v<int>,
        "std::is_arithmetic_v<double>: ", std::is_arithmetic_v<double>,
        "std::is_arithmetic_v<std::string>: ", std::is_arithmetic_v<std::string>);

    return 0;
}