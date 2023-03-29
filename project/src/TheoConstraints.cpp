#include "TheoConstraints.h"

int TheoCons::CheckResult(int check_bit) {
    int result = (check_bit == 1) ? 1 : 0;
    return result;
}

// vector<Condition> TheoCons::MakeTheoConsVector() {
//     vector<Condition> TConsVec = {{"BFB", BFB}, {"2Mins", TwoMins}, {"Unitary", ScatteringMatrixUnitary}, {"Perturbativity", Perturbativity}}; 
// }

int TheoCons::BFB(Parameters& Pars) {
    double aux1 = Pars.Getla3() + sqrt(Pars.Getla1()*Pars.Getla2());
    double aux2 = Pars.GetlaL() + sqrt(Pars.Getla1()*Pars.Getla2()); // Pars.Getla4() + Pars.Getla5() + aux1;
    
    int check = (Pars.Getla1() > 0 && Pars.Getla2() > 0 && aux1 > 0 && aux2 > 0) ? 1 : 0;
    
    if (check) {
        // printf("Passed BFB\n");
        return 1;
    }
    else {
        // printf("Potencial is not bound from below\n");
        return 0;
    }
}

int TheoCons::TwoMins(Parameters& Pars) {
    double aux1 = (Pars.GetMh()*Pars.GetMh())/sqrt(Pars.Getla1()); 
    double aux2 = Pars.Getm22Squared()/sqrt(Pars.Getla2());

    int check = (aux1 >= aux2) ? 1 : 0;
    if (check) {
        printf("Passed 2 mins\n");
        return 1;
    }
    else {
        printf("Inert vacuum is not garanteed to be global, failed 'TwoMins'\n");
        return 0;
    }
}
// CORRECT
int TheoCons::ScatteringMatrixUnitary(Parameters& Pars) {

    int result = 1;

    // According to IDM revisited
    // double L21EvenP = -Pars.Getla1() - Pars.Getla2() + sqrt(pow(Pars.Getla1() + Pars.Getla2(),2) + Pars.Getla4()*Pars.Getla4());
    // double L21EvenM = -Pars.Getla1() - Pars.Getla2() - sqrt(pow(Pars.Getla1() + Pars.Getla2(),2) + Pars.Getla4()*Pars.Getla4());

    // double  L01EvenP = -Pars.Getla1() - Pars.Getla2() + sqrt(pow(Pars.Getla1() + Pars.Getla2(),2) + Pars.Getla4()*Pars.Getla4());
    // double  L01EvenM = -Pars.Getla1() - Pars.Getla2() - sqrt(pow(Pars.Getla1() + Pars.Getla2(),2) + Pars.Getla4()*Pars.Getla4());

    // double L00EvenP = -3*(Pars.Getla1() + Pars.Getla2()) + sqrt( 9*pow(Pars.Getla1()-Pars.Getla2(),2) + pow(2*Pars.Getla3() + Pars.Getla4(),2) );
    // double L00EvenM = -3*(Pars.Getla1() + Pars.Getla2()) - sqrt( 9*pow(Pars.Getla1()-Pars.Getla2(),2) + pow(2*Pars.Getla3() + Pars.Getla4(),2) );

    // According to Reference in IDM main paper
    double L21EvenP = 0.5*(Pars.Getla1() + Pars.Getla2() + sqrt(pow(Pars.Getla1() - Pars.Getla2(),2) + 4*fabs(Pars.Getla5()*Pars.Getla5())));
    double L21EvenM = 0.5*(Pars.Getla1() + Pars.Getla2() - sqrt(pow(Pars.Getla1() - Pars.Getla2(),2) + 4*fabs(Pars.Getla5()*Pars.Getla5())));

    double  L01EvenP = 0.5*(Pars.Getla1() + Pars.Getla2() + sqrt(pow(Pars.Getla1() - Pars.Getla2(),2) + 4*Pars.Getla4()*Pars.Getla4()));
    double  L01EvenM = 0.5*(Pars.Getla1() + Pars.Getla2() - sqrt(pow(Pars.Getla1() - Pars.Getla2(),2) + 4*Pars.Getla4()*Pars.Getla4()));
    
    double L00EvenP = 0.5*( 3*(Pars.Getla1() + Pars.Getla2()) + sqrt( 9*pow(Pars.Getla1()-Pars.Getla2(),2) +4*pow(2*Pars.Getla3() + Pars.Getla4(),2) ) );
    double L00EvenM = 0.5*( 3*(Pars.Getla1() + Pars.Getla2()) - sqrt( 9*pow(Pars.Getla1()-Pars.Getla2(),2) +4*pow(2*Pars.Getla3() + Pars.Getla4(),2) ) );

    double L21Odd = Pars.Getla3() + Pars.Getla4();
    double L20Odd = Pars.Getla3() - Pars.Getla4();

    double L01OddP = Pars.Getla3() + fabs(Pars.Getla5());
    double L01OddM = Pars.Getla3() - fabs(Pars.Getla5());

    double L00OddP = Pars.Getla3() + 2*Pars.Getla4() + 3*fabs(Pars.Getla5());
    double L00OddM = Pars.Getla3() + 2*Pars.Getla4() - 3*fabs(Pars.Getla5());

    double Eigenvalues[] = {L21EvenP, L21EvenM, L01EvenP, L01EvenM, L00EvenP, L00EvenM, L21Odd, L20Odd, L01OddP, L01OddM, L00OddP, L00OddM};

    for (auto &i : Eigenvalues)
    {
        if (fabs(i) >= 8*M_PI) { // IDM revisited Must be < 8pi, antes tinha só >
            result = 0;
            break;
        }            
    }

    if (result == 1) {
        printf("Passed SMU\n");
    } else {
        printf("Did not pass SMU\n");
    }
    return result;
}

int TheoCons::Perturbativity(Parameters& Pars) {

    int check = (Pars.Getla2() <= 4*M_PI/3) ? 1 : 0;
    // Also for la1?

    if (check) {
        //printf("Passed Perturbativity\n");
        return 1;
    } else {
        //printf("Did not pass Perturbativity\n");
        return 0;
    }
}

// =============================================================

// TheoCons::TheoCons(Parameters& newPars) : Pars(newPars) {
//     Check = 0;
// }
// antes do 'Pars.Get' colocar 'Pars.' 
// int TheoCons::BFB(double la1, double la2, double la3, double laL) {
//     double aux1 = la3 + sqrt(la1*la2);
//     double aux2 = laL + sqrt(la1*la2); // la4 + la5 + aux1;
    
//     int check = (la1 > 0 && la2 > 0 && aux1 > 0 && aux2 > 0) ? 1 : 0;
    
//     if (check) {
//         // printf("Passed BFB\n");
//         return 1;
//     }
//     else {
//         // printf("Potencial is not bound from below\n");
//         return 0;
//     }
// }

// int TheoCons::TwoMins(double la1, double la2, double Mh, double m22Squared) {
//     double aux1 = (Mh*Mh)/sqrt(la1); 
//     double aux2 = m22Squared/sqrt(la2);

//     int check = (aux1 >= aux2) ? 1 : 0;
//     if (check) {
//         printf("Passed 2 mins\n");
//         return 1;
//     }
//     else {
//         printf("Inert vacuum is not garanteed to be global, failed 'TwoMins'\n");
//         return 0;
//     }
// }

// int TheoCons::ScatteringMatrixUnitary(double la1, double la2, double la3, double la4, double la5) {

//     int result = 1;

//     double L21EvenP = 0.5*(la1 + la2 + sqrt(pow(la1 - la2,2) + 4*fabs(la5*la5)));
//     double L21EvenM = 0.5*(la1 + la2 - sqrt(pow(la1 - la2,2) + 4*fabs(la5*la5)));

//     double  L01EvenP = 0.5*(la1 + la2 + sqrt(pow(la1 - la2,2) + 4*la4*la4));
//     double  L01EvenM = 0.5*(la1 + la2 - sqrt(pow(la1 - la2,2) + 4*la4*la4));
    
//     double L00EvenP = 0.5*( 3*(la1 + la2) + sqrt( 9*pow(la1-la2,2) +4*pow(2*la3 + la4,2) ) );
//     double L00EvenM = 0.5*( 3*(la1 + la2) - sqrt( 9*pow(la1-la2,2) +4*pow(2*la3 + la4,2) ) );
    
//     double L21Odd = la3 + la4;
//     double L20Odd = la3 - la4;

//     double L01OddP = la3 + fabs(la5);
//     double L01OddM = la3 - fabs(la5);

//     double L00OddP = la3 + 2*la4 + 3*fabs(la5);
//     double L00OddM = la3 + 2*la4 - 3*fabs(la5);

//     double Eigenvalues[] = {L21EvenP, L21EvenM, L01EvenP, L01EvenM, L00EvenP, L00EvenM, L21Odd, L20Odd, L01OddP, L01OddM, L00OddP, L00OddM};

//     for (auto &i : Eigenvalues)
//     {
//         if (fabs(i) > 8*M_PI) {
//             result = 0;
//             break;
//         }            
//     }

//     if (result == 1) {
//         printf("Passed SMU\n");
//     } else {
//         printf("Did not pass SMU\n");
//     }
//     return result;
// }

// int TheoCons::Perturbativity(double la2) {

//     int check = (la2 <= 4*M_PI/3) ? 1 : 0;

//     if (check) {
//         //printf("Passed Perturbativity\n");
//         return 1;
//     } else {
//         //printf("Did not pass Perturbativity\n");
//         return 0;
//     }
// }

// int TheoCons::CheckAllTheoCons() {
//     Check = 0;
//     Check = ((BFB() & TwoMins() & Perturbativity()) == 1) ? 1 : 0;

//     if (Check)
//         printf("Passed TheoCons\n");
//     else
//         printf("Did not pass TheoCons\n");
//     return Check;
// }

int TheoCons::GetCheck() {
    return Check;
}

// void TheoCons::GenNewPars() {
//     Pars.GenPars();
// }

// Parameters TheoCons::GetPars() {
//     return Pars;
// }

// CORRECT
int TheoCons::BFB_Test(double la1, double la2, double la3, double laL) {
    double aux1 = la3 + sqrt(la1*la2);
    double aux2 = laL + sqrt(la1*la2); // la4 + la5 + aux1;
    
    int check = (la1 > 0 && la2 > 0 && aux1 > 0 && aux2 > 0) ? 1 : 0;
    
    if (check) {
        // printf("Passed BFB\n");
        return 1;
    }
    else {
        // printf("Potencial is not bound from below\n");
        return 0;
    }
}

int TheoCons::BoundFromBelow(double la1, double la2, double la3, double laL, double Mh, double m22Squared) {
    int auxBFB = BFB_Test(la1, la2, la3, laL);
    int aux2Min = TwoMins_Test(la1, la2, Mh, m22Squared);

    int check = auxBFB;// && aux2Min;

    if (check) {
        //printf("Passed Perturbativity\n");
        return 1;
    } else {
        //printf("Did not pass Perturbativity\n");
        return 0;
    }
}

int TheoCons::QuarticCouplings(double la1, double la2, double la3, double la4, double la5, double laL) {
    // Quartic couplings must be perturbative
    int aux1 = (la1 <= 4*M_PI/3) ? 1 : 0;
    int aux2 = (la2 <= 4*M_PI/3) ? 1 : 0;
    int aux3 = (la3 <= 4*M_PI) ? 1 : 0;
    int aux4 = (laL <= 4*M_PI) ? 1 : 0;
    int aux5 = (la3+la4-la5 <= 4*M_PI) ? 1 : 0;

    int check =  aux1 && aux2 && aux3 && aux4 &&aux5 ; // && aux3; // PROBLEMA NO AUX3

    if (check) {
        //printf("Passed Perturbativity\n");
        return 1;
    } else {
        //printf("Did not pass Perturbativity\n");
        return 0;
    }
}

int TheoCons::ScatteringMatrixUnitary_Test(double la1, double la2, double la3, double la4, double la5) {

    int result = 1;

    double L21EvenP = 0.5*(la1 + la2 + sqrt(pow(la1 - la2,2) + 4*fabs(la5*la5)));
    double L21EvenM = 0.5*(la1 + la2 - sqrt(pow(la1 - la2,2) + 4*fabs(la5*la5)));

    double  L01EvenP = 0.5*(la1 + la2 + sqrt(pow(la1 - la2,2) + 4*la4*la4));
    double  L01EvenM = 0.5*(la1 + la2 - sqrt(pow(la1 - la2,2) + 4*la4*la4));
    
    double L00EvenP = 0.5*( 3*(la1 + la2) + sqrt( 9*pow(la1-la2,2) +4*pow(2*la3 + la4,2) ) );
    double L00EvenM = 0.5*( 3*(la1 + la2) - sqrt( 9*pow(la1-la2,2) +4*pow(2*la3 + la4,2) ) );
    
    double L21Odd = la3 + la4;
    double L20Odd = la3 - la4;

    double L01OddP = la3 + fabs(la5);
    double L01OddM = la3 - fabs(la5);

    double L00OddP = la3 + 2*la4 + 3*fabs(la5);
    double L00OddM = la3 + 2*la4 - 3*fabs(la5);

    double Eigenvalues[] = {L21EvenP, L21EvenM, L01EvenP, L01EvenM, L00EvenP, L00EvenM, L21Odd, L20Odd, L01OddP, L01OddM, L00OddP, L00OddM};

    for (auto &i : Eigenvalues)
    {
        if (fabs(i) > 8*M_PI) {
            result = 0;
            break;
        }            
    }

    // if (result == 1) {
    //     // printf("Passed SMU\n");
    // } else {
    //     // printf("Did not pass SMU\n");
    // }
    return result;
}

int TheoCons::TwoMins_Test(double la1, double la2, double Mh, double m22Squared) {
    double aux1 = (Mh*Mh)/sqrt(la1); 
    double aux2 = m22Squared/sqrt(la2);

    int check = (aux1 >= aux2) ? 1 : 0;
    if (check) {
        // printf("Passed 2 mins\n");
        return 1;
    } else {
        // printf("Inert vacuum is not garanteed to be global, failed 'TwoMins'\n");
        return 0;
    }
}

int TheoCons::Perturbativity_Test(double la1, double la2, double la3, double la4, double la5, double laL) {
    // int auxSMU = ScatteringMatrixUnitary_Test(la1, la2, la3, la4, la5);
    int auxQC = QuarticCouplings(la1, la2, la3, la4, la5, laL);

    int check = auxQC; //&& auxSMU;
    if (check) {
        return 1;
    } else {
        return 0;
    }
}


void TheoCons::InitSTUMatrices(double (&ImVdagV)[4][4], complex<double> (&UdagU)[2][2], complex<double> (&VdagV)[4][4], complex<double> (&UdagV)[2][4]) {
    // Matrix UDagU
    // For the Inert 2HDM is the identity matrix in 2x2
    for (int j = 0; j < 2; j++) {
        for (int k = 0; k < 2; k++) {
            if (j == k) {
                UdagU[j][k] = complex<double>(1.0, 0.0);
            }
            else {
                UdagU[j][k] = complex<double>(0.0, 0.0);
            }
        }
    }

    // Matrix UDagV
    // 2x4 complex matrix
    for (int j = 0; j < 2; j++) {
        for (int k = 0; k < 4; k++) {
            UdagV[j][k] = complex<double>(0.0, 0.0);
        }
    }
    UdagV[0][0] = complex<double>(0.0, 1.0);
    UdagV[0][1] = complex<double>(1.0, 0.0);
    UdagV[1][2] = complex<double>(1.0, 0.0);
    UdagV[1][3] = complex<double>(0.0, 1.0);

    // Matrix ImVdagV
    // 4x4 real matrix
    // Set all the values to 0
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            ImVdagV[i][j] = 0;
        }
    }
    // Set specific values
    ImVdagV[0][1] = -1;
    ImVdagV[1][0] = 1;
    ImVdagV[2][3] = 1;
    ImVdagV[3][2] = -1;

    // Matrix VdagV
    // 4x4 complex matrix
    // Set matrix to identity
    for (int j = 0; j < 4; j++) {
        for (int k = 0; k < 4; k++) {
            if (j == k) {
                VdagV[j][k] = complex<double>(1.0, 0.0);
            }
            else {
                VdagV[j][k] = complex<double>(0.0, 0.0);
            }
        }
    }

    VdagV[0][1] = complex<double>(0.0, -1.0);
    VdagV[1][0] = complex<double>(0.0, 1.0);
    VdagV[2][3] = complex<double>(0.0, 1.0);
    VdagV[3][2] = complex<double>(0.0, -1.0);
}

// Check if m11 is good
void TheoCons::InitSTUVars(double (&mneu)[4], double (&mch)[2], double &m11, double &MH, double &MA, double &MC) {
    StandardModel SM;
    mneu[0] = SM.GetSMValue("MZ"); // model.SM.SM.GetSMValue("MZ")
    mneu[1] = m11;
    mneu[2] = MH;
    mneu[3] = MA;

    mch[0] = SM.GetSMValue("MW"); // model.SM.GetSMValue("MW")
    mch[1] = MC;
    // cout << mch[1] << " " << mneu[1] << endl;
}

void TheoCons::CalculateSTU(double (&mneu)[4], double (&mch)[2], double (&ImVdagV)[4][4], 
        complex<double> (&UdagU)[2][2], complex<double> (&VdagV)[4][4], 
        complex<double> (&UdagV)[2][4], double& S, double& T, double& U) {

    int nns = 4;
    int ncs = 2;

    int j, k;
    double mW2, mZ2, mh2, z[nns], w[nns], zp[ncs], wp[ncs], wH, zH;
    double sw2, cw2;
    double g, alpha, G_F, mW, mZ, thetaW, mh, GW, GZ, pi;
    // double model.Gstu, model.model.Ghatstu, model.Fbigstu;

    StandardModel SM;

    // Common block data
    // mW = model.GetSMValue("MW");
    // G_F = model.GetSMValue("G_FERMI");
    // g = sqrt(8.0 * mW * mW * G_F / sqrt(2.0)); 
    // alpha = model.GetSMValue("ALPHA"); 
    // mZ = model.GetSMValue("MZ"); 
    // thetaW = asin(sqrt(model.GetSMValue("S2TW")));
    // mh = model.GetSMValue("MHIGGS"); 
    // GW = model.GetSMValue("GAW"); // GAW
    // GZ = model.GetSMValue("GAZ"); // GAZ

    mW = SM.GetSMValue("MW");
    G_F = SM.GetSMValue("G_FERMI");
    g = sqrt(8.0 * mW * mW * G_F / sqrt(2.0)); 
    alpha = SM.GetSMValue("ALPHA"); 
    mZ = SM.GetSMValue("MZ"); 
    thetaW = asin(sqrt(SM.GetSMValue("S2TW")));
    mh = SM.GetSMValue("MHIGGS"); 
    GW = SM.GetSMValue("GAW"); // GAW
    GZ = SM.GetSMValue("GAZ"); // GAZ

    pi = acos(-1);
    // int iboson = data[10];

    mW2 = mW * mW;
    mZ2 = mZ * mZ;
    mh2 = mh * mh;
    sw2 = sin(thetaW) * sin(thetaW);
    cw2 = cos(thetaW) * cos(thetaW);

    for (j = 0; j < nns; ++j)
    {
        z[j] = pow(mneu[j], 2) / mZ2;
        w[j] = pow(mneu[j], 2) / mW2;
    }

    for (j = 0; j < ncs; ++j)
    {
        zp[j] = pow(mch[j], 2) / mZ2;
        wp[j] = pow(mch[j], 2) / mW2;
    }

    zH = pow(mh, 2) / mZ2;
    wH = pow(mh, 2) / mW2;

    // Evaluate T from the formulas in arXiv: 0802.4353
    T = 0.0;

    for (j = 1; j < ncs; ++j)
    {
        for (k = 1; k < nns; ++k)
        {
            T += pow(fabs(UdagV[j][k]), 2) * SM.Fbigstu(pow(mch[j], 2), pow(mneu[k], 2));
        }
    }

    for (j = 1; j < nns - 1; ++j)
    {
        for (k = j + 1; k < nns; ++k)
        {
            T -= pow(ImVdagV[j][k], 2) * SM.Fbigstu(pow(mneu[j], 2), pow(mneu[k], 2));
        }
    }

    for (j = 1; j < ncs - 1; ++j)
    {
        for (k = j + 1; k < ncs; ++k)
        {
            T -= 2.0 * pow(fabs(UdagU[j][k]), 2) * SM.Fbigstu(pow(mch[j], 2), pow(mch[k], 2));
        }
    }

    for (j = 1; j < nns; ++j)
    {
        T += (3.0 * pow(ImVdagV[0][j], 2) * (SM.Fbigstu(mZ2, pow(mneu[j], 2)) - SM.Fbigstu(mW2, pow(mneu[j], 2))) );
    }

    T -= (3.0 * (SM.Fbigstu(mZ2, mh2) - SM.Fbigstu(mW2, mh2)) );

    T *= (1.0 / (16.0 * pi * sw2 * mW2)); // sw? g^2/64pi^2?
    // T *= (g*g/(64*pi*pi*mW2));

    // Evaluate S from the formulas in arXiv: 0802.4353
    S = 0.0;

    for (j = 1; j < ncs; ++j)
    {
        S += pow(2.0 * sw2 - real(UdagU[j][j]), 2) * SM.Gstu(zp[j], zp[j]);
    }

    for (j = 1; j < ncs - 1; ++j)
    {
        for (k = j + 1; k < ncs; ++k)
        {
            S += 2.0 * pow(fabs(UdagU[j][k]), 2) * SM.Gstu(zp[j], zp[k]);
        }
    }

    for (j = 1; j < nns - 1; ++j)
    {
        for (k = j + 1; k < nns; ++k)
        {
            S += pow(ImVdagV[j][k], 2) * SM.Gstu(z[j], z[k]);
        }
    }

    for (j = 1; j < ncs; ++j)
    {
        S -= 2.0 * real(UdagU[j][j]) * log(pow(mch[j], 2));
    }

    for (j = 1; j < nns; ++j)
    {
        S += real(VdagV[j][j]) * log(pow(mneu[j], 2));
        S += pow(ImVdagV[0][j], 2) * SM.Ghatstu(z[j]);
    }

        S -= (SM.Ghatstu(zH) + log(pow(mh, 2)));

        S *= 1/(24*M_PI); // S *= (1.0 / (24.0 * pi * sw2));
        // S *= (g*g/(384*pi*pi*cw2));

    // Evaluate U from the formulas in arXiv: 0802.4353
        U = 0.0;

    for (int j = 1; j < ncs; ++j) 
    {
        for (int k = 1; k < nns; ++k) 
        {
            U += pow(fabs(UdagV[j][k]), 2) * SM.Gstu(wp[j], w[k]);
        }
    }

    for (int j = 1; j < ncs; ++j) 
    {
        U -= pow((2.0 * sw2 - real(UdagU[j][j])), 2) * SM.Gstu(zp[j], zp[j]);
    }

    for (int j = 1; j < ncs - 1; ++j) 
    {
        for (int k = j + 1; k < ncs; ++k) 
        {
            U -= 2.0 * pow(fabs(UdagU[j][k]), 2) * SM.Gstu(zp[j], zp[k]);
        }
    }

    for (int j = 1; j < nns - 1; ++j) 
    {
        for (int k = j + 1; k < nns; ++k) 
        {
            U -= pow(ImVdagV[j][k], 2) * SM.Gstu(z[j], z[k]);
        }
    }

    for (int j = 1; j < nns; ++j) {
        U += (pow(ImVdagV[0][j], 2) * (SM.Ghatstu(w[j]) - SM.Ghatstu(z[j])) );
    }

    U -= (SM.Ghatstu(wH) + SM.Ghatstu(zH));
    U *= (1.0 / (24.0 * M_PI));
}

/*

// Evaluate T from the formulas in arXiv: 0802.4353
    T = 0.0;

    for (j = 1; j < ncs; ++j)
    {
        for (k = 1; k < nns; ++k)
        {
            T += pow(fabs(UdagV[j][k]), 2) * model.Fbigstu(pow(mch[j], 2), pow(mneu[k], 2));
        }
    }

    for (j = 1; j < nns - 1; ++j)
    {
        for (k = j + 1; k < nns; ++k)
        {
            T -= pow(ImVdagV[j][k], 2) * model.Fbigstu(pow(mneu[j], 2), pow(mneu[k], 2));
        }
    }

    for (j = 1; j < ncs - 1; ++j)
    {
        for (k = j + 1; k < ncs; ++k)
        {
            T -= 2.0 * pow(fabs(UdagU[j][k]), 2) * model.Fbigstu(pow(mch[j], 2), pow(mch[k], 2));
        }
    }

    for (j = 1; j < nns; ++j)
    {
        T += (3.0 * pow(ImVdagV[0][j], 2) * (model.Fbigstu(mZ2, pow(mneu[j], 2)) - model.Fbigstu(mW2, pow(mneu[j], 2))) );
    }

    T -= (3.0 * (model.Fbigstu(mZ2, mh2) - model.Fbigstu(mW2, mh2)) );

    T *= (1.0 / (16.0 * pi * sw2 * mW2)); // sw? g^2/64pi^2?
    // T *= (g*g/(64*pi*pi*mW2));

    // Evaluate S from the formulas in arXiv: 0802.4353
    S = 0.0;

    for (j = 1; j < ncs; ++j)
    {
        S += pow(2.0 * sw2 - real(UdagU[j][j]), 2) * model.Gstu(zp[j], zp[j]);
    }

    for (j = 1; j < ncs - 1; ++j)
    {
        for (k = j + 1; k < ncs; ++k)
        {
            S += 2.0 * pow(fabs(UdagU[j][k]), 2) * model.Gstu(zp[j], zp[k]);
        }
    }

    for (j = 1; j < nns - 1; ++j)
    {
        for (k = j + 1; k < nns; ++k)
        {
            S += pow(ImVdagV[j][k], 2) * model.Gstu(z[j], z[k]);
        }
    }

    for (j = 1; j < ncs; ++j)
    {
        S -= 2.0 * real(UdagU[j][j]) * log(pow(mch[j], 2));
    }

    for (j = 1; j < nns; ++j)
    {
        S += real(VdagV[j][j]) * log(pow(mneu[j], 2));
        S += pow(ImVdagV[0][j], 2) * model.Ghatstu(z[j]);
    }

        S -= (model.Ghatstu(zH) + log(pow(mh, 2)));

        S *= 1/(24*M_PI); // S *= (1.0 / (24.0 * pi * sw2));
        // S *= (g*g/(384*pi*pi*cw2));

    // Evaluate U from the formulas in arXiv: 0802.4353
        U = 0.0;

    for (int j = 1; j < ncs; ++j) 
    {
        for (int k = 1; k < nns; ++k) 
        {
            U += pow(fabs(UdagV[j][k]), 2) * model.Gstu(wp[j], w[k]);
        }
    }

    for (int j = 1; j < ncs; ++j) 
    {
        U -= pow((2.0 * sw2 - real(UdagU[j][j])), 2) * model.Gstu(zp[j], zp[j]);
    }

    for (int j = 1; j < ncs - 1; ++j) 
    {
        for (int k = j + 1; k < ncs + 1; ++k) 
        {
            U -= 2.0 * pow(fabs(UdagU[j][k]), 2) * model.Gstu(zp[j], zp[k]);
        }
    }

    for (int j = 1; j < nns - 1; ++j) 
    {
        for (int k = j + 1; k < nns; ++k) 
        {
            U -= pow(ImVdagV[j][k], 2) * model.Gstu(z[j], z[k]);
        }
    }

    for (int j = 1; j < nns; ++j) {
        U += (pow(ImVdagV[0][j], 2) * (model.Ghatstu(w[j]) - model.Ghatstu(z[j])) );
    }

    U -= (model.Ghatstu(wH) + model.Ghatstu(zH));
    U *= (1.0 / (24.0 * M_PI));

*/


int TheoCons::STU_Check(double &S, double &T, double &U) {
    const double Shat = 0.05;
    const double That = 0.09;
    const double Uhat = 0.01;

    double xSTU[3] = {S - Shat, T - That, U - Uhat};
    double aux_arr[3];
    double ChiSqSTU = 0;

    /*
    * 
    */

    const double C_Inverse[3][3] = {{836.17, -952.128, -445.745},
                            {-952.128, 1276.6, 696.809},
                            {-445.745, 696.809, 506.383}};

    // const double C_Inverse[3][3] = {{0.0121, 0.0129, -0.0071},
    //                                 {0.0129, 0.0169, -0.0119},
    //                                 {-0.0071, -0.0119, 0.0121}};

    // Product of matrices
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            aux_arr[i] = C_Inverse[i][j] * xSTU[j];
        }
        ChiSqSTU += aux_arr[i] * xSTU[i];
    }

    // Inner product function does it better!
    /*
    * The arguments for the std::inner_product function are as follows:
    * 1. The first two arguments are the two vectors (or arrays) to be multiplied.
    * 2. The third argument is the matrix (or array) to be multiplied by the vectors.
    * 3. The fourth argument is the initial value of the dot product (default is 0.0).
    */
    
    ChiSqSTU = inner_product(xSTU, xSTU + 3, &C_Inverse[0][0], 0.0);
    
    int check = (ChiSqSTU <= 8.025) ? 1 : 0;
    return check;
}

// int MyST_Check(double &S, double &T, double &U) {
//     const double S_error = 0.011;
//     const double T_error = 0.013;
//     // const double U_error = 0.011;

//     double SUL = S + S_error;
//     double SLL = S - S_error;
//     double TUL = T + T_error;
//     double TLL = T - T_error;

//     int check = (S > SLL && S < SUL && T > TLL && T < TUL) ? 1 : 0;
//     return check;
// }

// int TheoCons::STU_Test(double m11, double MH, double MA, double MC) {

//     // STU Matrices
//     double ImVdagV[4][4];
//     complex<double> UdagU[2][2], VdagV[4][4], UdagV[2][4];

//     InitSTUMatrices(ImVdagV, UdagU, VdagV, UdagV);

//     double mneu[4], mch[2];
//     InitSTUVars(mneu, mch, m11, MH, MA, MC);

//     double S, T, U;
//     CalculateSTU(mneu, mch, ImVdagV, UdagU, VdagV, UdagV, S, T, U);

//     // return STU_Check(S, T, U);
//     return MyST_Check(S, T, U);
// }

vector<double> TheoCons::ST_graph_prep(double m11, double MH, double MA, double MC) {
    // STU Matrices
    double ImVdagV[4][4];
    complex<double> UdagU[2][2], VdagV[4][4], UdagV[2][4];

    InitSTUMatrices(ImVdagV, UdagU, VdagV, UdagV);

    double mneu[4], mch[2];
    InitSTUVars(mneu, mch, m11, MH, MA, MC);

    double S, T, U;
    CalculateSTU(mneu, mch, ImVdagV, UdagU, VdagV, UdagV, S, T, U);
    // cout << "S " << S << " T " << T << " U " << U << endl;

    vector<double> STU;
    STU.push_back(S);
    STU.push_back(T);
    STU.push_back(U);

    // for (auto &ObParam : STU)
    // {
    //     cout << ObParam << " ";
    // }
    // cout << endl;

    return STU;
}


int TheoCons::ST(double m11, double MH, double MA, double MC, double &S, double &T, double &U) {

    double ImVdagV[4][4];
    complex<double> UdagU[2][2], VdagV[4][4], UdagV[2][4];
    double Corr;
    double a1, a2, a3, a4, a5, a6;

    // Define common variables
    double mneu[4], mch[2];
    InitSTUVars(mneu, mch, m11, MH, MA, MC);
    // cout << "Depois de init " << mch[1] << " " << mneu[1] << endl;

    // Call Evaluate_Matrices and Calculate_STU functions
    InitSTUMatrices(ImVdagV, UdagU, VdagV, UdagV);
    CalculateSTU(mneu, mch, ImVdagV, UdagU, VdagV, UdagV, S, T, U);

    // Define a1 to a6 constants
    a1 = -0.34215919;
    a2 = 0.77604111;
    a3 = -0.52618813;
    a4 = -0.03202802;
    a5 = 0.05277964;
    a6 = 0.00136192;

    // Calculate Corr
    Corr = a1 * pow(S, 2) + a2 * S * T + a3 * pow(T, 2) + a4 * S + a5 * T + a6;

    // Calculate ST
    if (Corr > 0) {
        return 1;
    } else {
        return 0;
    }
}

int TheoCons::STU_Test(double m11, double MH, double MA, double MC, double &S, double &T, double &U) {

    double ImVdagV[4][4];
    complex<double> UdagU[2][2], VdagV[4][4], UdagV[2][4];
    double Corr;
    double a1, a2, a3, a4, a5, a6;
    double UU, ST;
    UU = ST = 0;

    // Define common variables
    double mneu[4], mch[2];
    InitSTUVars(mneu, mch, m11, MH, MA, MC);
    // cout << "Depois de init " << mch[1] << " " << mneu[1] << endl;

    // Call Evaluate_Matrices and Calculate_STU functions
    InitSTUMatrices(ImVdagV, UdagU, VdagV, UdagV);
    CalculateSTU(mneu, mch, ImVdagV, UdagU, VdagV, UdagV, S, T, U);

    // Define a1 to a6 constants
    a1 = -0.34215919;
    a2 = 0.77604111;
    a3 = -0.52618813;
    a4 = -0.03202802;
    a5 = 0.05277964;
    a6 = 0.00136192;

    // Calculate Corr
    Corr = a1 * pow(S, 2) + a2 * S * T + a3 * pow(T, 2) + a4 * S + a5 * T + a6;

    // U check
    double ULL = 0.03-0.1;
    double UUL = 0.03+0.1;

    if (U >= ULL && U <= UUL && Corr > 0) {
        return 1;
    } else {
        return 0;
    }
}