#include "ExpConstraints.h"

ExpCons::ExpCons(Parameters& newPars) : Pars(newPars) {
    Check = 0;
}

// CONSTRAINTS


/**
 * @brief Check relation to Eletroweak bosons
 * 
 * @return int 
 */
int ExpCons::EWBosons() {
    double MW = 80.433; // W boson mass
    double MZ = 91.19;  // Z boson mass

    if (GetMH() + GetMC() >= MW && GetMA() + GetMC() >= MW && GetMA() + GetMH() >= MZ and 2*GetMC() >= MZ)
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
int ExpCons::LEPAnalysis() {
    if (GetMA() <= 100 && GetMH() <= 80 && abs(GetMA() - GetMH()) >= 8) {
        printf("Region ruled out by LEP Analysis\n");
        return 0;
    }
    else
        return 1;
}

/**
 * @brief Verify if all selected constraints are being met
 * 
 * @return int 
 */
int ExpCons::CheckAllExpCons() {
    Check = 0;
    Check = ((EWBosons() & LEPAnalysis()) == 1) ? 1 : 0;

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