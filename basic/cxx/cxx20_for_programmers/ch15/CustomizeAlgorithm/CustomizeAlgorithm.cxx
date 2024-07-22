#include <algorithm>
#include <array>
#include <concepts>
#include <iostream>
#include <iterator>
#include <list>
#include <ranges>
#include <vector>

template<typename T>
concept NumericInputRange = std::ranges::input_range<T> &&
    (std::integral<typename T::value_type> || std::floating_point<typename T::value_type>);

auto average(NumericInputRange auto const& range) {
    long double total{0};

    for (auto i{range.begin()}; i != range.end(); ++i) {
        total += *i;
    }

    return total / std::ranges::distance(range);
}

int main() {
    std::ostream_iterator<int> outputInt{std::cout, " "};
    const std::array ints{1, 2, 3, 4, 5};
    std::cout << "array ints: ";
    std::ranges::copy(ints, outputInt);
    std::cout << "\naverage of ints: " << average(ints) << "\n";

    std::ostream_iterator<double> outputDouble{std::cout, " "};
    const std::vector doubles{10.1, 20.2, 35.3};
    std::cout << "\nvector doubles: ";
    std::ranges::copy(doubles, outputDouble);
    std::cout << "\naverage of doubles: " << average(doubles) << "\n";

    std::ostream_iterator<long double> outputLongDouble{std::cout, " "};
    const std::list longDoubles{10.1L, 20.2L, 35.3L};
    std::cout << "\nlist longDoubles: ";
    std::ranges::copy(longDoubles, outputLongDouble);
    std::cout << "\naverage of longDoubles: " << average(longDoubles) << "\n";

    return 0;
}