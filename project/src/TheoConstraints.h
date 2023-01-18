#ifndef __THEOCONSTRAINTS__
#define __THEOCONSTRAINTS__

#include "Parameters.h"

class TheoCons : public Parameters {
    public:
    TheoCons();
    ~TheoCons() = default;

    int BFB();
    int TwoMins();
    int Perturbativity();

    int CheckAllTheoCons();
    int GetCheck();

    private:
    int Check = 0;
};
#endif