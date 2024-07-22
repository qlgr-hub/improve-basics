#include <fmt/format.h>
#include <iostream>
#include <random> 

// enum class
// enum class Status {keepRolling, won, lost};
// 直接使用则: Status:: 前缀限定
//
// 也可以 定义完 enum class 后加
// using enum Status 后续就可以不用加 Status:: 前缀限定
// 
// enum class Status : short {keepRolling, won, lost}; 指定实际类型
int rollDice();

int main() {
   enum class Status {keepRolling, won, lost};   
   
   int myPoint{0};
   Status gameStatus{Status::keepRolling};

   switch (const int sumOfDice{rollDice()}) {
      case 7:
      case 11:           
         gameStatus = Status::won;
         break;
      case 2:
      case 3:
      case 12:            
         gameStatus = Status::lost;
         break;
      default:
         myPoint = sumOfDice;
         std::cout << fmt::format("Point is {}\n", myPoint);
         break; 
   }

   while (Status::keepRolling == gameStatus) {
      if (const int sumOfDice{rollDice()}; sumOfDice == myPoint) {
         gameStatus = Status::won;
      }
      else if (sumOfDice == 7) {
         gameStatus = Status::lost;
      }
   }

   if (Status::won == gameStatus) {
      std::cout << "Player wins\n";
   }
   else {
      std::cout << "Player loses\n";
   }
}

int rollDice() {
   static std::random_device rd;
   static std::default_random_engine engine{rd()};
   static std::uniform_int_distribution randomDie{1, 6};

   const int die1{randomDie(engine)};
   const int die2{randomDie(engine)};
   const int sum{die1 + die2};

   std::cout << fmt::format("Player rolled {} + {} = {}\n", die1, die2, sum);

   return sum;
}