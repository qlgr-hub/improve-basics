#include <fmt/format.h>
#include <iostream>
#include "Date.h"

int main() {
    const Date date1{2006, 7, 4};
    Date date2{2022, 1, 1};

    std::cout << fmt::format("date1: {}\ndate2: {}\n\n",
        date1.toString(), date2.toString());
    date2 = date1;
    std::cout << fmt::format("After assignment, date2: {}\n", date2.toString());

    return 0;
}