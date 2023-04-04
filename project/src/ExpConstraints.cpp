#include "../include/ExpConstraints.h"

// CONSTRAINTS

// OK
int ExpCons::WZDecayWidths(double MH, double MA) {
    StandardModel SM;
    double mz = SM.GetSMValue("MZ");
    int check = 1;
    if (MH >= 0 && MH <= 41) {
        check = (MA >= 100) ? 1 : 0;
    } else if (MH >= 41 && MH <= 45) {
        check = ((MA >= mz - MH && MA <= MH + 8) || MA >= 100) ? 1 : 0;
    } else if (MH >= 45 && MH <= 80) {
        check = ((MA >= MH && MA <= MH + 8) || MA >= 100) ? 1 : 0;
    }
    return check;
}

int ExpCons::HChargedLifetime(double MH, double MA, double MC) {
    int check = ((MA >= MC) && (MC - MH <= 0.1)) ? 0 : 1;
    return check;
}

int ExpCons::HiggsWidth(double MH, double laL) {
    if (MH <= 45 && abs(laL) > 0.1) { //  &&
        return 0;
    } else {
        return 1;
    }
    // int check = (abs(laL) <= 0.1) ? 1 : 0;
    // return check;
}

int ExpCons::LUXDMData(double MH, double Mh, double laL) {
    if (MH <= Mh/2) { // MH >= Mh
        double limit_L = 0.03985 - 6.786e-4*MH - 4.828e-7*MH*MH; 
        double limit_U = - 0.03985 + 6.786e-4*MH + 4.828e-7*MH*MH; 

        if (laL >= limit_L && laL <= limit_U) {
            return 1;
        } else {
            return 0;
        }
    } else {
        return 1;
    }
    // int check = (MH >= 45) ? 1 : 0;
    // return check;
}

int ExpCons::EWBosons(double MH, double MA, double MC) {
    StandardModel SM;
    double MW = SM.GetSMValue("MW");
    double MZ = SM.GetSMValue("MZ");

    double aux1 = MH + MC;
    double aux2 = MA + MC;
    double aux3 = MA + MH;

    if (aux1 >= MW && aux2 >= MW && aux3 >= MZ && 2*MC >= MZ)
        return 1;
    else
        return 0;
}


int ExpCons::LEPAnalysis(double MH, double MA, double MC) {
    if (( MH >= MA || MH >= MC || (MC - MH < 0.1) ) || ( MA <= 100 && MH <= 80 && abs(MA - MH) >= 8 )) {
        // printf("Region ruled out by LEP Analysis\n");
        return 0;
    }
    else
        return 1;
}

int ExpCons::RelicDensity(double MH) {
    if (MH < 45) {
        return 0;
    }
    else if (MH <= 60 || MH >= 500) {
        return 1;
    } else {
        return 0;
    }
    // double sig_MHmax;
    // double sig_MHLUX;
    // double OmegaPlanck;
    // double OmegaMH;
    // int check = (sig_MHmax <= sig_MHLUX*OmegaPlanck/OmegaMH) ? 1 : 0;
// 1:86934 × 10−46 + 1:1236 × 10−47 MH=GeV + (−1:32312 × 10−52) (MH=GeV)2
// +
// 1:85167 × 10−28
// (−9:35439 × 1015) (MH=GeV) + 1:12151 × 1015 (MH=GeV)2;
    // return check;
}

int ExpCons::Extras(double MC, double MA) {
    if (MC >= MA) {
        return 1;
    } else {
        return 0;
    }
}


// ==========================================================================
/**
 * @brief Check relation to Eletroweak bosons
 * 
 * @return int 
 */
// int ExpCons::EWBosons(Parameters Pars) {
//     double MW = 80.433; // W boson mass
//     double MZ = 91.19;  // Z boson mass

//     if (Pars.GetMH() + Pars.GetMC() >= MW && Pars.GetMA() + Pars.GetMC() >= MW && Pars.GetMA() + Pars.GetMH() >= MZ and 2*Pars.GetMC() >= MZ)
//         return 1;
//     else {
//         printf("Problems with the EW Bosons mass condition\n");
//         return 0;
//     }
// }

/**
 * @brief Check mass relation with LEP Analysis
 * 
 * @return int 
 */
// int ExpCons::LEPAnalysis(Parameters Pars) {
//     if (Pars.GetMA() <= 100 && Pars.GetMH() <= 80 && abs(Pars.GetMA() - Pars.GetMH()) >= 8) {
//         printf("Region ruled out by LEP Analysis\n");
//         return 0;
//     }
//     else
//         return 1;
// }

// int TheoCons::TwoMins(Parameters Pars) {
//     double aux1 = (Pars.GetMh()*Pars.GetMh())/sqrt(Pars.Getla1()); 
//     double aux2 = Pars.Getm22Squared()/sqrt(Pars.Getla2());

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

int ExpCons::HiggsBoundsSignals(double MC, double Mh, double laL) {
    double ratio = MC/Mh;
    double limit = 0.2*laL + 0.75;
    if (ratio >= limit) {
        // printf("Passed HBS\n");
        return 1;   
    } else {
        // printf("Did not pass Higgs Bounds/Higgs Signals Constraint\n");
        return 0;
    }
}

/**
 * @brief Verify if all selected constraints are being met
 * 
 * @return int 
 */
// int ExpCons::CheckAllExpCons(Parameters Pars) {
//     Check = 0;
//     Check = ((EWBosons(Pars) & LEPAnalysis(Pars)) == 1) ? 1 : 0;

//     if (Check)
//         printf("Passed ExpCons\n");
//     else
//         printf("Did not pass ExpCons\n");
//     // if ( (EWBosons() & LEPAnalysis()) == 1) {
//     //     printf("Passed ExpCons\n");
//     //     return 1;
//     // }
//     // else {
//     //     printf("Did not pass ExpCons\n");
//     //     return 0;
//     // }
//     return Check;
// }

// int ExpCons::GetExpCons() {
//     return Check;
// }