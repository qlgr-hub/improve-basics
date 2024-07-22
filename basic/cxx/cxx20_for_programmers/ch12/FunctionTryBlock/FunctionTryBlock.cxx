#include <fmt/format.h>
#include <iostream>
#include <limits.h>
#include <stdexcept>

class Integer {
public:
    explicit Integer(int i) : value{i} {
        std::cout << fmt::format("Integer constructor: {}\n", value)
            << "Purposely throwing exception from Integer constructor\n";
        throw std::runtime_error("Integer constructor failed");
    }

private:
    int value{};
};

class ResourceManager {
public:
    ResourceManager(int i) try: myInteger{i} {
        std::cout << "ResourceManager constructor called\n";
    }
    catch  (const std::runtime_error& ex) {
        std::cerr << fmt::format(
            "Exception while contructing ResourceManager: ",
            ex.what()) << "\nAutomatically rethrowing the exception\n";
    }

private:
    Integer myInteger;
};

int main() {
    try {
        const ResourceManager resource{7};
    }
    catch (const std::runtime_error& ex) {
        std::cerr << fmt::format("Rethrown exception caught in main: {}\n", ex.what());
    }
}