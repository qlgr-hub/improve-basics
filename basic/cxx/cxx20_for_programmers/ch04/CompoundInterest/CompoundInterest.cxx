#include <ios>
#include <iostream>
#include <iomanip>
#include <cmath>

// std 流操纵元:
// std::setprecision(2) 浮点数显示精度 会四舍五入
// std::fixed 浮点数显示方式， 点分形式， std::scientific 科学表示 （e的多少多次方 这种）
// std::setw(4) 输出域的字符位宽

int main() {
    std::cout << std::fixed << std::setprecision(2);

    double principal{1000.00};
    double rate{0.05};

    std::cout << "Initial principal: " << principal << "\n";
    std::cout << "Interest rate: " << rate << "\n";

    std::cout << "\nYear" << std::setw(20) << "Amount on deposit" << "\n";

    for (int year{1}; year <= 10; ++year) {
        double amount{principal * pow(1.0 + rate, year)};
        std::cout << std::setw(4) << year << std::setw(20) << amount << "\n";
    }

    return 0;
}