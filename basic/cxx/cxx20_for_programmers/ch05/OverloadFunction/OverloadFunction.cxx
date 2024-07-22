#include <iostream>

int square(int x) {                            
   std::cout << "square of integer " << x << " is ";
   return x * x;                               
} 
         
double square(double y) {                     
   std::cout << "square of double " << y << " is "; 
   return y * y;                               
} 

int main() {
   std::cout << square(7);
   std::cout << '\n';
   std::cout << square(7.5);
   std::cout << '\n';
   return 0;
} 