#ifndef __THEOCONSTRAINTS__
#define __THEOCONSTRAINTS__

#include "Parameters.h"

#include <math.h>

class TheoCons {
    public:
    TheoCons() = default;
    // TheoCons(Parameters& newPars);
    ~TheoCons() = default;

    // int BFB(double la1, double la2, double la3, double laL);
    // int TwoMins(double la1, double la2, double Mh, double m22Squared);
    // int ScatteringMatrixUnitary(double la1, double la2, double la3, double la4, double la5);
    // int Perturbativity(double la2);

    int BFB(Parameters Pars);
    int TwoMins(Parameters Pars);
    int ScatteringMatrixUnitary(Parameters Pars);
    int Perturbativity(Parameters Pars);

    int BFB_Test(double la1, double la2, double la3, double laL);
    int Perturbativity_Test(double la2);

    // int CheckAllTheoCons();
    int GetCheck();

    // void GenNewPars();
    // Parameters GetPars();

    private:
    // Parameters Pars;
    int Check = 0;
};
#endif