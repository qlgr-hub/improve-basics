#include <iostream>

class Base {
public:
    virtual void print() const = 0;
};

class DerivedOne : public Base {
public:
    void print() const override { std::cout << "DerivedOne\n"; }
};

class DerivedTwo : public Base {
public:
    void print() const override { std::cout << "DerivedTwo\n"; }
};

class Multiple : public DerivedOne, public DerivedTwo {
public:
    void print() const override { DerivedTwo::print(); }
};

int main() {
    Multiple both{};
    DerivedOne one{};
    DerivedTwo two{};
    Base* array[3]{};

    // array[0] = &both; // error: ambiguous conversion from derived class 'Multiple' to base class 'Base'
    array[1] = &one;
    array[2] = &two;

    for (int i{0}; i < 3; ++i) {
        if (array[i]) {
            array[i]->print();
        }
    }

    return 0;
}