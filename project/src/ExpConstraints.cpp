#include "ExpConstraints.h"

// CONSTRAINTS

int WZDecayWidths(double MH, double MA) {
    double mz = 90.1;
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

int ChargedHLifetime(double MH, double MA, double MC) {
    int check = ((MA >= MC) && (MC - MH <= 0.1)) ? 0 : 1;
    return check;
}

int HiggsWidth(double laL) {
    int check = (abs(laL) <= 0.1) ? 1 : 0;
    return check;
}

int DMData(double MH) {
    int check = (MH >= 45) ? 1 : 0;
    return check;
}


// ==========================================================================
/**
 * @brief Check relation to Eletroweak bosons
 * 
 * @return int 
 */
int ExpCons::EWBosons(Parameters Pars) {
    double MW = 80.433; // W boson mass
    double MZ = 91.19;  // Z boson mass

    if (Pars.GetMH() + Pars.GetMC() >= MW && Pars.GetMA() + Pars.GetMC() >= MW && Pars.GetMA() + Pars.GetMH() >= MZ and 2*Pars.GetMC() >= MZ)
        return 1;
    else {
        printf("Problems with the EW Bosons mass condition\n");
        return 0;
    }
}

/**
 * @brief Check mass relation with LEP Analysis
 * 
 * @return int 
 */
int ExpCons::LEPAnalysis(Parameters Pars) {
    if (Pars.GetMA() <= 100 && Pars.GetMH() <= 80 && abs(Pars.GetMA() - Pars.GetMH()) >= 8) {
        printf("Region ruled out by LEP Analysis\n");
        return 0;
    }
    else
        return 1;
}

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
        printf("Did not pass Higgs Bounds/Higgs Signals Constraint\n");
        return 0;
    }
}

/**
 * @brief Verify if all selected constraints are being met
 * 
 * @return int 
 */
int ExpCons::CheckAllExpCons(Parameters Pars) {
    Check = 0;
    Check = ((EWBosons(Pars) & LEPAnalysis(Pars)) == 1) ? 1 : 0;

    if (Check)
        printf("Passed ExpCons\n");
    else
        printf("Did not pass ExpCons\n");
    // if ( (EWBosons() & LEPAnalysis()) == 1) {
    //     printf("Passed ExpCons\n");
    //     return 1;
    // }
    // else {
    //     printf("Did not pass ExpCons\n");
    //     return 0;
    // }
    return Check;
}

int ExpCons::GetExpCons() {
    return Check;
}