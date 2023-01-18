#ifndef __MYRANDOM__
#define __MYRANDOM__

#include <random>
// #include "TRandom3.h"

using namespace std;

class MyRandom {
    public:
    MyRandom() = default;
    ~MyRandom() = default;
    // TRandom3* TRand = new TRandom3(0);
    double UniDist(double min, double max); //doubles from -1 to 1

    private:
    random_device rd;

};
#endif