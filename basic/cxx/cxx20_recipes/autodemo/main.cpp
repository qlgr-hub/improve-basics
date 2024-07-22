#include <iostream>
#include <typeinfo>

using namespace std;

class MyClass
{
};

// C++11: auto AutoFunctionFromReturn(int parameter) -> int
auto AutoFunctionFromReturn(int parameter)
{
    return parameter;
}

template<typename T>
// C++11: auto AutoFunctionFromParameter(T parameter) -> decltype(parameter)
auto AutoFunctionFromParameter(T parameter)
{
    return parameter;
}


int main()
{
    auto variable = 1;
    cout << "Type of variable: " << typeid(variable).name() << endl;

    auto variableC = MyClass();
    cout << "Type of variableC: " << typeid(variableC).name() << endl;

    auto variable2{ 1 };
    cout << "Type of variable2: " << typeid(variable2).name() << endl;

    auto variableC2{ MyClass{} };
    cout << "Type of variableC2: " << typeid(variableC2).name() << endl;

    auto value = AutoFunctionFromReturn(1);
    cout << value << endl;

    auto value1 = AutoFunctionFromParameter(2);
    cout << value1 << endl;

    return 0;
}