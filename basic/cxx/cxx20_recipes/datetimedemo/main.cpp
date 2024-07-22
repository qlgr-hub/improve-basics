#include <chrono>
#include <iostream>
#include <ctime>
#include <iomanip>

using namespace std;

int main()
{
    chrono::system_clock::time_point pc_clock = chrono::system_clock::now();
    time_t pc_clock_time = chrono::system_clock::to_time_t(pc_clock);
    cout << "The time according to the computer clock is: " << put_time(localtime(&pc_clock_time), "%T %p") << endl;

    chrono::steady_clock::time_point start = chrono::steady_clock::now();
    chrono::high_resolution_clock::time_point start2 = chrono::high_resolution_clock::now();
    {
        chrono::system_clock::time_point now = chrono::system_clock::now();
        time_t now_c = chrono::system_clock::to_time_t(now);
        cout << "\n\nThe time now is: " << put_time(localtime(&now_c), "%F %T %b %I %p") << endl;
        time_t now_p = chrono::system_clock::to_time_t(now - chrono::hours(2));
        cout << "\n\nThe time 2 hours ago was: " << put_time(localtime(&now_p), "%F %T %B  %A") << "\n\n";
    }
    chrono::steady_clock::time_point end = chrono::steady_clock::now();
    chrono::high_resolution_clock::time_point end2 = chrono::high_resolution_clock::now();

    cout << "Computing lasted " << chrono::duration_cast<chrono::microseconds>(end - start).count() << " microseconds!" << endl;
    cout << "Computing high_resolution_clock yielded " << chrono::duration_cast<chrono::nanoseconds>(end2 - start2).count() << " nanoseconds!" << endl;

    return 0;
}





// #include <ctime>
// #include <chrono>
// #include <iostream>
// #include <thread>
//
// using namespace std;
// using namespace chrono;
// using namespace literals;
//
// int main()
// {
//     // auto currentTimePoint = system_clock::now();
//     // auto currentTime = system_clock::to_time_t( currentTimePoint );
//     // auto timeText = ctime( &currentTime );
//     //
//     // cout << timeText << endl;
//
//     auto startTimePoint = system_clock::now();
//
//     this_thread::sleep_for(5s);
//
//     auto endTimePoint = system_clock::now();
//
//     auto timeTaken = duration_cast<milliseconds>(endTimePoint - startTimePoint);
//
//     cout << "Time Taken: " << timeTaken.count() << endl;
//
//     return 0;
// }