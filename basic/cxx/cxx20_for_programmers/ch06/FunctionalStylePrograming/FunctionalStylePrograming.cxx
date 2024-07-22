#include <array>
#include <fmt/format.h>
#include <iostream>
#include <iterator>
#include <numeric>
#include <ranges>

// std::views::iota 生成指定范围的整数，像python的range
// std::views::filter 根据参数函数的要求，从惰性管道中筛选出值s
// std::views::transform 根据参数函数的要求，惰性管道中修改值s 映射 mapping 语义

int main() {
    auto showValues{
        [](auto& values, const std::string& message) {
            std::cout << fmt::format("{}: ", message);

            for (const auto& value : values) {
                std::cout << fmt::format("{} ", value);
            }

            std::cout << "\n";
        }
    };

    auto values1{std::views::iota(1, 11)};
    showValues(values1, "Generate integer 1-10");

    auto values2{values1 |
        std::views::filter([](const auto& x){return x % 2 == 0;})};
    showValues(values2, "Filtering even integers");

    auto values3{values2 |
        std::views::transform([](const auto& x){return x * x;})};
    showValues(values3, "Mapping even integers to squares");

    auto values4{values1 |
        std::views::filter([](const auto& x){return x % 2 == 0;}) |
        std::views::transform([](const auto& x){return x * x;})};
    showValues(values4, "Squares of even integers");

    std::cout << fmt::format("Sum squares of even integers 2-10: {}\n",
        std::accumulate(std::begin(values4), std::end(values4), 0));

    constexpr std::array numbers{1, 2, 3, 4, 6, 7, 8, 9, 10};
    auto values5{numbers |
        std::views::filter([](const auto& x){return x % 2 == 0;}) |
        std::views::transform([](const auto& x){return x * x;})};
    showValues(values5, "Squares of even integers in array numbers");

    return 0;
}