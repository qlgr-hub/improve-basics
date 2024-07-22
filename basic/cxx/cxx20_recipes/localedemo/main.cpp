#include <iomanip>
#include <iterator>
#include <string>
#include <iostream>

using namespace std;

int main()
{
    float dollar = 12345;
    cout.precision(2);
    
    cout.imbue(locale("en_US.UTF-8"));
    cout << "American locale: " << put_money(dollar) << endl;

    cout.imbue(locale("fr_FR.UTF-8"));
    wcout << "French locale: " << put_money(dollar) << endl; 

    cout.imbue(locale("de_DE.UTF-8"));
    wcout << "German locale: " << put_money(dollar) << endl; 

    cout.imbue(locale("ru_RU.UTF-8"));
    cout << "Russion locale: " << endl; 
    string alpha = "abcdefg";
    for (char letter : alpha)
        wcout << letter << endl;

    cout.imbue(locale(""));
    cout << "Default locale: " << put_money(dollar) << endl; 

    return 0;
}