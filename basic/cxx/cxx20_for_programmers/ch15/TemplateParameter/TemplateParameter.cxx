#include <concepts>
#include <fmt/format.h>
#include <iostream>
#include <string>
#include <tuple>
#include <utility>

using Part = std::tuple<int, std::string, int, double>;

Part getInventory(int partNumber) {
    using namespace std::string_literals;

    switch (partNumber) {
    case 1:
        return {1, "Hammer"s, 32, 9.95};
    case 2:
        return {2, "Screwdriver"s, 106, 6.99};
    default:
        return {0, "INVALID PART", 0, 0.0};
    }
}

template <typename T>
auto sum(T item) {
    return item;
}

template <typename FirstItem, typename... RemainingItems>
auto sum(FirstItem first, RemainingItems... theRest) {
    return first + sum(theRest...);
}

template <typename FirstItem, typename... RemainingItems>
auto foldingSum(FirstItem first, RemainingItems... theRest) {
    return (first + ... + theRest);
}

template <typename... Items>
auto unaryLeftAdd(Items... items) {
    return (... + items);
}

template <typename... Items>
auto unaryRightAdd(Items... items) {
    return (items + ...);
}

template <typename... Items>
auto unaryLeftSubtract(Items... items) {
    return (... - items);
}

template <typename... Items>
auto unaryRightSubtract(Items... items) {
    return (items - ...);
}

template <typename... Items>
auto binaryLeftAdd(Items... items) {
    return (0 + ... + items);
}

template <typename... Items>
auto binaryRightAdd(Items... items) {
    return (items + ... + 0);
}

template <typename... Items>
auto binaryLeftSubtract(Items... items) {
    return (0 - ... - items);
}

template <typename... Items>
auto binaryRightSubtract(Items... items) {
    return (items - ... - 0);
}

template <typename... Items>
void printItems(Items... items) {
    ((std::cout << items << "\n"), ...);
}

template <typename T, typename... Us>
concept SameTypeElements = (std::same_as<T, Us> && ...);

template <typename FirstItem, typename... RemainingItems>
    requires SameTypeElements<FirstItem, RemainingItems...>
auto foldingSum1(FirstItem first, RemainingItems... theRest) {
    return (first + ... + theRest);
}

int main() {
    for (int i{1}; i <= 2; ++i) {
        auto [partNumber, partName, quantity, price] {getInventory(i)};

        std::cout << fmt::format("{}: {}, {}: {}, {}: {}, {}: {:.2f}\n",
            "Part number", partNumber, "Tool", partName, "Quantity", quantity, "Price", price);
    }

    std::cout << "\nAccessing a tuple's elements by index number:\n";
    auto hammer{getInventory(1)};
    std::cout << fmt::format("{}: {}, {}: {}, {}: {}, {}: {:.2f}\n",
            "Part number", std::get<0>(hammer), "Tool", std::get<1>(hammer),
            "Quantity", std::get<2>(hammer), "Price", std::get<3>(hammer));

    std::cout << fmt::format("A Part tuple has {} elements\n",
        static_cast<int>(std::tuple_size<Part>{}));

    using namespace std::string_literals;

    std::cout << "Recursive variadic function template sum: "
        << fmt::format("\n{}{}\n{}{}\n{}{}\n{}{}\n\n",
            "sum(1): ", sum(1), "sum(1, 2): ", sum(1, 2),
            "sum(1, 2, 3): ", sum(1, 2, 3),
            "sum(\"s\"s, \"u\"s, \"m\"s): ", sum("s"s, "u"s, "m"s));

    std::cout << "variadic function template foldingSum: "
        << fmt::format("\n{}{}\n{}{}\n{}{}\n{}{}\n\n",
            "sum(1): ", foldingSum(1), "sum(1, 2): ", foldingSum(1, 2),
            "sum(1, 2, 3): ", foldingSum(1, 2, 3),
            "sum(\"s\"s, \"u\"s, \"m\"s): ", foldingSum("s"s, "u"s, "m"s));

    std::cout << "Unary left and right fold with addition:"
        << fmt::format("\n{}{}\n{}{}\n\n",
            "unaryLeftAdd(1, 2, 3, 4): ", unaryLeftAdd(1, 2, 3, 4),
            "unaryRightAdd(1, 2, 3, 4): ", unaryRightAdd(1, 2, 3, 4));

    std::cout << "Unary left and right fold with subtraction:"
        << fmt::format("\n{}{}\n{}{}\n\n",
            "unaryLeftSubtract(1, 2, 3, 4): ", unaryLeftSubtract(1, 2, 3, 4),
            "unaryRightSubtract(1, 2, 3, 4): ", unaryRightSubtract(1, 2, 3, 4));

    std::cout << "Binary left and right fold with addition:"
        << fmt::format("\n{}{}\n{}{}\n{}{}\n{}{}\n\n",
            "binaryLeftAdd(): ", binaryLeftAdd(),
            "binaryLeftAdd(1, 2, 3, 4): ", binaryLeftAdd(1, 2, 3, 4),
            "binaryRightAdd(): ", binaryRightAdd(),
            "binaryRightAdd(1, 2, 3, 4): ", binaryRightAdd(1, 2, 3, 4));

    std::cout << "Binary left and right fold with subtraction:"
        << fmt::format("\n{}{}\n{}{}\n{}{}\n{}{}\n\n",
            "binaryLeftSubtract(): ", binaryLeftSubtract(),
            "binaryLeftSubtract(1, 2, 3, 4): ", binaryLeftSubtract(1, 2, 3, 4),
            "binaryRightSubtract(): ", binaryRightSubtract(),
            "binaryRightSubtract(1, 2, 3, 4): ", binaryRightSubtract(1, 2, 3, 4));

    std::cout << "printItems(1, 2.2, \"hello\"):\n";
    printItems(1, 2.2, "hello");

    foldingSum1(1, 2, 3);
    foldingSum1("s"s, "u"s, "m"s);
    // foldingSum1(1, 2.2, "hello"s);
    
    return 0;
}