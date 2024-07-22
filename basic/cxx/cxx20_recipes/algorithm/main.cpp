#include <cinttypes>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <set>

using namespace std;

// class MyClass
// {
// private:
//     int m_Value;
//
// public:
//     MyClass(const int value)
//         : m_Value{ value }
//     {
//
//     }
//
//     int GetValue() const 
//     {
//         return m_Value;
//     }
//
//     bool operator<(const MyClass& other) const
//     {
//         return m_Value < other.m_Value;
//     }
// };
//
// bool CompareMyClass(const MyClass& left, const MyClass& right)
// {
//     return left.GetValue() < right.GetValue();
// }
//
//
// bool IsGreater(int left, int right)
// {
//     return left > right;
// }
//
//
struct Inventory
{
    string Name;
    int SKU;
    string Description;
    float Price;
};

bool operator<(const Inventory& left, const Inventory& right)
{
    return left.Name < right.Name;
}

set<Inventory> items
{
    { "hammer", 100, "standard regular hammer", 10.00 },
    { "saw", 200, "wood saw with plastic handle", 5.99 },
    { "nails", 300, "12 size nails, 10 ct.", 2.99 },
    { "saw", 400, "metal cutting saw", 13.99 }
};

int main()
{
    // using IntVector = vector<int32_t>;
    // using IntVectorIterator = IntVector::iterator;
    // using ConstIntVectorInterator = IntVector::const_iterator;
    //
    // using ReverseIntVectorIterator = IntVector::reverse_iterator;
    // using ConstReverseIntVectorInterator = IntVector::const_reverse_iterator;
    //
    // //IntVector myVector{ 0, 1, 2, 3, 4 };
    //
    // IntVector myVector(5, 0);
    // int32_t value{ 0 };
    //
    // // for (IntVectorIterator iter = myVector.begin(); iter != myVector.end(); ++iter) {
    // //     *iter = ++value;
    // // }
    // for (ReverseIntVectorIterator iter = myVector.rbegin(); iter != myVector.rend(); ++iter) {
    //     *iter = value++;
    // }
    // 
    //
    // // for (IntVectorIterator iter = myVector.begin(); iter != myVector.end(); ++iter) {
    // //     cout << "The value is: " << *iter << endl;
    // // }
    // for (ConstIntVectorInterator iter = myVector.cbegin(); iter != myVector.cend(); ++iter) {
    //     cout << "The value is: " << *iter << endl;
    // }
    // // for (ConstReverseIntVectorInterator iter = myVector.crbegin(); iter != myVector.crend(); ++iter) {
    // //     cout << "The value is: " << *iter << endl;
    // // }
    //
    //
    // vector<int32_t> myVector
    // {
    //     1,
    //     2,
    //     3,
    //     4,
    //     5
    // };
    // for_each(myVector.begin(), myVector.end(),
    //     [](int32_t value)
    //     {
    //         cout << value << endl;
    //     });
    //
    //
    // vector<int> myVector{ 4, 10, 6, 9, 1 };
    // auto mininum = min_element(myVector.cbegin(), myVector.cend());
    //
    // cout << "Minimun value: " << *mininum << std::endl;
    //
    //
    // vector<MyClass> myVector{ 4, 10, 6, 9, 1 };
    // auto mininum = min_element(myVector.cbegin(), myVector.cend());
    //
    // if (mininum != myVector.cend()) {
    //     cout << "Minimun value: " << mininum->GetValue() << std::endl;
    // }
    //
    //
    // vector<MyClass> myVector{ 4, 10, 6, 9, 1 };
    // auto mininum = min_element(myVector.cbegin(), myVector.cend(), CompareMyClass);
    //
    // if (mininum != myVector.cend()) {
    //     cout << "Minimun value: " << mininum->GetValue() << std::endl;
    // }
    //
    //
    // vector<int> myVector{ 4, 10, 6, 9, 1 };
    // auto intMinimun = max_element(myVector.cbegin(), myVector.cend());
    //
    // cout << "Minimun value: " << *intMinimun << std::endl;
    //
    // vector<MyClass> myMyClassVector{ 4, 10, 6, 9, 1 };
    // auto overrideOperatorMinimun = max_element(myMyClassVector.cbegin(), myMyClassVector.cend());
    //
    // if (overrideOperatorMinimun != myMyClassVector.cend()) {
    //     cout << "Minimun value: " << overrideOperatorMinimun->GetValue() << std::endl;
    // }
    //
    // auto functionComparasonMinimun = max_element(myMyClassVector.cbegin(), myMyClassVector.cend(), CompareMyClass);
    //
    // if (functionComparasonMinimun != myMyClassVector.cend()) {
    //     cout << "Minimun value: " << functionComparasonMinimun->GetValue() << std::endl;
    // }
    //
    //
    //
    // vector<int> myVector{ 3, 2, 3, 7, 3, 8, 9, 3 };
    // auto number = count(myVector.cbegin(), myVector.cend(), 3);
    // cout << "The number of 3s in myVector is: " << number << endl;
    //
    //
    // string myString{ "Bruce Sutherland!" };
    //
    // auto numberOfCapitals = count_if(
    //     myString.cbegin(),
    //     myString.cend(),
    //     [](auto&& character)
    //     {
    //         return static_cast<bool>(isupper(character));
    //     });
    // cout << "The number of capitals: " << numberOfCapitals << endl;
    //
    // auto numberOfLowerCase = count_if(
    //     myString.cbegin(),
    //     myString.cend(),
    //     [](auto&& character)
    //     {
    //         return static_cast<bool>(islower(character));
    //     });
    // cout << "The number of lower case letters: " << numberOfLowerCase << endl;
    //
    // auto numberOfAlphaNumerics = count_if(
    //     myString.cbegin(),
    //     myString.cend(),
    //     [](auto&& character)
    //     {
    //         return static_cast<bool>(isalpha(character));
    //     });
    // cout << "The number of alpha numeric characters: " << numberOfAlphaNumerics << endl;
    //
    // auto numberOfPunctuationMarks = count_if(
    //     myString.cbegin(),
    //     myString.cend(),
    //     [](auto&& character)
    //     {
    //         return static_cast<bool>(ispunct(character));
    //     });
    // cout << "The number of punctuation marks: " << numberOfPunctuationMarks << endl;
    //
    // auto numberOfWhiteSpaceCharacters = count_if(
    //     myString.cbegin(),
    //     myString.cend(),
    //     [](auto&& character)
    //     {
    //         return static_cast<bool>(isspace(character));
    //     });
    // cout << "The number of white space characters: " << numberOfWhiteSpaceCharacters << endl;
    //
    //
    //
    // string myString{ "Bruce Sutherland!" };
    //
    // auto found = find(myString.cbegin(), myString.cend(), 'e');
    // while (found != myString.cend()) {
    //     cout << "Found: " << *found << endl;
    //
    //     found = find(found + 1, myString.cend(), 'e');
    // }
    //
    //
    // vector<int> myVector{ 10, 6, 4, 7, 8, 3, 9 };
    // sort(myVector.begin(), myVector.end(), IsGreater);
    //
    // for (auto&& element : myVector) {
    //     cout << element << ", ";
    // }
    // cout << endl;
    //
    //
    //
    items.insert({ "glue", 500, "sticky", 1.99 });

    if (items.find({ "glue", 0, "", 0.0 }) != items.end()) {
        cout << "We have your part in stock!\n";
    }
    else {
        cout << "We could not find that part.\n";
    }

    return 0;
}