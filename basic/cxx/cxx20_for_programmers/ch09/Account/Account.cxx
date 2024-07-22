#include <fmt/format.h>
#include <iostream>
#include <string>
#include "Account.h"

int main() {
    Account myAccount;

    std::cout << fmt::format("Initial account name: {}\n", myAccount.getName());

    std::cout << "Enter the account name: ";
    std::string name{};
    std::getline(std::cin, name);
    myAccount.setName(name);

    std::cout << fmt::format("Updated account name: {}\n", myAccount.getName());

    Account account1{"Jane Green"};
    Account account2{"John Blue"};

    std::cout << fmt::format("account1 name is: {}\naccount2 name is: {}\n",
        account1.getName(), account2.getName());

    Account1 account1_1{"Jane Green", 50.00};
    Account1 account1_2{"John Blue", -7.00};

    std::cout << fmt::format("account1: {} balance is: ${:.2f}\n",
        account1_1.getName(), account1_1.getBalance());
    
    std::cout << fmt::format("account2: {} balance is: ${:.2f}\n",
        account1_2.getName(), account1_2.getBalance());

    std::cout << "Enter deposit amount for account1: ";
    double amount;
    std::cin >> amount;
    std::cout << fmt::format("adding ${:.2f} to account1 balance\n\n", amount);
    account1_1.deposit(amount);

    std::cout << fmt::format("account1: {} balance is: ${:.2f}\n",
        account1_1.getName(), account1_1.getBalance());
    
    std::cout << fmt::format("account2: {} balance is: ${:.2f}\n",
        account1_2.getName(), account1_2.getBalance());

    std::cout << "Enter deposit amount for account2: ";
    std::cin >> amount;
    std::cout << fmt::format("adding ${:.2f} to account2 balance\n\n", amount);
    account1_2.deposit(amount);

    std::cout << fmt::format("account1: {} balance is: ${:.2f}\n",
        account1_1.getName(), account1_1.getBalance());
    
    std::cout << fmt::format("account2: {} balance is: ${:.2f}\n",
        account1_2.getName(), account1_2.getBalance());

    return 0;
}