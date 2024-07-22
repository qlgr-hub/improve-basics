#include <fmt/format.h> 
#include <iostream>
#include <string> 


// std::string
// assign
// = +=
// append
// > < == !=
// compare
// substr
// swap
// capacity max_size size empty
// find 
// rfind
// find_first_of
// find_last_of
// find_first_not_of
// reserve  => C++20 以后这个不会减少空间了
// std::string::npos
// erase
// replace
// insert
// stoi
// stol
// stoul
// stoll
// stoull
// stof
// stod
// stold

void displayResult(const std::string& s, int result) {
    if (result == 0) {
        std::cout << fmt::format("{} == 0\n", s);
    }
    else if (result > 0) {
        std::cout << fmt::format("{} > 0\n", s);
    }
    else { // result < 0
        std::cout << fmt::format("{} < 0\n", s);
    }
}

void printStatistics(const std::string& s) {
    std::cout << fmt::format(
        "capacity: {}\nmax size: {}\nsize: {}\nempty: {}",
        s.capacity(), s.max_size(), s.size(), s.empty());
}

int main() {
    std::string s1{"cat"};
    std::string s2;
    std::string s3;

    s2 = s1;      
    s3.assign(s1);
    std::cout << fmt::format("s1: {}\ns2: {}\ns3: {}\n\n", s1, s2, s3);

    s2.at(0) = 'r';
    s3.at(2) = 'r';
    std::cout << fmt::format("After changes:\ns2: {}\ns3: {}", s2, s3);

    std::cout << "\n\nAfter concatenations:\n";
    std::string s4{s1 + "apult"};
    s1.append("acomb");
    s3 += "pet";
    std::cout << fmt::format("s1: {}\ns3: {}\ns4: {}\n", s1, s3, s4);

    std::string s5;
    s5.append(s1, 4, s1.size() - 4);
    std::cout << fmt::format("s5: {}\n", s5);

    const std::string s11{"Testing the comparison functions."};
    const std::string s12{"Hello"};
    const std::string s13{"stinger"};
    const std::string s14{s12};

    std::cout << fmt::format("\ns1: {}\ns2: {}\ns3: {}\ns4: {}\n\n",
        s11, s12, s13, s14);

    if (s11 > s14) {
        std::cout << "s1 > s4\n";
    }

    displayResult("s1.compare(s2)", s11.compare(s12));

    displayResult("s1.compare(2, 5, s3, 0, 5)",
        s11.compare(2, 5, s13, 0, 5));

    displayResult("s4.compare(0, s2.size(), s2)",
        s14.compare(0, s12.size(), s12));

    displayResult("s2.compare(0, 3, s4)", s12.compare(0, 3, s14));

    const std::string ss{"airplane"};
    std::cout << ss.substr(3, 4) << '\n';

    std::string s111{"one"};
    std::string s112{"two"};

    std::cout << fmt::format("Before swap:\ns1: {}; s2: {}\n\n", s111, s112);
    s111.swap(s112);
    std::cout << fmt::format("After swap:\ns1: {}; s2: {}\n", s111, s112);

    std::string string1;
    std::cout << "\nStatistics before input:\n";
    printStatistics(string1);

    std::cout << "\n\nEnter a string: ";
    std::cin >> string1;
    std::cout << fmt::format("The string entered was: {}\n", string1);
    std::cout << "Statistics after input:\n";
    printStatistics(string1);

    std::cout << "\n\nEnter a string: ";
    std::cin >> string1;
    std::cout << fmt::format("The string entered was: {}\n", string1);
    std::cout << "Statistics after input:\n";
    printStatistics(string1);

    string1 += "1234567890abcdefghijklmnopqrstuvwxyz1234567890";
    std::cout << fmt::format("\n\nstring1 is now: {}\n", string1);
    std::cout << "Statistics after concatenation:\n";
    printStatistics(string1);

    string1.resize(string1.size() + 10);
    std::cout << "\n\nStatistics after resizing to add 10 characters:\n";
    printStatistics(string1);
    std::cout << '\n';

    const std::string s{"noon is 12pm; midnight is not"};
    std::cout << "Original string: " << s;

    std::cout << fmt::format("\ns.find(\"is\"): {}\ns.rfind(\"is\"): {}",
        s.find("is"), s.rfind("is"));

    auto location{s.find_first_of("misop")};
    std::cout << fmt::format("\ns.find_first_of(\"misop\") found {} at {}",
        s.at(location), location);

    location = s.find_last_of("misop");
    std::cout << fmt::format("\ns.find_last_of(\"misop\") found {} at {}",
        s.at(location), location);

    location = s.find_first_not_of("noi spm");
    std::cout << fmt::format(
        "\ns.find_first_not_of(\"noi spm\") found {} at {}",
        s.at(location), location);

    location = s.find_first_not_of("12noi spm");
    std::cout << fmt::format(
        "\ns.find_first_not_of(\"12noi spm\") found {} at {}",
        s.at(location), location);

    location = s.find_first_not_of("noon is 12pm; midnight is not");

    if (location == std::string::npos) {
        std::cout << fmt::format("\n{}: not found\n",
            "s.find_first_not_of(\"noon is 12pm; midnight is not\")");
    }

    std::string string11{"The values in any left subtree"
        "\nare less than the value in the"
        "\nparent node and the values in"
        "\nany right subtree are greater"
        "\nthan the value in the parent node"};

    std::cout << fmt::format("Original string:\n{}\n\n", string11);

    string11.erase(62);
    std::cout << fmt::format("string1 after erase:\n{}\n\n", string11);

    size_t position{string11.find(" ")};

    while (position != std::string::npos) {
        string11.replace(position, 1, ".");
        position = string11.find(" ", position + 1);
    }

    std::cout << fmt::format("After first replacement:\n{}\n\n", string11);

    position = string11.find(".");

    while (position != std::string::npos) {
        string11.replace(position, 2, "xxxxx;;yyy", 5, 2);
        position = string11.find(".", position + 2);
    }

    std::cout << fmt::format("After second replacement:\n{}\n", string11);

    std::string s1_1{"beginning end"};
    std::string s1_2{"12345678"};

    std::cout << fmt::format("Initial strings:\ns1: {}\ns2: {}\n\n",
        s1_1, s1_2);

    s1_1.insert(10, "middle ");
    s1_2.insert(3, "xx", 0, std::string::npos);

    std::cout << fmt::format("Strings after insert:\ns1: {}\ns2: {}\n",
        s1_1, s1_2);

    return 0;
}