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
    
    // for (auto &name : ParNames)
    // {
    //     cout << name << endl;
    // }
    
    // cout << "Parameter constructor MH before GenPars " << GetMH() << endl;
    GenPars(); // Initialize values
    // cout << "Parameters constructor MH after GenPars " << GetMH() << endl;

}

Parameters& Parameters::operator=(const Parameters &obj) { // Works!

    if (this != &obj) {
        la2 = obj.la2;
        la3 = obj.la3;
        la4 = obj.la4;
        la5 = obj.la5;

        laL = obj.laL;

        MA = obj.MA;
        MC = obj.MC;
        MH = obj.MH;
        m22Squared = obj.m22Squared;
    }
    return *this;
}

// Copy constructor
Parameters::Parameters(const Parameters& newPars) {
    la1 = newPars.la1;
    la2 = newPars.la2;
    la3 = newPars.la3;
    la4 = newPars.la4;
    la5 = newPars.la5;

    laL = newPars.laL;
    MA = newPars.MA;
    MC = newPars.MC;
    MH = newPars.MH;
    m22Squared = newPars.m22Squared;
}

/*
ostream& operator<< (std::ostream& s, const Parameters& p) {
    s << "la1: " << p.la1 << endl;
    s << "la2: " << p.la2 << endl; 
    s << "la3: " << p.la3 << endl; 
    s << "la4: " << p.la4 << endl; 
    s << "la5: " << p.la5 << endl; 
    s << "laL: " << p.laL << endl; 
    s << "MA: " << p.MA << endl; 
    s << "MC: " << p.MC << endl; 
    s << "MH: " << p.MH << endl; 
    s << "(m_22)^2: " << p.m22Squared << endl;
    return s;
}*/

ostream& operator<<(std::ostream& s, const Parameters& p) {
    s << fixed << setprecision(6);
    s << p.Mh << " ";
    s << p.MH << " ";
    s << p.MA << " ";
    s << p.MC << " ";
    s << p.la2 << " ";
    s << p.laL << " ";
    s << p.la1 << " ";
    s << p.la3 << " ";
    s << p.la4 << " ";
    s << p.la5;
    return s;
}
// void Parameters::ScanSetup()
// {

//     la2 = UniDist(0,4.5); // (-4*M_PI, 4*M_PI); // Perturbativity
//     laL = UniDist(-1.5,2); // -1.5,2 // -2,4*M_PI -> For HBS

//     MH = UniDist(0,1000);
//     // cout << "**MH " << MH << endl;
//     // cout << MH << endl;
//     MA = UniDist(0,1000);
//     MC = UniDist(70,1000); // IDM revisited >80

//     // Eq 9 paper principal: strong bounds provided by the total width of the electroweak gauge bosons
//     while (MH >= MA || MH >= MC || (MC - MA < 0.1))
//     {   
//         MH = UniDist(0,1000);
//         // cout << "**MH " << MH << endl;
//         // cout << MH << endl;
//         MA = UniDist(0,1000);
//         MC = UniDist(70,1000); // IDM revisited >80
//     }
// }

void Parameters::ScanSetup()
{
    // la2 = UniDist(0,4.5);
    la2 = UniDist(0,4.5); // (-4*M_PI, 4*M_PI); // Perturbativity
    laL = UniDist(-1.5,2); // -1.5,2 // -2,4*M_PI -> For HBS

    MH = UniDist(0,1000);
    MA = UniDist(0,1000);
    MC = UniDist(70,1000); // IDM revisited >80

    // Eq 9 paper principal: strong bounds provided by the total width of the electroweak gauge bosons
    // DMC  mass MH has to be bigger than the other masses
    while (MH >= MA || MH >= MC || (MC - MH < 0.1))
    {   
        MH = UniDist(0,1000);
        // cout << "**MH " << MH << endl;
        // cout << MH << endl;
        MA = UniDist(0,1000);
        MC = UniDist(70,1000); // IDM revisited >80
    }
}


void Parameters::GenPars()
{
    // TRandom3* rnd = new TRandom3(0);
    // MH = rnd->Rndm()*1000;
    // MA = rnd->Rndm()*1000;
    // MC = rnd->Rndm()*1000;
    // la2 = rnd->Rndm()*1000;
    // laL = rnd->Rndm()*1000;
    if (scan_setup)
        ScanSetup();
    else {
        MH = UniDist(0,1000);
        MA = UniDist(0,1000);
        MC = UniDist(0,1000);
        la2 = UniDist(-500,500); // (-4*M_PI, 4*M_PI); // Perturbativity
        laL = UniDist(-500,500);
    }


    // MH = UniDist(0,1000);
    // MA = UniDist(0,1000);
    // MC = UniDist(0,1000);
    // la2 = UniDist(0,4.5); // (-4*M_PI, 4*M_PI); // Perturbativity
    // laL = UniDist(-1.5,2);

    m22Squared = v*v*laL - 2*MH*MH; // v*v*laL - 4*MA*MA -  2*MH*MH;
    
    la3 = laL + 2*(MC*MC - MH*MH)/(v*v);
    la4 = (MA*MA -2*MC*MC + MH*MH)/(v*v); // laL + 2*(MC*MC - MH*MH)/(v*v)
    la5 = (MH*MH - MA*MA)/(v*v);
}

void Parameters::ImportPars(const string &filename) {

    map<string, double> map;
    Parameters Pars;

    ifstream dataTest(filename);

    // Check if the file was successfully opened
    if (!dataTest.is_open()) {
        cerr << "Error: Unable to open file." << endl;
        exit(0);
    }
    // string line;
    string name;
    double value;

    // Read values
    while(dataTest >> name >> value) { // getline(dataTest, line)
        // stringstream ss(line);
        // getline(ss, name, ' ');
        // getline(ss, value, ' ');
        map[name] = value;
    }
    dataTest.close();

    this->la2 = map["la2"];
    // cout << "la2" << Pars.la2 << endl; usar Pars.la2 = map["la2"] nao funciona
    this->laL = map["laL"];
    this->MA = map["MH3"];
    this->MC = map["MHC"];
    this->MH = map["MHX"];

    this->SetPars();
}

void Parameters::SetPars() {
    la1 = (Mh*Mh)/(v*v);

    m22Squared = v*v*laL - 4*MA*MA -  2*MH*MH; // v*v*laL - 2*MH*MH;
    
    la3 = laL + 2*(MC*MC - MH*MH)/(v*v);
    la4 = (MA*MA -2*MC*MC + MH*MH)/(v*v); // laL + 2*(MC*MC - MH*MH)/(v*v)
    la5 = (MH*MH - MA*MA)/(v*v);
}

// GETTERS

vector<string> Parameters::GetParNames() {
    return ParNames;
}

double Parameters::GetMh() const {
    return Mh;
}

double Parameters::Getv() const {
    return v;
}

double Parameters::Getla1() const {
    return la1;
}

double Parameters::GetMH() const {
    return MH;
}

double Parameters::GetMA() const {
    return MA;
}

double Parameters::GetMC() const {
    return MC;
}

double Parameters::Getla2() const {
    return la2;
}

double Parameters::GetlaL() const {
    return laL;
}

double Parameters::Getm22Squared() const {
    return m22Squared;
}

double Parameters::Getla3() const {
    return la3;
}

double Parameters::Getla4() const {
    return la4;
}

double Parameters::Getla5() const {
    return la5;
}