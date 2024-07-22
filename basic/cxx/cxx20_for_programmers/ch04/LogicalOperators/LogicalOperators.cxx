#include <iostream>
#include <fmt/format.h>

int main() {
   std::cout << "Logical AND (&&)\n"
      << fmt::format("false && false: {}\n", false && false)
      << fmt::format("false && true: {}\n", false && true)
      << fmt::format("true && false: {}\n", true && false)
      << fmt::format("true && true: {}\n\n", true && true);

   std::cout << "Logical OR (||)\n"
      << fmt::format("false || false: {}\n", false || false)
      << fmt::format("false || true: {}\n", false || true)
      << fmt::format("true || false: {}\n", true || false)
      << fmt::format("true || true: {}\n\n", true || true);

   std::cout << "Logical negation (!)\n"
      << fmt::format("!false: {}\n", !false)
      << fmt::format("!true: {}\n", !true);
} 