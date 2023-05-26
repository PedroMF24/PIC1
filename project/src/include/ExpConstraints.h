#ifndef __EXPCONSTRAINTS__
#define __EXPCONSTRAINTS__

#include "Parameters.h"
#include "SM.h"

class ExpCons { // : public StandardModel
    public:
    ExpCons() = default;
    ~ExpCons() = default;

    /* Functions to reproduce IDM results with hard limits */
    int HiggsBoundsSignals(double MC, double Mh, double laL);
    int WZDecayWidths(double MH, double MA);
    int HChargedLifetime(double MH, double MA, double MC);
    int HiggsWidth(double MH, double laL);
    int LUXDMData(double MH, double Mh, double laL);
    int EWBosons(double MH, double MA, double MC);
    int LEPAnalysis(double MH, double MA, double MC);
    int RelicDensity(double MH);
    int Extras(double MC, double MA);

    int CheckAllExpCons(double Mh, double MH, double MA, double MC, double laL);

//     def EWBosons(MHX, MHC, MH3):
//     MW = 80.433 # W boson mass
//     MZ = 91.19  # Z boson mass

//     if (MHX + MHC >= MW and MH3 + MHC and MH3 + MHX >= MZ and 2*MHC >= MZ):
//         return True
//     else:
//         print("Problems with the EW Bosons mass condition")
//         quit()
//         # return 0

    // int EWBosons(Parameters Pars);
    // int LEPAnalysis(Parameters Pars);
    // int CheckAllExpCons(Parameters Pars);

    int GetExpCons();

    private:
    int Check;
};
#endif