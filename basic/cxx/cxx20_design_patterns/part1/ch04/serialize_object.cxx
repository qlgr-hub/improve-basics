#include <cstdint>
#include <sstream>
#include <string>
#include <boost/serialization/access.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <string_view>


struct Address {
    std::string street;
    std::string city;
    int suite;

    Address(std::string_view street, std::string_view city, int suite) 
        : street{ street }, city{ city }, suite{ suite } {       
    }

private:
    friend class boost::serialization::access;
    
    template <typename Ar>
    void serialize(Ar& ar, uint32_t version) {
        ar & street;
        ar & city;
        ar & suite;
    }
};


struct Contact {
    std::string name;
    Address* address{ nullptr };

    Contact() = default;

    Contact(std::string_view name, std::string_view street, std::string_view city, int suite) 
        : name{ name }, address{ new Address{ street, city, suite } } {
    }

    ~Contact() {
        if (address) {
            delete address;
            address = nullptr;
        }
    }

private:
    friend class boost::serialization::access;

    template <typename Ar>
    void serialize(Ar& ar, uint32_t version) {
        ar & name;
        ar & address; // note, no * here
    }
};


template <typename T>
T clone(T obj) {
    // 1. Serialize the object
    std::ostringstream oss;
    boost::archive::text_oarchive oa{ oss };
    oa << obj;
    std::string s = oss.str();

    // 2. Deserialize it
    std::istringstream iss{ oss.str() };
    boost::archive::text_iarchive ia{ iss };
    T result;
    ia >> result;

    return result;
}

int main() {
    Contact john{ "john", "123 East Dr", "London", 10 };
    Contact jane = clone(john);
    jane.name = "Jane";
    jane.address->suite = 11;
    return 0;
}
