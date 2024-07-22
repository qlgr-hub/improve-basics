#include <cstdlib>
#include <initializer_list>
#include <iostream>
#include <memory>
#include <string>
#include <string_view>
#include <vector>


struct BankAccount {
    void diposit(int amount) {
        /* ... */
    }
};

int main1() {
    BankAccount* ba = new BankAccount{};
    ba->diposit(123);
    delete ba;
    
    auto ba2 = std::make_shared<BankAccount>();
    ba2->diposit(123);
    return 0;
}


template <typename T>
struct Property {
    T value;

    Property(T&& initial_value) {
        *this = initial_value; // invokes operator =
    }

    operator T() {
        return value;
    }

    T operator=(T new_value) {
        return value = new_value;
    }
};


struct Creature {
    Property<int> strength{ 20 };
    Property<int> agility{ 5 };
};

int main2() {
    Creature creature;
    creature.agility = 20;
    auto x = creature.strength;
    std::cout << x << '\n';
    return 0;
}


struct Image {
    virtual void draw() = 0;
};

struct Bitmap final : Image {
    std::string filename;

    Bitmap(std::string_view filename) 
        : filename{ filename } {
        std::cout << "Loading Bitmap from " << filename << '\n';
    }

    void draw() override {
        std::cout << "Drawing Bitmap " << filename << '\n';
    }
};

class LazyBitmap final : Image {
    Bitmap* bmp{ nullptr };
    std::string filename;

public:
    LazyBitmap(std::string_view filename) 
        : filename{ filename } {
    }

    ~LazyBitmap() {
        delete bmp;
    }

    void draw() override {
        std::cout << "Drawing LazyBitmap " << filename << '\n';
        if (!bmp)
            bmp = new Bitmap{ filename };
        bmp->draw();
    }
};

int main3() {
    Bitmap img{ "pokemon.png" };
    img.draw();

    LazyBitmap img1{ "pokemon1.png" };
    img1.draw();

    return 0;
}


struct Pingable {
    virtual std::wstring ping(std::wstring_view message) = 0;
};

struct Pong : Pingable {
    std::wstring ping(std::wstring_view message) override {
        return std::wstring(message) + L" pong";
    }
};

void tryit(Pingable& pp) {
    std::wcout << pp.ping(L"ping") << '\n';
}

int main4() {
    Pong pp;
    for (int i{ 0 }; i < 3; ++i)
        tryit(pp);

    return 0;
}


// C# code
// [Route("api/[controller]")]
// public class PingPongController : Controller {
//     [HttpGet("{msg}")]
//     public string Get(string msg) {
//         return msg + " pong";
//     }
// }
//
//
// Implemented using the Windows REST SDK
// struct RemotePong : Pingable {
//     std::wstring ping(std::wstring_view message) override {
//         std::wstring result;
//         http_client client{ U("http://locahost:9149") };
//         uri_builder builder{ U("/api/pingpong") };
//         builder.append(message);
//         pplx::task<wstring> task {
//             client.request(methods::GET, builder.to_string()) \
//                 .then([=](https_response r) {
//                     return r.extract_string();
//                 })
//         };
//         task.wait();
//         return task.get();
//     }
// };
//
//
// int main() {
//     RemotePong rpp;
//     for (int i{ 0 }; i < 3; ++i)
//         tryit(rpp);
//     return 0;
// }




template <typename T>
struct Value {
    virtual operator T() const = 0;
};


template <typename T>
struct Const : Value<T> {
    const T v;

    Const() : v{} {
    }

    Const(T&& v) : v{ v } {
    }

    operator T() const override {
        return v;
    }
};

template <typename T>
struct OneOf : Value<T> {
    std::vector<T> values;

    OneOf() : values{ { T{} } } {
    }

    OneOf(std::initializer_list<T> values) : values{ values } {
    }

    operator T() const override {
        return values[rand() % values.size()];
    }
};

// void draw_ui(const Value<bool>& use_dark_theme) {
void draw_ui(bool use_dark_theme) {
    if (use_dark_theme)
        std::cout << "Using dark theme\n";
    else
        std::cout << "Using normal theme\n";
}

int main() {
    const Const<int> life{ 42 };
    std::cout << life / 2 << '\n';

    OneOf<int> stuff{ 1, 3, 5 };
    std::cout << stuff << '\n';

    OneOf<bool> sel{ true, false };
    draw_ui(sel);

    Const<bool> dark{ true };
    draw_ui(dark);

    return 0;
}