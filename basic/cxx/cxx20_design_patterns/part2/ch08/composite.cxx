#include <algorithm>
#include <array>
#include <cstdint>
#include <iostream>
#include <memory>
#include <numeric>
#include <string_view>
#include <vector>



// std::generator currernt g++13 not support yet.
// #include <generator>
//
//
// struct Values {
//     std::generator<int> operator() {
//         co_yield 1;
//         co_yield 2;
//         co_yield 3;
//     }
// };
//
// int main() {
//     Values v;
//     for (auto i : v)
//         std::cout << i << ' ';
//     return 0;
// }


class Creature1 {
    int strength;
    int agility;
    int intelligence;

public:
    int get_strength() const {
        return strength;
    }

    void set_strength(int strength) {
        this->strength = strength;
    }

    int get_agility() const {
        return agility;
    }

    void set_agility(int agility) {
        this->agility = agility;
    }

    int get_intelligence() const {
        return intelligence;
    }

    void set_intelligence(int intelligence) {
        this->intelligence = intelligence;
    }

    int sum() const {
        return strength + agility + intelligence;
    }

    double average() const {
        return sum() / 3.0;
    }

    int max() const {
        return std::max(std::max(strength, agility), intelligence);
    }
};



class Creature {
    enum Abilities { str, agl, intl, count };
    std::array<int, count> abilities;

public:
    int get_strength() const {
        return abilities[str];
    }

    void set_strength(int strength) {
        abilities[str] = strength;
    }

    int get_agility() const {
        return abilities[agl];
    }

    void set_agility(int agility) {
        abilities[agl] = agility;
    }

    int get_intelligence() const {
        return abilities[intl];
    }

    void set_intelligence(int intelligence) {
        abilities[intl] = intelligence;
    }

    int sum() const {
        return std::accumulate(abilities.begin(), abilities.end(), 0);
    }

    double average() const {
        return sum() / (double)count;
    }

    int max() const {
        return *std::max_element(abilities.begin(), abilities.end());
    }
};



struct GraphicObject {
    virtual void draw() = 0;
};

struct Circle : public GraphicObject {
    void draw() override {
        std::cout << "Circle\n";
    }
};

struct Group : public GraphicObject {
    std::string name;
    std::vector<GraphicObject*> objects;

    explicit Group(std::string_view name) 
        : name{ name } {  
    }

    void draw() override {
        std::cout << "Group " << name << " contains:\n";
        for (auto&& o : objects)
            o->draw();
    }
};

int main1() {
    Group root{ "root" };
    Circle c1, c2;
    root.objects.push_back(&c1);

    Group subgroup{ "sub" };
    subgroup.objects.push_back(&c2);

    root.objects.push_back(&subgroup);
    root.draw();

    return 0;
}



template <typename T>
concept Iterable = requires(T& t) {
    t.begin();
    t.end();
} || requires(T& t) {
    begin(t);
    end(t);
};


// template <Iterable Self>
// struct SomeNeurons {
//     template <Iterable T>
//     void connect_to(T& other) {
//         for (auto& from : *static_cast<Self*>(this)) {
//             for (auto& to : other) {
//                 from.out.push_back(&to);
//                 to.in.push_back(&from);
//             }
//         }
//     }
// };
//
// template <Iterable T>
// struct Scalar : public SomeNeurons<T> {
//     T* begin() { return reinterpret_cast<T*>(this); }
//     T* end() { return reinterpret_cast<T*>(this) + 1; }
// };
//
//
// Neuron not iterable per se
// struct Neuron : public Scalar<Neuron> {
//     std::vector<Neuron*> in;
//     std::vector<Neuron*> out;
//     uint32_t id;
//
//     Neuron() {
//         static int id{ 1 };
//         this->id = id++;
//     }
//
//     // template <>
//     // void connect_to<Neuron>(Neuron& other) {
//     //     out.push_back(&other);
//     //     other.in.push_back(this);
//     // }
// };
//
// NeuronLayer not iterable per se
// struct NeuronLayer : public std::vector<Neuron>, public SomeNeurons<NeuronLayer> {
//     NeuronLayer() = default;
//     NeuronLayer(int count) {
//         while (count --> 0)
//             emplace_back(Neuron{});
//     }
// };
//
//
// int main() {
//     Neuron n1, n2;
//     NeuronLayer layer1, layer2;
//
//     n1.connect_to(n2);
//     n1.connect_to(layer1);
//
//     layer1.connect_to(n1);
//     layer1.connect_to(layer2);
//
//     return 0;
// }



struct Neuron{
    std::vector<Neuron*> in;
    std::vector<Neuron*> out;
    uint32_t id;

    Neuron() {
        static int id{ 1 };
        this->id = id++;
    }

    Neuron* begin() { return this; }
    Neuron* end() { return this + 1; }
};


template <Iterable T>
class ConncetionProxy {
    T& item;

public:
    explicit ConncetionProxy(T& item) : item{ item } {
    }

    template <Iterable U>
    void operator>(U& other) {
        for (Neuron& from : item) {
            for (Neuron& to : other) {
                from.out.push_back(&to);
                to.in.push_back(&from);
            }
        }
    }
};

template <typename T>
ConncetionProxy<T> operator--(T&& item, int) {
    return ConncetionProxy<T>{ item };
}


int main2() {
    Neuron n1;
    Neuron n2;
    n1-->n2;

    return 0;
}



template <typename T>
struct Specification {
    virtual bool is_satisfied(T* item) const = 0;
};

template <typename T>
struct CompositeSpecification : public Specification<T> {
protected:
    std::vector<std::unique_ptr<Specification<T>>> specs;

    template <typename... Specs>
    CompositeSpecification(Specs... specs) {
        this->specs.reserve(sizeof...(Specs));
        (this->specs.push_back(std::make_unique<Specs>(std::move(specs))), ...);
    }
};

template <typename T>
struct AndSpecification : public CompositeSpecification<T> {
    template <typename... Specs>
    AndSpecification(Specs... specs) : CompositeSpecification<T>{ specs... } {
    }

    bool is_satisfied(T* item) const override {
        return std::all_of(this->specs.begin(), this->specs.end(), [=](const auto& s) {
            return s->is_satisfied(item);
        });
    }
};