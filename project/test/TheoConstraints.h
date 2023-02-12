#ifndef __THEOCONSTRAINTS__
#define __THEOCONSTRAINTS__

#include "Parameters.h"

#include <math.h>

class TheoCons {
    public:
    TheoCons() = default;
    TheoCons(Parameters& newPars);
    ~TheoCons() = default;

    int BFB();
    int TwoMins();
    int ScatteringMatrixUnitary();
    int Perturbativity();

    int CheckAllTheoCons();
    int GetCheck();

    void GenNewPars();
    Parameters GetPars();

    private:
    Parameters Pars;
    int Check = 0;
};
#endif