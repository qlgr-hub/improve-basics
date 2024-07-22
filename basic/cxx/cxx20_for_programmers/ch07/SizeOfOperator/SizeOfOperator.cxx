#include <fmt/format.h>
#include <iostream>

size_t getSize(double* ptr);

int main() {
    double numbers[20];

    std::cout << fmt::format("Number of bytes in numbers is {}\n",
        sizeof(numbers));

    std::cout << fmt::format("Number of bytes returned by getSize is {}\n",
        getSize(numbers));

    constexpr char c{};
    constexpr short s{};
    constexpr int i{};
    constexpr long l{};
    constexpr long long ll{};
    constexpr float f{};
    constexpr double d{};
    constexpr long double ld{};
    constexpr int array[20]{};
    const int* const ptr{array};

    std::cout << fmt::format("sizeof c = {}\tsizeof(char) = {}\n",
        sizeof c, sizeof(char));
    std::cout << fmt::format("sizeof s = {}\tsizeof(short) = {}\n",
        sizeof s, sizeof(short));
    std::cout << fmt::format("sizeof i = {}\tsizeof(int) = {}\n",
        sizeof i, sizeof(int));
    std::cout << fmt::format("sizeof l = {}\tsizeof(long) = {}\n",
        sizeof l, sizeof(long));
    std::cout << fmt::format("sizeof ll = {}\tsizeof(long long) = {}\n",
        sizeof ll, sizeof(long long));
    std::cout << fmt::format("sizeof f = {}\tsizeof(float) = {}\n",
        sizeof f, sizeof(float));
    std::cout << fmt::format("sizeof d = {}\tsizeof(double) = {}\n",
        sizeof d, sizeof(double));
    std::cout << fmt::format("sizeof ld = {}\tsizeof(long double) = {}\n",
        sizeof ld, sizeof(long double));
    std::cout << fmt::format("sizeof array = {}\n", sizeof array);
    std::cout << fmt::format("sizeof ptr = {}\n", sizeof ptr);

    return 0;
}
      
size_t getSize(double* ptr) {
   return sizeof(ptr);
}