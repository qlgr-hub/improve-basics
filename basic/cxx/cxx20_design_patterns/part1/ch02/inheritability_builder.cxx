#include <iostream>
#include <ostream>
#include <string>
#include <string_view>


struct Person {
    std::string name;
    std::string position;
    std::string date_of_birth;

    friend std::ostream& operator<<(std::ostream& os, const Person& obj) {
        return os << "name: " << obj.name << "position: " << obj.position
            << "date of birth: " << obj.date_of_birth;
    }
};


class PersonBuilder {
protected:
    Person person;

public:
    [[nodiscard]] Person build() const {
        return person;
    }
};


// doesn't work
// class PersonInfoBuilder : public PersonBuilder {
// public:
//     PersonInfoBuilder& called(std::string_view name) {
//         person.name = name;
//         return *this;
//     }
// };
//
// class PersonJobBuilder : public PersonInfoBuilder {
// public:
//     PersonJobBuilder& works_as(std::string_view position) {
//         person.position = position;
//         return *this;
//     }
// };
//
// int main() {
//     PersonJobBuilder pb;
//     // called returns a PersonInfoBuilder reference, PersonInfoBuilder has no works_as method
//     auto person = pb.called("Dmitri").works_as("Programmer").build();
// }


template <typename TSelf>
class PersonInfoBuilder : public PersonBuilder {
public:
    TSelf& called(std::string_view name) {
        person.name = name;

        // Shouldn't it be dynamic_cast ?
        // 1. No polymorphism required here
        // 2. Is static_cast more performant than dynamic_cast when polymorphism is not involved?
        return static_cast<TSelf&>(*this);
    }
};


template <typename TSelf>
class PersonJobBuilder : public PersonInfoBuilder<PersonJobBuilder<TSelf>> {
public:
    TSelf& works_as(std::string_view position) {
        this->person.position = position;
        return static_cast<TSelf&>(*this);;
    }
};

template <typename TSelf>
class PersonBirthDateBuilder : public PersonJobBuilder<PersonBirthDateBuilder<TSelf>> {
public:
    TSelf& born_on(std::string_view date_of_birth) {
        this->person.date_of_birth = date_of_birth;
        return static_cast<TSelf&>(*this);;
    }
};


class MyBuilder : public PersonBirthDateBuilder<MyBuilder> {};

int main() {
    MyBuilder mb;
    auto me = mb.called("Dmitri")
        .works_as("Programmer")
        .born_on("01/01/1980")
        .build();
    std::cout << me << '\n';
    return 0;
}