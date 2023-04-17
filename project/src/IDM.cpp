#include "include/IDM.h"

IDM::IDM() {
    // Pars.GenPars(1);
    // fApp = new TApplication("app", nullptr, nullptr);
    ClearParMap();
}

// IDM::IDM(TApplication* app) { // : fApp(app)
//     fRoot = new RootClass(app);
//     ClearParMap();
// }


IDM::IDM(Parameters& newPars) : Pars(newPars) {

    Pars = newPars;
    ClearParMap();
    // TheoCons TC(Pars);
    // ExpCons EC(Pars);
    // vector<string> parNames = {"la2", "la3", "la4", "la5", "laL", "MH", "MC", "MA", "m22Squared"};
    // vector<double> values;
    // values.clear();

    // for (auto &i : parNames)
    // {
    //     ParMap.insert(make_pair(i,values));
    // }
    // cout << "IDM constructor MH " << Pars.GetMH() << endl;
}

void IDM::PrintParMap() {
    // Print map
    for (const auto& pair : ParMap)
    {
        cout << "Key: " << pair.first << endl;
        cout << "Values: ";
        for (const auto& val : pair.second)
        {
            cout << val << " ";
        }
        cout << endl;
    }
}

void IDM::AssignPars(double& la2, double& la3, double& la4, 
                    double& la5, double& laL, double& m22Sqr, 
                    double& MH, double& MA, double& MC, double i) {
    la2 = ParMap["la2"][i];
    la3 = ParMap["la3"][i];
    la4 = ParMap["la4"][i];
    la5 = ParMap["la5"][i];
    laL = ParMap["laL"][i];
    m22Sqr = ParMap["m22Squared"][i];
}

const Parameters& IDM::GetPars() const {
    return Pars;
}

// Not ready
// void IDM::GenNewPars() {
//     Pars.GenPars(1);
// }

void IDM::AddToMap() {
    ParMap["la2"].push_back(Pars.Getla2());
    ParMap["la3"].push_back(Pars.Getla3());
    ParMap["la4"].push_back(Pars.Getla4());
    ParMap["la5"].push_back(Pars.Getla5());
    ParMap["laL"].push_back(Pars.GetlaL());
    ParMap["MH"].push_back(Pars.GetMH());
    ParMap["MC"].push_back(Pars.GetMC());
    ParMap["MA"].push_back(Pars.GetMA());
    ParMap["m22Squared"].push_back(Pars.Getm22Squared());
}

void IDM::StoreParsTest(int nPoints) {
    ClearParMap();
    cout << "Generating and storing Parameters...\n";
    Pars.SetScanBit(true);
    for (int i = 0; i < nPoints; i++) {
        Pars.GenPars(); // 1
        // Mudar para while. if (Check all constraints) {AddToMap}
        AddToMap();
    }
}

// struct {
//     // Couplings
//     double la1;
//     double la2;
//     double la3;
//     double la4;
//     double la5;
//     double laL;
//     // Masses
//     double Mh; // = mh = m11
//     double MH;
//     double MA;
//     double MC;
//     double m22;
//     // vev
//     double v;

// } TempPars;

void IDM::StoreCheckedPars(int nPoints) {
    ClearParMap();
    cout << "Generating and storing Parameters...\n";
    Pars.SetScanBit(true);
    int i = 0;
    while (i < nPoints) {
        Pars.GenPars();
        // Check all constraints
        if (CheckTeoCons()) { // 
            AddToMap();
            i++;
        }
    }
    WriteMapToFile("data/PassedTeoCons/PassedTeoCons.dat", ParMap, Pars);
}

void IDM::GenWriteCheckedPars(const string& filename, int nPoints) {
    cout << "Generating and Writting " << nPoints << " Parameters" << " to " << filename << endl;
    // Create or open file
    ofstream outfile(filename);
    // Check if file was created or opened successfully
    if (!outfile.is_open()) {
        cerr << "**Error: could not create file " << filename << endl;
        exit(0);
    }
    // Write header
    vector<string> names = Pars.GetParNames();
    auto it = names.begin();
    if (it != names.end()) {
        outfile << *it;
        ++it;
    }
    while (it != names.end()) {
        outfile << " " << *it;
        ++it;
    }
    outfile << endl;
    // Generate and Write Parameters
    Pars.SetScanBit(true);
    int i = 0;
    while (i < nPoints) {
        Pars.GenPars();
        // Check all constraints
        if (CheckTeoCons()) { // CheckTeoCons()
            outfile << Pars << endl;
            i++;
        }
    }
    // Close the file
    outfile.close();
}



int IDM::CheckTeoCons() {

    double Mh = 125.1;
    double v = 246;
    double la1 = Pars.Getla1(); // (Mh/v)**2

    // Mass Basis
    double MH = Pars.GetMH(); // MHX CDM
    double MA = Pars.GetMA(); // MH3 It is A in IDM paper
    double MC = Pars.GetMC(); // MHC Charged Higgs
    double la2 = Pars.Getla2(); // lambda_2
    double laL = Pars.GetlaL(); // la3 + la4 + la5

    // Coupling Parameters Basis
    double m22Squared = Pars.Getm22Squared();
    double la3 = Pars.Getla3();
    double la4 = Pars.Getla4();
    double la5 = Pars.Getla5();

    double S, T, U;

    // Other conditions implicit in number generation
    int BFB = BFB_Test(la1, la2, la3, laL);                             // OK
    int TM = TwoMins_Test(la1, la2, Mh, m22Squared);
    int SMU = ScatteringMatrixUnitary_Test(la1, la2, la3, la4, la5);
    int Pert = Perturbativity_Test(la1, la2, la3, la4, la5, laL);       // OK
    int STU = STU_Test(Mh, MH, MA, MC, S, T, U); // Mh = m11            // OK
    // BFB && Pert && STU && TM && SMU
    // CheckResult(STU)
    return (BFB && Pert && STU && TM && SMU);

    /* =================================================================== */

    // Perturbativity(Pars);
}


int IDM::CheckallCons() {

    double Mh = 125.1;
    double v = 246;
    double la1 = Pars.Getla1(); // (Mh/v)**2

    // Mass Basis
    double MH = Pars.GetMH(); // MHX CDM
    double MA = Pars.GetMA(); // MH3 It is A in IDM paper
    double MC = Pars.GetMC(); // MHC Charged Higgs
    double la2 = Pars.Getla2(); // lambda_2
    double laL = Pars.GetlaL(); // la3 + la4 + la5

    // Coupling Parameters Basis
    double m22Squared = Pars.Getm22Squared();
    double la3 = Pars.Getla3();
    double la4 = Pars.Getla4();
    double la5 = Pars.Getla5();

    double S, T, U;

    if (!BFB_Test(la1, la2, la3, laL)) {
        return 0;
    }

    if (!TwoMins_Test(la1, la2, Mh, m22Squared)) {
        return 0;
    }

    if (!ScatteringMatrixUnitary_Test(la1, la2, la3, la4, la5)) {
        return 0;
    }

    if (!Perturbativity_Test(la1, la2, la3, la4, la5, laL)) {
        return 0;
    }

    if (!STU_Test(Mh, MH, MA, MC, S, T, U)) {
        return 0;
    }

    if (!LEPAnalysis(MH, MA, MC)) {
        return 0;
    }

    if (!HiggsWidth(MH, laL)) {
        return 0;
    }

    if (!EWBosons(MH, MA, MC)) {
        return 0;
    }

    if (!HChargedLifetime(MH, MA, MC)) {
        return 0;
    }

    if (!LUXDMData(MH, Mh, laL)) {
        return 0;
    }

    if (!WZDecayWidths(MH, MA)) {
        return 0;
    }

    if (!HiggsBoundsSignals(MC, Mh, laL)) {
        return 0;
    }

    if (!Extras(MC, MA)) {
        return 0;
    }

    return 1;
}


    // double Mh = 125.1;
    // double v = 246;
    // double la1 = Pars.Getla1(); // (Mh/v)**2

    // // Mass Basis
    // double MH = Pars.GetMH(); // MHX CDM
    // double MA = Pars.GetMA(); // MH3 It is A in IDM paper
    // double MC = Pars.GetMC(); // MHC Charged Higgs
    // double la2 = Pars.Getla2(); // lambda_2
    // double laL = Pars.GetlaL(); // la3 + la4 + la5

    // // Coupling Parameters Basis
    // double m22Squared = Pars.Getm22Squared();
    // double la3 = Pars.Getla3();
    // double la4 = Pars.Getla4();
    // double la5 = Pars.Getla5();

    // double S, T, U;
    // int GOOD = 1;
    // // Other conditions implicit in number generation
    // int BFB = BFB_Test(la1, la2, la3, laL);                             // OK
    // int TM = TwoMins_Test(la1, la2, Mh, m22Squared);
    // int SMU = ScatteringMatrixUnitary_Test(la1, la2, la3, la4, la5);
    // int Pert = Perturbativity_Test(la1, la2, la3, la4, la5, laL);       // OK
    // int STU = STU_Test(Mh, MH, MA, MC, S, T, U); // Mh = m11            // OK
    // // BFB && Pert && STU && TM && SMU
    // // CheckResult(STU)
    // int LEP = LEPAnalysis(MH, MA, MC);
    // int HWD = HiggsWidth(MH, laL);
    // int EWB = EWBosons(MH, MA, MC);
    // int HCL = HChargedLifetime(MH, MA, MC);
    // int LUX = LUXDMData(MH, Mh, laL);
    // int WZD = WZDecayWidths(MH, MA);
    // // int ORD = RelicDensity(MH);
    // int HBS = HiggsBoundsSignals(MC, Mh, laL);

    // int EXT = Extras(MC, MA);

    // vector<int> vec_check = {BFB, TM, SMU, Pert, STU, LEP, HWD, EWB, HCL, LUX, WZD,  HBS, EXT}; // ORD,
    //     for (auto &bit : vec_check)
    //     {
    //         GOOD = GOOD && bit;
    //         if (!GOOD) return GOOD;
    //     }
    // return GOOD;
// }


void IDM::WriteMicrOMEGAs(const string& filename, int nPoints) {
    cout << "Generating and Writting " << nPoints << " Parameters" << " to " << filename << " for MicrOMEGAs"<< endl;
    // Create or open file
    ofstream outfile(filename);
    // Check if file was created or opened successfully
    if (!outfile.is_open()) {
        cerr << "**Error: could not create file " << filename << endl;
        exit(0);
    }
    // Do not write header
    // vector<string> names = Pars.GetParNames();
    // auto it = names.begin();
    // if (it != names.end()) {
    //     outfile << *it;
    //     ++it;
    // }
    // while (it != names.end()) {
    //     outfile << " " << *it;
    //     ++it;
    // }
    // outfile << endl;
    // Generate and Write Parameters
    outfile << setprecision(10) << scientific;
    Pars.SetScanBit(true);
    int i = 0;
    while (i < nPoints) {
        Pars.GenPars();
        // Check all constraints
        if (CheckTeoCons()) { // 
            // cout << i << endl;
            outfile << i << " "
            << Pars.GetMh() << " " 
            << Pars.GetMH() << " "
            << Pars.GetMA() << " "
            << Pars.GetMC() << " "
            << Pars.Getla2() << " "
            << Pars.GetlaL() << endl;
            i++;
        }
    }
    // Close the file
    outfile.close();
}

vector<pair<double,double>> IDM::GetParsSTU(int nPoints) {
    ClearParMap();
    cout << "Generating and storing Parameters that pass STU...\n";
    int i = 0;
    vector<pair<double, double>> STVals; // ST.first = S, ST.second = T;
    Pars.SetScanBit(false);
    while (i < nPoints) {
        Pars.GenPars(); // 1
        // Mudar para while. if (Check all constraints) {AddToMap}
        double S, T, U;
        if (ST(Pars.GetMh(), Pars.GetMH(), Pars.GetMA(), Pars.GetMC(), S, T, U)) {
            AddToMap();
            STVals.push_back(make_pair(S,T));
            i++;
        }
    }
    return STVals;
}

/*
void removePointFromMapVectors(map<string, vector<double>> &myMap, int pos) {
    for (auto& pair : myMap) {
        auto iter = pair.second.begin() + pos;
        if (iter != pair.second.end()) {
            pair.second.erase(iter);
        } else { 
            fprintf(stderr, "**removePoint error\n");
            exit(0);
        }
    }
}*/

void IDM::TM_Test(){
    Pars.SetScanBit(true);
    int i = 0;
    while (i < 20) {
        Pars.GenPars();
        double la1 = Pars.Getla1();
        double la2 = Pars.Getla2();
        double m22Sq = Pars.Getm22Squared();
        double mhSq = Pars.GetMh()*Pars.GetMh();
        double B = m22Sq/sqrt(la2);
        double A = mhSq/sqrt(la1); 
        cout << "A: " << A << " B: " << B;
        double check = TwoMins_Test(la1, la2, sqrt(mhSq), m22Sq);
        cout << "\tResult = " << check << endl;
        i++;
    }
}


void IDM::FirstPlot(const string& filename) {
    cout << "Making FirstPlot...\n";
    TApplication app("app", nullptr, nullptr);
    TCanvas *c = new TCanvas("c", "FirstPlot", 1300, 800);
    TMultiGraph *mg = new TMultiGraph();

    string name = "Title";
    mg->SetTitle(" ");

    /* IMPORTANT TO TO STOREPARSTEST FIRST */
    WriteMapToFile(filename, ParMap, Pars);

    // vector<int> keepIndex;

    TGraph *grCheck = new TGraph();
    grCheck->SetTitle("Allowed");
    TGraph *grBFB = new TGraph();
    grBFB->SetTitle("Positivity");

    TGraph *grBoth = new TGraph();
    grBoth->SetTitle("Both");

    TGraph *grPert = new TGraph();
    grPert->SetTitle("Perturbativity");


    double la1 = Pars.Getla1();
    double Mh = Pars.GetMh();

    int N = 0;
    int max = ParMap["MH"].size();

    double la2, la3, la4, la5, laL, m22Sqr, MH, MA, MC;

    for (int i = 0; i < max; i++) {
        AssignPars(la2, la3, la4, la5, laL, m22Sqr, MH, MA, MC, i);
        // double la2 = ParMap["la2"][i];
        // double la3 = ParMap["la3"][i];
        // double la4 = ParMap["la4"][i];
        // double la5 = ParMap["la5"][i];
        // double laL = ParMap["laL"][i];
        // double m22Squared = ParMap["m22Squared"][i];

        int bfb =  BFB_Test(la1, la2, la3, laL); //  BoundFromBelow(la1, la2, la3, laL, Mh, m22Squared);
        int Pert = (la2 <= 4*M_PI/3) ? 1 : 0; // Perturbativity_Test(la1, la2, la3, la4, la5, laL);
        // int twoMins = TwoMins(Pars);

        int check = bfb && Pert; // & twoMins;

        if (bfb == 1 && Pert == 0)
        {
            grPert->AddPoint(la2, laL);
        } else if (bfb == 0 && Pert == 1) 
        {
            grBFB->AddPoint(la2, laL);
        } else if (check) {
            grCheck->AddPoint(la2, laL);
            // keepIndex.push_back(i);
            // AddToMap();
            // cout << "Got here\n";
        } else if (bfb == 0 && Pert == 0) {
            grBoth->AddPoint(la2, laL);
            // cout << "Zeros\n";
        } else {
            cout << "Should never get here\n";
        }
    }

    // FilterParMap(keepIndex);
    // Zona de descarte

    // map<string, vector<double>> auxParMap;
    // ClearParMap(auxParMap);
    // for (auto &pair : ParMap)
    // {
    //     for (int i = 0; i < pair.second.size(); i++)
    //     {
    //         auto iter = find(keepIndex.begin(), keepIndex.end(), i);
    //         if (iter != keepIndex.end())
    //             auxParMap[pair.first].push_back(ParMap[pair.first][i]);
    //     }
    // }

    // ParMap = auxParMap;


    grCheck->SetMarkerColor(2);
    grCheck->SetMarkerStyle(20);

    grBFB->SetMarkerColor(4);
    grBFB->SetMarkerStyle(20);

    grPert->SetMarkerColor(3);
    grPert->SetMarkerStyle(20);

    grBoth->SetMarkerColor(1);
    grBoth->SetMarkerStyle(20);

    mg->Add(grCheck);
    mg->Add(grPert);
    mg->Add(grBFB);
    mg->Add(grBoth);

    mg->GetXaxis()->SetTitle("#lambda_{2}");
    mg->GetXaxis()->CenterTitle();
    mg->GetYaxis()->SetTitle("#lambda_{345}");
    

    mg->Draw("AP");

    // c->BuildLegend();
    TLegend *leg = new TLegend(0.9, 0.7, 0.99, 0.9);
    leg->SetHeader("Constraints", "C");
    leg->AddEntry(grCheck, "Allowed", "p");
    leg->AddEntry(grBFB, "BFB", "p");
    leg->AddEntry(grPert, "Pert", "p");
    leg->AddEntry(grBoth, "Both", "p");
    leg->Draw();

    c->Update();

    string dir = "bin/Plots/";
    name.append("CopyParMapTest.png");
    dir.append(name);
    c->SaveAs(dir.c_str());

    TRootCanvas *rc = (TRootCanvas *)c->GetCanvasImp();
    rc->Connect("CloseWindow()", "TApplication", gApplication, "Terminate()");
    app.Run();
    
}

void IDM::FilterParMap(vector<int> keepIndex) {
    // Create a new map to store the copied values
    map<string, vector<double>> auxParMap;

    // Copy the values from ParMap to auxParMap
    for (auto &pair : ParMap)
    {
        for (int i = 0; i < pair.second.size(); i++)
        {
            auto iter = find(keepIndex.begin(), keepIndex.end(), i);
            if (iter != keepIndex.end())
                auxParMap[pair.first].push_back(ParMap[pair.first][i]);
        }
    }
    // Assign the new map to ParMap
    ParMap = auxParMap;
}

/*
void IDM::FirstPlot() {
    // TApplication app("app", nullptr, nullptr);
    TCanvas *c = new TCanvas("c", "multigraph", 800, 800);
    TMultiGraph *mg = new TMultiGraph();

    string name = "Title";
    mg->SetTitle(name.c_str());


    int N = 0;

    TGraph *grCheck = new TGraph();
    grCheck->SetTitle("Allowed");
    TGraph *grBFB = new TGraph();
    grBFB->SetTitle("Positivity");

    TGraph *grBoth = new TGraph();
    grBoth->SetTitle("Both");

    TGraph *grPert = new TGraph();
    grPert->SetTitle("Perturbativity");

    while (N<30000) // 10000
    {
        // cout << "**MH before while genpars " << Pars.GetMH() << endl;
        Pars.GenPars(); // GetPars().GenPars();
        // cout << "**MH after while genpars " << Pars.GetMH() << endl;

        int bfb = BFB(Pars);
        int Pert = Perturbativity(Pars);
        // int twoMins = TwoMins(Pars);

        int check = bfb && Pert; // & twoMins;

        if (bfb == 1 && Pert == 0)
        {
            grPert->AddPoint(Pars.Getla2(), Pars.GetlaL());
        } else if (bfb == 0 && Pert == 1) 
        {
            grBFB->AddPoint(Pars.Getla2(), Pars.GetlaL());
        } else if (check) {
            grCheck->AddPoint(Pars.Getla2(), Pars.GetlaL());
            AddToMap();
            // cout << "Got here\n";
        } else if (bfb == 0 && Pert == 0) {
            grBoth->AddPoint(Pars.Getla2(), Pars.GetlaL());
            // cout << "Zeros\n";
        } else {
            cout << "Weirdge\n";
        }
        N++;
    }

    // while (N<10000)
    // {
    //     Pars.GenPars();
    //     int bfb = BFB(Pars);
    //     int Pert = Perturbativity(Pars);
    //     // int twoMins = TwoMins(Pars);

    //     int check = bfb && Pert; // & twoMins;

    //     if (Pert == 0)
    //     {
    //         grPert->AddPoint(Pars.Getla2(), Pars.GetlaL());
    //     } else if (bfb == 0) 
    //     {
    //         grBFB->AddPoint(Pars.Getla2(), Pars.GetlaL());
    //     } else if (check) {
    //         // write
    //         grCheck->AddPoint(Pars.Getla2(), Pars.GetlaL());
    //         cout << "Got here\n";
            
    //     } else {
    //         cout << "Weirdge\n";
    //     }
    //     N++;
    // }

    grCheck->SetMarkerColor(2);
    grCheck->SetMarkerStyle(20);

    grBFB->SetMarkerColor(4);
    grBFB->SetMarkerStyle(20);

    grPert->SetMarkerColor(3);
    grPert->SetMarkerStyle(20);

    grBoth->SetMarkerColor(1);
    grBoth->SetMarkerStyle(20);

    mg->Add(grCheck);
    mg->Add(grPert);
    mg->Add(grBFB);
    mg->Add(grBoth);
    
    mg->Draw("AP");

    c->BuildLegend();

    c->Update();

    string dir = "bin/Plots/";
    name.append("FP.png");
    dir.append(name);
    c->SaveAs(dir.c_str());

    delete c;

    
    // for (int* ptr : vec)
    //     delete ptr;
    // vec.clear();
    // delete [] grCheck;
    // delete [] grBoth;
    // delete [] grPert;
    // delete [] grBFB;
    // delete [] mg;
    // delete [] c;




    // c->Update();

    // string dir = "bin/Plots/";
    // name.append(".png");
    // dir.append(name);
    // c->SaveAs(dir.c_str());

    // TRootCanvas *rc = (TRootCanvas *)c->GetCanvasImp();
    // rc->Connect("CloseWindow()", "TApplication", gApplication, "Terminate()");
    // app.Run();
    
} */

void IDM::LimitsFromColliders() {
    cout << "Making Limits From the Colliders Plot...\n";
    TApplication app("app", nullptr, nullptr);
    cout << "Entered limits!\n";

    TCanvas *c = new TCanvas("c", "LimitsFromColliders", 800, 800);
    cout << "After creating c\n";

    TMultiGraph *mg = new TMultiGraph();

    string name = "Title";
    mg->SetTitle(name.c_str());

    TGraph *grCheck = new TGraph();
    grCheck->SetTitle("Allowed");

    TGraph *grExp = new TGraph();
    grExp->SetTitle("Higgs Bounds/Higgs Signals");

    int N = ParMap["MC"].size();
    cout << "N " << N << endl;

    double h = Pars.GetMh();
    cout << "Before for!\n";
    for (int i = 0; i < N; i++)
    {
        double la3 = ParMap["la3"][i];
        double MC = ParMap["MC"][i];
        double laL = ParMap["laL"][i];
        int check = HiggsBoundsSignals(MC, h, laL);
        // cout << "Check bit " << check << endl;
        if (check)
        {
            if (la3 > -2 && la3 < 14 && MC/h < 10 && MC/h > -2) {
                grCheck->AddPoint(la3, MC/h); // Pars.GetlaL();
            }
            
            // AddToMap();
        } else if (check == 0) 
        {
            if (la3 > -2 && la3 < 14 && MC/h < 10 && MC/h > -2) {
                grExp->AddPoint(la3, MC/h); // Pars.GetlaL();
            }
        } else {
            cout << "Weirdge\n";
        }
    }

    grCheck->SetMarkerColor(2);
    grCheck->SetMarkerStyle(20);

    grExp->SetMarkerColor(3);
    grExp->SetMarkerStyle(20);

    mg->Add(grCheck);
    mg->Add(grExp);
    
    mg->Draw("AP");

    c->BuildLegend();
    // c->Update();

    string dir = "bin/Plots/";
    name.append("HBS.png");
    dir.append(name);
    c->SaveAs(dir.c_str());

    TRootCanvas *rc = (TRootCanvas *)c->GetCanvasImp();
    rc->Connect("CloseWindow()", "TApplication", gApplication, "Terminate()");
    app.Run();
}

/*
void IDM::SavePars(const string &filename) {
    //Open the output file
    ofstream outputFile(filename);
    if (!outputFile.is_open()) {
        fprintf(stderr, "**Can not open file to save parameters\n");
        exit(0);
    }
    //Write column headings
	for (auto const& [key, value] : ParMap) 
		outputFile << key << ",";
	outputFile << "\n";
	// write data
	for (int i = 0; i < ParMap.begin()->second.size(); i++) {
		for (auto const& [key, value] : ParMap) 
			outputFile << value[i] << ",";
		outputFile << "\n";
	}

    // for (auto iter = ParMap.begin(); iter != ParMap.end(); ++iter) {
    //     string key = iter->first;
    //     outputFile << key << ",";
    // }
    // outputFile << "\n";
    // // write data
    // for (auto iter = ParMap.begin(); iter != ParMap.end(); ++iter) {
    //     vector<double> value = iter->second;
    //     for (int i = 0; i < value.size(); i++) 
    //         outputFile << value[i] << ",";
    //     outputFile << "\n";
    // }
    
    //Close the file
    outputFile.close();
}*/
/*
// void IDM::SavePars(const string &filename) {
//     //Open the output file
//     ofstream outputFile(filename);
//     if (!outputFile.is_open()) {
//         fprintf(stderr, "**Can not open file to save parameters\n");
//         exit(0);
//     }
//     //Write column headings
// 	for (auto const &pair : ParMap) 
// 		outputFile << pair.first << ",";
// 	outputFile << "\n";
// 	// write data
// 	for (int i = 0; i < ParMap.begin()->second.size(); i++) {
// 		for (auto const &pair : ParMap) 
// 			outputFile << pair.second[i] << ",";
// 		outputFile << "\n";
// 	}
//     // Close the file
//     outputFile.close();
// }*/

void IDM::ClearParMap() {
    // Save map just in case if it is not empty
    if (!ParMap.empty()) {
        SavePars("data/Saved.csv", ParMap);
        cout << "Clearing Parameter Map...\n";
        // Clear map
        ParMap.clear();
        // Initialize map
        vector<string> parNames = {"la2", "la3", "la4", "la5", "laL", "MH", "MC", "MA", "m22Squared"};
        vector<double> values;
        values.clear();
        // Insert pairs of [Key,Values] of the parameters   
        for (auto &i : parNames)
            ParMap.insert(make_pair(i,values));
    } else 
        return;
}
/*
void IDM::ReadCSV(const string &filename) {
    ClearParMap();
    printf("Reading %s into Parameter Map\n", filename.c_str());

    ifstream input(filename);

    if (!input.is_open()) {
        fprintf(stderr, "**Can not open CSV file to read\n");
        exit(0);
    }

	string line, col;
	vector<string> header;

        getline(input, line);
		stringstream ss(line);
		while (getline(ss, col, ',')) {
			header.push_back(col);
		}

		// Read values
		while (getline(input, line)) {
			stringstream ss(line);
			int i = 0;
			while (getline(ss, col, ',')) {
				ParMap[header[i]].push_back(stod(col));
				i++;
			}
		}
    // Print map after reading
	
    for (auto &pair : ParMap) {
		cout << pair.first << ": ";
		for (auto& value : pair.second) {
			cout << value << " ";
		}
		cout << endl;
	}
    
}*/

/*
void IDM::WriteDat(const string &filename) {

    // Open and verify if it was opened correctly
    ofstream file;
    file.open(filename);
    if (!file.is_open()) {
        fprintf(stderr, "**Can not open DAT file to write\n");
        exit(0);
    }

  // Get the size of the largest vector
    int maxSize = 0;
    map<string, vector<double>>::iterator it;
    for (it = ParMap.begin(); it != ParMap.end(); ++it)
        maxSize = max(maxSize, (int)it->second.size());

    // Write the strings
    for (it = ParMap.begin(); it != ParMap.end(); ++it)
        file << it->first << "\t\t";
    file << endl;
    
    // Write each element in a column
    for (int i = 0; i < maxSize; i++) {
        for (it = ParMap.begin(); it != ParMap.end(); ++it) {
        if (i < it->second.size())
            file << it->second[i] << "\t\t";
        else
            file << "0 ";
        }
        file << endl;
    }
    file.close();
}*/

/*
void IDM::WriteElementToFile(string key, ofstream &file, int i) {
    // use the find function to search for the key and get the element at that key if it exists
    // map<string, vector<double>> myMap
    auto found_key = ParMap.find(key);
    if (found_key != ParMap.end())
        file << found_key->second[i] << "\t"; 
    // setprecision(n) to limit significant digits of number to n digits
    // file << setprecision(5) << found_key->second[i] << "\t"; 
}*/

/**
 * @brief Write ParMap to a .dat file formatted for Experimental constraints
 * 
 * @param filename 
 */
/*
void IDM::WriteMapToFile(const string &filename) {
    cout << "Writting Parameter Map to .dat file...\n";

    ofstream file;
    file.open(filename);

    if (!file.is_open()) {
        fprintf(stderr, "**Can not open .dat file to write\n");
        exit(0);
    }

    // Get the size of the largest vector
    int maxSize = 0;
    map<string, vector<double>>::iterator it;
    for (it = ParMap.begin(); it != ParMap.end(); ++it)
		maxSize = max(maxSize, (int)it->second.size());

    // Order of variables to be written in .dat file
	// The name must be exactly correct, or the data will not appear in the file
    string parNames[] = {"mh", "MH", "MA", "MC", "la2", "laL", "la1", "la3", "la4", "la5"}; // "m11Sq"
	// double m11Sq = Pars.Getla1()*Pars.Getv()*Pars.Getv(); // m11^2 = la1*v^2
    double mh = Pars.GetMh();
	double la1 = Pars.Getla1();
	// Write the column names
    for (auto &par : parNames)
		file << par << "\t";
	file << endl;

    // Write each element in a column
    for (int i = 0; i < maxSize; i++) {
      	// file << "1 "; // Write the value for m11squared
		for (auto &par : parNames)
		{
			if (par != "mh" && par != "la1") {
				WriteElementToFile(par, file, i);
			} else if (par == "mh") {
				file << mh << "\t";
			} else if (par == "la1") {
				file << la1 << "\t";
			} else {
				fprintf(stderr, "**Acessed entry while writting that should not exist\n");
				exit(0);
			}
		}
	

    // writeElementToFile(ParMap, "la2", file, i);
    // writeElementToFile(ParMap, "laL", file, i);
    
    // file << "2 "; // Write the constant value for la1
    
    // writeElementToFile(ParMap, "mh", file, i);
    // writeElementToFile(ParMap, "ma", file, i);
    // writeElementToFile(ParMap, "mc", file, i);
    // writeElementToFile(ParMap, "la3", file, i);
    // writeElementToFile(ParMap, "la4", file, i);
    // writeElementToFile(ParMap, "la5", file, i);
    
		file << endl;
    }
    file.close();
    cout << "Parameter Map written to " << filename << "\n";
}

*//*
void IDM::ReadDAT(const string &filename) {
    ClearParMap();
    printf("Reading %s into Parameter Map\n", filename.c_str());

    ifstream input(filename);

    if (!input.is_open()) {
        fprintf(stderr, "**Can not open DAT file to read\n");
        exit(0);
    }

	string line, col;
	vector<string> header;

    getline(input, line);
	stringstream ss(line);
	while (getline(ss, col, '\t')) {
		header.push_back(col);
	}
    
	// Read values
	while (getline(input, line)) {
		stringstream ss(line);
		int i = 0;
		while (getline(ss, col, '\t')) {
			ParMap[header[i]].push_back(stod(col));
            cout << "header " << header[i] << " Value " << ParMap[header[i]][i] << endl; 
			i++;
		}
	}
}*/

vector<double> IDM::GetParMapVal(const string &name) {
    auto it = ParMap.find(name);
    if (it == ParMap.end()) {
        fprintf(stderr, "**No ParMap parameter called %s was found\n", name.c_str());
        exit(0);
    }
    return it->second;
}

/* ============================================================= */
/*
void IDM::IDMC_Test() {
    cout << "Making FirstPlot...\n";
    TApplication app("app", nullptr, nullptr);
    TCanvas *c = new TCanvas("c", "FirstPlot", 800, 800);
    TMultiGraph *mg = new TMultiGraph();

    string name = "Title";
    mg->SetTitle(name.c_str());

    TGraph *grCheck = new TGraph();
    grCheck->SetTitle("Allowed");
    TGraph *grBFB = new TGraph();
    grBFB->SetTitle("Positivity");

    TGraph *grBoth = new TGraph();
    grBoth->SetTitle("Both");

    TGraph *grPert = new TGraph();
    grPert->SetTitle("Perturbativity");

    double la1 = Pars.Getla1();
    double Mh = Pars.GetMh();

    int N = 0;
    int max = ParMap["MH"].size();

    for (int i = 0; i < max; i++) {

        double mh_in = Mh;
        double mH_in = ParMap["MH"][i];
        double mA_in = ParMap["MA"][i];
        double mHp_in = ParMap["MC"][i];
        double l2_in = ParMap["la2"][i];
        double l3_in = ParMap["la3"][i];
        double laL = ParMap["laL"][i];
        // char *file = "data/test.txt";

        if ((mh_in <= 0) || (mH_in <= 0) || (mA_in <= 0) || (mHp_in <= 0)) {
            cout << "ERROR: All mass parameters must be positive\n";
            exit(0);
        }

        THDM model;
        SM sm;

        bool pset = model.set_inert(mh_in, mH_in, mA_in, mHp_in, l2_in, l3_in);

        if (!pset) {
            cerr << "The parameters you have specified were not valid\n";
            exit(0);
        }

        // Reference SM Higgs mass for EW precision observables
        double mh_ref = 125.;
        Constraints check(model);

        // model.print_param_phys(); // 2HDM parameters in physical mass basis
        // model.print_param_gen(); // 2HDM parameters in generic basis
        // model.print_param_higgs(); // 2HDM parameters in Higgs basis

        // check.print_all(mh_ref); // Constraints and Oblique Parameters

        const HBHSResult *hbhsres_ptr = nullptr;
        #if defined HiggsBounds
        HBHS hbhs{};

        const HBHSResult hbhs_result = hbhs.check(model);
        hbhs_result.hb.print();
        hbhs_result.hs.print();
        hbhsres_ptr = &hbhs_result;
        #endif

        // model.write_LesHouches(file, true, true, true, hbhsres_ptr);

        int bfb = model.check_stability();
        int Pert = model.check_perturbativity();
        int Check = bfb && Pert; // & twoMins;

        if (bfb == 1 && Pert == 0)
        {
            grPert->AddPoint(l2_in, laL);
        } else if (bfb == 0 && Pert == 1) 
        {
            grBFB->AddPoint(l2_in, laL);
        } else if (Check) {
            grCheck->AddPoint(l2_in, laL);
            // keepIndex.push_back(i);
            // AddToMap();
            // cout << "Got here\n";
        } else if (bfb == 0 && Pert == 0) {
            grBoth->AddPoint(l2_in, laL);
            // cout << "Zeros\n";
        } else {
            cout << "Should never get here\n";
        }
    }

    grCheck->SetMarkerColor(2);
    grCheck->SetMarkerStyle(20);

    grBFB->SetMarkerColor(4);
    grBFB->SetMarkerStyle(20);

    grPert->SetMarkerColor(3);
    grPert->SetMarkerStyle(20);

    grBoth->SetMarkerColor(1);
    grBoth->SetMarkerStyle(20);

    mg->Add(grCheck);
    mg->Add(grPert);
    mg->Add(grBFB);
    mg->Add(grBoth);
    
    mg->Draw("AP");

    c->BuildLegend();

    c->Update();

    string dir = "bin/Plots/";
    name.append("CopyParMapTest.png");
    dir.append(name);
    c->SaveAs(dir.c_str());

    TRootCanvas *rc = (TRootCanvas *)c->GetCanvasImp();
    rc->Connect("CloseWindow()", "TApplication", gApplication, "Terminate()");
    app.Run();
}*/

int MyST_Check(double &S, double &T) {

    const double Shat = 0.05;
    const double That = 0.09;

    const double S_error = 0.11;
    const double T_error = 0.13;
    // const double U_error = 0.11;

    double SUL = Shat + S_error;
    double SLL = Shat - S_error;
    double TUL = That + T_error;
    double TLL = That - T_error;

    int check = (S > SLL && S < SUL && T > TLL && T < TUL) ? 1 : 0;
    return check;
}

// vector<vector<double>> 

// vector<pair<double,double>> readProfSTU() {
// cout << "Reading professor STU data...\n";
//     ifstream infile("data/STU/check/profSTUdata.dat");
//     vector<pair<double,double>> res;
//     double s, t;
//     while (infile >> s >> t) {
//         res.push_back(make_pair(s,t));
//     }
//     return res;
// }

// T = 0 se massas de escalares forem iguais
// quao diferentes massas podem ser

// void WriteSTUPars(vector<pair<double,double>> values, const string &filename) {
//     // Open and verify if it was opened correctly
//     cout << "Writting STU approved Parameters in file..." << endl;
//     ofstream file;
//     file.open(filename);
//     if (!file.is_open()) {
//         fprintf(stderr, "**Can not open DAT file to write\n");
//         exit(0);
//     }
//     file << "S" << "\t" << "T" << endl;

//     // Write each element in a column
//     for (auto &pair : values)
//     {
//         file << pair.first << "\t" << pair.second << endl;
//     }
//     file.close();
// }
/*
// "data/PassedTeoCons/PassedTeoCons.dat", "Scatter", "MA", "MC"
void IDM::FinalPlots(const string& Title, const string& XAxis, const string& YAxis, int N_points) {
    // Graph* grInfo = ReadGraphData(filename, Title, X, Y);
    // cout << "Making " << grInfo->GetTitle() << " final graph...\n";

    StoreParsTest(N_points);

    // RootClass root(grInfo);
    Graph* grBFB = new Graph("BFB");
    Graph* grSTU = new Graph("STU");
    Graph* grUNI = new Graph("UNI");
    Graph* grPER = new Graph("PER");
    Graph* grTMI = new Graph("TMI");
    Graph* grEXP = new Graph("EXP");

    Graph* grOK = new Graph("OK");

    double Mh = Pars.GetMh();
    double v = Pars.Getv();
    double la1 = Pars.Getla1(); // (Mh/v)**2

    int max = ParMap["MH"].size();

    for (int i = 0; i < max; i++) {
        double la2 = ParMap["la2"][i];
        double la3 = ParMap["la3"][i];
        double la4 = ParMap["la4"][i];
        double la5 = ParMap["la5"][i];
        double laL = ParMap["laL"][i];
        double m22Squared = ParMap["m22Squared"][i];
        double MH = ParMap["MH"][i]; // MHX CDM
        double MA = ParMap["MA"][i]; // MH3 It is A in IDM paper
        double MC = ParMap["MC"][i]; // MHC Charged Higgs
        // S T U Oblique parameters
        double S, T, U;
        // Other conditions implicit in number generation
        int BFB = BFB_Test(la1, la2, la3, laL);                             // OK
        int TMI = TwoMins_Test(la1, la2, Mh, m22Squared);
        int UNI = ScatteringMatrixUnitary_Test(la1, la2, la3, la4, la5);
        int PER = Perturbativity_Test(la1, la2, la3, la4, la5, laL);       // OK
        int STU = STU_Test(Mh, MH, MA, MC, S, T, U); // Mh = m11            // OK

        int HWD = HiggsWidth(laL);
        int EWB = EWBosons(MH, MA, MC);
        int LEP = LEPAnalysis(MH, MA);

        int EXP = HWD && EWB && LEP;

        double X, Y;
        X = MA;
        Y = MC;

        if (BFB == 0) {
            grBFB->AddPoint(X, Y);
        } else if (UNI == 0) {
            grUNI->AddPoint(X, Y);
        } else if (STU == 0) {
            grSTU->AddPoint(X, Y);
        } else if (PER == 0) {
            grPER->AddPoint(X, Y);
        } else if (TMI == 0) {
            grTMI->AddPoint(X, Y);
        } else if (EXP == 0) {
            grEXP->AddPoint(X, Y);
        } else {
            grOK->AddPoint(X, Y);
        }
    }
    
    RootClass root(grBFB);
    root.ScatterPlot(4, true);
    grBFB->SetLegendBit(true);
    grBFB->SetSaveOutputBit(true);

    root.SetNewGraph(grSTU);
    root.ScatterPlot(3, true);

    root.SetNewGraph(grUNI);
    root.ScatterPlot(6, true);

    root.SetNewGraph(grPER);
    root.ScatterPlot(877, true);

    root.SetNewGraph(grTMI);
    root.ScatterPlot(806, true);

    root.SetNewGraph(grEXP);
    root.ScatterPlot(7, true);

    root.SetNewGraph(grOK);
    root.ScatterPlot(2, true);

    root.MultiGraphPlot(Title, XAxis, YAxis);

    delete grBFB;
    delete grUNI;
    delete grSTU;
    delete grTMI;
    delete grPER;
    delete grEXP;
    delete grOK;
}

*/

void IDM::FinalPlots(const string& Title, const string& XAxis, const string& YAxis, int N_points) {
    // Graph* grInfo = ReadGraphData(filename, Title, X, Y);
    // cout << "Making " << grInfo->GetTitle() << " final graph...\n";

    // StoreParsTest(N_points);


    // RootClass root(grInfo);
    Graph* grBFB = new Graph("BFB");
    Graph* grSTU = new Graph("STU");
    Graph* grUNI = new Graph("UNI");
    Graph* grPER = new Graph("PER");
    Graph* grTMI = new Graph("TMI");
    Graph* grEXP = new Graph("EXP");

    Graph* grOK = new Graph("OK");

    double Mh = Pars.GetMh();
    double v = Pars.Getv();
    double la1 = Pars.Getla1(); // (Mh/v)**2

    // int max = ParMap["MH"].size();

    // for (int i = 0; i < max; i++) {
    ClearParMap();
    cout << "Generating Parameters of final plots...\n";
    Pars.SetScanBit(true);
    bool do_first = true;
    int i = 0;
    int a, b, c, d, e, f, g;
    a = b = c = d = e = f = g = 0;
    while (i < N_points) {
        Pars.GenPars();

        double la2 = Pars.Getla2();
        double la3 = Pars.Getla3();
        double la4 = Pars.Getla4();
        double la5 = Pars.Getla5();
        double laL = Pars.GetlaL();
        double m22Squared = Pars.Getm22Squared();
        double MH = Pars.GetMH(); // MHX CDM
        double MA = Pars.GetMA(); // MH3 It is A in IDM paper
        double MC = Pars.GetMC(); // MHC Charged Higgs



        // S T U Oblique parameters
        double S, T, U;

        double X, Y;
        X = MA;
        Y = MC;

        // if (!RelicDensity(MH)) {
        //     //if (f < 300) {
        //         grEXP->AddPoint(X, Y);
        //         //f++;
        //         //continue;
        //     //}
        // }

        // Other conditions implicit in number generation
        int TMI = TwoMins_Test(la1, la2, Mh, m22Squared);
        int BFB = BFB_Test(la1, la2, la3, laL);                             // OK
        // if (!(BFB && TMI)) {
        //     if (a<300) {
        //         grBFB->AddPoint(X, Y);
        //         a++;
        //         continue;
        //     }
        // }

        // int PER = Perturbativity_Test(la1, la2, la3, la4, la5, laL);       // OK
        int UNI = ScatteringMatrixUnitary_Test(la1, la2, la3, la4, la5);
        // if (!(UNI && PER)) {
        //     //if (b<300) {
        //         grUNI->AddPoint(X, Y);
        //         //b++;
        //         //continue;
        //     //}
        //     // grUNI->AddPoint(X, Y);
        // } 

        int STU = STU_Test(Mh, MH, MA, MC, S, T, U); // Mh = m11            // OK
        // if (!STU) {
        //    //if (c<300) {
        //         grSTU->AddPoint(X, Y);
        //         //c++;
        //         //continue;
        //     //}
        // } 

        int LEP = LEPAnalysis(MH, MA, MC);
        // if (!LEP) {
            //if (f < 300) {
                //grEXP->AddPoint(X, Y);
                //f++;
                //continue;
            //}
        // }

        int HWD = HiggsWidth(MH, laL);
        int EWB = EWBosons(MH, MA, MC);
        int HCL = HChargedLifetime(MH, MA, MC);
        int LUX = LUXDMData(MH, Mh, laL);
        int WZD = WZDecayWidths(MH, MA);
        int ORD = RelicDensity(MH);

        int EXT = Extras(MC, MA);

        int HBS = HiggsBoundsSignals(MC, Mh, laL);

        int EXP = LEP && LUX && HWD && EWB && HCL && WZD && HBS && EXT; // LUX ORD &&

        // if (!EXP) {
        //     //if (f < 300) {
        //         grEXP->AddPoint(X, Y);
        //         //f++;
        //         //continue;
        //     //}
        // }

        int GOOD = TMI && ORD && LEP && BFB && UNI && STU && LUX && HWD && EWB && HCL && WZD && HBS && EXT; // ; 

        // if (GOOD) {
        //     grOK->AddPoint(X, Y);
        // }
        // i++;

        if ( i%100 != 0 ) {
            if (!do_first) {
                // cout << "Done " << i << " points" << endl;
                do_first = true;
            }
        }

        if (BFB == 0 || TMI == 0) {
            if (a<300) {
                grBFB->AddPoint(X, Y);
                a++;
            }
        } 
        else if (STU == 0) {
            if (c<300) {
                grSTU->AddPoint(X, Y);
                c++;
            }
        } 
        // else if (PER == 0) {
        //     if (d<300) {
        //         grPER->AddPoint(X, Y);
        //         d++;
        //     }
        // } 
        // else if (TMI == 0) {
        //     if (e<300) {
        //         grTMI->AddPoint(X, Y);
        //         e++;
        //     }
        // } 
        else if (UNI == 0) {
            if (b<300) {
                grUNI->AddPoint(X, Y);
                b++;
            }
            // grUNI->AddPoint(X, Y);
        } 
        else if (EXP == 0) { // else
            if (f<300) {
                grEXP->AddPoint(X, Y);
                f++;
            }
        } 
        else if (GOOD) {
            grOK->AddPoint(X, Y);
            
        } else {
            fprintf(stderr, "**Warning: FinalPlots, should never get here\n");
        }

        i++;
        
        if ( i%100 == 0 ) {
            if (do_first) {
                cout << "Done " << i << " points" << endl;
                do_first = false;
            }
        }
    }

    // Graph* grOK = new Graph("OK");
    // grOK = ReadGraphData("data/PassedTeoCons/Good/PassedTeoCons.dat", "OK", XAxis, YAxis);

        // double la2 = ParMap["la2"][i];
        // double la3 = ParMap["la3"][i];
        // double la4 = ParMap["la4"][i];
        // double la5 = ParMap["la5"][i];
        // double laL = ParMap["laL"][i];
        // double m22Squared = ParMap["m22Squared"][i];
        // double MH = ParMap["MH"][i]; // MHX CDM
        // double MA = ParMap["MA"][i]; // MH3 It is A in IDM paper
        // double MC = ParMap["MC"][i]; // MHC Charged Higgs

    // }
    


    const int Marker = 20;

    RootClass root(grEXP); // 
    root.ScatterPlot(7, true, Marker);
    grEXP->SetLegendBit(true);
    grEXP->SetSaveOutputBit(true);

    // root.ScatterPlot(4, true, Marker);
    // grBFB->SetLegendBit(true);
    // grBFB->SetSaveOutputBit(true);

    root.SetNewGraph(grBFB);
    root.ScatterPlot(4, true, Marker);

    root.SetNewGraph(grUNI);
    root.ScatterPlot(6, true, Marker);

    root.SetNewGraph(grSTU);
    root.ScatterPlot(3, true, Marker);

    // root.SetNewGraph(grPER);
    // root.ScatterPlot(877, true, Marker);

    // root.SetNewGraph(grTMI);
    // root.ScatterPlot(806, true, Marker);

    // root.SetNewGraph(grEXP);
    // root.ScatterPlot(7, true, Marker);

    root.SetNewGraph(grOK);
    root.ScatterPlot(2, true, Marker);

    root.MultiGraphPlot(Title, XAxis, YAxis);

    delete grBFB;
    delete grUNI;
    delete grSTU;
    delete grTMI;
    delete grPER;
    delete grEXP;
    delete grOK;
}



void IDM::SXT(int nPoints) {
cout << "Making SXT graph...\n";
    TApplication app("app", nullptr, nullptr);
    TCanvas *c = new TCanvas("c", "SXT", 800, 800);

    vector<int> keepIndex;

    vector<double> Svec, Tvec;
    Svec.clear();
    Tvec.clear();
    vector<double> aux;

    double la1 = Pars.Getla1();
    double m11 = 125.1; // Pars.GetMh();

    // vector<vector<double>> ST = readProfSTU();

    int N = 0;
    int max =  ParMap["MH"].size(); // ST[0].size(); // 
    cout << "Max " << max << endl;

/*
    for (int i = 0; i < max; i++) {

        double MH = ParMap["MH"][i];
        double MA = ParMap["MA"][i];
        double MC = ParMap["MC"][i];

        double la2 = ParMap["la2"][i];
        double la3 = ParMap["la3"][i];

        // cout << "Values in SXT " << m11 << " " << MH << " " << MA << " " << MC << endl;
        // aux = ST_graph_prep(m11, MH, MA, MC);
        // double SVal = aux[0];
        // double TVal = aux[1];
        // // double UVal = aux[2];
        // // cout << "S: " << aux[0] << " T: " << aux[1] << endl;
        // cout << "SVAL e TVAL " << SVal << " " << TVal << endl;
        // if (MyST_Check(SVal, TVal)) {
        //     cout << " Checked" << endl;
        //     S.push_back(SVal);
        //     T.push_back(TVal);
        // }
        // int twoMins = TwoMins(Pars);

    // Graph prep before 
        // double S, T, U;
        // S = T = U = 0;
        // ST(m11, MH, MA, MC, S, T, U);
        // Svec.push_back(S);
        // Tvec.push_back(T);
        // // cout << "Antes " << S << endl;
        if (ST(m11, MH, MA, MC, S, T, U)) {
            cout << "(S,T) = (" << S << ", " << T <<  ") para (MH,MA,MC,la2,la3) = "  
            << MH << ", " << MA << ", " << MC << ", " << la2 << ", " << la3 << ")" << endl;
            Svec.push_back(S);
            Tvec.push_back(T);
        }
    }
    */

    vector<pair<double, double>> Values = GetParsSTU(nPoints);
    WriteSTUPars(Values, "data/STU/STU_Points.dat");
    WriteDat("data/STU/STU_PointsPars.dat", ParMap);

    for (int i = 0; i < nPoints; i++)
    {
        Svec.push_back(Values[i].first);
        Tvec.push_back(Values[i].second);
    }
    

    int Npoints = Svec.size();
    TGraph *gr = new TGraph(Npoints, &Svec[0], &Tvec[0]);
    // TGraph *gr = new TGraph(max, &ST[0][0], &ST[1][0]);

    string name = "SXT_19-03";
    gr->SetTitle(name.c_str());
    gr->GetXaxis()->SetTitle("S");
    gr->GetYaxis()->SetTitle("T");
    

    gr->SetMarkerColor(4);
    gr->SetMarkerStyle(20);
    
    gr->Draw("AP");

    // c->BuildLegend();

    c->Update();

    string dir = "bin/Plots/";
    name.append(".png");
    dir.append(name);
    c->SaveAs(dir.c_str());

    TRootCanvas *rc = (TRootCanvas *)c->GetCanvasImp();
    rc->Connect("CloseWindow()", "TApplication", gApplication, "Terminate()");
    app.Run();
}



void IDM::OverlapSXT(const string& filename) {
    TApplication app("app", nullptr, nullptr);
    TCanvas *c = new TCanvas("c", "canvas", 1300, 800);
    c->SetGrid();

    TMultiGraph *mg = new TMultiGraph();
    string name = "S-T Plane";
    mg->SetTitle(name.c_str());

    vector<double> Svec, Tvec;
    Svec.clear();
    Tvec.clear();
    vector<double> aux;

    // double la1 = Pars.Getla1();
    // double Mh = 125.1; // Pars.GetMh();
    // double m11 = Mh*Mh;

    // vector<pair<double, double>> Values = GetParsSTU(nPoints);

    // WriteSTUPars(Values, "data/STU/STU_Points.dat");
    // WriteDat("data/STU/STU_PointsPars.dat", ParMap);
    
    ReadDAT(filename, ParMap);
    int N = 0;
    int max =  ParMap["MH"].size(); // ST[0].size(); // 
    cout << "Max " << max << endl;

    double la1 = Pars.Getla1();
    double Mh = Pars.GetMh();

    double S,T,U;

    for (int i = 0; i < max; i++) {
        double MH = ParMap["MH"][i];
        double MA = ParMap["MA"][i];
        double MC = ParMap["MC"][i];
        STU_Test(Mh, MH, MA, MC, S, T, U);
        Svec.push_back(S);
        Tvec.push_back(T);
    }
    

    // for (int i = 0; i < nPoints; i++)
    // {
    //     Svec.push_back(Values[i].first);
    //     Tvec.push_back(Values[i].second);
    // }

    int Npoints = Svec.size();
    TGraph *gr = new TGraph(Npoints, &Svec[0], &Tvec[0]);
    // TGraph *gr = new TGraph(max, &ST[0][0], &ST[1][0]);
    gr->SetTitle("SXT");
    gr->SetMarkerColor(4);
    gr->SetMarkerStyle(10);

    Svec.clear();
    Tvec.clear();
    
    vector<pair<double, double>>  profValues = readProfSTU();
    int ProfPoints = profValues.size();
    for (auto &pair : profValues)
    {
        Svec.push_back(pair.first);
        Tvec.push_back(pair.second);
    }
    
    
    TGraph *grprof = new TGraph(Svec.size(), &Svec[0], &Tvec[0]);
    grprof->SetTitle("Elipse");
    grprof->SetMarkerColor(2);
    grprof->SetMarkerStyle(10);

    mg->Add(gr);
    mg->Add(grprof);

    c->Update();

    mg->GetXaxis()->SetTitle("S");
    mg->GetXaxis()->CenterTitle();
    mg->GetYaxis()->SetTitle("T");
    mg->Draw("AP");

    // c->BuildLegend();

    TLegend *leg = new TLegend(0.9, 0.7, 0.99, 0.9);
    leg->SetHeader("Constraints", "C");
    leg->AddEntry(grprof, "Allowed", "p");
    leg->AddEntry(gr, "Results", "p");
    leg->Draw();

    c->Update();

    string dir = "bin/Plots/";
    name.append(".png");
    dir.append(name);
    c->SaveAs(dir.c_str());

    TRootCanvas *rc = (TRootCanvas *)c->GetCanvasImp();
    rc->Connect("CloseWindow()", "TApplication", gApplication, "Terminate()");
    app.Run();
}


// NAO APAGAR, MTO IMPORTANTE
/*/
void IDM::OverlapSXT(int nPoints) {
    TApplication app("app", nullptr, nullptr);
    TCanvas *c = new TCanvas("c", "canvas", 1300, 800);
    c->SetGrid();

    TMultiGraph *mg = new TMultiGraph();
    string name = "S-T Plane";
    mg->SetTitle(name.c_str());

    vector<double> Svec, Tvec;
    Svec.clear();
    Tvec.clear();
    vector<double> aux;

    // double la1 = Pars.Getla1();
    // double Mh = 125.1; // Pars.GetMh();
    // double m11 = Mh*Mh;

    // vector<pair<double, double>> Values = GetParsSTU(nPoints);

    // WriteSTUPars(Values, "data/STU/STU_Points.dat");
    // WriteDat("data/STU/STU_PointsPars.dat", ParMap);
    
    ReadDAT("data/PassedTeoCons/PassedTeoCons.dat", ParMap);
    int N = 0;
    int max =  ParMap["MH"].size(); // ST[0].size(); // 
    cout << "Max " << max << endl;

    double la1 = Pars.Getla1();
    double Mh = Pars.GetMh();

    double S,T,U;

    for (int i = 0; i < max; i++) {
        double MH = ParMap["MH"][i];
        double MA = ParMap["MA"][i];
        double MC = ParMap["MC"][i];

        if (ST(Mh, MH, MA, MC, S, T, U)) {
            Svec.push_back(S);
            Tvec.push_back(T);
        }
    }
    

    // for (int i = 0; i < nPoints; i++)
    // {
    //     Svec.push_back(Values[i].first);
    //     Tvec.push_back(Values[i].second);
    // }

    int Npoints = Svec.size();
    TGraph *gr = new TGraph(Npoints, &Svec[0], &Tvec[0]);
    // TGraph *gr = new TGraph(max, &ST[0][0], &ST[1][0]);
    gr->SetTitle("SXT");
    gr->SetMarkerColor(4);
    gr->SetMarkerStyle(20);

    Svec.clear();
    Tvec.clear();
    vector<pair<double, double>>  profValues = readProfSTU();
    int ProfPoints = profValues.size();
    for (auto &pair : profValues)
    {
        Svec.push_back(pair.first);
        Tvec.push_back(pair.second);
    }
    
    
    TGraph *grprof = new TGraph(Svec.size(), &Svec[0], &Tvec[0]);
    grprof->SetTitle("Elipse");
    grprof->SetMarkerColor(2);
    grprof->SetMarkerStyle(20);

    mg->Add(grprof);
    mg->Add(gr);

    c->Update();

    mg->GetXaxis()->SetTitle("S");
    mg->GetXaxis()->CenterTitle();
    mg->GetYaxis()->SetTitle("T");
    mg->Draw("AP");

    // c->BuildLegend();

    TLegend *leg = new TLegend(0.9, 0.7, 0.99, 0.9);
    leg->SetHeader("Constraints", "C");
    leg->AddEntry(grprof, "Allowed", "p");
    leg->AddEntry(gr, "Results", "p");
    leg->Draw();

    c->Update();

    string dir = "bin/Plots/";
    name.append(".png");
    dir.append(name);
    c->SaveAs(dir.c_str());

    TRootCanvas *rc = (TRootCanvas *)c->GetCanvasImp();
    rc->Connect("CloseWindow()", "TApplication", gApplication, "Terminate()");
    app.Run();
}*/


/*
void IDM::OverlapSXT(int nPoints) {
    TApplication app("app", nullptr, nullptr);
    TCanvas *c = new TCanvas("c", "canvas", 1300, 800);

    TMultiGraph *mg = new TMultiGraph();
    string name = "S-T Plane";
    mg->SetTitle(name.c_str());

    vector<double> Svec, Tvec;
    Svec.clear();
    Tvec.clear();
    vector<double> aux;

    double la1 = Pars.Getla1();
    double Mh = 125.1; // Pars.GetMh();
    double m11 = Mh*Mh;

    int N = 0;
    int max =  ParMap["MH"].size(); // ST[0].size(); // 
    cout << "Max " << max << endl;

    vector<pair<double, double>> Values = GetParsSTU(nPoints);
    WriteSTUPars(Values, "data/STU/STU_Points.dat");
    WriteDat("data/STU/STU_PointsPars.dat", ParMap);

    for (int i = 0; i < nPoints; i++)
    {
        Svec.push_back(Values[i].first);
        Tvec.push_back(Values[i].second);
    }

    int Npoints = Svec.size();
    TGraph *gr = new TGraph(Npoints, &Svec[0], &Tvec[0]);
    // TGraph *gr = new TGraph(max, &ST[0][0], &ST[1][0]);
    gr->SetTitle("SXT");
    gr->SetMarkerColor(4);
    gr->SetMarkerStyle(20);

    Svec.clear();
    Tvec.clear();
    vector<pair<double, double>>  profValues = readProfSTU();
    int ProfPoints = profValues.size();
    for (auto &pair : profValues)
    {
        Svec.push_back(pair.first);
        Tvec.push_back(pair.second);
    }
    
    
    TGraph *grprof = new TGraph(Svec.size(), &Svec[0], &Tvec[0]);
    grprof->SetTitle("Elipse");
    grprof->SetMarkerColor(2);
    grprof->SetMarkerStyle(20);

    mg->Add(grprof);
    mg->Add(gr);

    c->Update();

    mg->GetXaxis()->SetTitle("S");
    mg->GetXaxis()->CenterTitle();
    mg->GetYaxis()->SetTitle("T");
    mg->Draw("AP");

    // c->BuildLegend();

    TLegend *leg = new TLegend(0.9, 0.7, 0.99, 0.9);
    leg->SetHeader("Constraints", "C");
    leg->AddEntry(grprof, "Allowed", "p");
    leg->AddEntry(gr, "Results", "p");
    leg->Draw();

    c->Update();

    string dir = "bin/Plots/";
    name.append(".png");
    dir.append(name);
    c->SaveAs(dir.c_str());

    TRootCanvas *rc = (TRootCanvas *)c->GetCanvasImp();
    rc->Connect("CloseWindow()", "TApplication", gApplication, "Terminate()");
    app.Run();
}
*/

void IDM::STU_BAD() {
    /* See values from professor */
    // ReadCSV("data/STU/check/STU-Bad.csv", ParMap);
    // WriteMapToFile("data/STU/check/Verify_STU.dat", ParMap, Pars);
    /* Gen new values and */
    ReadDAT("data/PassedTeoCons/PassedTeoCons.dat", ParMap);
    WriteMapToFile("data/teste.dat", ParMap, Pars);
}

void IDM::ParsGraph(const string& path, const string& Title, const string& xName, const string& yName) {
    // Graph grValues = ReadGraphData(path, Title, xName, yName);
    // cout << grValues << endl;

    // fRoot = new RootClass(grValues, fApp);
    // fRoot->ScatterPlot(2, false);
    // delete fRoot;

    // RootClass root(grValues);
    // root.ScatterPlot(2, false);

    // root.GraphPlot(true, 2, 20, true);

    // Graph gr2 = ReadGraphData(path, "Teste", "MH", "la2");
    // root.SetNewGraph(gr2);
    // // root.GraphPlot(true, 2, 20, true);

    
    // root.MultiGraphPlot("MultiName");
}

void IDM::Omegas(const string& filename) {

    double OmegaPlanckLimit = 0.1197;
    double OUL = OmegaPlanckLimit + 0.0022;
    double OLL = OmegaPlanckLimit - 0.0022;

    double OmegaLimit = 0.1241;


    Graph *gr = ReadGraphData(filename, "", "laL", "Omega");


    Graph *grUP = new Graph("Above Limit");
    Graph *grDown = new Graph("Under Limit");
    Graph *grOK = new Graph("In Limit");

    // gr->GetX().clear();

    int N = gr->GetY().size();
    for (int i = 0; i < N; i++) {
        // gr->AddToX(i);
        double X = gr->GetX()[i];
        double Y = gr->GetY()[i];

        if (Y > 1e-9 && Y < OLL) {
            grDown->AddPoint(X, Y);
        }
        else if ( Y >= OLL && Y <= OUL) {
            grOK->AddPoint(X, Y);
        }
        else if (Y > OUL) {
            grUP->AddPoint(X, Y);
        }
        else {
            cout << "Should never get here" << endl;
            cout << Y << endl;
        }
        
    }

    // cout << "grOK:" << endl;
    // for (auto &val : grOK->GetY())
    // {
    //     cout << val << endl;
    // }
    //     cout << "grUP:" << endl;
    // for (auto &val : grUP->GetY())
    // {
    //     cout << val << endl;
    // }
    //     cout << "grDown:" << endl;
    // for (auto &val : grDown->GetY())
    // {
    //     cout << val << endl;
    // }
    

    // int N = gr->GetY().size();
    // vector<double> vecUP, vecDown, vecOK, vecX;
    // for (int i = 0; i < N; i++) {
    //     // gr->AddToX(i);

    //     double Y = gr->GetY()[i];
        
    //     if (Y < 0) {
    //         cout << "OLAAAAAAAAaaaaaaaaaaaaaaaaaaA" << endl;
    //         continue;
    //     } 
    //     else {
    //         vecX.push_back(gr->GetX()[i]);
    //         if (Y < OLL) {
    //             // cout << Y << endl;
    //             vecDown.push_back(Y);
    //         }
    //         else if ( Y >= OLL && Y <= OUL) {
    //             vecOK.push_back(Y);
    //         }
    //         else if (Y > OUL) {
    //             vecUP.push_back(Y);
    //         }
    //         else {
    //             cout << "Should never get here" << endl;
    //         }
    //     }
    // }

    // for (auto &val : vecUP)
    // {
    //     if (val > 1 ) cout << val << endl;
    // }
    

    // Graph *grUP = new Graph("Above Limit", "Points", vecX, "Above Limit", vecUP);
    // Graph *grDown = new Graph("Under Limit", "Points", vecX, "Under Limit", vecDown);
    // Graph *grOK = new Graph("In Limit", "Points", vecX, "In Limit", vecOK);
    

    RootClass* root = new RootClass(grOK);
    root->ScatterPlot(4, true, 20);
    grOK->SetOpenWindowBit(true);
    grOK->SetSaveOutputBit(true);

    root->SetNewGraph(grUP);
    root->ScatterPlot(3, true, 20);
    root->SetNewGraph(grDown);
    root->ScatterPlot(2, true, 20);

    root->MultiGraphPlot("MGraph title", "laL", "Relic Density #Omega");

    // cout << "after" << endl;

    delete root;
    delete gr;
    delete grOK;
    delete grUP;
    delete grDown;
}