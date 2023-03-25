#ifndef __PARAMETERS__
#define __PARAMETERS__

#include <iostream>
#include <stdlib.h>
#include <vector>
#include <string>
#include <map>

#include <sstream>
#include <fstream>

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
    void GenPars(int scan_setup);
    void ImportPars(const string &filename);
    void SetPars();

    double GetMh() const;
    double Getv() const;
    double Getla1() const;
    double Getla2() const;
    double GetlaL() const;
    double GetMH() const;
    double GetMA() const;
    double GetMC() const;

    double Getm22Squared() const;
    double Getla3() const;
    double Getla4() const;
    double Getla5() const;

    vector<string> GetParNames();

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

    vector<string> ParNames = {"mh", "MH", "MA", "MC", "la2", "laL", "la1", "la3", "la4", "la5"};

    // MyRandom Rd;
};
#endif