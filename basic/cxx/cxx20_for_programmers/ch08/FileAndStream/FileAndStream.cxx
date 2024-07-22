#include <cstdlib>           
#include <fmt/format.h> 
#include <fstream>
#include <iostream>
#include <string>

// ios::app 追加
// ios::ate 追加?
// ios::in  读
// ios::out 写
// ios::trunc ios::out's default 覆盖
// ios::binary 二进制 读写
//
// seekg seek get istream  set i position
// seekp seek put ostream  set o position
// ios::beg
// ios::cur
// ios::end
// tellg tell get istream  get i position
// tellp tell put ostream  get o position
// std::istream::pos_type
// std::ostream::pos_type
//
// std::quoted 文本文件内容 中处理有引号的内容

// 写
// int main() {             
//     if (std::ofstream output{"clients.txt", std::ios::out}) {
//         std::cout << "Enter the account, name, and balance.\n"
//             << "Enter end-of-file to end input.\n? ";
//
//         int account;
//         std::string name;
//         double balance;
//
//         while (std::cin >> account >> name >> balance) {
//             output << fmt::format("{} {} {}\n", account, name, balance);
//             std::cout << "? ";
//         }
//     }
//     else {
//         std::cerr << "File could not be opened\n";
//         std::exit(EXIT_FAILURE);
//     }
//
//     return 0;
// }

// read
int main() {       
    if (std::ifstream input{"clients.txt", std::ios::in}) {
        std::cout << fmt::format("{:<10}{:<13}{:>7}\n",
            "Account", "Name", "Balance");

        int account;
        std::string name;
        double balance;

        while (input >> account >> name >> balance) {
            std::cout << fmt::format("{:<10}{:<13}{:>7.2f}\n",
            account, name, balance);
        }
    }
    else {
        std::cerr << "File could not be opened\n";
        std::exit(EXIT_FAILURE);
    }

    return 0;
}