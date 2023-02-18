#ifndef __EXPCONSTRAINTS__
#define __EXPCONSTRAINTS__

#include "Parameters.h"

class ExpCons {
    public:
    ExpCons() = default;
    ~ExpCons() = default;

    int HiggsBoundsSignals(double MC, double Mh, double laL);

//     def EWBosons(MHX, MHC, MH3):
//     MW = 80.433 # W boson mass
//     MZ = 91.19  # Z boson mass

//     if (MHX + MHC >= MW and MH3 + MHC and MH3 + MHX >= MZ and 2*MHC >= MZ):
//         return True
//     else:
//         print("Problems with the EW Bosons mass condition")
//         quit()
//         # return 0

    int EWBosons(Parameters Pars);
    int LEPAnalysis(Parameters Pars);
    int CheckAllExpCons(Parameters Pars);

    int GetExpCons();

    private:
    int Check;
};
#endif