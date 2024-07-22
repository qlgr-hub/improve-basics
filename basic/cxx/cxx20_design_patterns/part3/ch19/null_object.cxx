#include <iostream>
#include <memory>
#include <string>
#include <string_view>


struct Logger {
    virtual ~Logger() = default;
    virtual void info(std::string_view s) = 0;
    virtual void warn(std::string_view s) = 0;
};


class BankAccount {
    std::shared_ptr<Logger> log;

public:
    std::string name;
    int balance{ 0 };

    BankAccount(const std::shared_ptr<Logger>& logger, std::string_view name, int balance) 
        : log{ logger }, name{ name }, balance{ balance } {
    }

    void deposit(int amount) {
        balance += amount;
        log->info("Deposited $" + std::to_string(amount) + " to " + name + ", balance is now $" + std::to_string(balance));
    }
};


struct CosoleLogger : Logger {
    void info(std::string_view s) override {
        std::cout << s << '\n';
    }

    void warn(std::string_view s) override {
        std::cout << "WARNING!!! " << s << '\n';
    }
};


struct NullLogger : Logger {
    void info(std::string_view s) override {
    }
    
    void warn(std::string_view s) override {
    }
};


struct OptionalLogger : Logger {

    // On the surface it is Pimpl pattern, 
    // but in reality it is virtual proxy pattern.
    std::shared_ptr<Logger> impl;
    
    static std::shared_ptr<Logger> no_logging;

    OptionalLogger(const std::shared_ptr<Logger>& logger) : impl{ logger } {
    }

    void info(std::string_view s) override {
        if (impl)
            impl->info(s);
    }

    void warn(std::string_view s) override {
        if (impl)
            impl->warn(s);
    }
};
std::shared_ptr<Logger> OptionalLogger::no_logging{};


class BankAccount2 {
    std::shared_ptr<Logger> log;

public:
    std::string name;
    int balance{ 0 };

    BankAccount2(std::string_view name, int balance, 
        const std::shared_ptr<Logger>& logger = OptionalLogger::no_logging) 
        : log{ logger }, name{ name }, balance{ balance } {
    }

    void deposit(int amount) {
        balance += amount;
        log->info("Deposited $" + std::to_string(amount) + " to " + name + ", balance is now $" + std::to_string(balance));
    }
};

int main() {
    BankAccount2 account{ "primary account", 1000 };
    account.deposit(2000);
    return 0;
}

// Cooperation with other patterns.
// 1. virtual proxy: As shown in this example.
// 2. strategy: null strategy
// 3. visitor: null visitable object
// 4. state: null state
