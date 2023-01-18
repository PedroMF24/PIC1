#include "TheoConstraints.h"

TheoCons::TheoCons() {
    Check = 0;
}

int TheoCons::BFB() {
    double aux1 = Getla3() + sqrt(Getla1()*Getla2());
    double aux2 = Getla4() + Getla5() + aux1;

    int check = (Getla1() > 0 && Getla2() > 0 && aux1 > 0 && aux2 > 0) ? 1 : 0;

    if (check) {
        printf("Passed BFB\n");
        return 1;
    }
    else {
        printf("Potencial is not bound from below\n");
        return 0;
    }
}

int TheoCons::TwoMins() {
    double aux1 = (GetMh()*GetMh())/sqrt(Getla1()); 
    double aux2 = Getm22Squared()/sqrt(Getla2());

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

int TheoCons::Perturbativity() {
    if (Getla1() <= 4*M_PI && Getla2() <= 4*M_PI && Getla3() <= 4*M_PI && Getla4() <= 4*M_PI && Getla5() <= 4*M_PI) {
        printf("Passed Perturbativity\n");
        return 1;
    } else {
        printf("Did not pass Perturbativity\n");
        return 0;
    }
}

int TheoCons::CheckAllTheoCons() {
    Check = 0;
    Check = ((BFB() & TwoMins()) == 1) ? 1 : 0;

    if (Check)
        printf("Passed TheoCons\n");
    else
        printf("Did not pass ExpCons\n");

    return Check;
}

int TheoCons::GetCheck() {
    return Check;
}