#include <iostream>
#include <array>

constexpr size_t rows{2};
constexpr size_t columns{3};
void printArray(const std::array<std::array<int, columns>, rows>& a);

int main() {
   constexpr std::array values1{std::array{1, 2, 3}, std::array{4, 5, 6}};
   constexpr std::array values2{std::array{1, 2, 3}, std::array{4, 5, 0}};

   std::cout << "values1 by row:\n";
   printArray(values1);

   std::cout << "\nvalues2 by row:\n";
   printArray(values2);
}
            
void printArray(const std::array<std::array<int, columns>, rows>& a) {        
   for (const auto& row : a) {        
      for (const auto& element : row) {
         std::cout << element << ' ';
      }

      std::cout << '\n';         
   }
}