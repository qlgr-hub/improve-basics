#include <fmt/format.h>
#include <iterator>
#include <iostream>
#include <string>
#include <string_view>
#include <algorithm>

class Employee {
public:
    Employee(std::string_view first, std::string_view last, int salary)
        : m_first{first}, m_last{last}, m_salary{salary} {}

    std::string getFirst() const {return m_first;}
    std::string getLast() const {return m_last;}
    int getSalary() const {return m_salary;}
private:
    std::string m_first;
    std::string m_last;
    // int m_salary;

public:
    int m_salary;
};

std::ostream& operator<<(std::ostream& out, const Employee& e) {
    out << fmt::format("{:10}{:10}{}", e.getLast(), e.getFirst(), e.getSalary());
    return out;
}

int main() {
    std::array employees{
        Employee{"Jason", "Red", 5000},
        Employee{"Ashley", "Green", 7600},
        Employee{"Matthew", "Indigo", 3587}
    };

    std::ostream_iterator<Employee> output{std::cout, "\n"};

    std::cout << "Employees:\n";
    std::ranges::copy(employees, output);

    std::ranges::sort(employees, {}, [](const auto& e) {return e.getSalary();});
    std::cout << "\nEmployees sorted in ascending order by salary:\n";
    std::ranges::copy(employees, output);

    std::ranges::sort(employees, std::ranges::greater{}, &Employee::getSalary);
    std::cout << "\nEmployees sorted in descending order by salary:\n";
    std::ranges::copy(employees, output);

    std::ranges::sort(employees, std::ranges::greater{}, &Employee::m_salary);
    std::cout << "\nEmployees sorted in descending order by salary:\n";
    std::ranges::copy(employees, output);
    return 0;
}