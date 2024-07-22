#pragma once
#include <string>
#include <string_view>
#include "Date.h"

class Employee {
public:
    Employee(std::string_view firstName, std::string_view lastName,
        const Date& birthDate, const Date& hireDate);
    std::string toString() const;
    ~Employee();
private:
    std::string m_firstName;
    std::string m_lastName;
    Date m_birthDate;
    Date m_hireDate;
};