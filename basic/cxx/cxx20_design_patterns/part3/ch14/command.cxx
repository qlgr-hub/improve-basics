#include <initializer_list>
#include <iostream>
#include <memory>
#include <vector>


struct BankAccount {
    int balance{ 0 };
    int overdraft_limit{ -500 };

    void deposit(int amount) {
        balance += amount;
        std::cout << "deposited " << amount << ", balance is now " << balance << '\n';
    }

    bool withdraw(int amount) {
        if (balance - amount >= overdraft_limit) {
            balance -= amount;
            std::cout << "withdraw " << amount << ", balance is now " << balance << '\n';
            return true;
        }
        return false;
    }
};


struct Command {
    bool succeeded{ false };

    // virtual void call() const = 0;
    virtual void call() = 0;
    virtual void undo() = 0;
};

struct BankAccountCommand final : Command {
    BankAccount& account;
    enum Action{ deposit, withdraw } action;
    int amount;

    BankAccountCommand(BankAccount& account, Action action, int amount) 
        : account{ account }, action{ action }, amount{ amount } {
    }

    void call() /* const */ override {
        switch (action) {
        case deposit: account.deposit(amount); break;
        case withdraw: succeeded = account.withdraw(amount); break;
        default: break;
        }
    }

    void undo() override {
        switch (action) {
        case withdraw: if (succeeded) { account.deposit(amount); } break;
        case deposit: account.withdraw(amount); break;
        default: break;
        }
    }
};


struct CompositeBankAccountCommand : std::vector<BankAccountCommand>, Command {
    CompositeBankAccountCommand(const std::initializer_list<value_type>& items) 
        : std::vector<BankAccountCommand>{ items } {
    }

    void call() override {
        bool ok{ true };
        for (auto& cmd : *this) {
            if (ok) {
                cmd.call();
                ok = cmd.succeeded;
            }
            else {
                cmd.succeeded = false;
            }
        }
            
    }

    void undo() override {
        for (auto it{ rbegin() }; it != rend(); ++it)
            it->undo();
    }
};


struct MoneyTransferCommand : CompositeBankAccountCommand {
    MoneyTransferCommand(BankAccount& from, BankAccount& to, int amount) 
        : CompositeBankAccountCommand{
            BankAccountCommand{ from, BankAccountCommand::withdraw, amount},
            BankAccountCommand{ to, BankAccountCommand::deposit, amount }
        } {
        // constructor body
    }
};


int main1() {
    BankAccount ba;
    std::shared_ptr<Command> cmd{ std::make_shared<BankAccountCommand>(ba, BankAccountCommand::deposit, 100) };
    // Command cmd{ ba, BankAccountCommand::deposit, 100 };
    cmd->call();
    return 0;
}



/////////////////////////////// CQS (Command Query Separation) ///////////////////////////////////////////////
enum class CreatureAbility { strength, agility };

struct CreatureCommand {
    enum Action { set, increaseBy, decreaseBy } action;
    CreatureAbility ability;
    int amount;
};

struct CreatureQuery {
    CreatureAbility ability;
};

class Creature {
    int strength;
    int agility;

public:
    Creature(int strength, int agility) 
        : strength{ strength }, agility{ agility } {
    }

    void process_command(const CreatureCommand& cc) {
        int *ability{ nullptr };
        switch (cc.ability) {
        case CreatureAbility::strength:
            ability = &strength;
            break;
        
        case CreatureAbility::agility:
            ability = &agility;
            break;

        default: break;
        }

        switch (cc.action) {
        case CreatureCommand::set:
            *ability = cc.amount;
            break;

        case CreatureCommand::increaseBy:
            *ability += cc.amount;
            break;

        case CreatureCommand::decreaseBy:
            *ability -= cc.amount;
            break;

        default: break;
        }
    }

    int process_query(const CreatureQuery& q) const {
        switch (q.ability) {
        case CreatureAbility::strength: return strength;
        case CreatureAbility::agility: return agility;
        default: break;
        }
        return 0;
    }

    void set_strength(int value) {
        process_command(CreatureCommand{ CreatureCommand::set, CreatureAbility::strength, value});
    }

    int get_strength() const {
        return process_query(CreatureQuery{ CreatureAbility::strength });
    }

    void set_agility(int value) {
        process_command(CreatureCommand{ CreatureCommand::set, CreatureAbility::agility, value});
    }

    int get_agility() const {
        return process_query(CreatureQuery{ CreatureAbility::agility });
    }
};