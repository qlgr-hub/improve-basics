#include <fmt/format.h> 
#include <iostream>
#include <string>
#include <string_view> 

// std::string_view
// remove_prefix
// remove_suffix

int main() {
    std::string s1{"red"};
    std::string s2{s1};
    std::string_view v1{s1};
    std::cout << fmt::format("s1: {}\ns2: {}\nv1: {}\n\n", s1, s2, v1);

    s1.at(0) = 'R';
    std::cout << fmt::format("s1: {}\ns2: {}\nv1: {}\n\n", s1, s2, v1);

    std::cout << fmt::format("s1 == v1: {}\ns2 == v1: {}\n\n",
        s1 == v1, s2 == v1);

    v1.remove_prefix(1);
    v1.remove_suffix(1);
    std::cout << fmt::format("s1: {}\nv1: {}\n\n", s1, v1);

    std::string_view v2{"C-string"};
    std::cout << "The characters in v2 are: ";
    for (char c : v2) {
        std::cout << c << " ";
    }

    std::cout << fmt::format("\n\nv2.size(): {}\n", v2.size());
    std::cout << fmt::format("v2.find('-'): {}\n", v2.find('-'));
    std::cout << fmt::format("v2.starts_with('C'): {}\n",
        v2.starts_with('C'));

    return 0;
}
