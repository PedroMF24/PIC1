#include "TheoConstraints.h"

TheoCons::TheoCons(Parameters& newPars) : Pars(newPars) {
    Check = 0;
}

int TheoCons::BFB() {
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

int TheoCons::TwoMins() {
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

int TheoCons::ScatteringMatrixUnitary() {

    int result = 1;

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
        if (abs(i) > 8*M_PI) {
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

int TheoCons::Perturbativity() {

    int check = (Pars.Getla2() <= 4*M_PI/3) ? 1 : 0;

    if (check) {
        //printf("Passed Perturbativity\n");
        return 1;
    } else {
        //printf("Did not pass Perturbativity\n");
        return 0;
    }
}

int TheoCons::CheckAllTheoCons() {
    Check = 0;
    Check = ((BFB() & TwoMins() & Perturbativity()) == 1) ? 1 : 0;

    if (Check)
        printf("Passed TheoCons\n");
    else
        printf("Did not pass TheoCons\n");
    return Check;
}

int TheoCons::GetCheck() {
    return Check;
}

void TheoCons::GenNewPars() {
    Pars.GenPars();
}

Parameters TheoCons::GetPars() {
    return Pars;
}