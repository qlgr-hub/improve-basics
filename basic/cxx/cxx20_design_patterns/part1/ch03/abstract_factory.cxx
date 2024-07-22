#include <functional>
#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <string_view>


struct HotDrink {
    virtual void prepare(int valume) = 0;
};


struct Tea final : public HotDrink {
    void prepare(int volume) override {
        std::cout << "Take tea bag, boil water, pour " << volume << "ml, add some lemon" << '\n';
    }
};


struct Coffee final : public HotDrink {
    void prepare(int volume) override {
        std::cout << "Take coffee bag, boil water, pour " << volume << "ml, add some lemon" << '\n';
    }
};


std::unique_ptr<HotDrink> make_drink(std::string_view type) {
    std::unique_ptr<HotDrink> drink;

    if (type == "tea") {
        drink = std::make_unique<Tea>();
        drink->prepare(200);
    }
    else {
        drink = std::make_unique<Coffee>();
        drink->prepare(50);
    }

    return drink;
}


struct HotDrinkFactory {
    virtual std::unique_ptr<HotDrink> make() const = 0;
};


struct TeaFactory final : public HotDrinkFactory {
    std::unique_ptr<HotDrink> make() const override {
        auto tea{ std::make_unique<Tea>() };
        tea->prepare(200);
        return tea;
    }
};

struct CoffeeFactory final : public HotDrinkFactory {
    std::unique_ptr<HotDrink> make() const override {
        auto coffee{ std::make_unique<Coffee>() };
        coffee->prepare(50);
        return coffee;
    }
};


class DrinkFactory {
    std::map<std::string, std::unique_ptr<HotDrinkFactory>> hot_factories;

public:
    DrinkFactory() {
        hot_factories["tea"] = std::make_unique<TeaFactory>();
        hot_factories["coffee"] = std::make_unique<CoffeeFactory>();
    }

public:
    std::unique_ptr<HotDrink> make_drink(const std::string& name, int volume) {
        auto drink{ hot_factories[name]->make() };
        drink->prepare(volume);
        return drink;
    }
};


class DrinkWithVolumeFactory {
    std::map<std::string, std::function<std::unique_ptr<HotDrink>()>> factories;

public:
    DrinkWithVolumeFactory() {
        factories["tea"] = [] {
            auto tea { std::make_unique<Tea>() };
            tea->prepare(200);
            return tea;
        };
    }

public:
    std::unique_ptr<HotDrink> make_drink(const std::string& name) {
        return factories[name]();
    }
};
