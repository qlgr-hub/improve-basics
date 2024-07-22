#include <exception>
#include <iostream>
#include <memory>
#include <vector>

struct Point2D {
    double x;
    double y;
};


class Wall {
    Point2D start;
    Point2D end;
    double elevation;
    double height;

public:
    Wall(const Point2D& start, const Point2D& end, double elevation, double height)
        : start{ start }, end{ end }, elevation{ elevation }, height{ height } {
    }
};


enum class Material {
    brick,
    aerated_concrete,
    drywall
};


// Throwing exceptions from constructors is not a good idea.
// class SolidWall : public Wall {
//     double width;
//     Material material;
//
// public:
//     SolidWall(const Point2D& start, const Point2D& end, double elevation, double height, double width, Material material)
//         : Wall{ start, end, elevation, height }, width{ width}, material{ material } {
//         if (elevation < 0 && material == Material::aerated_concrete)
//             throw std::invalid_argument("elevation");
//
//         if (width < 120 && material == Material::brick)
//             throw std::invalid_argument("width");
//     }
// };


class SolidWall : public Wall {
    // doesn't work
    // error: invalid use of template-id 'make_unique<SolidWall>' in declaration of primary template
    // template<typename ...Args>
    // friend std::unique_ptr<SolidWall> std::make_unique<SolidWall>(Args&&...);

    double width;
    Material material;

// protected:
public:
    SolidWall(const Point2D& start, const Point2D& end, double elevation, double height, double width, Material material)
        : Wall{ start, end, elevation, height }, width{ width}, material{ material } {
    }

public:
    bool intersects(const Wall& w) {
        // TODO: implement ignore
        return false;
    }

public:
    // static SolidWall create_main(const Point2D& start, const Point2D& end, double elevation, double height) {
    //     return SolidWall{ start, end, elevation, height, 375, Material::aerated_concrete };
    // }

    static std::shared_ptr<SolidWall> create_main(const Point2D& start, const Point2D& end, double elevation, double height) {
        if (elevation < 0)
            return {};
        return std::make_shared<SolidWall>(start, end, elevation, height, 375, Material::aerated_concrete);
    }

    std::unique_ptr<SolidWall> create_partition(const Point2D& start, const Point2D& end, double elevation, double height) {
        return std::make_unique<SolidWall>(start, end, elevation, height, 120, Material::brick);
    }

public:
    friend std::ostream& operator<<(std::ostream& os, const SolidWall& obj) {
        return os << "SolidWall";
    }
};

// int main() {
//     const auto main_wall = SolidWall::create_main({0, 0}, {0, 3000}, 2700, 3000);
//     std::cout << main_wall << '\n';
// }


class Factory {
    static std::vector<std::weak_ptr<Wall>> walls;

public:
    static std::shared_ptr<SolidWall> create_main(const Point2D& start, const Point2D& end, double elevation, double height) {
        if (elevation < 0)
            return {};
        return std::make_shared<SolidWall>(start, end, elevation, height, 375, Material::aerated_concrete);
    }

    static std::shared_ptr<SolidWall> create_partition(const Point2D& start, const Point2D& end, double elevation, double height) {
        const auto this_wall = new SolidWall{ start, end, elevation, height, 120, Material::brick };

        for (const auto wall : walls) {
            if (auto p = wall.lock()) {
                if (this_wall->intersects(*p)) {
                    delete this_wall;
                    return {};
                }
            }
        }

        std::shared_ptr<SolidWall> ptr{ this_wall };
        walls.push_back(ptr);
        return ptr;
    }
};

// int main() {
//     const auto partition = Factory::create_partition({2000, 0}, {2000, 4000}, 0, 2700);
//     std::cout << *partition << '\n';
//     return 0;
// }


enum class WallType {
    basic,
    main,
    partition
};

struct WallFactory {
    

    static std::shared_ptr<Wall> create_wall(WallType type, const Point2D& start, const Point2D& end, double elevation, double height) {
        switch (type) {
        case WallType::main:
            return std::make_shared<SolidWall>(start, end, elevation, height, 375, Material::aerated_concrete);
        case WallType::partition:
            return std::make_shared<SolidWall>(start, end, elevation, height, 120, Material::brick);
        case WallType::basic:
             return std::make_shared<Wall>(start, end, elevation, height);
        default: break;
        }
        return {};
    }
};

// int main() {
//     const auto also_partition = WallFactory::create_wall(WallType::partition, {0, 0}, {5000, 0}, 0, 4200);
//     if (also_partition)
//         std::cout << *std::dynamic_pointer_cast<SolidWall>(also_partition) << '\n';
//     return 0;
// }



class Wall1 {
    Point2D start;
    Point2D end;
    double elevation;
    double height;

protected:
    Wall1(const Point2D& start, const Point2D& end, double elevation, double height)
        : start{ start }, end{ end }, elevation{ elevation }, height{ height } {
    }

    friend class BasicWallFactory;

private:
    class BasicWallFactory {
        BasicWallFactory() = default;

    public:
        std::shared_ptr<Wall1> create(const Point2D& start, const Point2D& end, double elevation, double height) {
            auto wall = new Wall1{ start, end, elevation, height };
            return std::shared_ptr<Wall1>{ wall };
        }
    };

public:
    static BasicWallFactory factory;

public:
    friend std::ostream& operator<<(std::ostream& os, const Wall1& obj) {
        return os << "Wall1";
    }
};

int main() {
    auto basic = Wall1::factory.create({0, 0}, {5000, 0}, 0, 3000);
    std::cout << *basic << '\n';
    return 0;
}
