#include <iostream>

int main() {
    int c{5};
    std::cout << "c before postincrement: " << c << "\n";
    std::cout << " postincrementing c: " << c++ << "\n";
    std::cout << "c after postincrement: " << c << "\n";

    c = 5;
    std::cout << "c before preincrement: " << c << "\n";
    std::cout << " preincrementing c: " << ++c << "\n";
    std::cout << "c after preincrement: " << c << "\n";

    return 0;
}