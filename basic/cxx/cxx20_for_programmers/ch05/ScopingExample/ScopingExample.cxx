#include <iostream>

void useLocal();
void useStaticLocal();
void useGlobal();

int x{1};

int main() {
    std::cout << "global x in main is " << x << "\n";

    const int x{5};

    std::cout << "local x in main's outer scope is " << x << "\n";

    {
        const int x{7};

        std::cout << "local x in main's inner scope is " << x << "\n";
    }

    std::cout << "local x in main's outer scope is " << x << "\n";

    useLocal();
    useStaticLocal();
    useGlobal();
    useLocal();
    useStaticLocal();
    useGlobal();

    return 0;
}

void useLocal() {
    int x{25};

    std::cout << "\nlocal x is " << x << " on entering useLocal\n";
    ++x;
    std::cout << "\nlocal x is " << x << " on exiting useLocal\n";
}

void useStaticLocal() {
    static int x{50};

    std::cout << "\nlocal static x is " << x << " on entering useStaticLocal\n";
    ++x;
    std::cout << "\nlocal static x is " << x << " on exiting useStaticLocal\n";
}

void useGlobal() {
    std::cout << "\nglobal x is " << x << " on entering useGlobal\n";
    x *= 10;
    std::cout << "\nglobal x is " << x << " on exiting useGlobal\n";
}