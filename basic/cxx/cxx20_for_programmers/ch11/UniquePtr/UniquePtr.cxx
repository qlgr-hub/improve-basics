#include <fmt/format.h>
#include <iostream>
#include <memory>

class Integer {
public:
    Integer(int i) : value{i} {
        std::cout << fmt::format("Constructor for Integer {}\n", value);
    }

    ~Integer() {
        std::cout << fmt::format("Destructor for Integer {}\n", value);
    }

    int getValue() const {return value;}
private:
    int value{0};
};

int main() {
    std::cout << "Creating a unique_ptr that points to an Integer\n";
    
    auto ptr{std::make_unique<Integer>(7)};

    std::cout << fmt::format("Integer value: {}\n\nMain ends\n", ptr->getValue());
    return 0;
}