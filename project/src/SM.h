#ifndef __STANDARDMODEL__
#define __STANDARDMODEL__

#include <iostream>
#include <string>
#include <cmath>
#include <cstdlib>
#include <complex>
#include <map>

using namespace std;

class StandardModel {
    public:
    StandardModel();
    ~StandardModel() = default;

    // double Get(const string &name) const;
    double GetSMValue(string name);

    double STU(double MH10, double MH20, double mA1, double mC1);
    void My_STU(double MH10, double MH20, double mA1, double mC1, 
                double &S, double &T, double &U);

    // Auxiliary functions for STU Parameters
    double Fbigstu(double x, double y);
    double fsmallstu(double z, double w);
    double Gstu(double x, double y);
    double Ghatstu(double x);

    private:
    double g, G_F, mW, mZ, thetaW, mH, GW, GZ;
    double pi = 3.14;
    map<string, double> SMConstants;
};
#endif