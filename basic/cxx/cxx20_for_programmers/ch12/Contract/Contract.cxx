#include <iostream>

// 编译器还未支持 先不玩了！！！！

double quotient(double numerator, double denominator)
    [[pre: denominator != 0.0]];

int main() {
    std::cout << "quotient(100, 7): " << quotient(100, 7)
        << "\nquotient(100, 0): " << quotient(100, 0) << "\n";
    
    return 0;
}

double quotient(double numerator, double denominator) {
    return numerator / denominator;
}