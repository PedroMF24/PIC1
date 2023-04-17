#include "include/SM.h"

/**
 * @brief Constructor: Initialize map of SM constants
 * 
 */
StandardModel::StandardModel() {                // Units in GeV
    SMConstants["MW"] = 80.35797;               // W boson mass
    SMConstants["GAW"] = 2.08430;                // 2.085; Weak current coupling
    SMConstants["MZ"] = 91.15348;               // Z boson mass
    SMConstants["GAZ"] = 2.49427;               // 2.4952; Neutral current coupling
    SMConstants["E_MASS"] = 0.510998928e-03;    // Electron mass
    SMConstants["MU_MASS"] = 1.056583715e-01;   // Mu mass
    SMConstants["TAU_MASS"] = 1.77682;          // Tau mass
    SMConstants["TOP_MASS"] = 172.5;            // Top mass
    SMConstants["TOP_MASSZ"] = 171.0;           // 
    SMConstants["CHARM_MASS"] = 1.64;           // Charm mass
    SMConstants["CHARM_MASSZ"] = 0.63;          // 
    SMConstants["UP_MASS"] = 0.0023;            // Up mass
    SMConstants["DOWN_MASS"] = 0.0048;          // Down mass
    SMConstants["STRANGE_MASS"] = 0.095;        // Strange mass
    SMConstants["BOTTOM_MASS"] = 4.75;          // Bottom mass
    SMConstants["BOTTOM_MASSZ"] = 2.89;         // 
    SMConstants["ALPHA"] = 1.0/137.035999074;   // Fine structure constant
    SMConstants["ALPHAZ"] = 1.0/127.916;
    SMConstants["S2TW"] = 0.23116;
    SMConstants["HBARC"] = 0.1973269718;        // Reduced planck's constant times velocity of light
    SMConstants["G_FERMI"] = 1.1663787e-05;     // Fermi's constant
    SMConstants["MHIGGS"] = 125.1;
    SMConstants["THETA_W"] = acos(SMConstants["MW"] / SMConstants["MZ"] );
}

/**
 * @brief Return value of SM constant
 * 
 * @param name of constant 
 * @return double 
 */
double StandardModel::GetSMValue(string name) const {
    auto it = SMConstants.find(name);
    if (it == SMConstants.end()) {
        fprintf(stderr, "**No SM constant called %s was found\n", name.c_str());
        return -1;
    }
    return it->second;
}

/*
double StandardModel::Get(const string &name) const {
    if (name == "g") return g;
    else if (name == "G_F") return G_F;
    else if (name == "mW") return mW;
    else if (name == "mZ") return mZ;
    else if (name == "thetaW") return thetaW;
    else if (name == "mH") return mH;
    else if (name == "GW") return GW;
    else if (name == "GZ") return GZ;
    else if (name == "pi") return pi;
    else return 0;
}*/
/*
void StandardModel::My_STU(double MH10, double MH20, double mA1, double mC1, 
            double &S, double &T, double &U)
{
    int j, k;
    int nns = 4;
    int ncs = 2;

    double mneu[nns], mch[ncs];
    double ImVdagV[4][4], UdagU[2][2], VdagV[4][4], UdagV[2][4];
    double a1, a2, a3, a4, a5, a6;
    double v, v1, v2, v3;

    mneu[0] = mZ;
    mneu[1] = MH10;
    mneu[2] = MH20;
    mneu[3] = mA1;

    mch[0] = mW;
    mch[1] = mC1;

    Evaluate_Matrices(ImVdagV, UdagU, VdagV, UdagV);

    Calculate_STU(mneu, mch, ImVdagV, UdagU, VdagV, UdagV, S, T, U);
}


double StandardModel::STU(double MH10, double MH20, double mA1, double mC1) {
    double ST, UU;
    if (ST(MH10, MH20, mA1, mC1) == 1.0 && UU(MH10, MH20, MA1, MC1) == 1.0) {
        return 1.0;
    } else {
        return 0.0;
    }
}

double ST(double MH10, double MH20, double mA1, double mC1) 
{
    int j, k, iboson, nns, ncs;
    double g, alpha, G_F, mW, mZ, thetaW, GW, GZ, pi, mh;
    double ImVdagV[4][4];
    complex<double> UdagU[2][2], VdagV[4][4], UdagV[2][4];
    double mch[2], mneu[4];
    double S, T, U, Corr;
    double a1, a2, a3, a4, a5, a6;

    g = 0.65;
    alpha = 0.0075;
    G_F = 1.1663787e-5;
    mW = 80.385;
    mZ = 91.1876;
    thetaW = 0.5;
    mh = 125.7;
    GW = mW * mW / (mZ * mZ * cos(thetaW) * cos(thetaW));
    GZ = mW * mW / (mZ * mZ * sin(thetaW) * sin(thetaW));
    pi = 3.14159265358979323846;
    iboson = 0;

    mneu[1] = MZ;
    mneu[2] = MH10;
    mneu[3] = MH20;
    mneu[4] = mA1;

    mch[1] = MW;
    mch[2] = mC1;

    Evaluate_Matrices(ImVdagV, UdagU, VdagV, UdagV);
    Calculate_STU(mneu, mch, ImVdagV, UdagU, VdagV, UdagV, S, T, U);

    a1 = -0.34215919;
    a2 = 0.77604111;
    a3 = -0.52618813;
    a4 = -0.03202802;
    a5 = 0.05277964;
    a6 = 0.00136192;

    Corr = a1 * pow(S, 2) + a2 * S * T + a3 * pow(T, 2) + a4 * S + a5 * T + a6;

    if (Corr > 0) {
        return 1;
    }
    else {
        return 0;
    }
}*/

/* Auxiliary functions */

double StandardModel::Fbigstu(double x, double y) {
    double Fbigstu;

    if (x == y) {
        Fbigstu = 0.0;
    } else {
        Fbigstu = (x + y) / 2.0 - x * y / (x - y) * log(x / y);
    }

    return Fbigstu;
}

double StandardModel::fsmallstu(double z, double w) {
    double fsmallstu;

    if (w > 0.0) {
        fsmallstu = sqrt(w) * log(fabs((z - sqrt(w)) / (z + sqrt(w))));
    } else if (w == 0.0) {
        fsmallstu = 0.0;
    } else {
        fsmallstu = 2.0 * sqrt(-w) * atan(sqrt(-w) / z);
    }

    return fsmallstu;
}

double StandardModel::Gstu(double x, double y) {
    double Gstu;

    if (x == y) {
        Gstu = -16.0/3.0 + 5.0*(x+y) - 2.0*pow(x-y,2.0) + 3.0*2.0*y + 
    (1.0 - 2.0*(x+y) + pow(x-y,2.0))*
    fsmallstu(x+y-1.0,1.0-2.0*(x+y)+pow(x-y,2.0));
    }
    else {
        Gstu = -16.0/3.0 + 5.0*(x+y) - 2.0*pow(x-y,2.0) + 3.0*((x*x+y*y)
    /(x-y) - x*x + y*y + pow(x-y,3.0)/3.0)*log(x/y) + 
    (1.0 - 2.0*(x+y) + pow(x-y,2.0))*
    fsmallstu(x+y-1.0,1.0-2.0*(x+y)+pow(x-y,2.0));
    }

    return Gstu;
}

// ?
double StandardModel::Ghatstu(double x) {
    double Ghatstu;

    if (x == 1.0) {
        Ghatstu = -79.0/3.0 + 9.0*x - 2.0*x*x -18.0 +
    (12.0 - 4.0*x + x*x)*fsmallstu(x,x*x-4.0*x);
    }
    else {
        Ghatstu = -79.0/3.0 + 9.0*x - 2.0*x*x + (-10.0 + 18.0*x -
    6.0*x*x + pow(x,3.0) - 9.0*(x+1.0)/(x-1.0))*log(x) +
    (12.0 - 4.0*x + x*x)*fsmallstu(x,x*x-4.0*x);
    }

    return Ghatstu;
}

// void solve_cubic_eq(complex<double>& x0, complex<double>& x1, complex<double>& x2, complex<double> poly[4]) {

//     complex<double> zeta{-0.5, 0.8660254037844386};  // sqrt3(1)
//     complex<double> zeta2{-0.5,-0.8660254037844386};  // sqrt3(1)**2
//     double third = 0.3333333333333333;                    // 1/3
//     complex<double> a_1 = pow(poly[4], -1.0);
//     complex<double> E1 = -poly[3] * a_1;
//     complex<double> E2 = poly[2] * a_1;
//     complex<double> E3 = -poly[1] * a_1;

//     complex<double> s0 = E1;
//     complex<double> E12 = E1 * E1;
//     complex<double> A = 2.0 * E1 * E12 - 9.0 * E1 * E2 + 27.0 * E3;  // s1^3 + s2^3
//     complex<double> B = E12 - 3.0 * E2;  // s1 s2
//     // quadratic equation: z^2-Az+B^3=0  where roots are equal to s1^3 and s2^3
//     complex<double> A2 = A * A;
//     complex<double> delta = sqrt(A2 - 4.0 * (B * B * B));
//     complex<double> s1;
//     if (real(conj(A) * delta) >= 0.0) { // scallar product to decide the sign yielding bigger magnitude
//         s1 = pow(0.5 * (A + delta), third);
//     } else {
//         s1 = pow(0.5 * (A - delta), third);
//     }
//     complex<double> s2;
//     if (s1 == complex<double>{0.0, 0.0}) {
//         s2 = complex<double>{0.0, 0.0};
//     } else {
//         s2 = B / s1;
//     }

//     x0 = third * (s0 + s1 + s2);
//     x1 = third * (s0 + s1 * zeta2 + s2 * zeta);
//     x2 = third * (s0 + s1 * zeta + s2 * zeta2);  
// }