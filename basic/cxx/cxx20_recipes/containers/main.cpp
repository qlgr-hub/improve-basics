#include <cinttypes>
#include <iostream>
#include <array>
#include <vector>
#include <list>
#include <forward_list>
#include <set>
#include <string>
#include <map>
#include <unordered_set>
#include <unordered_map>

using namespace std;

struct person { string name; int age; int weight; float height; };

int main()
{
    person bill{ .name{"Bill"}, .age = 22, .weight = 180, .height{6.2} };
    person sally{ .name = "Sally", .age = 19, .weight = 120 };

    cout << "Person " << bill.name << " has a height of " << bill.height << endl;
    cout << "Person " << sally.name << " has a height of " << sally.height << endl;
    return 0;
}




// class MapObject
// {
// private:
//     string m_Name;
//
// public:
//     MapObject(const string& name)
//         : m_Name{ name }
//     {
//
//     }
//
//     const string& GetName() const
//     {
//         return m_Name;
//     }
// };
//
// int main()
// {
//     unordered_map<int32_t, MapObject> myMap
//     {
//         pair<int32_t, MapObject>{ 5, MapObject{ "Five" } },
//         pair<int32_t, MapObject>{ 3, MapObject{ "Three" } },
//         pair<int32_t, MapObject>{ 4, MapObject{ "Four" } },
//         pair<int32_t, MapObject>{ 1, MapObject{ "One" } },
//         pair<int32_t, MapObject>{ 2, MapObject{ "Two" } }
//     };
//
//     for (auto&& number : myMap) {
//         cout << number.second.GetName() << endl;
//     }
//
//     auto iter = myMap.find(3);
//     if (iter != myMap.end()) {
//         cout << "Found: " << iter->second.GetName() << endl;
//     }
//
//     return 0;
// }
//
//
//
// class SetObject;
//
// namespace std
// {
//     template<>
//     class hash<SetObject>
//     {
//     public:
//         template<typename... Args>
//         size_t operator()(Args&&... setObject) const
//         {
//             return hash<string>()((forward<Args...>(setObject...)).GetName());
//         }
//     };
// }
//
// class SetObject
// {
// private:
//     string m_Name;
//     size_t m_Hash{};
//
// public:
//     SetObject(const string& name)
//         : m_Name{ name }
//         , m_Hash{ hash<SetObject>()(*this) }
//     {
//
//     }
//
//     const string& GetName() const
//     {
//         return m_Name;
//     }
//
//     const size_t& GetHash() const
//     {
//         return m_Hash;
//     }
//
//     bool operator==(const SetObject& other) const
//     {
//         return m_Hash == other.m_Hash;
//     }
// };
//
// int main()
// {
//     unordered_set<SetObject> mySet;
//     mySet.emplace("Five");
//     mySet.emplace("Three");
//     mySet.emplace("Four");
//     mySet.emplace("One");
//     mySet.emplace("Two");
//     cout << showbase << hex;
//
//     for (auto&& number : mySet) {
//         cout << number.GetName() << " - " << number.GetHash() << endl;
//     }
//
//     auto iter = mySet.find({ "Three" });
//     if (iter != mySet.end()) {
//         cout << "Found: " << iter->GetName() << " with hash: " << iter->GetHash() << endl;
//     }
//
//     return 0;
// }
//
// class MapObject
// {
// private:
//     string m_Name;
//
// public:
//     MapObject(const string& name)
//         : m_Name{ name }
//     {
//
//     }
//
//     const string& GetName() const
//     {
//         return m_Name;
//     }
// };
//
// int main()
// {
//     //map<int32_t, MapObject> myMap
//     map<int32_t, MapObject, greater<int32_t>> myMap
//     {
//         pair<int32_t, MapObject>{ 6, MapObject{ "Six" } },
//         pair<int32_t, MapObject>{ 3, MapObject{ "Three" } },
//         pair<int32_t, MapObject>{ 4, MapObject{ "Four" } },
//         pair<int32_t, MapObject>{ 1, MapObject{ "One" } },
//         pair<int32_t, MapObject>{ 2, MapObject{ "Two" } }
//     };
//
//     for (auto&& number : myMap) {
//         cout << number.second.GetName() << endl;
//     }
//     cout << endl;
//
//     myMap.emplace(pair<int32_t, MapObject>{ 5, MapObject{ "Five" } });
//
//     for (auto&& number : myMap) {
//         cout << number.second.GetName() << endl;
//     }
//     cout << endl;
//
//     auto iter = myMap.find(3);
//     if (iter != myMap.end()) {
//         cout << "Found: " << iter->second.GetName() << endl;
//     }
//
//     return 0;
// }
//
//
//
// class SetObject
// {
// private:
//     string m_Name;
//     int32_t m_Key{};
//
// public:
//     SetObject(int32_t key, const string& name)
//         : m_Name{ name }
//         , m_Key{ key }
//     {
//
//     } 
//
//     SetObject(int32_t key)
//         : SetObject(key, "")
//     {
//
//     }
//
//     const string& GetName() const
//     {
//         return m_Name;
//     }
//
//     int32_t GetKey() const
//     {
//         return m_Key;
//     }
//
//     bool operator<(const SetObject& other) const
//     {
//         return m_Key < other.m_Key;
//     }
//
//     bool operator>(const SetObject& other) const
//     {
//         return m_Key > other.m_Key;
//     }
// };
//
// int main()
// {
//     //set<SetObject> mySet
//     set<SetObject, greater<SetObject>> mySet
//     {
//         { 6, "Six" },
//         { 3, "Three" },
//         { 4, "Four" },
//         { 1, "One" },
//         { 2, "Two" }  
//     };
//
//     for (auto&& number : mySet) {
//         cout << number.GetName() << endl;
//     }
//     cout << endl;
//
//     mySet.emplace(SetObject{ 5, "Five" });
//
//     for (auto&& number : mySet) {
//         cout << number.GetName() << endl;
//     }
//     cout << endl;
//
//     auto iter = mySet.find(3);
//     if (iter != mySet.end()) {
//         cout << "Found: " << iter->GetName() << endl;
//     }
//
//     return 0;
// }
//
//
//
// int main()
// {
    // const uint32_t numberOfElements{ 5 };
    // int32_t normalArray[numberOfElements]{ 10, 65, 3000, 2, 49 };
    // // for (uint32_t i{ 0 }; i < numberOfElements; ++i) {
    // //     cout << normalArray[i] << endl;
    // // }
    // for (auto&& number : normalArray) {
    //     cout << number << endl;
    // }
    //
    //
    // const uint32_t numberOfElements{ 5 };
    // array<int32_t, numberOfElements> stlArray{ 10, 65, 3000, 2, 49 };
    // for (uint32_t i = 0; i < numberOfElements; ++i) {
    //     cout << stlArray[i] << endl;
    // }
    //
    // cout << "\n\n";
    //
    // for (auto&& number : stlArray) {
    //     cout << number << endl;
    // }
    //
    //
    // vector<int32_t> stlVector{ 10, 65, 3000, 2, 49 };
    // cout << "The size is: " << stlVector.size() << endl;
    // for (uint32_t i = 0; i < stlVector.size(); ++i) {
    //     cout << stlVector[i] << endl;
    // }
    //
    // stlVector.emplace_back(50);
    //
    // cout << "The size is: " << stlVector.size() << endl;
    // for (auto&& number : stlVector) {
    //     cout << number << endl;
    // }
    //
    //
    // vector<int32_t> stlVector{1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};
    // cout << "The size is: " << stlVector.size() << endl;
    // cout << "The capacity is: " << stlVector.capacity() << endl;
    //
    // stlVector.emplace_back(17);
    //
    // cout << "The size is: " << stlVector.size() << endl;
    // cout << "The capacity is: " << stlVector.capacity() << endl;
    //
    // for (auto&& number : stlVector) {
    //     cout << number << endl;
    // }
    //
    //
    // vector<int32_t> stlVector{ 1, 2, 3, 4, 5 };
    //
    // auto iterator = stlVector.begin() + 2;
    // stlVector.emplace(iterator, 6);
    //
    // for (auto&& number : stlVector) {
    //     cout << number << endl;
    // }
    //
    //
    // vector<int32_t> stlVector{1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};
    // cout << "The size is: " << stlVector.size() << endl;
    // cout << "The capacity is: " << stlVector.capacity() << endl;
    //
    // for (auto&& number : stlVector) {
    //     cout << number << ", ";
    // }
    //
    // while (stlVector.size() > 0) {
    //     auto iterator = stlVector.end() - 1;
    //     stlVector.erase(iterator);
    // }
    //
    // cout << endl << endl << "The size is: " << stlVector.size() << endl;
    // cout << "The capacity is: " << stlVector.capacity() << endl << endl;
    //
    // for (auto&& number : stlVector) {
    //     cout << number << ", ";
    // }
    // cout << endl;
    //
    //
    // vector<int32_t> stlVector{1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};
    //
    // while (stlVector.size() > 0) {
    //     auto iterator = stlVector.end() - 1;
    //     stlVector.erase(iterator);
    //
    //     if ((stlVector.size() * 2) == stlVector.capacity()) {
    //         stlVector.shrink_to_fit();
    //     }
    //
    //     cout << "The size is: " << stlVector.size() << endl;
    //     cout << "The capacity is: " << stlVector.capacity() << endl;
    // }
    //
    //
    // list<int32_t> myList{ 1, 2, 3, 4, 5 };
    //
    // myList.emplace_front(6);
    // myList.emplace_back(7);
    //
    // auto forwardIter = myList.begin();
    // ++forwardIter;
    // ++forwardIter;
    // myList.emplace(forwardIter, 9);
    //
    // auto reverseIter = myList.end();
    // --reverseIter;
    // --reverseIter;
    // --reverseIter;
    // myList.emplace(reverseIter, 8);
    //
    // for (auto&& number : myList) {
    //     cout << number << endl;
    // }
    //
    //
    // forward_list<int32_t> myList{ 1, 2, 3, 4, 5 };
    //
    // myList.emplace_front(6);
    //
    // auto forwardIter = myList.begin();
    // ++forwardIter;
    // ++forwardIter;
    // myList.emplace_after(forwardIter, 9);
    //
    // for (auto&& number : myList) {
    //     cout << number << endl;
    // }
    //
    //
    //
    // return 0;
// }