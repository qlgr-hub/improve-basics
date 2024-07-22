
#include <iostream>
#include <memory>
#include <ostream>
#include <string_view>
#include <boost/di.hpp>
// #include <string_view>


// struct ILogger {
//     virtual void log_info(std::string_view info) const = 0;
// };
//
// class Reporting {
//     const ILogger& logger;
//
// public:
//     Reporting(const ILogger& logger) : logger{ logger } {
//     }
//
//     void prepare_report() {
//         logger.log_info("Preparing the report");
//     }
// };


struct Engine {
    float valume { 5 };
    int hourse_power{ 400 };

    friend std::ostream& operator<<(std::ostream& os, const Engine& obj) {
        return os << "volume: " << obj.valume << " hourse power: " << obj.hourse_power;
    }
};


struct ILogger {
    virtual ~ILogger() {}
    virtual void log(std::string_view s) = 0;
};


struct ConsoleLogger : ILogger {
    ConsoleLogger() {}

    void log(std::string_view s) override {
        std::cout << "LOG: " << s << '\n';
    }
};


struct Car {
    std::unique_ptr<Engine> engine;
    std::shared_ptr<ILogger> logger;

    Car(std::unique_ptr<Engine> e, const std::shared_ptr<ILogger>& logger)
        : engine{ std::move(e) }, logger{ logger } {
    }

    friend std::ostream& operator<<(std::ostream& os, const Car& obj) {
        return os << "car with engine: " << *obj.engine;
    }
};

int main() {
    auto injector = boost::di::make_injector(boost::di::bind<ILogger>().to<ConsoleLogger>());
    auto car = injector.create<std::shared_ptr<Car>>();
    return 0;
}