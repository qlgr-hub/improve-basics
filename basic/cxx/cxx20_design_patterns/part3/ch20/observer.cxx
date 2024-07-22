#include <algorithm>
#include <cstring>
#include <iostream>
#include <iterator>
#include <mutex>
#include <pstl/glue_algorithm_defs.h>
#include <string_view>
#include <vector>
#include <boost/signals2.hpp>
#include <boost/bind.hpp>


class Person {
    int age;

public:
    Person(int age) : age{ age } {
    }

public:
    int get_age() const {
        return age;
    }

    void set_age(int value) {
        age = value;
    }
};


struct PersonListener {
    virtual void person_changed(Person& p, std::string_view property_name) = 0;
};


template <typename T>
struct Observer {
    virtual void field_changed(T& source, std::string_view field_name) = 0;
};


// struct Creature {
// };

struct ConsolePersonObserver : Observer<Person>/*, Observer<Creature> */ {
    void field_changed(Person& source, std::string_view field_name) override {
        if (field_name == "age") {
            std::cout << "Person's age has changed to " << source.get_age() << '\n';
        }
    }

    // void field_changed(Creature& source, std::string_view field_name) override {
    //     // TODO: 
    // }
};


template <typename T>
class Observable {
    // You can consider using concurrent_vector 
    // in PPL/TPL、TBB/PPL to avoid managing locks yourself
    std::vector<Observer<T>*> observers;
    std::mutex mtx;

public:
    // VER1: if notify -> field_changed -> unsubscribe, no re-entrancy
    // void notify(T& source, std::string_view name) {
    //     std::scoped_lock<std::mutex> lock{ mtx };
    //
    //     for (auto obs : observers)
    //         obs->field_changed(source, name);
    // }

    // VER2:
    // void notify(T& source, std::string_view name) {
    //     for (auto obs : observers)
    //         if (obs)
    //             obs->field_changed(source, name);
    // }

    void notify(T& source, std::string_view name) {
        std::vector<Observer<T>*> observers_copy;
        {
            std::scoped_lock<std::mutex> lock{ mtx };
            observers_copy = observers;
        }
        // The lock has been released here.
        
        for (auto obs : observers_copy)
            if (obs)
                obs->field_changed(source, name);
    }

    void subscribe(Observer<T>* f) {
        std::scoped_lock<std::mutex> lock{ mtx };

        observers.push_back(f);
    }

    // VER2:
    // void unsubscribe(Observer<T>* f) {
    //     auto it{ std::find(observers.begin(), observers.end(), f) };
    //     if (it != observers.end())
    //         *it = nullptr;
    // }

    void unsubscribe(Observer<T>* f) {
        std::scoped_lock<std::mutex> lock{ mtx };

        observers.erase(std::remove(observers.begin(), observers.end(), f), observers.end());
    }
};


// enum class CitizenShip {
//     Country_A
//     /* ... */
// };
class Person1 : public Observable<Person1> {
    int age;
    // CitizenShip citizenship;

public:
    Person1(int age) : age{ age } {
    }

public:
    int get_age() const {
        return age;
    }

    void set_age(int value) {
        if (age == value)
            return;

        auto old_can_vote{ can_vote() };
        age = value;
        notify(*this, "age");

        if (old_can_vote != can_vote())
            notify(*this, "can_vote");
    }

    // void set_citizenship(CitizenShip value) {
    //     if (citizenship == value)
    //         return;
    //
    //     auto old_can_vote{ can_vote() };
    //     citizenship = value;
    //     notify(*this, "citizenship");
    //
    //     if (old_can_vote != can_vote())
    //         notify(*this, "can_vote");
    // }


    // Although there is no actual attribute field, 
    // the value depends on multiple other properties.
    bool can_vote() const {
        if (/* citizenship != <balabala>  || */age < 16)
            return false;
        return true;
    }
};


struct ConsolePersonObserver1 : Observer<Person1> {
    void field_changed(Person1& source, std::string_view field_name) override {
        std::cout << "Person's " << field_name << " has changed to " << source.get_age() << '\n';
    }
};


int main1() {
    Person1 p{ 20 };
    ConsolePersonObserver1 cpo;
    p.subscribe(&cpo);
    p.set_age(21);
    p.set_age(22);
    return 0;
}


struct TrafficAdministration : Observer<Person1> {
    void field_changed(Person1& source, std::string_view field_name) override {
        if (field_name == "age") {
            if (source.get_age() < 17)
                std::cout << "Whoa there, you are not old enough to drive!\n";
        }
        else {
            // oh, ok, they are old enough, let's not monitor them
            std::cout << "We no longer care!\n";
            source.unsubscribe(this);
        }
    }
};


template <typename T>
struct Observable2 {
    boost::signals2::signal<void(T&, std::string_view)> property_changed;
};

// class Person2 : public Observable2<Person2> {
//     int age;
//
// public:
//     Person2(int age) : age{ age } {
//     }
//
// public:
//     int get_age() const {
//         return age;
//     }
//
//     void set_age(int value) {
//         if (age == value)
//             return;
//
//         age = value;
//         property_changed(*this, "age");
//     }
// };


struct Person2 {
    std::string name;

    Person2() = default;
    Person2(std::string_view name) : name{ name } {
    }
};

class PersonView : public Observable2<Person2> {
    Person2& person;

public:
    PersonView(Person2& person) : person{ person } {
    }

public:
    std::string_view get_name() const {
        return person.name;
    }

    void set_name(std::string_view value) {
        if (person.name == value)
            return;

        person.name = value;
        property_changed(person, "name");
    }
};


int main() {
    // Person2 p{ 123 };
    //
    // auto conn = p.property_changed.connect([](Person2&, std::string_view prop_name) {
    //     std::cout << prop_name << " has been changed" << '\n';
    // });
    //
    // p.set_age(20);
    //
    // conn.disconnect();

    Person2 p{ "john" };
    PersonView pv{ p };
    
    auto conn = pv.property_changed.connect([](Person2&, std::string_view prop_name) {
        std::cout << prop_name << " has been changed" << '\n';
    });

    pv.set_name("jane");

    conn.disconnect();
    return 0;
}