#include <iostream>
#include <stdexcept>

void function3() {
    std::cout << "In function 3\n";
    throw std::runtime_error{"runtime_error in function3"};
}

void function2() {
    std::cout << "function3 is called inside function2\n";
    function3();
}

void function1() {
    std::cout << "function2 is called inside function1\n";
    function2();
}

int main() {
    // if not catching exception 
    // -- terminate called after throwing an instance of 'std::runtime_error'
    // -- Aborted (core dumped)
    //try {
        std::cout << "function1 is called inside main\n";
        function1();
    //}
    //catch (const std::runtime_error& error) {
    //    std::cout << "Exception occurred: " << error.what()
    //        << "\nException handled in main\n";
    //}

    return 0;
}