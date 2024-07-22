// Pimpl

#include <iostream>
#include <string>


struct Person {
    std::string name;

    void greet() const;

public:
    Person();
    ~Person();

private:
    struct PersonImpl;
    PersonImpl* impl;
};

struct Person::PersonImpl {
    void greet() const {
        std::cout << "Hello ..." << '\n';
    }
};

Person::Person() : impl{ new PersonImpl{} } {
}

Person::~Person() {
    delete impl;
}

void Person::greet() const {
    impl->greet();
}




struct Renderer {
    virtual void render_circle(float x, float y, float radius) = 0;
};

struct VectorRenderer : public Renderer {
    void render_circle(float x, float y, float radius) override {
        std::cout << "Drawing a vector circle of radius " << radius << '\n';
    }
};

struct RasterRenderer : public Renderer {
    void render_circle(float x, float y, float radius) override {
        std::cout << "Rasterizing circle of radius " << radius << '\n';
    }
};


struct Shape {
protected:
    Renderer& renderer;

    Shape(Renderer& renderer) : renderer{ renderer } {
    }

public:
    virtual void draw() = 0;
    virtual void resize(float factor) = 0;
};

struct Circle : public Shape {
    float x;
    float y;
    float radius;

    Circle(Renderer& renderer, float x, float y, float radius) 
        : Shape{ renderer }, x{ x }, y{ y }, radius{ radius } {  
    }

    void draw() override {
        renderer.render_circle(x, y, radius);
    }

    void resize(float factor) override {
        radius += factor;
    }
};


int main() {
    RasterRenderer rr;
    Circle raster_circle{ rr, 5, 5, 5 };
    raster_circle.draw();
    raster_circle.resize(2);
    raster_circle.draw();
    return 0;
}

