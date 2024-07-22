#include <algorithm>
#include <iostream>
#include <iterator>
#include <map>
#include <ranges>
#include <string>
#include <vector>

int main() {
    std::ostream_iterator<int> output{std::cout, " "};
    auto isEven{[](int x){return x % 2 == 0;}};
    auto evens{std::views::iota(0) | std::views::filter(isEven)};

    std::cout << "First five even ints: ";
    std::ranges::copy(evens | std::views::take(5), output);
    std::cout << "\n";

    std::cout << "\nEven ints less than 12: ";
    auto lessThan12{evens | std::views::take_while([](int x) {return x < 12;})};
    std::ranges::copy(lessThan12, output);
    std::cout << "\n";

    std::cout << "\nEven ints less than 12 reversed: ";
    std::ranges::copy(lessThan12 | std::views::reverse, output);
    std::cout << "\n";

    std::cout << "\nSquares of even ints less than 12 reversed: ";
    std::ranges::copy(
            lessThan12 
                | std::views::reverse
                | std::views::transform([](int x) {return x * x;}), 
            output);
    std::cout << "\n";

    std::cout << "\nSkip 1000 even ints, then take five: ";
    std::ranges::copy(
            evens | std::views::drop(1000) | std::views::take(5), 
            output);
    std::cout << "\n";

    std::cout << "\nFirst five even ints greater than 1000: ";
    std::ranges::copy(
            evens 
                | std::views::drop_while([](int x) {return x <= 1000;}) 
                | std::views::take(5), 
            output);
    std::cout << "\n";

    using namespace std::string_literals;

    std::map<std::string, int> romanNumberals{
        {"Ⅰ"s, 1}, {"Ⅱ"s, 2}, {"Ⅲ"s, 3}, {"Ⅳ"s, 4}, {"Ⅴ"s, 5},
    };
    auto displayPair{[](const auto& p) {std::cout << p.first << " = " << p.second << "\n";}};
    std::cout << "\n\nromanNumberals:\n";
    std::ranges::for_each(romanNumberals, displayPair);

    std::ostream_iterator<std::string> stringOutput{std::cout, " "};
    std::cout << "\nKeys in romanNumberals: ";
    std::ranges::copy(romanNumberals | std::views::keys, stringOutput);

    std::cout << "\nValues in romanNumberals: ";
    std::ranges::copy(romanNumberals | std::views::values, output);
    std::cout << "\n";

    std::cout << "\nKeys in romanNumberals via std::views::elements: ";
    std::ranges::copy(romanNumberals | std::views::elements<0>, stringOutput);

    std::cout << "\nValues in romanNumberals via std::views::elements: ";
    std::ranges::copy(romanNumberals | std::views::elements<1>, output);
    std::cout << "\n";

    return 0;
}