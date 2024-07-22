#include <fmt/format.h>
#include <iostream>
#include <stdexcept>
#include <string_view>
#include "Time.h"

int main() {
    Time t{};

    t.setHour(18).setMinute(30).setSecond(22);

    std::cout << fmt::format("24-hour time: {}\n12-hour time: {}\n\n",
        t.to24HourString(), t.to12HourString());

    std::cout << fmt::format("New 12-hour time: {}\n",
        t.setTime(20, 20, 20).to12HourString());

    return 0;
}