#include <fmt/format.h>
#include <array>
#include <iostream>
#include <iterator>
#include <algorithm>
#include <random>
#include <vector>


char nextLetter() {
    static char letter{'A'};
    return letter++;
}

int main() {
    std::array<char, 10> chars{};

    std::ranges::fill(chars, '5');
    std::cout << "chars after filling with 5s: ";
    std::ostream_iterator<char> output{std::cout, " "};
    std::ranges::copy(chars, output);
    std::cout << "\n";

    std::ranges::fill_n(chars.begin(), 5, 'A');
    std::cout << "chars after filling five elements with 'A's: ";
    std::ranges::copy(chars, output);
    std::cout << "\n";

    std::ranges::generate(chars, nextLetter);
    std::cout << "chars after generating letters A-J: ";
    std::ranges::copy(chars, output);
    std::cout << "\n";

    std::ranges::generate_n(chars.begin(), 5, nextLetter);
    std::cout << "chars after generating K-O into elements 0-4: ";
    std::ranges::copy(chars, output);
    std::cout << "\n";

    std::ranges::generate_n(chars.begin(), 3,
        [](){
            static char letter{'A'};
            return letter++;
        });
    std::cout << "chars after generating A-C into elements 0-2: ";
    std::ranges::copy(chars, output);
    std::cout << "\n";

    std::array a1{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    std::array a2{a1};
    std::array a3{1, 2, 3, 4, 1000, 6, 7, 8, 9, 10};
    std::ostream_iterator<int> output1{std::cout, " "};

    std::cout << "a1 contains: ";
    std::ranges::copy(a1, output1);
    std::cout << "\na2 contains: ";
    std::ranges::copy(a2, output1);
    std::cout << "\na3 contains: ";
    std::ranges::copy(a3, output1);
    std::cout << "\n";

    std::cout << fmt::format("\na1 is equal to a2: {}\n", std::ranges::equal(a1, a2));
    std::cout << fmt::format("a1 is equal to a3: {}\n", std::ranges::equal(a1, a3));

    auto location{std::ranges::mismatch(a1, a3)};
    std::cout << fmt::format("a1 and a3 mismatch at index {} ({} vs. {})\n",
        (location.in1 - a1.begin()), *location.in1, *location.in2);

    std::string s1{"HELLO"};
    std::string s2{"BYE BYE"};
    std::cout << fmt::format("\"{}\" < \"{}\": {}\n", s1, s2,
        std::ranges::lexicographical_compare(s1, s2));

    std::vector init{10, 2, 15, 4, 10, 6};
    std::vector v1{init};
    std::cout << "v1: ";
    std::ranges::copy(v1, output1);

    auto removed{std::ranges::remove(v1, 10)};
    v1.erase(removed.begin(), removed.end());
    std::cout << "\nv1 after removing 10s: ";
    std::ranges::copy(v1, output1);

    std::vector v2{init};
    std::cout << "\n\nv2: ";
    std::ranges::copy(v2, output1);

    std::vector<int> c1{};
    std::ranges::remove_copy(v2, std::back_inserter(c1), 10);
    std::cout << "\nc1 after coping v2 without 10s: ";
    std::ranges::copy(c1, output1);
    std::cout << "\n";

    std::vector v3{init};
    std::cout << "\nv3: ";
    std::ranges::copy(v3, output1);

    auto greaterThan9{[](auto x) {return x > 9;}};
    auto removed2{std::ranges::remove_if(v3, greaterThan9)};
    v3.erase(removed2.begin(), removed2.end());
    std::cout << "\nv3 after removing elements greater than 9: ";
    std::ranges::copy(v3, output1);
    std::cout << "\n";

    std::vector v4{init};
    std::cout << "\n\nv4: ";
    std::ranges::copy(v4, output1);

    std::vector<int> c2{};
    std::ranges::remove_copy_if(v2, std::back_inserter(c2), greaterThan9);
    std::cout << "\nc2 after coping v4 without elements greater than 9: ";
    std::ranges::copy(c2, output1);
    std::cout << "\n";

    std::array a11{10, 2, 15, 4, 10, 6};
    std::cout << "a11: ";
    std::ranges::copy(a11, output1);

    std::ranges::replace(a11, 10, 100);
    std::cout << "\na11 after replacing 10s with 100s: ";
    std::ranges::copy(a11, output1);

    std::array a12{10, 2, 15, 4, 10, 6};
    std::array<int, a12.size()> c11{};
    std::cout << "\n\na12: ";
    std::ranges::copy(a12, output1);

    std::ranges::replace_copy(a12, c11.begin(), 10, 100);
    std::cout << "\nc11 after replacing a12's 10s with 100s: ";
    std::ranges::copy(c11, output1);
    std::cout << "\n";

    std::array a13{10, 2, 15, 4, 10, 6};
    std::cout << "\na13: ";
    std::ranges::copy(a13, output1);

    std::ranges::replace_if(a13, greaterThan9, 100);
    std::cout << "\na13 after replacing values greater than 9 with 100s: ";
    std::ranges::copy(a13, output1);
    std::cout << "\n";

    std::array a14{10, 2, 15, 4, 10, 6};
    std::array<int, a14.size()> c12{};
    std::cout << "\n\na14: ";
    std::ranges::copy(a14, output1);

    std::ranges::replace_copy_if(a13, c12.begin(), greaterThan9, 100);
    std::cout << "\nc12 after replacing a14's values greater than 9 with 100s: ";
    std::ranges::copy(c12, output1);
    std::cout << "\n";

    std::array a21{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    std::cout << "\na21: ";
    std::ranges::copy(a21, output1);

    std::default_random_engine randomEngine{std::random_device{}()};
    std::ranges::shuffle(a21, randomEngine);
    std::cout << "\na21 shuffuled: ";
    std::ranges::copy(a21, output1);
    std::cout << "\n";

    std::array a22{100, 2, 8, 1, 50, 3, 8, 8, 9, 10};
    std::cout << "\na22: ";
    std::ranges::copy(a22, output1);
    auto result1{std::ranges::count(a22, 8)};
    std::cout << "\nCount of 8s in a22: " << result1 << "\n";
    auto result2{std::ranges::count_if(a22, [](auto x) {return x > 9;})};
    std::cout << "\nCount of a22 elements greater than 9: " << result2 << "\n";

    if (auto result{std::ranges::min_element(a22)}; result != a22.end()) {
        std::cout << "\na22 minimun element: " << *result << "\n";
    }

    if (auto result{std::ranges::max_element(a22)}; result != a22.end()) {
        std::cout << "\na22 maximum element: " << *result << "\n";
    }

    auto [min_, max_]{std::ranges::minmax_element(a22)};
    std::cout << "\na22 minimun and maximum element: " << *min_ << " and "  << *max_ << "\n";

    std::array<int, a11.size()> cubes{};
    std::ranges::transform(a11, cubes.begin(), [](auto x){return x * x * x;});
    std::cout << "\n\na11 values cubed: ";
    std::ranges::copy(cubes, output1);
    std::cout << "\n";

    std::array values{10, 2, 17, 5, 16, 8, 13, 11, 20, 7};
    std::cout << "\nvalues contains: ";
    std::ranges::copy(values, output1);
    std::cout << "\n";

    if (auto loc1{std::ranges::find(values, 16)}; loc1 != values.cend()) {
        std::cout << "\nFound 16 at index: " << (loc1 - values.cbegin()) << "\n";
    }
    else {
        std::cout << "\n16 not found\n";
    }

    if (auto loc2{std::ranges::find(values, 100)}; loc2 != values.cend()) {
        std::cout << "\nFound 100 at index: " << (loc2 - values.cbegin()) << "\n";
    }
    else {
        std::cout << "\n100 not found\n";
    }

    auto isGreaterThan10{[](auto x) {return x > 10;}};
    auto loc3{std::ranges::find_if(values, isGreaterThan10)};
    if (loc3 != values.cend()) {
        std::cout << "\nFirst value greater than 10: " << *loc3
            << "\nfound at index: " << (loc3 - values.cbegin()) << "\n";
    }
    else {
        std::cout << "\nNo values greater than 10 were found.\n";
    }

    std::ranges::sort(values);
    std::cout << "\nvalues after sort: ";
    std::ranges::copy(values, output1);
    std::cout << "\n";

    if (std::ranges::binary_search(values, 13)) {
        std::cout << "\n13 was found in values\n";
    }
    else {
        std::cout << "\n13 was not found in values\n";
    }

    if (std::ranges::binary_search(values, 100)) {
        std::cout << "\n100 was found in values\n";
    }
    else {
        std::cout << "\n100 was not found in values\n";
    }

    if (std::ranges::all_of(values, isGreaterThan10)) {
        std::cout << "\nAll values elements are greater than 10\n";
    }
    else {
        std::cout << "\nSome values elements are not greater than 10\n";
    }

    if (std::ranges::any_of(values, isGreaterThan10)) {
        std::cout << "\nSome values elements are greater than 10\n";
    }
    else {
        std::cout << "\nNo values elements are greater than 10\n";
    }

    if (std::ranges::none_of(values, isGreaterThan10)) {
        std::cout << "\nNo values elements are greater than 10\n";
    }
    else {
        std::cout << "\nSome values elements are greater than 10\n";
    }

    auto loc4{std::ranges::find_if_not(values, isGreaterThan10)};
    if (loc4 != values.cend()) {
        std::cout << "\nFirst value not greater than 10: " << *loc4
            << "\nfound at index: " << (loc4 - values.cbegin()) << "\n";
    }
    else {
        std::cout << "\nOnly values greater than 10 were found.\n";
    }

    std::array values1{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    std::cout << "\nvalues1 contains: ";
    std::ranges::copy(values1, output1);
    std::cout << "\n";

    std::swap(values1[0], values1[1]);
    std::cout << "\nafter std::swap of values1[0] and values1[1]: ";
    std::ranges::copy(values1, output1);
    std::cout << "\n";

    std::iter_swap(values1.begin(), values1.begin() + 1);
    std::cout << "\nafter std::iter_swap of values1[0] and values1[1]: ";
    std::ranges::copy(values1, output1);
    std::cout << "\n";

    std::cout << "\nBefore swap_ranges \nvalues1 contains: ";
    std::ranges::copy(values1, output1);
    std::array values2{10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    std::cout << "\nvalues2 contains: ";
    std::ranges::copy(values2, output1);
    std::cout << "\n";
    std::ranges::swap_ranges(values1, values2);
    std::cout << "\nAfter swap_ranges \nvalues1 contains: ";
    std::ranges::copy(values1, output1);
    std::cout << "\nvalues2 contains: ";
    std::ranges::copy(values2, output1);
    std::cout << "\n";

    std::ranges::swap_ranges(values1.begin(), values1.begin() + 5,
        values2.begin(), values2.begin() + 5);
    std::cout << "\nAfter swap_ranges for 5 elements \nvalues1 contains: ";
    std::ranges::copy(values1, output1);
    std::cout << "\nvalues2 contains: ";
    std::ranges::copy(values2, output1);
    std::cout << "\n";

    std::array a31{1, 3, 5, 7, 9};
    std::array a32{2, 4, 5, 7, 9};
    std::cout << "\narray1 contains: ";
    std::ranges::copy(a31, output1);
    std::cout << "\narray2 contains: ";
    std::ranges::copy(a32, output1);
    std::cout << "\n";

    std::array<int, a31.size()> results{};
    std::ranges::copy_backward(a31, results.end());
    std::cout << "\nAfter copy_backward results contains: ";
    std::ranges::copy(results, output1);
    std::cout << "\n";

    std::array<int, a31.size() + a32.size()> results2{};
    std::ranges::merge(a31, a32, results2.begin());
    std::cout << "\nAfter merge results2 contains: ";
    std::ranges::copy(results2, output1);
    std::cout << "\n";

    std::vector v5(results2.begin(), results2.end());
    auto [first, last]{std::ranges::unique(v5)};
    v5.erase(first, last);
    std::cout << "\nAfter unique v5 contains: ";
    std::ranges::copy(v5, output1);
    std::cout << "\n";

    std::cout << "\nAfter reverse a21 contains: ";
    std::ranges::reverse(a31);
    std::ranges::copy(a31, output1);
    std::cout << "\n";

    std::vector<int> v6{};
    std::cout << "\nAfter copy_if v6 contains: ";
    std::ranges::copy_if(a32, std::back_inserter(v6),
        [](auto x){return x % 2 == 0;});
    std::ranges::copy(v6, output1);
    std::cout << "\n";

    std::vector<int> v7{};
    std::cout << "\nAfter copy_n v7 contains: ";
    std::ranges::copy_n(a32.begin(), 3, std::back_inserter(v7));
    std::ranges::copy(v7, output1);
    std::cout << "\n";

    std::array a41{1, 3, 5, 7, 9, 1, 3, 5, 7, 9};
    std::cout << "\na41 contains: ";
    std::ranges::copy(a41, output1);
    std::cout << "\n";

    std::ranges::inplace_merge(a41, a41.begin() + 5);
    std::cout << "\nAfter inplace_merge, a41 contains: ";
    std::ranges::copy(a41, output1);
    std::cout << "\n";

    std::vector<int> results3{};
    std::ranges::unique_copy(a41, std::back_inserter(results3));
    std::cout << "\nAfter unique_copy, results3 contains: ";
    std::ranges::copy(results3, output1);
    std::cout << "\n";

    std::vector<int> results4{};
    std::ranges::reverse_copy(a41, std::back_inserter(results4));
    std::cout << "\nAfter reverse_copy, results4 contains: ";
    std::ranges::copy(results4, output1);
    std::cout << "\n";

    std::array a51{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    std::array a52{4, 5, 6, 7, 8};
    std::array a53{4, 5, 6, 11, 15};

    std::cout << "\na51 contains: ";
    std::ranges::copy(a51, output1);
    std::cout << "\na52 contains: ";
    std::ranges::copy(a52, output1);
    std::cout << "\na53 contains: ";
    std::ranges::copy(a53, output1);
    std::cout << "\n";

    std::cout << fmt::format("\na51 {} a52\n",
        std::ranges::includes(a51, a52) ? "includes" : "does not include");
    std::cout << fmt::format("a51 {} a53\n",
        std::ranges::includes(a51, a53) ? "includes" : "does not include");

    std::vector<int> difference{};
    std::ranges::set_difference(a51, a52, std::back_inserter(difference));
    std::cout << "\nset_difference of a51 and a52 is: ";
    std::ranges::copy(difference, output1);
    std::cout << "\n";

    std::vector<int> intersection{};
    std::ranges::set_intersection(a51, a52, std::back_inserter(intersection));
    std::cout << "\nset_intersection of a51 and a52 is: ";
    std::ranges::copy(intersection, output1);
    std::cout << "\n";

    std::vector<int> symmtricDifference{};
    std::ranges::set_symmetric_difference(a51, a53, std::back_inserter(symmtricDifference));
    std::cout << "\nset_symmetric_difference of a51 and a53 is: ";
    std::ranges::copy(symmtricDifference, output1);
    std::cout << "\n";

    std::vector<int> unionSet{};
    std::ranges::set_union(a51, a53, std::back_inserter(unionSet));
    std::cout << "\nset_union of a51 and a53 is: ";
    std::ranges::copy(unionSet, output1);
    std::cout << "\n";

    std::array values3{2, 2, 4, 4, 4, 6, 6, 6, 6, 8};
    std::cout << "\nvalues3 contains: ";
    std::ranges::copy(values3, output1);
    std::cout << "\n";

    auto lower{std::ranges::lower_bound(values3, 6)};
    std::cout << "\nLower bound of 6 is index: " << (lower - values3.begin()) << "\n";

    auto upper{std::ranges::upper_bound(values3, 6)};
    std::cout << "\nUpper bound of 6 is index: " << (upper - values3.begin()) << "\n";

    auto [first1, last1]{std::ranges::equal_range(values3, 6)};
    std::cout << "\nUsing equal_range:\n Lower bound of 6 is index: "
        << (first1 - values3.begin());
    std::cout << "\n Upper bound of 6 is index: "
        << (last1 - values3.begin()) << "\n";

    std::cout << "\n\nUse lower_bound to locate the first point "
        << "at which 3 can be inserted in order";
    lower = std::ranges::lower_bound(values3, 3);
    std::cout << "\n Lower bound of 3 is index: "
        << (lower - values3.begin()) << "\n";

    std::cout << "\n\nUse upper_bound to locate the last point "
        << "at which 7 can be inserted in order";
    upper = std::ranges::upper_bound(values3, 7);
    std::cout << "\n Upper bound of 7 is index: "
        << (upper - values3.begin()) << "\n";

    std::cout << "Minimum of 12 and 7 is: " << std::min(12, 7)
        << "\nMaximum of 12 and 7 is: " << std::max(12, 7)
        << "\nMinimum of 'G' and 'Z' is: '" << std::min('G', 'Z') << "'"
        << "\nMaximum of 'G' and 'Z' is: '" << std::max('G', 'Z') << "'"
        << "\nMinimum of 'z' and 'Z' is: '" << std::min('z', 'Z') << "'"
        << "\n";

    auto [smaller, larger]{std::minmax(12, 7)};
    std::cout << "\nMinimum of 12 and 7 is: " << smaller
        << "\nMaximum of 12 and 7 is: " << larger << "\n";

    std::array items{3, 100, 52, 77, 22, 31, 1, 98, 13, 40};
    std::cout << "\nitems contains: ";
    std::ranges::copy(items, output1);
    std::cout << "\n";

    auto [smaller1, larger1]{std::ranges::minmax(items)};
    std::cout << "Minimum value in items is: " << smaller1
        << "\nMaximum value in items is: " << larger1 << "\n";

    std::cout << "\nstd::gcd(75, 20): " << std::gcd(75, 20)
        << "\nstd::gcd(17, 13): " << std::gcd(17, 13) << "\n";

    std::cout << "\nstd::lcm(3, 5): " << std::lcm(3, 5)
        << "\nstd::lcm(12, 9): " << std::lcm(12, 9) << "\n";

    std::array<int, 5> ints{};
    std::iota(ints.begin(), ints.end(), 1);
    std::cout << "\nints contains: ";
    std::ranges::copy(ints, output1);
    std::cout << "\n";

    std::cout << "\nSum of ints: "
        << std::reduce(ints.begin(), ints.end())
        << "\nproduct of ints: "
        << std::reduce(ints.begin(), ints.end(), 1, std::multiplies{})
        << "\n";

    std::cout << "\nints contains: ";
    std::ranges::copy(ints, output1);
    std::cout << "\n\npartial_sum of ints using std::plus by default: ";
    std::partial_sum(ints.begin(), ints.end(), output1);
    std::cout << "\npartial_sum of ints using std::multiplies: ";
    std::partial_sum(ints.begin(), ints.end(), output1, std::multiplies{});
    std::cout << "\n";

    std::array heapArray{3, 100, 52, 77, 22, 31, 1, 98, 13, 40};
    std::cout << "heapArray before make_heap: ";
    std::ranges::copy(heapArray, output1);
    std::cout << "\n";
    std::ranges::make_heap(heapArray);
    std::cout << "heapArray after make_heap: ";
    std::ranges::copy(heapArray, output1);
    std::cout << "\n";
    std::ranges::sort_heap(heapArray);
    std::cout << "heapArray after sort_heap: ";
    std::ranges::copy(heapArray, output1);
    std::cout << "\n";

    auto push{
        [&](std::vector<int>& heap, int value) {
            std::cout << "\n\npushing " << value << " onto heap";
            heap.push_back(value);
            std::ranges::push_heap(heap);
            std::cout << "\nheap: ";
            std::ranges::copy(heap, output1);
        }
    };

    auto pop{
        [&](std::vector<int>& heap) {
            std::ranges::pop_heap(heap);
            std::cout << "\n\npopping highest priority item: " << heap.back();
            heap.pop_back();
            std::cout << "\nheap: ";
            std::ranges::copy(heap, output1);
        }
    };

    std::vector<int> heapVector{};
    for (auto value : {3, 52, 100}) {
        push(heapVector, value);
    }

    pop(heapVector);
    push(heapVector, 22);

    pop(heapVector);
    push(heapVector, 77);

    pop(heapVector);
    pop(heapVector);
    pop(heapVector);
    std::cout << "\n";

    return 0;
}