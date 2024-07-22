#include <memory>
#include <string>
#include <string_view>


struct Address {
    std::string street;
    std::string city;
    int suite;

    Address(std::string_view street, std::string_view city, int suite)
        : street{ street }, city{ city }, suite{ suite } {
    }
};


struct Contact {
    std::string name;
    Address* address;

public:
    Contact(std::string_view name, std::string_view street, std::string_view city, int suite) 
        : name{ name }, address{ new Address{ street, city, suite } } {
    }

    Contact(const Contact& other) 
        : name{ other.name }
        , address{ new Address{ *other.address } } {
        // address = new Address{ other.address->street, other.address->city, other.address->suite };
    }

    Contact(Contact&& other) : name{ other.name }, address{ other.address } {
        other.address = nullptr;
    }

    ~Contact() {
        if (address) {
            delete address;
            address = nullptr;
        }
    }

    Contact& operator=(const Contact& other) {
        if (this != &other) {
            name = other.name;

            if (address)
                delete address;

            address = new Address{ *other.address };
        }
        return *this;
    }

    Contact& operator=(Contact&& other) {
        if (this != &other) {
            name = other.name;
            address = other.address;

            other.address = nullptr;
        }
        return *this;
    }
};


class EmployeeFactory {
    static Contact main;
    static Contact aux;

    static std::unique_ptr<Contact> NewEmployee(std::string_view name, int suite, const Contact& proto) {
        auto result{ std::make_unique<Contact>(proto) };
        result->name = name;
        result->address->suite = suite;
        return result;
    }

public:
    static std::unique_ptr<Contact> NewMainOfficeEmployee(std::string_view name, int suite) {
        return NewEmployee(name, suite, main);
    }

    static std::unique_ptr<Contact> NewAuxOfficeEmployee(std::string_view name, int suite) {
        return NewEmployee(name, suite, aux);
    }
};
Contact EmployeeFactory::main = Contact{ "", "123 East Dr", "London", 0 };
Contact EmployeeFactory::aux = Contact{ "", "123B East Dr", "London", 0 };


int main() {
    auto john = EmployeeFactory::NewAuxOfficeEmployee("john", 123);
    auto jane = EmployeeFactory::NewMainOfficeEmployee("jane", 125);
    return 0;
}
