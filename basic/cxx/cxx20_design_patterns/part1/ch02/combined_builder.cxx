#include <string>
#include <string_view>


class PersonAddressBuilder;
class PersonJobBuilder;
class PersonBuilder;

class Person {
    friend class PersonAddressBuilder;
    friend class PersonJobBuilder;

    std::string street_address;
    std::string post_code;
    std::string city;
    std::string company_name;
    std::string position;
    double annual_income{ 0 };

public:
    Person() {}

public:
    static PersonBuilder build();
};


class PersonBuilderBase {
protected:
    Person& person;
    explicit PersonBuilderBase(Person& person)
        : person{ person } {
    }

public:
    operator Person() {
        return std::move(person);
    }

    PersonAddressBuilder lives() const;
    PersonJobBuilder works() const;
};


class PersonBuilder : public PersonBuilderBase {
    Person p;

public:
    PersonBuilder() : PersonBuilderBase{ p } {
    }
};

// Need to be defined here
PersonBuilder Person::build() {
    return PersonBuilder{};
}


class PersonAddressBuilder : public PersonBuilderBase {
    using self = PersonAddressBuilder;

public:
    explicit PersonAddressBuilder(Person& person)
        : PersonBuilderBase{ person } {
    }

    self& at(std::string_view street_address) {
        person.street_address = street_address;
        return *this;
    }

    self& with_postcode(std::string_view post_code) {
        person.post_code = post_code;
        return *this;
    }

    self& in(std::string_view city) {
        person.city = city;
        return *this;
    }
};

// Need to be defined here
PersonAddressBuilder PersonBuilderBase::lives() const {
    return PersonAddressBuilder{ person };
}


class PersonJobBuilder : public PersonBuilderBase {
    using self = PersonJobBuilder;

public:
    explicit PersonJobBuilder(Person& person)
        : PersonBuilderBase{ person } {
    }

    self& at(std::string_view company_name) {
        person.company_name = company_name;
        return *this;
    }

    self& as_a(std::string_view position) {
        person.position = position;
        return *this;
    }

    self& earning(double annual_income) {
        person.annual_income = annual_income;
        return *this;
    }
};

// Need to be defined here
PersonJobBuilder PersonBuilderBase::works() const {
    return PersonJobBuilder{ person };
}

int main() {
    Person p = Person::build().lives().at("123 London Road") \
        .with_postcode("SW1 1GB").in("London").works() \
        .at("PragmaSoft").as_a("Consultant").earning(10e6);

    return 0;
}