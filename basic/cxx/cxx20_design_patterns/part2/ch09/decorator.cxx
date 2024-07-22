#include <cstdint>
#include <functional>
#include <iostream>
#include <sstream>
#include <string>
#include <string_view>
#include <type_traits>
#include <utility>


struct Shape {
    virtual std::string str() const = 0;
};


struct Circle : public Shape {
    float radius;

    explicit Circle(float radius) 
        : radius{ radius } {
    }

    void resize(float factor) {
        radius *= factor;
    }

    std::string str() const override {
        std::ostringstream oss;
        oss << "A circle of radius " << radius;
        return oss.str();
    }
};


struct Square : public Shape {
    int size;

    explicit Square(int size) 
        : size{ size } {
    }

    void resize(int size) {
        this->size = size;
    }

    std::string str() const override {
        std::ostringstream oss;
        oss << "A square with side " << size;
        return oss.str();
    }
};


struct ColoredShape : Shape {
    Shape& shape;
    std::string color;

    ColoredShape(Shape& shape, std::string_view color) 
        : shape{ shape }, color{ color } {
    }

    std::string str() const override {
        std::ostringstream oss;
        oss << shape.str() << " has the color " << color;
        return oss.str();
    }

    void make_dark() {
        if (constexpr auto dark = "dark"; !color.starts_with(dark))
            color.insert(0, dark);
    }
};


int main1() {
    Circle circle{ 0.5f };
    ColoredShape redCircle{ circle, "red" };
    std::cout << redCircle.str() << '\n';

    redCircle.make_dark();
    std::cout << redCircle.str() << '\n';
    return 0;
}


struct TransparentShape : Shape {
    Shape& shape;
    uint8_t transparency;

    TransparentShape(Shape& shape, uint8_t transparency) 
        : shape{ shape }, transparency{ transparency } {
    }

    std::string str() const override {
        std::ostringstream oss;
        oss << shape.str() << " has " << static_cast<float>(transparency) / 255.f * 100.f << " % transparency";
        return oss.str();
    }
};


int main2() {
    Square square{ 3 };
    TransparentShape demiSquare{ square, 85 };
    std::cout << demiSquare.str() << '\n';

    Circle c{ 23.f };
    ColoredShape cs{ c, "green" };
    TransparentShape myCircle{ cs, 64 };
    std::cout << myCircle.str() << '\n';
    return 0;
}


template <typename T>
struct ColoredShape1 : T {
    // A better approach is to use the concept
    static_assert(std::is_base_of_v<Shape, T>, "Template argument must be a Shape");

    std::string color;

    template <typename... Args>
    ColoredShape1(std::string_view c, Args... args)
        : T(std::forward<Args>(args)...), color{ c } {
    }

    std::string str() const override {
        std::ostringstream oss;
        oss << T::str() << " has the color " << color;
        return oss.str();
    }
};


template <typename T>
struct TranspatentShape1 : T {
    uint8_t transparency;

    template <typename... Args>
    TranspatentShape1(uint8_t transparency, Args... args) 
        : T(std::forward<Args>(args)...), transparency{ transparency } { 
    }

    std::string str() const override {
        std::ostringstream oss;
        oss << T::str() << " has " << static_cast<float>(transparency) / 255.f * 100.f << " % transparency";
        return oss.str();
    }
};


int main3() {
    ColoredShape1<TranspatentShape1<Square>> square{ "red", 51, 5 };
    square.size = 2;
    square.transparency = 50;
    std::cout << square.str() << '\n';
    square.resize(3);

    return 0;
}




struct Logger {
    std::function<void()> func;
    std::string name;

    Logger(const std::function<void()>& func, std::string_view name) 
        : func{ func }, name{ name } {
    }

    void operator()() const {
        std::cout << "Entering " << name << '\n';
        func();
        std::cout << "Exiting " << name << '\n';
    }
};

int main4() {
    Logger([]() { std::cout << "Hello\n"; }, "HelloFunction")();
    return 0;
}


template <typename Func>
struct Logger2 {
    Func func;
    std::string name;

    Logger2(const Func& func, std::string_view name) 
        : func{ func }, name{ name } {
    }

    void operator()() const {
        std::cout << "Entering " << name << '\n';
        func();
        std::cout << "Exiting " << name << '\n';
    }
};

template <typename Func>
auto make_logger2(Func func, std::string_view name) {
    return Logger2<Func>{ func, name };
}

int main5() {
    auto call = make_logger2([]() { std::cout << "Hello\n"; }, "HelloFunction");
    call();
    return 0;
}



double add(double a, double b) {
    std::cout << a << "+" << b << "=" << (a + b) << '\n';
    return a + b;
}


// It must be declared like this first
template <typename> struct Logger3; 

template <typename R, typename... Args>
struct Logger3<R(Args...)> {
    std::function<R(Args...)> func;
    std::string name;

    Logger3(std::function<R(Args...)> func, std::string_view name) 
        : func{ func }, name{ name } {
    }

    R operator()(Args... args) {
        std::cout << "Entering " << name << '\n';
        R res{ func(args...) };
        std::cout << "Exiting " << name << '\n';
        return res;
    }
};

template <typename R, typename... Args>
auto make_logger3(R (*func)(Args...), std::string_view name) {
    return Logger3<R(Args...)>{ std::function<R(Args...)>(func), name };
}

int main() {
    auto logged_add = make_logger3(add, "Add");
    auto result = logged_add(2, 3);
    std::cout << result << '\n';
    return 0;
}
