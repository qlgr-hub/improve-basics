#pragma once
#include <string>
#include <string_view>

class Employee {
public:
    explicit Employee(std::string_view name);
    virtual ~Employee() = default;

    void setName(std::string_view name);
    std::string getName() const;

    double earnings() const;
    std::string toString() const;
protected:
    virtual std::string getString() const;
private:
    std::string m_name;

    virtual double getPay() const = 0;
};