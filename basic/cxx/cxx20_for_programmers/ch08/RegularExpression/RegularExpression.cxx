#include <fmt/format.h> 
#include <iostream>
#include <regex>

int main() {
    std::regex r1{"02215"};
    std::cout << "Matching against: 02215\n"
        << fmt::format("02215: {}; 51220: {}\n\n",
            std::regex_match("02215", r1), std::regex_match("51220", r1));

    std::regex r2{R"(\d{5})"};
    std::cout << R"(Matching against: \d{5})" << "\n"
        << fmt::format("02215: {}; 9876: {}\n\n",
            std::regex_match("02215", r2),
            std::regex_match("9876", r2));

    std::regex r3{"[A-Z][a-z]*"};
    std::cout << "Matching against: [A-Z][a-z]*\n"
        << fmt::format("Angel: {}; tina: {}\n\n",
            std::regex_match("Angel", r3), std::regex_match("tina", r3));

    std::regex r4{"[^a-z]"};
    std::cout << "Matching against: [^a-z]\n"
        << fmt::format("A: {}; a: {}\n\n",
            std::regex_match("A", r4), std::regex_match("a", r4));

    std::regex r5{"[*+$]"};
    std::cout << "Matching against: [*+$]\n"
        << fmt::format("*: {}; !: {}\n\n",
            std::regex_match("*", r5), std::regex_match("!", r5));

    std::regex r6{"[A-Z][a-z]+"};
    std::cout << "Matching against: [A-Z][a-z]+\n"
        << fmt::format("Angel: {}; T: {}\n\n",
            std::regex_match("Angel", r6), std::regex_match("T", r6));

    std::regex r7{"labell?ed"};
    std::cout << "Matching against: labell?ed\n"
        << fmt::format("labelled: {}; labeled: {}; labellled: {}\n\n",
            std::regex_match("labelled", r7),
            std::regex_match("labeled", r7),
            std::regex_match("labellled", r7));

    std::regex r8{R"(\d{3,})"};
    std::cout << R"(Matching against: \d{3,})" << "\n"
        << fmt::format("123: {}; 1234567890: {}; 12: {}\n\n",
            std::regex_match("123", r8),
            std::regex_match("1234567890", r8),
            std::regex_match("12", r8));

    std::regex r9{R"(\d{3,6})"};
    std::cout << R"(Matching against: \d{3,6})" << "\n"
        << fmt::format("123: {}; 123456: {}; 1234567: {}; 12: {}\n",
            std::regex_match("123", r9), std::regex_match("123456", r9),
            std::regex_match("1234567", r9), std::regex_match("12", r9));

    return 0;
}