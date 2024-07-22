#include <fmt/format.h>
#include <iostream>
#include "SalariedCommissionEmployee.h"
#include "SalariedEmployee.h"

int main() {
    // 1. SalariedEmployee
    // SalariedEmployee employee{"Sue Jones", 300.0};
    //
    // std::cout << "Employee information obtained by get function:\n"
    //     << fmt::format("name: {}\nsalary: ${:.2f}\n", employee.getName(),
    //     employee.getSalary());
    //
    // employee.setSalary(500.0);
    // std::cout << "\nUpdated employee information from function toString:\n"
    //     << employee.toString();
    //
    // std::cout << fmt::format("\nearnings: ${:.2f}\n", employee.earnings());
    //
    //
    // 2. SalariedCommissionEmployee
    // SalariedCommissionEmployee employee{"Bob Lewis", 300.0, 5000.0, .04};
    //
    // std::cout << "Employee information obtained by get function:\n"
    //     << fmt::format("{}: {}\n{}: ${:.2f}\n{}: {:.2f}\n{}: {:.2f}", 
    //     "name", employee.getName(), "salary", employee.getSalary(),
    //     "grossSales", employee.getGrossSales(), "commissionRate", employee.getCommissionRate());
    //
    // employee.setGrossSales(8000.0);
    // employee.setCommissionRate(0.1);
    // std::cout << "\nUpdated employee information from function toString:\n"
    //     << employee.toString();
    //
    // std::cout << fmt::format("\nearnings: ${:.2f}\n", employee.earnings());
    //
    //
    // 3. pointers
    // SalariedEmployee salaried{"Sue Jones", 500.0};
    // SalariedCommissionEmployee salariedCommission{
    //    "Bob Lewis", 300.0, 5000.0, .04};
    //
    // std::cout << fmt::format("{}:\n{}\n{}\n",
    //     "DISPLAY BASE-CLASS AND DERIVED-CLASS OBJECTS",
    //     salaried.toString(), salariedCommission.toString());
    //
    // SalariedEmployee* salariedPtr{&salaried};
    // std::cout << fmt::format("{}\n{}:\n{}\n",
    //     "CALLING TOSTRING WITH BASE-CLASS POINTER TO",
    //     "BASE-CLASS OBJECT INVOKES BASE-CLASS FUNCTIONALITY",
    //     salariedPtr->toString());
    //
    // SalariedCommissionEmployee* salariedCommissionPtr{&salariedCommission};
    // std::cout << fmt::format("{}\n{}:\n{}\n",
    //     "CALLING TOSTRING WITH DERIVED-CLASS POINTER TO",
    //     "DERIVED-CLASS OBJECT INVOKES DERIVED-CLASS FUNCTIONALITY",
    //     salariedCommissionPtr->toString());
    //
    // salariedPtr = &salariedCommission;
    // std::cout << fmt::format("{}\n{}:\n{}\n",
    //     "CALLING TOSTRING WITH BASE-CLASS POINTER TO DERIVED-CLASS",
    //     "OBJECT INVOKES BASE-CLASS FUNCTIONALITY",
    //     salariedPtr->toString());
    //
    // SalariedEmployee salaried{"Sue Jones", 500.0};
    // SalariedCommissionEmployee* salariedCommissionPtr{&salaried}; // error: cannot initialize a variable of type 'SalariedCommissionEmployee *' with an rvalue of type 'SalariedEmployee *'
    //
    //SalariedCommissionEmployee salariedCommission{
    //    "Bob Lewis", 300.0, 5000.0, .04};
    //SalariedEmployee* salariedPtr{&salariedCommission};
    //
    //std::string name{salariedPtr->getName()};
    //double salary{salariedPtr->getSalary()};
    //
    //double grossSales{salariedPtr->getGrossSales()}; // error: no member named 'getGrossSales' in 'SalariedEmployee' double grossSales{salariedPtr->getGrossSales()};
    //double commissionRate{salariedPtr->getCommissionRate()}; // error: no member named 'getCommissionRate' in 'SalariedEmployee' double commissionRate{salariedPtr->getCommissionRate()};
    //salariedPtr->setGrossSales(8000.0); // error: no member named 'setGrossSales' in 'SalariedEmployee' salariedPtr->setGrossSales(8000.0);
    //
    //
    // 4. 
    SalariedEmployee salaried{"Sue Jones", 500.0};
    SalariedCommissionEmployee salariedCommission{
       "Bob Lewis", 300.0, 5000.0, .04};
    
    std::cout << fmt::format("{}\n{}:\n{}\n{}\n",
        "INVOKING TOSTRING FUNCTION ON BASE-CLASS AND",
        "DERIVED-CLASS OBJECTS WITH STATIC BINDING",
        salaried.toString(), salariedCommission.toString());

    std::cout << "INVOKING TOSTRING FUNCTION ON BASE-CLASS AND\n"
        << "DERIVED-CLASS OBJECTS WITH DYNAMIC BINDING\n\n";
    
    SalariedEmployee* salariedPtr{&salaried};
    std::cout << fmt::format("{}\n{}:\n{}\n",
        "CALLING VIRTUL FUNCTION TOSTRING WITH BASE-CLASS POINTER",
        "TO BASE-CLASS OBJECT INVOKES BASE-CLASS FUNCTIONALITY",
        salariedPtr->toString());
    
    SalariedCommissionEmployee* salariedCommissionPtr{&salariedCommission};
    std::cout << fmt::format("{}\n{}:\n{}\n",
        "CALLING VIRTUL FUNCTION TOSTRING WITH DERIVED-CLASS POINTER",
        "TO DERIVED-CLASS OBJECT INVOKES DERIVED-CLASS FUNCTIONALITY",
        salariedCommissionPtr->toString());
    
    salariedPtr = &salariedCommission;
    std::cout << fmt::format("{}\n{}:\n{}\n",
        "CALLING VIRTUL FUNCTION TOSTRING WITH BASE-CLASS POINTER",
        "TO DERIVED-CLASS OBJECT INVOKES DERIVED-CLASS FUNCTIONALITY",
        salariedPtr->toString());

    return 0;
}