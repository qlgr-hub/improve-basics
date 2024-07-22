#include "cipher.h"
#include <iostream>
#include <string>

int main() {
    std::string plainText;
    std::cout << "Enter the text to encrypt:\n";
    getline(std::cin, plainText);

    std::string secretKey;
    std::cout << "\nEnter the secret key:\n";
    getline(std::cin, secretKey);

    Cipher cipher; 

    std::string cipherText{cipher.encrypt(plainText, secretKey)};
    std::cout << "\nEncrypted:\n   " << cipherText << '\n';

    std::cout << "\nDecrypted:\n   "  
        << cipher.decrypt(cipherText, secretKey) << '\n';

    std::cout << "\nEnter the ciphertext to decipher:\n";
    getline(std::cin, cipherText);
    std::cout << "\nDecrypted:\n   " 
        << cipher.decrypt(cipherText, secretKey) << '\n';

    return 0;
}