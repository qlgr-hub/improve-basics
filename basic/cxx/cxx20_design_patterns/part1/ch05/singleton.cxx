// #include <boost/atomic.hpp>
// #include <boost/memory_order.hpp>
// #include <boost/thread/mutex.hpp>
// #include <boost/thread/pthread/mutex.hpp>
// #include <cstdint>
// #include <stdexcept>
#include <functional>
#include <map>
#include <memory>
#include <optional>
#include <stack>
#include <string>
#include <string_view>
#include <sys/stat.h>
#include <thread>
#include <vector>
#include <gtest/gtest.h>
#include <boost/di.hpp>


struct Database {
    Database(const Database&) = delete;
    Database(Database&&) = delete;
    Database& operator=(const Database&) = delete;
    Database& operator=(Database&&) = delete;

protected:
    Database() = default;

public:
    static Database& get() {
        // thread sage since c++11
        static Database database;
        return database;
    }


// 1. Thread-safe singleton implementation before C++11 (double checked locking)
// private:
//     static boost::atomic<Database*> inst;
//     static boost::mutex mtx;
//
//     static Database& instance() {
//         Database* db = inst.load(boost::memory_order_consume);
//         if (!db) {
//             boost::mutex::scoped_lock lock(mtx);
//             db = inst.load(boost::memory_order_consume);
//             if (!db) {
//                 db = new Database();
//                 inst.store(db, boost::memory_order_release);
//             }
//         }
//         return *db;
//     }
//
//
// 2. bad idea
//     Database() {
//         static int instance_count{ 0 };
//         if (++instance_count > 1)
//             throw std::runtime_error("Cannot make >1 database!");
//     }
//
//
// 3. new object version
//     static Database* get() {
//         static Database* database = new Database{};
//         return database;
//     }
// private:
//     ~Database();
};


struct IDatabase {
    virtual int get_population(const std::string& name) = 0;
};


class SingletonDatabase : public IDatabase {
    // Prevents objects from being created by copying or construction.
    SingletonDatabase(const SingletonDatabase&) = delete;
    SingletonDatabase(SingletonDatabase&&) = delete;
    SingletonDatabase& operator=(const SingletonDatabase&) = delete;
    SingletonDatabase& operator=(SingletonDatabase&&) = delete;
    SingletonDatabase() = default;
    
private:
    std::map<std::string, int> capitals;

public:
    static SingletonDatabase& get() {
        static SingletonDatabase db;
        return db;
    }

    int get_population(const std::string& name) override {
        return capitals[name];
    }
};


struct SingletonRecordFinder {
    int total_population(const std::vector<std::string>& names) {
        int result{ 0 };
        for (const auto& name : names)
            result += SingletonDatabase::get().get_population(name);
        return result;
    }
};


// bad idea, because SingletonRecordFinder depends on a singlton object
TEST(RecordFinderTests, SingletonRecordFinderTest) {
    SingletonRecordFinder rf;
    std::vector<std::string> names{ "Seoul", "Mexico City" };
    int tp = rf.total_population(names);
    EXPECT_EQ(17500000 + 17400000, tp);
}


struct ConfigurableRecordFinder {
    IDatabase& db;

    explicit ConfigurableRecordFinder(IDatabase& db) 
        : db{ db } {
    }

    int total_population(const std::vector<std::string>& names) {
        int result{ 0 };
        for (const auto& name : names)
            result += db.get_population(name);
        return result;
    }
};


class DummyDatabase : public IDatabase {
    std::map<std::string, int> capitals;

public:
    DummyDatabase() {
        capitals["alpha"] = 1;
        capitals["beta"] = 2;
        capitals["gamma"] = 3;
    }

    int get_population(const std::string& name) override {
        return capitals[name];
    }
};

TEST(RecordFinderTests, DummyTotalPopulationTest) {
    DummyDatabase db{};
    ConfigurableRecordFinder rf{ db };
    EXPECT_EQ(4, rf.total_population(std::vector<std::string>{ "alpha", "gamma" }));
}


class PerThreadSingleton {
    PerThreadSingleton() {
        id = std::this_thread::get_id();
    }

public:
    std::thread::id id;

    static PerThreadSingleton& get() {
        thread_local PerThreadSingleton instance;
        return instance;
    }
};

int main1() {
    std::thread t1{
        []() {
            std::cout << "t1: " << PerThreadSingleton::get().id << '\n';
        }
    };

    std::thread t2{
        []() {
            std::cout << "t2: " << PerThreadSingleton::get().id << '\n';
            std::cout << "t2 again: " << PerThreadSingleton::get().id << '\n';
        }
    };

    t1.join();
    t2.join();

    return 0;
}


class BuildingContext final {
    int height{ 0 };
    BuildingContext() = default;

    static std::stack<BuildingContext> stack;


public:
    int get_height() const {
        return height;
    }

    struct Token {
        ~Token() {
            if (stack.size() > 1)
                stack.pop();
        }
    };

    // version 1
    static Token with_height(int height) {
        auto copy{ current() };
        copy.height = height;
        stack.push(copy);
        return Token{};
    }

    static BuildingContext current() {
        return stack.top();
    }

    // version 2
    static void with_height(int height, std::function<void()> action) {
        auto copy = current();
        copy.height = height;
        stack.push(copy);
        action();
        stack.pop();
    }

};
std::stack<BuildingContext> BuildingContext::stack{ {BuildingContext{}} };


struct Point2D {
    double x;
    double y;
};

class Wall {
    Point2D start;
    Point2D end;
    int height;

public:
    Wall(const Point2D& start, const Point2D& end, std::optional<int> height = std::nullopt)
        : start{ start }, end{ end } {
        this->height = height.value_or(
            BuildingContext::current().get_height()
        );
    }
};


struct Building {
    std::vector<Wall> walls;
};


int main2() {
    Building house{};

    // set default wall height to 3000 
    auto _ = BuildingContext::with_height(3000);

    house.walls.emplace_back(Wall{ {0, 0}, {5000, 0} });
    house.walls.emplace_back(Wall{ {0, 0}, {0, 4000} });

    // temproarily set wall height to 3500
    {
        auto _ = BuildingContext::with_height(3500);
        house.walls.emplace_back(Wall{ {5000, 0}, {7000, 0} });
    }

    // uses default wall height 3000 again
    house.walls.emplace_back(Wall{ {0, 4000}, {3000, 4000} });

    // overrides to use wall height of 4000
    house.walls.emplace_back(Wall{ {0, 4000}, {3000, 4000}, 4000 });

    // override to use wall height of 4000 with with_height veriosn 2 (not thread safe)
    BuildingContext::with_height(4000, [&]() {
        house.walls.emplace_back(Wall{ {0, 0}, {5000, 5000} });
    });

    return 0;
}



struct IFoo {
    virtual void somefunc() = 0;
};

struct Foo : public IFoo {
    static int id;

    Foo() {
        ++id;
    }

    void somefunc() override {
        std::cout << "Foo::somefunc(), id: " << id << '\n';
    }
};
int Foo::id = 0;

int main() {
    auto injector{ 
        boost::di::make_injector(boost::di::bind<IFoo>().to<Foo>().in(boost::di::singleton))
    };

    auto foo{ injector.create<std::shared_ptr<IFoo>>() };
    foo->somefunc(); // output: Foo::somefunc(), id: 1

    auto foo1{ injector.create<std::shared_ptr<IFoo>>() };
    foo1->somefunc(); // output: Foo::somefunc(), id: 1

    return 0;
}



// Monostate (单态模式)
class Printer {
    static int id;

public:
    int get_id() const { return id; };
    void set_id(int value) { id = value; }
};
