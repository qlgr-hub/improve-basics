#include <iostream>
#include <cassert>
#include <string>
#include <cstddef>
#include <concepts>

using namespace std;

// class MyClass
// {
// private:
//     int m_Value{ 0 };
//
// public:
//     MyClass() = default;
//
//     MyClass(int value)
//         : m_Value{ value }
//     {
//
//     }
//
//     MyClass(int number1, int number2)
//         : m_Value{ number1 + number2 }
//     {
//
//     }
//
//     int GetValue() const
//     {
//         return m_Value;
//     }
//
//     // MyClass operator +(const MyClass& other) const
//     // {
//     //     return m_Value + other.m_Value;
//     // }
// };
//
// // ostream& operator <<(ostream& os, const MyClass& myClass)
// // {
// //     os << myClass.GetValue();
// //     return os;
// // }
//
// // int Add(int a, int b)
// // {
// //     return a + b;
// // }
//
// template<typename T>
// T Add(const T& a, const T& b)
// {
//     return a + b;
// }
//
// template<>
// MyClass Add(const MyClass& myClass1, const MyClass& myClass2)
// {
//     return MyClass(myClass1.GetValue(), myClass2.GetValue());
// }
//
// template<typename T>
// void Print(const T& value1, const T& value2, const T& result)
// {
//     cout << "The result of adding" << endl;
//     cout << value1 << endl;
//     cout << "to" << endl;
//     cout << value2 << endl;
//     cout << "is" << endl;
//     cout << result;
//
//     cout << endl << endl;
// }
//
// template<>
// void Print(const MyClass& value1, const MyClass& value2, const MyClass& result)
// {
//     cout << "The result of adding" << endl;
//     cout << value1.GetValue() << endl;
//     cout << "to" << endl;
//     cout << value2.GetValue() << endl;
//     cout << "is" << endl;
//     cout << result.GetValue();
//
//     cout << endl << endl;
// }
//
//
// template<typename T, int numberOfElements>
// class MyArray
// {
// private:
//     T m_Array[numberOfElements];
//
// public:
//     MyArray()
//         : m_Array{}
//     {
//
//     }
//
//     T& operator[](const unsigned int index)
//     {
//         return m_Array[index];
//     }
// };
//
//
//
// template<typename T>
// class Singleton
// {
// private:
//     static T* m_Instance;
//
// public:
//     Singleton()
//     {
//         assert(m_Instance == nullptr);
//         m_Instance = static_cast<T*>(this);
//     }
//
//     virtual ~Singleton()
//     {
//         m_Instance = nullptr;
//     }
//
//     static T& GetSingleton()
//     {
//         return *m_Instance;
//     }
//
//     static T* GetSingletonPtr()
//     {
//         return m_Instance;
//     }
// };
//
// template<typename T>
// T* Singleton<T>::m_Instance = nullptr;
//
// class Manager 
//     : public Singleton<Manager>
// {
// public:
//     void Print() const
//     {
//         cout << "Singleton Manager Successfully Printing!" << endl;
//     }
// };
//
//
//
// unsigned int SDBMHash(const string& key)
// {
//     unsigned int result{ 0 };
//
//     for (unsigned int character : key) {
//         result = character + (result << 6) + (result << 16) - result;
//     }
//
//     return result;
// }
//
//
//
// template<int stringLength>
// struct SDBMCalculator
// {
//     constexpr static unsigned int Calculate(const char* const stringToHash, unsigned int& value)
//     {
//         unsigned int character { SDBMCalculator<stringLength - 1>::Calculate(stringToHash, value) };
//         value = character + (value << 6) + (value << 16) - value;
//         return stringToHash[stringLength - 1];
//     }
//
//     constexpr static unsigned int CalculateValue(const char* const stringToHash)
//     {
//         unsigned int value{};
//         unsigned int character { SDBMCalculator<stringLength>::Calculate(stringToHash, value) };
//         value = character + (value << 6) + (value << 16) - value;
//         return value;
//     }
// };
//
// template<>
// struct SDBMCalculator<1>
// {
//     constexpr static unsigned int Calculate(const char* const stringToHash, unsigned int& value)
//     {
//         return stringToHash[0];
//     }
// };
//
// constexpr unsigned int sdbmHash{ SDBMCalculator<16>::CalculateValue("Bruce Sutherland") };
//
//
//
template<typename T>
concept Hashable = requires(T a)
{
    { hash<T>{}(a) }->convertible_to<size_t>;
};

struct foobar{};

template<Hashable T>
void foo(T){}

int main()
{
    // const int number1{ 1 };
    // const int number2{ 2 };
    // const int result{ Add(number1, number2) };
    // Print(number1, number2, result);
    //
    // const float floatResult{ Add(static_cast<float>(number1), static_cast<float>(number2)) };
    // Print<float>(number1, number2, floatResult);
    //
    //
    // const MyClass number1{ 1 };
    // const MyClass number2{ 2 };
    // const MyClass result{ Add(number1, number2) };
    // Print(number1, number2, result);
    //
    //
    //
    // const unsigned int ARRAY_SIZE{ 5 };
    // MyArray<int, ARRAY_SIZE> myIntArray;
    // for (unsigned int i{ 0 }; i < ARRAY_SIZE; ++i) {
    //     myIntArray[i] = i;
    // }
    //
    // for (unsigned int i{ 0 }; i < ARRAY_SIZE; ++i) {
    //     cout << myIntArray[i] << endl;
    // }
    // cout << endl;
    //
    // MyArray<float, ARRAY_SIZE> myFloatArray;
    // for (unsigned int i{ 0 }; i < ARRAY_SIZE; ++i) {
    //     myFloatArray[i] = static_cast<float>(i) + 0.5f;
    // }
    //
    // for (unsigned int i{ 0 }; i < ARRAY_SIZE; ++i) {
    //     cout << myFloatArray[i] << endl;
    // }
    //
    //
    //
    // new Manager();
    // Manager& manger{ Manager::GetSingleton() };
    // manger.Print();
    // delete Manager::GetSingletonPtr();
    //
    //
    //
    // string data{ "Bruce Sutherland" };
    // unsigned int sdbmHash{ SDBMHash(data) };
    //
    // cout << "The hash of " << data << " is " << sdbmHash << endl;
    //
    //cout << "The hash of Bruce Sutherland is " << sdbmHash << endl;
    //
    //
    //
    foo("abc 123 this is easy!"s);
    foo(foobar{});

    return 0;
}