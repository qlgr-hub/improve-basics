#include <iostream>

int main() {
    if (int value{7}; value == 7) {
      std::cout << "value is " << value << "\n";
   }
   else {
      std::cout << "value is not 7; it is " << value << "\n";
   }

   if (int value{13}; value == 9) {
      std::cout << "value is " << value << "\n";
   }
   else {
      std::cout << "value is not 9; it is " << value << "\n";
   }

   return 0;
}