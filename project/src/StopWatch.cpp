#include "../include/StopWatch.h"

void StopWatch::StartTimer() {
    start = high_resolution_clock::now();
}

void StopWatch::StopTimer() {
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    Time += duration.count();
}

void StopWatch::ResetTimer()
{
    start = high_resolution_clock::time_point();
    Time = 0.0;
    cout << "Timer reset..." << endl;
}

void StopWatch::PrintTime() {
    if (Time/1e6 >= 60) {
        cout << "Execution time: " << fixed << setprecision(3) << Time/(1e6*60) << " minutes" << endl;
    } else {
        cout << "Execution time: " << fixed << setprecision(3) << Time/1e6 << " seconds" << endl;
    }
}

void StopWatch::Lap() {
    StopTimer();
    PrintTime();
    StartTimer();
}


/*
 * TEST STOPWATCH CLASS
*/

/*

    StopWatch clock;
    StopWatch clock2;
    clock.StartTimer();
    IDM idm;
    idm.StoreCheckedPars(10000);
    clock.StopTimer();
    clock.PrintTime();

    cout << "1. Reset" << endl;

    clock.ResetTimer();
    clock.PrintTime();

    clock.StartTimer();
    idm.StoreCheckedPars(10000);
    clock.StopTimer();
    clock.PrintTime();

    cout << "2. No Reset" << endl;

    idm.StoreCheckedPars(10000);
    clock.PrintTime();
    cout << "3. Did it again with no timer, should be same time" << endl;
    
    clock.StartTimer();
    clock2.StartTimer();
    idm.StoreCheckedPars(10000);
    clock.StopTimer();
    clock2.StopTimer();
    cout << "Clock 1: ";
    clock.PrintTime();
    cout << "Clock 2: ";
    clock2.PrintTime();

*/