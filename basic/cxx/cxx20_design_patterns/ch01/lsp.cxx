
#include <iostream>
// #include <stdexcept>


class Rectangle {
protected:
    int width;
    int height;

public:
    Rectangle(int width, int height) : width{ width }, height{ height } {
    }

    int get_width() const { return width; }
    virtual void set_width(int w) { width = w; }

    int get_height() const { return height; }
    virtual void set_height(int h) { height = h; }

    int erea() const { return width * height; }

    bool is_square() const { return width == height; }
};

class Square : public Rectangle {
public:
    Square(int size) : Rectangle{ size, size } {
    }

    void set_width(int w) override {
        width = height = w;
    }

    void set_height(int h) override {
        width = height = h;
    }
};


// class Square : public Rectangle {
// public:
//     Square(int size) : Rectangle{ size, size } {
//     }
//
//     // Violates the PLS (principle of least surprise).
//     void set_width(int w) override {
//         throw std::runtime_error("square not support set_width");
//     }
//
//     void set_height(int h) override {
//         throw std::runtime_error("square not support set_height");
//     }
//
//     void set_size(int s) {
//         width = height = s;
//     }
// };


// Factories instead of inheritance
struct RectangleFactory {
    static Rectangle create_rectangle(int w, int h);
    static Rectangle create_square(int s);
};


void process(Rectangle& r) {
    int w = r.get_width();
    r.set_height(10);

    std::cout << "expected area = " << (w * 10) << ", got " << r.erea() << '\n';
}

int main() {
    Square s{ 5 };
    process(s);

    return 0;
}