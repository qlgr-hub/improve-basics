#include <fmt/format.h>  
#include <iostream>

long fibonacci(long number);

int main() {
    for (int counter{0}; counter <= 10; ++counter) {
        std::cout << fmt::format("fibonacci({}) = {}\n", 
            counter, fibonacci(counter));
    }

    std::cout << fmt::format("\nfibonacci(20) = {}\n", fibonacci(20))
        << fmt::format("fibonacci(30) = {}\n", fibonacci(30))
        << fmt::format("fibonacci(35) = {}\n", fibonacci(35));

    return 0;
} 
                         
long fibonacci(long number) {            
    if ((0 == number) || (1 == number)) {
        return number;                                       
    }                                                       
    else {
        return fibonacci(number - 1) + fibonacci(number - 2);
    }                                                       
}   