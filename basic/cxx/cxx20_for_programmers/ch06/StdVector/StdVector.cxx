#include <iostream>
#include <vector>
#include <stdexcept>

void outputVector(const std::vector<int>& items);
void inputVector(std::vector<int>& items);

int main() {
    std::vector<int> integer1(7);
    std::vector<int> integer2(10);

    std::cout << "Size of vector integer1 is " << integer1.size()
        << "\nvector after initialization:";
    outputVector(integer1);

    std::cout << "Size of vector integer2 is " << integer2.size()
        << "\nvector after initialization:";
    outputVector(integer2);

    std::cout << "\nEnter 17 integers:\n";
    inputVector(integer1);
    inputVector(integer2);

    std::cout << "\nAfter input, the vectors contain:\n"
        << "integers1:";
    outputVector(integer1);
    std::cout << "integers2:";
    outputVector(integer2);

    std::cout << "\nEvaluating: integers1 != integers2\n";
    if (integer1 != integer2) {
        std::cout << "integers1 and integers2 are not equal\n";
    }

    std::vector<int> integer3{integer1};

    std::cout << "Size of vector integer3 is " << integer3.size()
        << "\nvector after initialization:";
    outputVector(integer3);

    integer1 = integer2;

    std::cout << "integers1:";
    outputVector(integer1);
    std::cout << "integers2:";
    outputVector(integer2);

    std::cout << "\nEvaluating: integers1 == integers2\n";
    if (integer1 == integer2) {
        std::cout << "integers1 and integers2 are equal\n";
    }

    std::cout << "\nintegers1.at(5) is " << integer1.at(5);

    std::cout << "\n\nAssigning 1000 to integers1.at(5)\n";
    integer1.at(5) = 1000;
    std::cout << "integers1:";
    outputVector(integer1);

    try {
        std::cout << "\nAttempt to display integers1.at(15)\n";
        std::cout << integer1.at(15) << '\n';
    }
    catch (const std::out_of_range& ex) {
        std::cerr << "An exception occurred: " << ex.what() << '\n';
    }

    std::cout << "\nCurrent integers3 size is: " << integer3.size();
    integer3.push_back(1000);
    std::cout << "\nNew integers3 size is: " << integer3.size()
        << "\nintegers3 now contains: ";
    outputVector(integer3);

    return 0;
}

void outputVector(const std::vector<int>& items) {
    for (const int& item : items) {
        std::cout << item << " ";
    }

    std::cout << "\n";
}

void inputVector(std::vector<int>& items) {
    for (int& item : items) {
        std::cin >> item;
    }
}
