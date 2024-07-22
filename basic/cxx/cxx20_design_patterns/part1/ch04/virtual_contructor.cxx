#include <string>
#include <string_view>


struct Address {
    std::string street;
    std::string city;
    int suite;

    Address(std::string_view street, std::string_view city, int suite)
        : street{ street }, city{ city }, suite{ suite } {
    }

    virtual Address* clone() {
        return new Address{ street, city, suite };
    }
};


struct ExtendedAddress : public Address {
    std::string country;
    std::string postcode;

    ExtendedAddress(std::string_view street, std::string_view city,
                    int suite, std::string_view country, std::string_view postcode)
        : Address{ street, city, suite }
        , country{ country}
        , postcode{ postcode } {
    }

    ExtendedAddress* clone() override {
        return new ExtendedAddress{ street, city, suite, country, postcode };
    }
};
