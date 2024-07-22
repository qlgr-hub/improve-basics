#pragma once
#include <string>

class Date {
public:
    Date(int year, int month, int day);
    std::string toString() const;
private:
    int m_year;
    int m_month;
    int m_day;
};