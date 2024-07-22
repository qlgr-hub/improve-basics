#include <iostream>
#include <sstream>
#include <string>
#include <fmt/format.h>

int main() {
    std::ostringstream output;

    const std::string string1{"Output of several data types "};
    const std::string string2{"to an ostringstream object:"};
    const std::string string3{"\ndouble: "};
    const std::string string4{"\n   int: "};

    constexpr double d{123.4567};
    constexpr int i{22};

    output << string1 << string2 << string3 << d << string4 << i;

    std::cout << "output contains:\n" << output.str();

    output << "\nmore characters added";
    std::cout << "\n\noutput now contains:\n" << output.str() << '\n';

    const std::string inputString{"Atonia test 123 4.7 A"};
    std::istringstream input{inputString};
    std::string s1;
    std::string s2;
    int i1;
    double d1;
    char c;

    input >> s1 >> s2 >> i1 >> d1 >> c;

    std::cout << "Items extracted from the istringstream object:\n"
        << fmt::format("{}\n{}\n{}\n{}\n{}\n", s1, s2, i1, d1, c);

    if (long value; input >> value) {
        std::cout << fmt::format("\nlong value is: {}\n", value);
    }
    else {
        std::cout << fmt::format("\ninput is empty\n");
    }

    return 0;
}