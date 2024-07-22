#include <fmt/format.h>
#include <iostream>
#include "CreateAndDestroy.h"

CreateAndDestroy::CreateAndDestroy(int ID, std::string_view messege)
    : m_ID{ID}, m_message{messege} {
    std::cout << fmt::format("Object {} constructor runs {}\n", m_ID, m_message);
}

CreateAndDestroy::~CreateAndDestroy() {
    std::cout << fmt::format("{}Object {} destructor runs {}\n", 
        (m_ID == 1 || m_ID == 6 ? "\n" : ""), m_ID, m_message);
}
