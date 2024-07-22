#include <fmt/format.h>
#include <stdexcept>
#include "Time.h"

// Time::Time(int hour/* = 0 */, int minute/* = 0 */, int second/* = 0 */) {
//     setTime(hour, minute, second);
// }
Time::Time() : Time{0, 0, 0} {

}

Time::Time(int hour) : Time{hour, 0, 0} {

}

Time::Time(int hour, int minute) : Time{hour, minute, 0} {

}

Time::Time(int hour, int minute, int second) {
    setTime(hour, minute, second);
}

void Time::setTime(int hour, int minute, int second) {
    if (hour < 0 || hour >= 24) {
        throw std::invalid_argument {"hour was out of range"};
    }

    if (minute < 0 || minute >= 60) {
        throw std::invalid_argument {"minute was out of range"};
    }

    if (second < 0 || second >= 60) {
        throw std::invalid_argument {"second was out of range"};
    }

    m_hour = hour;
    m_minute = minute;
    m_second = second;
}

void Time::setHour(int hour) {
    setTime(hour, m_minute, m_second);
}

void Time::setMinute(int minute) {
    setTime(m_hour, minute, m_second);
}

void Time::setSecond(int second) {
    setTime(m_hour, m_minute, second);
}

int& Time::badSetHour(int hour) {
    setTime(hour, m_minute, m_second);
    return m_hour;
}

int Time::getHour() const {
    return m_hour;
}

int Time::getMinute() const {
    return m_minute;
}

int Time::getSecond() const {
    return m_second;
}

std::string Time::to24HourString() const {
    return fmt::format("{:02d}:{:02d}:{:02d}", getHour(),
        getMinute(), getSecond());
}

std::string Time::to12HourString() const {
    return fmt::format("{}:{:02d}:{:02d} {}",
        ((getHour() % 12 == 0)? 12 : getHour() % 12),
        getMinute(), getSecond(), (getHour() < 12 ? "AM" : "PM"));
}