#include <iostream>
#include <string>

using namespace std;

// namespace
// {
//     const string STRING{ "This is a string"s };
// }
//
// int main()
// {
//     cout << STRING << endl;
//     return 0;
// }

// namespace 
// {
//     const char* const STRING{ "This is a string" };
//     char* EDIT_STRING{ "Attempt to Edit" };
// }
//
// int main()
// {
//     cout << STRING << endl;
//
//     cout << EDIT_STRING << endl;
//     EDIT_STRING[0] = 'a';
//     cout << EDIT_STRING << endl;
//
//     return 0;
// }



#define DEBUG_STRING_LITERALS !NDEBUG

namespace
{
#if DEBUG_STRING_LITERALS
    using DebugStringLiteral = string;
#endif

#if DEBUG_STRING_LITERALS
    DebugStringLiteral STRING{ "This is a string" };
#endif
}

int main()
{
#if DEBUG_STRING_LITERALS
    cout << STRING << endl;
#endif

    return 0;
}