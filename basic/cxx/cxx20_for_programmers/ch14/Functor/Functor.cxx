#include <iostream>
#include <array>
#include <iterator>
#include <numeric>
#include <ranges>
#include <algorithm>

int sumSquares(int total, int value) {
    return total + value * value;
}

class SumSquaresClass {
public:
    int operator()(int total, int value) {
        return total + value * value;
    }
};

int main() {
    std::array integers{1, 2, 3, 4};
    std::ostream_iterator<int> output{std::cout, " "};

    std::cout << "array integers contains: ";
    std::ranges::copy(integers, output);
    std::cout << "\n";

    int result{std::accumulate(integers.cbegin(), integers.cend(), 0, sumSquares)};
    std::cout << "\n\nSum of squares\n" << "via binary function sumSquares: " << result;

    result = std::accumulate(integers.cbegin(), integers.cend(), 0, SumSquaresClass{});
    std::cout << "\nvia a SumSquaresClass fuction object: " << result;

    result = std::accumulate(integers.cbegin(), integers.cend(), 0,
        [](auto total, auto value){return total + value * value;});
    std::cout << "\nvia lambda: " << result << "\n";

    return 0;
}