#include <cctype>
#include <fmt/format.h>
#include <array>
#include <iostream>
#include <stdexcept>
#include "Date.h"

Date::Date(int year, int month, int day)
    : m_year{year}, m_month{month}, m_day{day} {
    if (month < 1 || month > mouthPerYear) {
        throw std::invalid_argument{"month must be 1-12"};
    }

    if (!_checkDay(day)) {
        throw std::invalid_argument{
            "Invalid day for current month and year"};
    }

    std::cout << fmt::format("Date object constructor: {}\n", toString());
}

std::string Date::toString() const {
    return fmt::format("{}-{:02d}-{:02d}", m_year, m_month, m_day);
}

Date::~Date() {
    std::cout << fmt::format("Date object destructor: {}\n", toString());
}

bool Date::_checkDay(int day) const {
    static const std::array daysPerMonth {
        0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31
    };

    if (1 <= day && day <= daysPerMonth.at(m_month)) {
        return true;
    }

    if (m_month == 2 && day == 29 && (m_year % 400 == 0 ||
        (m_year % 4 == 0 && m_year % 100 != 0))) {
        return true;
    }

    return false;
}
