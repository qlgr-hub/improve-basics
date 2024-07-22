#include <iostream>
#include <cinttypes>

int main()
{
    /* int */ int32_t wholeNumber1 = 64;
    std::cout << "wholeNumber1 equals " << wholeNumber1 << std::endl;

    /* int */ int32_t wholeNumber2 = ( wholeNumber1 + 32 );
    std::cout << "wholeNumber2 equals " << wholeNumber2 << std::endl;

    /* int */ int32_t wholeNumber3 = ( wholeNumber2 - wholeNumber1 );
    std::cout << "wholeNumber3 equals " << wholeNumber3 << std::endl;

    /* int */ int32_t wholeNumber4 = ( wholeNumber2 * wholeNumber1 );
    std::cout << "wholeNumber4 equals " << wholeNumber4 << std::endl;

    /* int */ int32_t wholeNumber5 = ( wholeNumber4 / wholeNumber1 );
    std::cout << "wholeNumber5 equals " << wholeNumber5 << std::endl;

    /* int */ int32_t wholeNumber6 = ( wholeNumber4 % wholeNumber1 );
    std::cout << "wholeNumber6 equals " << wholeNumber6 << std::endl;



    int equal1 = 10;
    int equal2 = 10;
    bool isEqual = (equal1 != equal2); //(equal1 == equal2);
    std::cout << "Are the numbers equal? " << isEqual << std::endl;

    int notEqual1 = 10;
    int notEqual2 = 100;
    bool isNotEqual = (notEqual1 != notEqual2); //(notEqual1 == notEqual2);
    std::cout << "Are the numbers equal? " << isNotEqual << std::endl;

    int greaterThan1 = 10;
    int greaterThan2 = 1;
    bool isGreaterThan = (greaterThan1 > greaterThan2);
    std::cout << "Is the left number greater than the right? " << isGreaterThan << std::endl;

    int notGreaterThan1 = 10;
    int notGreaterThan2 = 100;
    bool isNotGreaterThan = (notGreaterThan1 > notGreaterThan2);
    std::cout << "Is the left number greater than the right? " << isNotGreaterThan << std::endl;

    int lessThan1 = 1;
    int lessThan2 = 10;
    bool isLessThan = (lessThan1 < lessThan2);
    std::cout << "Is the left number less than the right? " << isLessThan << std::endl;

    int notLessThan1 = 100;
    int notLessThan2 = 10;
    bool isNotLessThan = (notLessThan1 < notLessThan2);
    std::cout << "Is the left number less than the right? " << isNotLessThan << std::endl;


    bool isTrue{ (10 == 10) && (20 == 20) };
    std::cout << "True? " << isTrue << std::endl;

    bool isFalse = isTrue && (1 == 2);
    std::cout << "True? " << isFalse << std::endl;

    bool isTrue1{ (1 == 1) || (0 == 1) };
    std::cout << "True? " << isTrue1 << std::endl;

    isTrue1 = (0 == 1) || (1 == 1);
    std::cout << "True? " << isTrue1 << std::endl;

    isTrue1 = (1 == 1) || (1 == 1);
    std::cout << "True? " << isTrue1 << std::endl;

    isTrue1 = (0 == 1) || (1 == 0);
    std::cout << "True? " << isTrue1 << std::endl;


    uint32_t hexValue{ 0x89 };
    std::cout << "Decimal: " << hexValue << std::endl;
    std::cout << std::hex << "HexDecimal: " << hexValue << std::endl; 
    std::cout << std::showbase << std::hex << "HexDecimal(with base): " << hexValue << std::endl; 

    return 0;
}