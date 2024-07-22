#include <fmt/format.h>
#include "Date.h"

Date::Date(int year, int month, int day)
    : m_year{year}, m_month{month}, m_day{day} {
}

std::string Date::toString() const {
    return fmt::format("{}-{:02d}-{:02d}", m_year, m_month, m_day);
}
