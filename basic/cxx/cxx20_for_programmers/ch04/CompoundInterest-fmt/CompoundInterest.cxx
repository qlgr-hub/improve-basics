#include <iostream>
#include <fmt/format.h>
#include <cmath>

// format 格式说明:
// : 引入格式说明符
// >7.2f 浮点数 在7个字符的位宽内 右对齐显示 并且保留2位小数
// >4d 整数在 4个字符的位宽内右对齐显示

int main() {
    double principal{1000.00};
    double rate{0.05};

    std::cout << fmt::format("Initial principal: {:>7.2f}\n", principal);
    std::cout << fmt::format("Interest rate: {:>7.2f}\n", rate);

    std::cout << fmt::format("\n{}{:>20}\n", "Year", "Amount on deposit");

    for (int year{1}; year <= 10; ++year) {
        double amount{principal * pow(1.0 + rate, year)};
        std::cout << fmt::format("{:>4d}{:>20.2f}\n", year, amount);
    }

    return 0;
}