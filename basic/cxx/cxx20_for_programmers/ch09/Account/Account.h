#ifndef __ACCOUNT_H__
#define __ACCOUNT_H__

#include <algorithm>
#include <string>
#include <string_view>

class Account {
public:
    Account() {}

    explicit Account(std::string_view name)
        : m_name{name} {
        // empty body
    }

    void setName(std::string_view name) {
        m_name = name;
    }

    const std::string& getName() const {
        return m_name;
    }

private:
    std::string m_name;
};

class Account1 {
public:
    Account1(std::string_view name, double balance)
        : m_name{name}, m_balance{std::max(0.0, balance)} {
    }

    void deposit(double amount) {
        if (amount > 0.0) {
            m_balance += amount;
        }
    }

    double getBalance() const {
        return m_balance;
    }

    void setName(std::string_view name) {
        m_name = name;
    }

    const std::string& getName() const{
        return m_name;
    }
private:
    std::string m_name;
    double m_balance;
};

#endif // !__ACCOUNT_H__