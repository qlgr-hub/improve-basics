#include <chrono>
#include <iostream>
#include <string>
#include <vector>

using namespace std;
using namespace chrono;
using namespace literals;

class MyClass
{
private:
    vector<string> m_Strings {
        "This is a pertty long string that"
        " must be copy constructed into"
        " copyConstructed!"s
    };

    int m_Value{ 1 };

public:
    MyClass() = default;
    MyClass(const MyClass& rhs) = default;
    MyClass(MyClass&& rhs) = default;

    int GetValue() const
    {
        return m_Value;
    }
};

int main()
{
    using MyVector = vector<MyClass>;
    constexpr unsigned int ITERATIONS{ 10000000U };

    MyVector copyConstructed(ITERATIONS);
    int valueCopy{ 0 };

    auto copyStartTime = high_resolution_clock::now();
    for (unsigned int i = 0; i < ITERATIONS; ++i) {
        MyClass myClass;
        copyConstructed.push_back(myClass);
        valueCopy = myClass.GetValue();
    }
    auto copyEndTime = high_resolution_clock::now();

    MyVector MoveConstructed(ITERATIONS);
    int valueMove{ 0 };

    auto moveStartTime = high_resolution_clock::now();
    for (unsigned int i = 0; i < ITERATIONS; ++i) {
        MyClass myClass;
        MoveConstructed.push_back(move(myClass));
        valueMove = myClass.GetValue();
    }
    auto moveEndTime = high_resolution_clock::now();

    auto copyDuration = duration_cast<milliseconds>(copyEndTime - copyStartTime);
    cout << "Copy lasted: " << copyDuration.count() << "ms" << endl;

    auto moveDuration = duration_cast<milliseconds>(moveEndTime - moveStartTime);
    cout << "Copy lasted: " << moveDuration.count() << "ms" << endl;

    return 0;
}

















// #include <iostream>
//
// using namespace std;
//
// class MyClass
// {
// private:
//     static int s_Counter;
//     int* m_Member{ &s_Counter };
//
// public:
//     MyClass()
//     {
//         ++(*m_Member);
//         cout << "Constructing: " << GetValue() << endl;
//     }
//
//     ~MyClass()
//     {
//         if (m_Member) {
//             --(*m_Member);
//             m_Member = nullptr;
//             cout << "Destructing: " << s_Counter << endl;
//         }
//         else {
//             cout << "Destructing a moved-from instance " << endl;
//         }
//     }
//
//     MyClass(const MyClass& rhs)
//         : m_Member{ rhs.m_Member }
//     {
//         ++(*m_Member);
//         cout << "Copying: " << GetValue() << endl;
//     }
//
//     MyClass(MyClass&& rhs)
//         : m_Member{ rhs.m_Member }
//     {
//         cout << hex << showbase;
//         cout << "Moving: " << &rhs << " to " << this << endl;
//         cout << noshowbase << dec;
//         rhs.m_Member = nullptr;
//     }
//
//     int GetValue() const
//     {
//         return *m_Member;
//     }
// };
// int MyClass::s_Counter{ 0 };
//
// MyClass CopyMyClass(MyClass parameter)
// {
//     return parameter;
// }
//
// int main()
// {
//     // auto object1 = MyClass();
//     // cout << object1.GetValue() << endl;
//
//     // {
//     //     auto object2 = MyClass();
//     //     cout << object2.GetValue() << endl;
//     // }
//
//     // auto object3 = MyClass();
//     // cout << object3.GetValue() << endl;
//
//     auto object1 = MyClass();
//
//     {
//         auto object2 = MyClass();
//     }
//
//     auto object3 = MyClass();
//     auto object4 = CopyMyClass(object3);
//
//     return 0;
// }