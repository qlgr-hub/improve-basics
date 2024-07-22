#include <algorithm>
#include <array>
#include <cstdint>
#include <functional>
#include <iostream>
#include <typeinfo>
#include <vector>

using MyArray = std::array<uint32_t, 5>;
using MyVector = std::vector<MyArray::value_type>; 

void PrintArray(const std::function<void(MyArray::value_type)>& myFunction)
{
    MyArray myArray{ 1, 2, 3, 4, 5 };

    std::for_each(myArray.cbegin(),
        myArray.cend(), 
        myFunction);
}

int main()
{
    // MyArray myArray{ 1, 2, 3, 4, 5 };
    // auto myClosure = [](auto&& number) { 
    //         std::cout << number << std::endl; 
    //     };
    // std::cout << typeid(myClosure).name() << std::endl;
    //
    // std::for_each(mtArray.cbegin(),
    //     mtArray.cend(), 
    //     [](auto&& number) { 
    //         std::cout << number << std::endl; 
    //     });
    //
    // std::for_each(myArray.cbegin(),
    //     myArray.cend(), 
    //     myClosure);
    //
    // PrintArray(myClosure);


    // MyVector myCopy;
    // auto myClosure = [&myCopy](auto&& number) { 
    //         std::cout << number << std::endl;
    //         myCopy.push_back(number);
    //     };
    //
    // PrintArray(myClosure);
    //
    // std::for_each(myCopy.cbegin(),
    //     myCopy.cend(), 
    //    [](auto&& number) { 
    //         std::cout << number << std::endl; 
    //     });


    // MyVector myCopy;
    // // 使用mutable的原因是 c++中的lambda默认创建的闭包是const的
    // // 所以其中捕获额变量也是const的
    // auto myClosure = [myCopy](auto&& number) mutable { 
    //         std::cout << number << std::endl;
    //         myCopy.push_back(number);
    //     };
    //
    // PrintArray(myClosure);
    //
    // std::for_each(myCopy.cbegin(),
    //     myCopy.cend(), 
    //     [](auto&& number) { 
    //         std::cout << number << std::endl; 
    //     });


    MyVector myCopy;
    auto myClosure = [&myCopy](const MyArray::value_type& number) { 
            std::cout << number << std::endl;
            myCopy.push_back(number);
        };

    PrintArray(myClosure);

    std::for_each(myCopy.cbegin(),
        myCopy.cend(),
        [](const MyVector::value_type& number) {
            std::cout << number << std::endl;
        });

    return 0;
}