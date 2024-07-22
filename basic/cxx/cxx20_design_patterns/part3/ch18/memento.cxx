#include <iostream>
#include <memory>
#include <ostream>
#include <vector>
// #include <boost/circular_buffer.hpp>


class Memento final {
    int balance;

public:
    Memento(int balance) : balance{ balance } {
    }

    friend class BankAccount;
    friend class BankAccount2;
};


class BankAccount {
    /* const */ int balance{ 0 };

public:
    explicit BankAccount(int balance) : balance{ balance } {
    }

    Memento deposit(int amount) {
        balance += amount;
        return balance;
    }

    void restore(const Memento& m) {
        balance = m.balance;
    }
};


class BankAccount2 {
    int balance{ 0 };
    std::vector<std::shared_ptr<Memento>> changes;
    
    // This solution can be considered if memory is insufficient.
    // boost::circular_buffer<std::shared_ptr<Memento>> changes{ 5 };
    
    int current;

public:
    explicit BankAccount2(int balance) : balance{ balance } {
        changes.emplace_back(std::make_shared<Memento>(balance));
        current = 0;
    }

    std::shared_ptr<Memento> deposit(int amount) {
        balance += amount;
        auto m{ std::make_shared<Memento>(balance) };
        changes.push_back(m);
        ++current;
        return m;
    }

    void restore(const std::shared_ptr<Memento>& m) {
        if (m) {
            balance = m->balance;
            changes.push_back(m);
            current = changes.size() - 1;
        }
    }

    std::shared_ptr<Memento> undo() {
        if (current > 0) {
            --current;
            auto m{ changes[current] };
            balance = m->balance;
            return m;
        }
        return {};
    }

    std::shared_ptr<Memento> redo() {
        if (current + 1 < changes.size()) {
            ++current;
            auto m{ changes[current] };
            balance = m->balance;
            return m;
        }
        return {};
    }

    friend std::ostream& operator<<(std::ostream& os, const BankAccount2& obj) {
        return os << "balance: " << obj.balance;
    }
};

int main() {
    BankAccount2 ba{ 100 };
    ba.deposit(50);
    ba.deposit(25);
    std::cout << ba << '\n';

    ba.undo();
    std::cout << "Undo1: " << ba << '\n';
    ba.undo();
    std::cout << "Undo2: " << ba << '\n';
    ba.redo();
    std::cout << "Redo2: " << ba << '\n';
    ba.undo();
    std::cout << "Undo2 again: " << ba << '\n';

    return 0;
}