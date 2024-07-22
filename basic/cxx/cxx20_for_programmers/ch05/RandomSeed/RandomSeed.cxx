#include <iostream>
#include <random>

int main() {
    unsigned int seed{0};

    std::cout << "Enter seed: ";
    std::cin >> seed;

    std::default_random_engine engine{seed};

    std::uniform_int_distribution randomDie{1, 6};

    for (int counter{1}; counter <= 10; ++counter) {
        std::cout << randomDie(engine) << " ";
    }
    
    std::cout << "\n";
    return 0;
}