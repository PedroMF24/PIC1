#ifndef __PARAMETERS__
#define __PARAMETERS__

#include <iostream>
#include <stdlib.h>
#include <vector>
#include <string>

#include <sstream>
#include <fstream>
#include <map>

// #include "TRandom3.h"
#include "MyRandom.h"

using namespace std;

class Parameters : public MyRandom {
    public:
    Parameters();
    ~Parameters() = default;

    Parameters& operator=(const Parameters& obj);
    // copy constructor
    Parameters(const Parameters& newPars);
    // Print Parameters
    friend std::ostream& operator<<(ostream& s, const Parameters& p);

    void ScanSetup();
    void GenPars();
    void ImportPars(const string &filename);
    void SetPars();

    double GetMh();
    double Getv();
    double Getla1();
    double Getla2();
    double GetlaL();
    double GetMH();
    double GetMA();
    double GetMC();

    double Getm22Squared();
    double Getla3();
    double Getla4();
    double Getla5();

    private:
    double Mh = 125.1;
    double v = 246;
    double la1 = 0; // (Mh/v)**2

    // Mass Basis
    double MH = 0; // MHX CDM
    double MA = 0; // MH3 It is A in IDM paper
    double MC = 0; // MHC Charged Higgs
    double la2 = 0; // lambda_2
    double laL = 0; // la3 + la4 + la5

    // Coupling Parameters Basis
    double m22Squared = 0;
    double la3 = 0;
    double la4 = 0;
    double la5 = 0;

    MyRandom Rd;
};


// class IDM_Pars {
// public:
//     IDM_Pars() = default;
//     ~IDM_Pars() = default;
// private:
//     Parameters Pars;
// };

#endif