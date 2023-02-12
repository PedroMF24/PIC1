#ifndef __EXPCONSTRAINTS__
#define __EXPCONSTRAINTS__

#include "Parameters.h"

class ExpCons : public Parameters {
    public:
    ExpCons();
    ExpCons(Parameters& newPars);
    ~ExpCons() = default;

    int EWBosons();
    int LEPAnalysis();
    int CheckAllExpCons();

    int GetExpCons();

    private:
    Parameters Pars;
    int Check;
};
#endif