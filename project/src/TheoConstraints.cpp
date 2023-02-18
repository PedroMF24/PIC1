#include "TheoConstraints.h"

int TheoCons::BFB(Parameters Pars) {
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

int TheoCons::TwoMins(Parameters Pars) {
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
int TheoCons::ScatteringMatrixUnitary(Parameters Pars) {

    int result = 1;

    // According to IDM revisited
    // double L21EvenP = -Pars.Getla1() - Pars.Getla2() + sqrt(pow(Pars.Getla1() + Pars.Getla2(),2) + Pars.Getla4()*Pars.Getla4());
    // double L21EvenM = -Pars.Getla1() - Pars.Getla2() - sqrt(pow(Pars.Getla1() + Pars.Getla2(),2) + Pars.Getla4()*Pars.Getla4());

    // double  L01EvenP = -Pars.Getla1() - Pars.Getla2() + sqrt(pow(Pars.Getla1() + Pars.Getla2(),2) + Pars.Getla4()*Pars.Getla4());
    // double  L01EvenM = -Pars.Getla1() - Pars.Getla2() - sqrt(pow(Pars.Getla1() + Pars.Getla2(),2) + Pars.Getla4()*Pars.Getla4());

    // double L00EvenP = -3*(Pars.Getla1() + Pars.Getla2()) + sqrt( 9*pow(Pars.Getla1()-Pars.Getla2(),2) + pow(2*Pars.Getla3() + Pars.Getla4(),2) );
    // double L00EvenM = -3*(Pars.Getla1() + Pars.Getla2()) - sqrt( 9*pow(Pars.Getla1()-Pars.Getla2(),2) + pow(2*Pars.Getla3() + Pars.Getla4(),2) );

    // According to Reference in IDM main paper
    double L21EvenP = 0.5*(Pars.Getla1() + Pars.Getla2() + sqrt(pow(Pars.Getla1() - Pars.Getla2(),2) + 4*abs(Pars.Getla5()*Pars.Getla5())));
    double L21EvenM = 0.5*(Pars.Getla1() + Pars.Getla2() - sqrt(pow(Pars.Getla1() - Pars.Getla2(),2) + 4*abs(Pars.Getla5()*Pars.Getla5())));

    double  L01EvenP = 0.5*(Pars.Getla1() + Pars.Getla2() + sqrt(pow(Pars.Getla1() - Pars.Getla2(),2) + 4*Pars.Getla4()*Pars.Getla4()));
    double  L01EvenM = 0.5*(Pars.Getla1() + Pars.Getla2() - sqrt(pow(Pars.Getla1() - Pars.Getla2(),2) + 4*Pars.Getla4()*Pars.Getla4()));
    
    double L00EvenP = 0.5*( 3*(Pars.Getla1() + Pars.Getla2()) + sqrt( 9*pow(Pars.Getla1()-Pars.Getla2(),2) +4*pow(2*Pars.Getla3() + Pars.Getla4(),2) ) );
    double L00EvenM = 0.5*( 3*(Pars.Getla1() + Pars.Getla2()) - sqrt( 9*pow(Pars.Getla1()-Pars.Getla2(),2) +4*pow(2*Pars.Getla3() + Pars.Getla4(),2) ) );

    double L21Odd = Pars.Getla3() + Pars.Getla4();
    double L20Odd = Pars.Getla3() - Pars.Getla4();

    double L01OddP = Pars.Getla3() + abs(Pars.Getla5());
    double L01OddM = Pars.Getla3() - abs(Pars.Getla5());

    double L00OddP = Pars.Getla3() + 2*Pars.Getla4() + 3*abs(Pars.Getla5());
    double L00OddM = Pars.Getla3() + 2*Pars.Getla4() - 3*abs(Pars.Getla5());

    double Eigenvalues[] = {L21EvenP, L21EvenM, L01EvenP, L01EvenM, L00EvenP, L00EvenM, L21Odd, L20Odd, L01OddP, L01OddM, L00OddP, L00OddM};

    for (auto &i : Eigenvalues)
    {
        if (abs(i) >= 8*M_PI) { // IDM revisited Must be < 8pi, antes tinha só >
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

int TheoCons::Perturbativity(Parameters Pars) {

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

//     double L21EvenP = 0.5*(la1 + la2 + sqrt(pow(la1 - la2,2) + 4*abs(la5*la5)));
//     double L21EvenM = 0.5*(la1 + la2 - sqrt(pow(la1 - la2,2) + 4*abs(la5*la5)));

//     double  L01EvenP = 0.5*(la1 + la2 + sqrt(pow(la1 - la2,2) + 4*la4*la4));
//     double  L01EvenM = 0.5*(la1 + la2 - sqrt(pow(la1 - la2,2) + 4*la4*la4));
    
//     double L00EvenP = 0.5*( 3*(la1 + la2) + sqrt( 9*pow(la1-la2,2) +4*pow(2*la3 + la4,2) ) );
//     double L00EvenM = 0.5*( 3*(la1 + la2) - sqrt( 9*pow(la1-la2,2) +4*pow(2*la3 + la4,2) ) );
    
//     double L21Odd = la3 + la4;
//     double L20Odd = la3 - la4;

//     double L01OddP = la3 + abs(la5);
//     double L01OddM = la3 - abs(la5);

//     double L00OddP = la3 + 2*la4 + 3*abs(la5);
//     double L00OddM = la3 + 2*la4 - 3*abs(la5);

//     double Eigenvalues[] = {L21EvenP, L21EvenM, L01EvenP, L01EvenM, L00EvenP, L00EvenM, L21Odd, L20Odd, L01OddP, L01OddM, L00OddP, L00OddM};

//     for (auto &i : Eigenvalues)
//     {
//         if (abs(i) > 8*M_PI) {
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

int TheoCons::Perturbativity_Test(double la2) {

    int check = (la2 <= 4*M_PI/3) ? 1 : 0;

    if (check) {
        //printf("Passed Perturbativity\n");
        return 1;
    } else {
        //printf("Did not pass Perturbativity\n");
        return 0;
    }
}