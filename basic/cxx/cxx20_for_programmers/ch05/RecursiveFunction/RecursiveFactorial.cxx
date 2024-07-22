#include <iostream>
#include <fmt/format.h>
#include <boost/multiprecision/cpp_int.hpp>

boost::multiprecision::cpp_int factorial(int number);

int main() {
    for (int counter{0}; counter <= 10; ++counter) {
        std::cout << fmt::format("{:>2}! = ", counter) << factorial(counter) 
        << '\n';
    } 

    std::cout << fmt::format("\n{:>2}! = ", 20) << factorial(20) 
        << fmt::format("\n{:>2}! = ", 30) << factorial(30) 
        << fmt::format("\n{:>2}! = ", 40) << factorial(40) << '\n';

    return 0;
} 
   
boost::multiprecision::cpp_int factorial(int number) {                     
    if (number <= 1) {
        return 1;
    }                                             
    else {
        return number * factorial(number - 1);     
    }                                             
} 