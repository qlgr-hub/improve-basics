#include <fmt/format.h>
#include "Base1.h"
#include "Base2.h"
#include "Derived.h"

int main() {
    Base1 base1{10};
    Base2 base2{'Z'};
    Derived derived{7, 'A', 3.5};

    std::cout << fmt::format("{}: {}\n{}: {}\n{}: {}\n\n",
        "Object base1 contains", base1.getData(),
        "Object base2 contains the character", base2.getData(),
        "Object derived contains", derived.toString());

    std::cout << fmt::format("{}\n{}: {}\n{}: {}\n{}: {}\n\n",
        "Data members of Derived can be accessed individually:",
        "int", derived.Base1::getData(),
        "char", derived.Base2::getData(),
        "double", derived.getReal());
    
    std::cout << "Derived can be treated as an object"
        << " of either base class:\n";

    Base1* base1Ptr = &derived;
    std::cout << fmt::format("base1Ptr->getData() yields {}\n", base1Ptr->getData());

    Base2* base2Ptr = &derived;
    std::cout << fmt::format("base2Ptr->getData() yields {}\n", base2Ptr->getData());

    return 0;
}