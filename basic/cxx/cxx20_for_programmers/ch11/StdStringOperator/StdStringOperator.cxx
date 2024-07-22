#include <fmt/format.h>
#include <iostream>
#include <stdexcept>
#include <string>
#include <string_view>

int main() {
    std::string s1{"happy"};
    std::string s2{" birthday"};
    std::string s3;
    std::string_view v{"hello"};

    std::cout << "s1: \"" << s1 << "\"; s2: \"" << s2
        << "\"; s3: \"" << s3 << "\"; v: \"" << v << "\"\n\n";

    std::cout << "The results of comparing s2 and s1:\n"
        << fmt::format("s2 == s1: {}\n", s2 == s1)
        << fmt::format("s2 != s1: {}\n", s2 != s1)
        << fmt::format("s2 > s1: {}\n", s2 > s1)
        << fmt::format("s2 < s1: {}\n", s2 < s1)
        << fmt::format("s2 >= s1: {}\n", s2 >= s1)
        << fmt::format("s2 <= s1: {}\n", s2 <= s1);

    std::cout << "Testing s3.empty():\n";
    if (s3.empty()) {
        std::cout << "s3 is empty; assigning s1 to s3;\n";
        s3 = s1;
        std::cout << fmt::format("s3 is \"{}\"\n\n", s3);
    }

    s1 += s2;
    std::cout << fmt::format("s1 += s2 yields s1 = {}\n\n", s1);

    s1 += " to you";
    std::cout << fmt::format("s1 += \" to you\" yields s1 = {}\n\n", s1);

    using namespace std::string_literals;
    s1 += ", have a great day!"s;
    std::cout << fmt::format("s1 += \", have a great day!\"s yields s1 = {}\n\n", s1);

    std::cout << fmt::format("{} {}\n{}\n\n",
        "The substring of s1 starting at location 0 for",
        " 14 characters, s1.substr(0, 14), is:", s1.substr(0, 14));

    std::cout << fmt::format("{} {}\n{}\n\n",
        "The substring of s1 starting at",
        " location 15, s1.substr(15), is:", s1.substr(15));

    std::string s4{s1};
    std::cout << fmt::format("s4 = {}\n\n", s4);

    std::cout << "assigning s4 to s4\n";
    s4 = s4;
    std::cout << fmt::format("s4 = {}\n\n", s4);

    std::cout << "initializing s5 with string_view v\n";
    std::string s5{v};
    std::cout << fmt::format("s5 is {}\n\n", s5);

    s1[0] = 'H';
    s1[6] = 'B';
    std::cout << fmt::format("{}:\n{}\n\n",
        "after s1[0] = 'H' and s1[6] = 'B', s1 is", s1);

    try {
        std::cout << "Attempt to assign 'd' to s1.at(100) yields:\n";
        s1.at(100) = 'd';
    }
    catch (const std::out_of_range& ex) {
        std::cerr << fmt::format("An exception occurred: {}\n", ex.what());
    }
    
    return 0;
}