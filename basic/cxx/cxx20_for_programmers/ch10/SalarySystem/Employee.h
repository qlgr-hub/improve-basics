#pragma once
#include <string>
#include <string_view>

class Employee {
public:
    explicit Employee(std::string_view name);
    virtual ~Employee() = default;

    void setName(std::string_view name);
    std::string getName() const;

    virtual double earnings() const = 0;
    virtual std::string toString() const;

private:
    std::string m_name;
};