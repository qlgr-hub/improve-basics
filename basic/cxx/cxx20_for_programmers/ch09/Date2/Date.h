#pragma once
#include <string>

class Date {
public:
    static const int mouthPerYear{12};
    Date(int year, int month, int day);
    std::string toString() const;
    ~Date();
private:
    int m_year;
    int m_month;
    int m_day;

    bool _checkDay(int day) const;
};