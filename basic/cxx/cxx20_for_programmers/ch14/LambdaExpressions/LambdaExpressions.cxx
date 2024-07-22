#include <algorithm>
#include <array>
#include <bits/ranges_algo.h>
#include <iostream>
#include <iterator>

void timesThree(int i) {
    std::cout << i * 3 << " ";
}

int main() {
    std::array values{1, 2, 3, 4};
    std::ostream_iterator<int> output{std::cout, " "};

    std::cout << "values contains: ";
    std::ranges::copy(values, output);
    std::cout << "\n";

    std::copy(values.cbegin(), values.cend(), output);
    std::cout << "\n";

    std::cout << "Display each element multiplied by two: ";
    std::ranges::for_each(values, [](auto i) {std::cout << i * 2 << " ";});
    std::cout << "\n";
    std::for_each(values.cbegin(), values.cend(), [](auto i) {std::cout << i * 2 << " ";});
    std::cout << "\n";

    std::cout << "Display each element multiplied by three: ";
    std::ranges::for_each(values, timesThree);
    std::cout << "\n";

    int sum{0};
    std::ranges::for_each(values, [&sum](auto i) {sum += i;});
    std::cout << "Sum of value's elements is: " << sum << "\n";
    return 0;
}