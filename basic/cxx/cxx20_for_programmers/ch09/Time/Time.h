#ifndef __TIME_H__
#define __TIME_H__

#include <string>

class Time {
public:
    // Time(int hour = 0, int minute = 0, int second = 0);
    Time();
    Time(int hour);
    Time(int hour, int minute);
    Time(int hour, int minute, int second);

    void setTime(int hour, int minute, int second);
    void setHour(int hour);
    void setMinute(int minute);
    void setSecond(int second);

    int& badSetHour(int hour);

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