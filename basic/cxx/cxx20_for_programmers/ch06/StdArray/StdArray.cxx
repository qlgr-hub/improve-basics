#include <fmt/format.h>
#include <iostream>
#include <array>

int main() {
   std::array<int, 5> values;
     
   for (size_t i{0}; i < values.size(); ++i) {
      values[i] = 0;
   }

   std::cout << fmt::format("{:>7}{:>10}\n", "Element", "Value");

   for (size_t i{0}; i < values.size(); ++i) {
      std::cout << fmt::format("{:>7}{:>10}\n", i, values[i]);
   }

   std::cout << fmt::format("\n{:>7}{:>10}\n", "Element", "Value");

   for (size_t i{0}; i < values.size(); ++i) {
      std::cout << fmt::format("{:>7}{:>10}\n", i, values.at(i));
   }

   values.at(10);
   return 0;
}