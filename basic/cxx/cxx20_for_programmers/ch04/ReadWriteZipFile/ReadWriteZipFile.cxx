#include <iostream>
#include <string>
#include "zip_file.hpp"

int main() {
    std::cout << "Enter a ZIP file name: ";
    std::string zipFileName;
    std::getline(std::cin, zipFileName);

    std::string content{
        "This chapter introduces all but one of the remaining control "
        "statments--the for, do...while, switch, break and continue "
        "statments. We explore the essentials of counter-controlled "
        "interation. We use compound-interest calculations to begin "
        "investigating the issues of processing monetary amounts. First, "
        "we discuss the representational errors associated with "
        "floating-point types. We use a switch statement to count the "
        "number of A, B, C, D and F grade equivalents  in a set of "
        "numeric grades. We show C++17's enhancements that allow you to "
        "initialize one or more variables of the same type in the "
        "headers of if and switch statements."};

    std::cout << "\ncontent.length(): " << content.length() << "\n";

    miniz_cpp::zip_file output;
    output.writestr("intro.txt", content);
    output.save(zipFileName);

    miniz_cpp::zip_file input{zipFileName};
    std::cout << "\nZIP file's name: " << input.get_filename()
        << "\n\nZIP file's directory listing:\n";
    input.printdir();

    miniz_cpp::zip_info info{input.getinfo("intro.txt")};
    std::cout << "\nFile name: " << info.filename
        << "\nOriginal size: " << info.file_size
        << "\nCompressed size: " << info.compress_size;

    std::string extractedContent{input.read(info)};
    std::cout << "\n\nOriginal contents of intro.txt:\n"
        << extractedContent << "\n";

    return 0;
}