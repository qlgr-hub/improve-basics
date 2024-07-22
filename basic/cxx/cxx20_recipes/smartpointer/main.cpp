#include <iostream>
#include <memory>
#include <string>

using namespace std;

class MyClass
{
private:
    string m_Name;
    int m_Value;

public:
    MyClass(const string& name, int value)
        : m_Name{ name }
        , m_Value{ value }
    {
        cout << "Constructing!" << endl;
    }

    ~MyClass()
    {
        cout << "Destructing!" << endl;
    }

    const string& GetName() const
    {
        return m_Name;
    }

    int GetValue() const 
    {
        return m_Value;
    }
};

using MySharedPtr = shared_ptr<MyClass>;
using MyWeakPtr = weak_ptr<MyClass>;

auto PassSharedPtr(MySharedPtr ptr)
{
    cout << "In Function Name: " << ptr->GetName() << endl;
    return ptr;
}

int main()
{
    MyWeakPtr weakPtr;
    {
        auto sharedPointer = make_shared<MyClass>("MyClass", 10);
        weakPtr = sharedPointer;

        {
            auto newSharedPointer = PassSharedPtr(sharedPointer);

            if (sharedPointer)
            {
                cout << "First Object Name: " << sharedPointer->GetName() << endl;
            }

            cout << "Second Object Name: " << newSharedPointer->GetName() << endl;

            auto sharedFromWeak1 = weakPtr.lock();
            if (sharedFromWeak1)
            {
                cout << "Name From Weak1: " << sharedFromWeak1->GetName() << endl;
            }
        }
    }

    auto sharedFromWeak2 = weakPtr.lock();
    if (!sharedFromWeak2)
    {
        cout << "Shared Pointer Out Of Scope!" << endl;
    }

    return 0;
}













// using MySharedPtr = shared_ptr<MyClass>;
//
// auto PassSharedPtr(MySharedPtr ptr)
// {
//     cout << "In Function Name: " << ptr->GetName() << endl;
//     return ptr;
// }
//
// int main()
// {
//     auto sharedPointer = make_shared<MyClass>("MyClass", 10);
//     {
//         auto newSharedPointer = PassSharedPtr(sharedPointer);
//
//         if (sharedPointer)
//         {
//             cout << "First Object Name: " << sharedPointer->GetName() << endl;
//         }
//         cout << "Second Object Name: " << newSharedPointer->GetName() << endl;
//     }
//
//     return 0;
// }
//
//
//
// using MyUniquePtr = unique_ptr<MyClass>;
//
// auto PassUniquePtr(MyUniquePtr ptr)
// {
//     cout << "In Function Name: " << ptr->GetName() << endl;
//     return ptr;
// }
//
// int main()
// {
//     // unique_ptr<MyClass> uniquePointer{ make_unique<MyClass>() };
//     // cout << uniquePointer->GetValue() << endl;
//
//     auto uniquePointer = make_unique<MyClass>("MyClass", 10);
//     auto newUniquePointer = PassUniquePtr(move(uniquePointer));
//
//     if (uniquePointer)
//     {
//         cout << "First Object Name: " << uniquePointer->GetName() << endl;
//     }
//     cout << "Second Object Name: " << newUniquePointer->GetName() << endl;
//
//     return 0;
// }