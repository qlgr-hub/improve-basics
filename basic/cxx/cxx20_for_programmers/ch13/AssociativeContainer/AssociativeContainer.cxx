#include <algorithm>
#include <fmt/format.h>
#include <functional>
#include <iostream>
#include <iterator>
#include <map>
#include <ranges>
#include <set>
#include <utility>
#include <vector>

int main() {
    std::multiset<int, std::less<int>> ints{};
    std::cout << fmt::format("15s in ints: {}\n", ints.count(15));

    std::cout << "Inserting two 15s into ints\n";
    ints.insert(15);
    ints.insert(15);
    std::cout << fmt::format("15s in ints: {}\n\n", ints.count(15));

    for (int i : {15, 20}) {
        if (auto result{ints.find(i)}; result != ints.end()) {
            std::cout << fmt::format("Found {} in ints\n", i);
        }
        else {
            std::cout << fmt::format("Did not find {} in ints\n", i);
        }
    }

    for (int i : {15, 20}) {
        if (ints.contains(i)) {
            std::cout << fmt::format("Found {} in ints\n", i);
        }
        else {
            std::cout << fmt::format("Did not find {} in ints\n", i);
        }
    }

    const std::vector values{7, 22, 9, 1, 18, 30, 100, 22, 85, 13};
    ints.insert(values.cbegin(), values.cend());
    std::cout << "\nAfter insert, ints contains:\n";
    std::ranges::copy(ints, std::ostream_iterator<int>{std::cout, " "});
    std::cout << "\n";

    std::cout << fmt::format("\n\nlower_bound(22): {}\nupper_bound(22): {}\n\n",
        *ints.lower_bound(22), *ints.upper_bound(22));

    auto p{ints.equal_range(22)};
    std::cout << fmt::format("\n\nlower_bound(22): {}\nupper_bound(22): {}\n\n",
        *p.first, *p.second);

    
    std::cout << "\n\nset demos: \n";
    std::set doubles{2.1, 4.2, 9.5, 2.1, 3.7};
    std::cout << "doubles contains: ";
    std::ranges::copy(doubles, std::ostream_iterator<double>{std::cout, " "});
    std::cout << "\n";

    auto p1{doubles.insert(13.8)};
    std::cout << fmt::format("\n{} {} inserted\n", *(p1.first), (p1.second ? "was" : "was not"));
    std::cout << "doubles contains: ";
    std::ranges::copy(doubles, std::ostream_iterator<double>{std::cout, " "});
    std::cout << "\n";

    auto p2{doubles.insert(9.5)};
    std::cout << fmt::format("\n{} {} inserted\n", *(p2.first), (p2.second ? "was" : "was not"));
    std::cout << "doubles contains: ";
    std::ranges::copy(doubles, std::ostream_iterator<double>{std::cout, " "});
    std::cout << "\n";

    std::cout << "\n\nmultimap demos: \n";
    std::multimap<int, double> pairs{};
    std::cout << fmt::format("Number of 15 keys in pairs: {}\n", pairs.count(15));
    pairs.insert(std::make_pair(15, 99.3));
    pairs.insert(std::make_pair(15, 2.7));
    std::cout << fmt::format("Number of 15 keys in pairs: {}\n\n", pairs.count(15));
    pairs.insert({30, 111.11});
    pairs.insert({10, 22.22});
    pairs.insert({25, 33.333});
    pairs.insert({20, 9.345});
    pairs.insert({5, 77.54});
    std::cout << "Multimap pairs contains:\nKey\tValue\n";
    for (const auto& mapItem : pairs) {
        std::cout << fmt::format("{}\t{}\n", mapItem.first, mapItem.second);
    }
    std::multimap<int, double> pairs1{
        {10, 22.22}, {20, 9.345}, {5, 77.54}};
    std::cout << "Multimap pairs1 contains:\nKey\tValue\n";
    for (const auto& mapItem : pairs1) {
        std::cout << fmt::format("{}\t{}\n", mapItem.first, mapItem.second);
    }

    std::cout << "\n\nmap demos: \n";
    std::map<int, double> pairs2{{15, 2.7}, {30, 111.11}, {5, 1010.1},
        {10, 22.22}, {25, 33.333}, {5, 77.54}, {20, 9.345}, {15, 99.3}};
    
    std::cout << "pairs2 conrains:\nKey\tValue\n";
    for (const auto& mapItem : pairs2) {
        std::cout << fmt::format("{}\t{}\n", mapItem.first, mapItem.second);
    }

    pairs2[25] = 9999.99;
    pairs2[40] = 8765.43;
    std::cout << "\nAfter updates, pairs2 conrains:\nKey\tValue\n";
    for (const auto& mapItem : pairs2) {
        std::cout << fmt::format("{}\t{}\n", mapItem.first, mapItem.second);
    }

    return 0;
}