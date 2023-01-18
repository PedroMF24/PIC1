#include "Parameters.h"

// CONSTRUCTOR

Parameters::Parameters() 
{
    la1 = (Mh*Mh)/(v*v);

    MH = 0; // CDM
    MA = 0; // MH3 It is A in IDM paper
    MC = 0; // MHC Charged Higgs
    la2 = 0; // lambda_2
    laL = 0; // la3 + la4 + la5

    GenPars(); // Initialize values
}

void Parameters::GenPars()
{
    // TRandom3* rnd = new TRandom3(0);
    // MH = rnd->Rndm()*1000;
    // MA = rnd->Rndm()*1000;
    // MC = rnd->Rndm()*1000;
    // la2 = rnd->Rndm()*1000;
    // laL = rnd->Rndm()*1000;

    MH = Rd.UniDist(0,1000);
    MA = Rd.UniDist(0,1000);
    MC = Rd.UniDist(0,1000);
    la2 = Rd.UniDist(0,1000); // (-4*M_PI, 4*M_PI); // Perturbativity
    laL = Rd.UniDist(0,1000);

    m22Squared = v*v*laL - 2*MH*MH;
    
    la3 = laL + 2*(MC*MC - MH*MH)/(v*v);
    la4 = laL + 2*(MC*MC - MH*MH)/(v*v);
    la5 = MH*MH - MA*MA;
}

// GETTERS

double Parameters::GetMh() {
    return Mh;
}

double Parameters::Getv() {
    return v;
}

double Parameters::Getla1() {
    return la1;
}

double Parameters::GetMH() {
    return MH;
}

double Parameters::GetMA() {
    return MA;
}

double Parameters::GetMC() {
    return MC;
}

double Parameters::Getla2() {
    return la2;
}

double Parameters::GetlaL() {
    return laL;
}

double Parameters::Getm22Squared() {
    return m22Squared;
}

double Parameters::Getla3() {
    return la3;
}

double Parameters::Getla4() {
    return la4;
}

double Parameters::Getla5() {
    return la5;
}