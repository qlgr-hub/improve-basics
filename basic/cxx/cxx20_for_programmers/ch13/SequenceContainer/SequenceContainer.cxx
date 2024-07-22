#include <algorithm>
#include <bits/ranges_algobase.h>
#include <cstddef>
#include <deque>
#include <fmt/format.h>
#include <iostream>
#include <iterator>
#include <list>
#include <ranges>
#include <vector>

void showResult(int value, size_t size, size_t capacity) {
    std::cout << fmt::format("appended: {}; size: {}; capacity: {}\n",
        value, size, capacity);
}


template <typename T>
void printList(const std::list<T>& items) {
    if (items.empty()) {
        std::cout << "List is empty\n";
    }
    else {
        std::ostream_iterator<T> output{std::cout, " "};
        std::ranges::copy(items, output);
    }
}

int main() {
    std::vector<int> integers{};
    std::cout << "Size of integers: " << integers.size()
        << "\nCapacity of integers: " << integers.capacity() << "\n\n";

    for (int i : std::views::iota(1, 11)) {
        integers.push_back(i);
        showResult(i, integers.size(), integers.capacity());
    }

    std::cout << "\nOutput integers using iterators: ";
    for (auto constIterator{integers.cbegin()};
        constIterator != integers.cend(); ++constIterator) {
        std::cout << *constIterator << ' ';
    }
    std::cout << "\n";

    std::cout << "\nOutput integers in reverse using iterators: ";
    for (auto reverseIterator{integers.crbegin()};
        reverseIterator != integers.crend(); ++reverseIterator) {
        std::cout << *reverseIterator << ' ';
    }
    std::cout << "\n";

    std::vector values{1, 2, 3, 4, 5};
    std::vector<int> integers1{values.cbegin(), values.cend()};
    std::ostream_iterator<int> output{std::cout, " "};
    std::cout << "integers1 contains: ";
    std::copy(integers1.cbegin(), integers1.cend(), output);
    std::cout << "\n";

    std::cout << fmt::format("\nfront: {}\nback: {}\n\n",
        integers1.front(), integers1.back());

    integers1[0] = 7;
    integers1.at(2) = 10;
    integers1.insert(integers1.cbegin() + 1, 22);

    std::cout << "Contents of vector integers1 after changes: ";
    std::ranges::copy(integers1, output);
    std::cout << "\n";

    integers1.erase(integers1.cbegin());
    std::cout << "\n\nintegers1 after erasing first element: ";
    std::ranges::copy(integers1, output);
    std::cout << "\n";

    integers1.erase(integers1.cbegin(), integers1.cend());
    std::cout << fmt::format("\nErased all elements: integers1 {} empty\n",
        integers1.empty() ? "is" : "is not");

    integers1.insert(integers1.cbegin(), values.cbegin(), values.cend());
    std::cout << "\nContents of vector integers1 before clear: ";
    std::ranges::copy(integers1, output);
    std::cout << "\n";

    integers1.clear();
    std::cout << fmt::format("\nAfter clear, integers1 {} empty\n",
        integers1.empty() ? "is" : "is not");

    std::cout << "\n\nList demos: \n";
    std::list<int> values_l;
    values_l.push_front(1);
    values_l.push_front(2);
    values_l.push_back(4);
    values_l.push_back(3);
    std::cout << "values_l contains: ";
    printList(values_l);
    std::cout << "\n";

    values_l.sort();
    std::cout << "values_l after sorting contains: ";
    printList(values_l);
    std::cout << "\n";

    std::vector ints{2, 6, 4, 8};
    std::list<int> otherValues{};
    otherValues.insert(otherValues.cbegin(), ints.cbegin(), ints.cend());
    std::cout << "After insert, otherValues contains: ";
    printList(otherValues);
    std::cout << "\n";

    values_l.splice(values_l.cend(), otherValues);
    std::cout << "After splice, values_l contains: ";
    printList(values_l);
    std::cout << "\n";

    values_l.sort();
    std::cout << "After sort, values_l contains: ";
    printList(values_l);
    std::cout << "\n";

    otherValues.insert(otherValues.cbegin(), ints.cbegin(), ints.cend());
    otherValues.sort();
    std::cout << "After insert and sort, otherValues contains: ";
    printList(otherValues);
    std::cout << "\n";

    values_l.merge(otherValues);
    std::cout << "After merge:\n values_l contains: ";
    printList(values_l);
    std::cout << "\n";
    std::cout << "otherValues contains: ";
    printList(otherValues);
    std::cout << "\n";

    values_l.pop_front();
    values_l.pop_back();
    std::cout << "After pop_front and pop_back:\n values contains: ";
    printList(values_l);
    std::cout << "\n";

    values_l.unique();
    std::cout << "After unique, values contains: ";
    printList(values_l);
    std::cout << "\n";

    values_l.swap(otherValues);
    std::cout << "After swap:\n values contains: ";
    printList(values_l);
    std::cout << "\n";
    std::cout << "otherValues contains: ";
    printList(otherValues);
    std::cout << "\n";

    values_l.assign(otherValues.cbegin(), otherValues.cend());
    std::cout << "After assign, values_l contains: ";
    printList(values_l);
    std::cout << "\n";

    values_l.merge(otherValues);
    std::cout << "After merge, values_l contains: ";
    printList(values_l);
    std::cout << "\n";

    values_l.remove(4);
    std::cout << "After remove(4), values_l contains: ";
    printList(values_l);
    std::cout << "\n";

    std::cout << "\n\ndeque demos: \n";
    std::deque<double> values_d;
    std::ostream_iterator<double> output_d{std::cout, " "};

    values_d.push_front(2.2);
    values_d.push_front(3.5);
    values_d.push_back(1.1);
    std::cout << "values_d contains: ";

    for (size_t i{0}; i < values_d.size(); ++i) {
        std::cout << values_d[i] << ' ';
    }

    values_d.pop_front();
    std::cout << "\nAfter pop_front, values_d contains: ";
    std::ranges::copy(values_d, output_d);

    values_d[1] = 5.4;
    std::cout << "\nAfter values_d[1] = 5.4, values_d contains: ";
    std::ranges::copy(values_d, output_d);
    std::cout << "\n";

    return 0;
}