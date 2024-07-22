#ifndef __TIME_H__
#define __TIME_H__

#include <string>

class Time {
public:
    Time(int hour = 0, int minute = 0, int second = 0);

    Time& setTime(int hour, int minute, int second);
    Time& setHour(int hour);
    Time& setMinute(int minute);
    Time& setSecond(int second);

    int getHour() const;
    int getMinute() const;
    int getSecond() const;
    
    std::string to24HourString() const;
    std::string to12HourString() const;
private:
    int m_hour{0};
    int m_minute{0};
    int m_second{0};
};

#endif // !__TIME_H__