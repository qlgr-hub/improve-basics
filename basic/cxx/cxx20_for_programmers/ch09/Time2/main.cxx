#include <fmt/format.h>
#include <iostream>
#include <stdexcept>
#include <string_view>
#include "Time.h"

int main() {
    Time wakeUp{6, 45, 0};
    const Time noon{12, 0, 0};

    wakeUp.setHour(18);
    // noon.setHour(12); // 'this' argument to member function 'setHour' has type 'const Time', but function is not marked const
    wakeUp.getHour();
    noon.getMinute();
    noon.to24HourString();
    // noon.to12HourString(); // 'this' argument to member function 'to12HourString' has type 'const Time', but function is not marked const

    return 0;
}