#ifndef __STOPWATCH__
#define __STOPWATCH__

#include <iostream>
#include <chrono>
#include <iomanip>

using namespace std;
using namespace chrono;

// StartTimer function
// void StartTimer(high_resolution_clock::time_point& start) {
//     start = high_resolution_clock::now();
// }

// // StopTimer function
// void StopTimer(high_resolution_clock::time_point& start) {
//     auto stop = high_resolution_clock::now();
//     auto duration = duration_cast<microseconds>(stop - start);
//     double seconds = duration.count()/1e6;
//     // auto duration = duration_cast<milliseconds>(stop - start);  // duration*1e6;
//     cout << "Execution time: " << fixed << setprecision(3) <<seconds << " seconds" << endl;
// }

class StopWatch
{
public:
    StopWatch() = default;
    ~StopWatch() = default;

    void StartTimer();
    void StopTimer();
    void ResetTimer();
    void Lap();

    void PrintTime();

private:
    high_resolution_clock::time_point start;
    double Time = 0;
};
#endif