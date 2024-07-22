#include <iostream>

using namespace std;

int main(int argc, char* argv[])
{
    // uint32_t bits{ 0x00011000 };
    // cout << showbase << hex;
    // cout << "Result of 0x00011000 & 0x00011000: " << (bits & bits) << endl;
    // cout << "Result of 0x00011000 & 0x11100111: " << (bits & ~bits) << endl;
    //
    // uint32_t leftBits{ 0x00011000 };
    // uint32_t rightBits{ 0x00010100 };
    // cout << showbase << hex;
    // cout << "Result of 0x00011000 | 0x00010100: " << (leftBits | rightBits) << endl;
    // cout << "Result of 0x00011000 | 0x11100111: " << (leftBits | ~leftBits) << endl;
    //
    // uint32_t leftBits{ 0x00011000 };
    // uint32_t rightBits{ 0x00010100 };
    // cout << showbase << hex;
    // cout << "Result of 0x00011000 ^ 0x00010100: " << (leftBits ^ rightBits) << endl;
    // cout << "Result of 0x00011000 ^ 0x11100111: " << (leftBits ^ ~leftBits) << endl;
    //
    // const uint32_t maskBits{ 16 };
    // uint32_t leftShifted{ 0x00001010 << maskBits };
    // cout << showbase << hex;
    // cout << "Left shifted: " << leftShifted << endl;
    //
    // uint32_t lowerMask{ 0x0000FFFF };
    // leftShifted |= (0x11110110 & lowerMask);
    // cout << "Packed left shifted: " << leftShifted << endl;
    //
    // uint32_t lowerValue{ (leftShifted & lowerMask) };
    // cout << "Lower value unmasked: " << lowerValue << endl;
    //
    // uint32_t upperValue{ (leftShifted >> maskBits) };
    // cout << "Upper value unmasked: " << upperValue << endl;
    //
    // const uint32_t maskBits{ 16 };
    // uint32_t narrowingBits{ 0x00008000 << maskBits };
    //cout << showbase << hex;
    // cout << narrowingBits << endl;
    //
    // const uint32_t maskBits{ 16 };
    // uint32_t uintValue{ 0x00008080u << maskBits };
    // cout << showbase << hex;
    // cout << uintValue << endl;
    //
    const uint32_t maskBits{ 16 };
    int32_t lowerMask{ 0x0000FFFF };
    int32_t leftShifted{ 0x00008080 << maskBits };
    cout << showbase << hex;
    cout << "Left shifted: " << leftShifted << endl;
    int32_t rightShifted{ (leftShifted >> maskBits) };
    cout << "Right shifted: " << rightShifted << endl;
    cout << "Unmasked right shifted: " << (rightShifted & lowerMask) << endl;

    return 0;
}