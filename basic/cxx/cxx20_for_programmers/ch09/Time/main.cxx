#include <fmt/format.h>
#include <iostream>
#include <stdexcept>
#include <string_view>
#include "Time.h"

void displayTime(std::string_view message, const Time& time) {
    std::cout << fmt::format("{}\n24-hour time: {}\n12-hour time: {}\n\n",
        message, time.to24HourString(), time.to12HourString());
}

int main() {
    const Time t1{};
    const Time t2{2};
    const Time t3{21, 34};
    const Time t4{12, 25, 42};

    std::cout << "Constructed with:\n\n";
    displayTime("t1: all arguments defaulted", t1);
    displayTime("t2: hour specified; minute and second defaulted", t2);
    displayTime("t3: hour and minute specified; second defaulted", t3);
    displayTime("t3: hour, minute and second specified", t4);

    try {
        const Time t5{27, 74, 99};
    }
    catch (const std::invalid_argument& e) {
        std::cout << fmt::format("t5 not created: {}\n", e.what());
    }

    Time t{};

    int& hourRef{t.badSetHour(20)};
    std::cout << fmt::format("Valid hour defore modification: {}\n", hourRef);
    hourRef = 30;
    std::cout << fmt::format("Invalid hour after modification: {}\n", hourRef);

    t.badSetHour(12) = 74;
    std::cout << "After using t.badSetHour(12) as an lvalue, "
        << fmt::format("hour is: {}\n", t.getHour());

    return 0;
}