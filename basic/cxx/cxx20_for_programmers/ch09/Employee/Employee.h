#pragma once
#include <string>
#include <string_view>

class Employee {
public:
    Employee(std::string_view firstName, std::string_view lastName);
    ~Employee();
    const std::string& getFirstName() const;
    const std::string& getLastName() const;

    static int getCount();
private:
    std::string m_firstName;
    std::string m_lastName;

    inline static int m_count{0}; 
};