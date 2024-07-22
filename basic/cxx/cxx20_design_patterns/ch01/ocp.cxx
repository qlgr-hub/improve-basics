
#include <iostream>
#include <string>
#include <vector>


enum class Color { Red, Green, Blue };
enum class Size { Small, Medium, Large };

struct Product {
    std::string name;
    Color color;
    Size size;
};

struct ProductFilter {
    using Items = std::vector<Product*>;

    Items by_color(Items items, Color color) {
        Items result;
        for (auto& i : items)
            if (i->color == color)
                result.push_back(i);
        return result;
    }

    Items by_size(Items items, Size sise) {
        Items result;
        for (auto& i : items)
            if (i->size == sise)
                result.push_back(i);
        return result;
    }

    Items by_color_and_size(Items items, Color color, Size sise) {
        Items result;
        for (auto& i : items)
            if (i->color == color && i->size == sise)
                result.push_back(i);
        return result;
    }
};




//////////////////////////////////////////////////////////////////////
// template <typename T> struct AndSpecification;

template <typename T>
struct Specification {
    virtual bool is_satisfied(T* item) const = 0;

    // Extensions replace modifications so the global operator solution is preferred.
    // AndSpecification<T> operator&&(Specification<T>& other) {
    //     return AndSpecification<T>{ *this, other };
    // }
};

template <typename T>
struct Filter {
    virtual std::vector<T*> filter(std::vector<T*> items,
        Specification<T>& spec) const = 0;
};


struct BetterFilter : Filter<Product> {
    std::vector<Product*> filter(std::vector<Product*> items,
        Specification<Product>& spec) const override {
        std::vector<Product*> result;
        for (auto& i : items)
            if (spec.is_satisfied(i))
                result.push_back(i);
        return result;
    }
};


struct ColorSpecification : Specification<Product> {
    Color color;
    
    explicit ColorSpecification(Color color) : color{ color } {
    }

    bool is_satisfied(Product* item) const override {
        return item->color == color;
    }
};


struct SizeSpecification : Specification<Product> {
    Size size;
    
    explicit SizeSpecification(Size size) : size{ size } {
    }

    bool is_satisfied(Product* item) const override {
        return item->size == size;
    }
};


template <typename T>
struct AndSpecification : Specification<T> {
    const Specification<T>& first;
    const Specification<T>& second;
    
    AndSpecification(const Specification<T>& first, const Specification<T>& second) 
        : first{ first }, second{ second } {
    }

    bool is_satisfied(Product* item) const override {
        return first.is_satisfied(item) && second.is_satisfied(item);
    }
};


template <typename T>
AndSpecification<T> operator&&(const Specification<T>& first, 
                               const Specification<T>& second) {
    return { first, second };
}


int main() {
    Product apple{ "Apple", Color::Green, Size::Small };
    Product tree{ "Tree", Color::Green, Size::Large };
    Product house{ "House", Color::Blue, Size::Large };

    std::vector<Product*> all{ &apple, &tree, &house };

    BetterFilter df;
    ColorSpecification green{ Color::Green };

    auto green_things = df.filter(all, green);
    for (auto& x : green_things)
        std::cout << x->name << " is green\n";

    // SizeSpecification large{ Size::Large };
    // AndSpecification<Product> green_and_large{ large, green };

    auto green_and_large = SizeSpecification{ Size::Large } && green;
    auto big_green_things = df.filter(all, green_and_large);
    for (auto& x : big_green_things)
        std::cout << x->name << " is large and green\n";

    return 0;
}