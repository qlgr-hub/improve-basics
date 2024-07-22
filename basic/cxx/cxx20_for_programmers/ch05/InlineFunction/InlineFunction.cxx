#include <iostream> 

inline double cube(double side) {               
   return side * side * side;
}                                               

int main() {
   double sideValue;
   std::cout << "Enter the side length of your cube: ";
   std::cin >> sideValue;

   std::cout << "Volume of cube with side " 
      << sideValue << " is " << cube(sideValue) << '\n';
    return 0;
} 