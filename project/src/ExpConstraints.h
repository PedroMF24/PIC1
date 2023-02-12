#ifndef __EXPCONSTRAINTS__
#define __EXPCONSTRAINTS__

#include "Parameters.h"

class ExpCons {
    public:
    ExpCons();
    ExpCons(Parameters& newPars);
    ~ExpCons() = default;

//     def EWBosons(MHX, MHC, MH3):
//     MW = 80.433 # W boson mass
//     MZ = 91.19  # Z boson mass

//     if (MHX + MHC >= MW and MH3 + MHC and MH3 + MHX >= MZ and 2*MHC >= MZ):
//         return True
//     else:
//         print("Problems with the EW Bosons mass condition")
//         quit()
//         # return 0

    int EWBosons();
    int LEPAnalysis();
    int CheckAllExpCons();

    int GetExpCons();

    private:
    Parameters Pars;
    int Check;
};
#endif