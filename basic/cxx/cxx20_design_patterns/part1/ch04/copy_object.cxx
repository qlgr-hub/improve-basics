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
    Address address;
};

void copy_construct_contacts() {
    Contact worker{ "", Address{ "123 East Dr", "London", 0 } };
    
    Contact john = worker;
    john.name = "John Doe";
    john.address.suite = 10;

    Contact jane = worker;
    jane.name = "Jane Doe";
    jane.address.suite = 11;
}


struct Contact1 {
    std::string name;
    Address* address;


public:
    Contact1(std::string_view name, std::string_view street, std::string_view city, int suite) 
        : name{ name }, address{ new Address{ street, city, suite } } {
    }

    Contact1(const Contact1& other) 
        : name{ other.name }
        , address{ new Address{ *other.address } } {
        // address = new Address{ other.address->street, other.address->city, other.address->suite };
    }

    Contact1(Contact1&& other) : name{ other.name }, address{ other.address } {
        other.address = nullptr;
    }

    ~Contact1() {
        if (address) {
            delete address;
            address = nullptr;
        }
    }

    Contact1& operator=(const Contact1& other) {
        if (this != &other) {
            name = other.name;

            if (address)
                delete address;

            address = new Address{ *other.address };
        }
        return *this;
    }

    Contact1& operator=(Contact1&& other) {
        if (this != &other) {
            name = other.name;
            address = other.address;

            other.address = nullptr;
        }
        return *this;
    }
};

void copy_construct_contacts1() {
    Contact1 worker{ "", "123 East Dr", "London", 0 };
    
    Contact1 john = worker;
    john.name = "John Doe";
    john.address->suite = 10;

    Contact1 jane = worker;
    jane.name = "Jane Doe";
    jane.address->suite = 11;
}

