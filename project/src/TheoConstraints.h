#ifndef __THEOCONSTRAINTS__
#define __THEOCONSTRAINTS__

#include "Parameters.h"
#include "SM.h"

#include <math.h>
#include <complex.h>
#include <functional>

// using Condition = pair<string, function<int(const Parameters&)>>; 

class TheoCons {
    public:
    TheoCons() = default;
    // TheoCons(Parameters& newPars);
    ~TheoCons() = default;

    int CheckResult(int check_bit);
    // int BFB(double la1, double la2, double la3, double laL);
    // int TwoMins(double la1, double la2, double Mh, double m22Squared);
    // int ScatteringMatrixUnitary(double la1, double la2, double la3, double la4, double la5);
    // int Perturbativity(double la2);

    // vector<Condition> MakeTheoConsVector();
    int BFB(Parameters& Pars);
    int TwoMins(Parameters& Pars);
    int ScatteringMatrixUnitary(Parameters& Pars);
    int Perturbativity(Parameters& Pars);

    // Potencial bound from below
    int BoundFromBelow(double la1, double la2, double la3, double laL, double Mh, double m22Squared);
    int BFB_Test(double la1, double la2, double la3, double laL);
    int TwoMins_Test(double la1, double la2, double Mh, double m22Squared);

    // Perturbativity
    int Perturbativity_Test(double la1, double la2, double la3, double la4, double la5, double laL);
    int ScatteringMatrixUnitary_Test(double la1, double la2, double la3, double la4, double la5);
    int QuarticCouplings(double la1, double la2, double la3, double laL);

    // STU
    void InitSTUVars(double (&mneu)[4], double (&mch)[2], double &m11, double &MH, double &MA, double &MC);
    void InitSTUMatrices(double (&ImVdagV)[4][4], complex<double> (&UdagU)[2][2], complex<double> (&VdagV)[4][4], complex<double> (&UdagV)[2][4]);
    // void InitSTUVars(double mneu[4], double mch[2], double m11, double MH, double MA, double MC);
    void CalculateSTU(double (&mneu)[4], double (&mch)[2], double (&ImVdagV)[4][4], 
        complex<double> (&UdagU)[2][2], complex<double> (&VdagV)[4][4], 
        complex<double> (&UdagV)[2][4], double& S, double& T, double& U);
    int STU_Check(double &S, double &T, double &U);
    int ST(double m11, double MH, double MA, double MC, double &S, double &T, double &U);

    int STU_Test(double m11, double MH, double MA, double MC, double &S, double &T, double &U);
    // int STU_Test(double m11, double MH, double MA, double MC);
    vector<double> ST_graph_prep(double m11, double MH, double MA, double MC);
    
    // int CheckAllTheoCons();
    int GetCheck();

    // void GenNewPars();
    // Parameters GetPars();

    private:
    // Parameters Pars;
    int Check = 0;
};
#endif