#include <array>
#include <cstdint>
#include <iostream>

// constexpr uint32_t ArraySizeFunction(int parameter)
// {
//     return parameter;
// }

// C++14:
constexpr uint32_t ArraySizeFunction(uint32_t parameter)
{
    uint32_t value{ parameter };
    if (value > 10) {
        value = 10;
    }

    return value;
}

class MyClass
{
private: 
    uint32_t m_Member;

public:
    constexpr MyClass(uint32_t parameter)
        : m_Member{parameter}
    {
    }

    constexpr uint32_t GetValue() const
    {
        return m_Member;
    }
};

int reg_const()
{ return 999; }
constexpr int new_const()
{ return 999; }

int main()
{
    //constexpr uint32_t ARRAY_SIZE{ 5 };
    //constexpr uint32_t ARRAY_SIZE{ ArraySizeFunction(5) };
    constexpr uint32_t ARRAY_SIZE{ MyClass{ 5 }.GetValue() };
    std::array<uint32_t, ARRAY_SIZE> mtArray{ 1, 2, 3, 4, 5 };

    for (auto&& number : mtArray) {
        std::cout << number << std::endl;
    }

    const int first = reg_const();
    int second = new_const();
    second = 1;

    std::cout << first << " != to " << second << std::endl;

    return 0;
}