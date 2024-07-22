#include <fmt/format.h>
#include <iostream>
#include <stdexcept>
#include <utility>
#include "MyArray.h"

MyArray getArrayByValue() {
    MyArray localInts{10, 20, 30};
    return localInts;
}

MyArray getArrayByValue1() {
    return MyArray{10, 20, 30};
}

int main() {
    MyArray ints1(7);
    MyArray ints2(10);

    std::cout << fmt::format("\nints1 size: {}\ncontents: ", ints1.size())
        << ints1 << "\n";

    std::cout << fmt::format("\nints2 size: {}\ncontents: ", ints2.size())
        << ints2 << "\n";

    std::cout << "\n\nEnter 17 integers: ";
    std::cin >> ints1 >> ints2;

    std::cout << "\nints1: " << ints1 << "\nints2: " << ints2 << "\n";

    std::cout << "\n\nEvaluating: ints1 != ints2\n";
    if (ints1 != ints2) {
        std::cout << "ints1 and ints2 are not equal\n\n";
    }

    MyArray ints3{ints1};
    std::cout << fmt::format("\nints3 size: {}\ncontents: ", ints3.size())
        << ints3 << "\n";

    std::cout << "\n\nAssigning ints2 to ints1:\n";
    ints1 = ints2;
    std::cout << "\nints1: " << ints1 << "\nints2: " << ints2 << "\n";

    std::cout << "\n\nEvaluating: ints1 == ints2\n";
    if (ints1 == ints2) {
        std::cout << "ints1 and ints2 are equal\n\n";
    }

    std::cout << fmt::format("ints1[5] is {}\n", ints1[5]);

    std::cout << "Assigning 1000 to ints1[5]\n";
    ints1[5] = 1000;
    std::cout << "ints1: " << ints1 << "\n";

    try {
        std::cout << "\n\nAttempt to assign 1000 to ints1[15]\n";
        ints1[15] = 1000;
    }
    catch (const std::out_of_range& ex) {
        std::cerr << fmt::format("An exception occurred: {}\n", ex.what());
    }
    
    std::cout << "\nInitialize ints4 with temporary MyArray object\n";
    MyArray ints4{getArrayByValue1()};

    std::cout << fmt::format("\nints4 size: {}\ncontents: ", ints4.size())
        << ints4 << "\n";

    std::cout << "\nInitialize ints5 with results of std::move(ints4)\n";
    MyArray ints5{std::move(ints4)};

    std::cout << fmt::format("\nints5 size: {}\ncontents: ", ints5.size())
        << ints5 << fmt::format("\n\nSize if ints4 is now: {}\n", ints4.size());

    std::cout << "\nMove ints5 into ints4 via move assignment\n";
    ints4 = std::move(ints5);

    std::cout << fmt::format("\nints4 size: {}\ncontents: ", ints4.size())
        << ints4 << fmt::format("\n\nSize if ints5 is now: {}\n", ints5.size());

    if (ints5) {
        std::cout << "\n\nints5 contains elements\n";
    }
    else {
        std::cout << "\n\nints5 is empty\n";
    }

    std::cout << "\nints4: " << ints4;
    std::cout << "\npreincrementing ints4: " << ++ints4;

    std::cout << "\n\npostincrementing ints4: " << ints4++ << "\n";
    std::cout << "\nints4 now contains: " << ints4 << "\n";

    std::cout << "\nAdd 7 to every ints4 element: " << (ints4 += 7) << "\n";

    return 0;
}