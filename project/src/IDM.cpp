#include "IDM.h"

IDM::IDM() {
    Pars.GenPars(1);
}

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

Parameters IDM::GetPars() {
    return Pars;
}

// Not ready
void IDM::GenNewPars() {
    Pars.GenPars(1);
}

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

void IDM::StorePars(int nPoints) {
    ClearParMap();
    cout << "Generating and storing Parameters...\n";
    for (int i = 0; i < nPoints; i++) {
        Pars.GenPars(1); // 1
        AddToMap();
    }
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


void IDM::FirstPlot() {
    cout << "Making FirstPlot...\n";
    TApplication app("app", nullptr, nullptr);
    TCanvas *c = new TCanvas("c", "FirstPlot", 800, 800);
    TMultiGraph *mg = new TMultiGraph();

    string name = "Title";
    mg->SetTitle(name.c_str());

    vector<int> keepIndex;

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
        double la2 = ParMap["la2"][i];
        double la3 = ParMap["la3"][i];
        double la4 = ParMap["la4"][i];
        double la5 = ParMap["la5"][i];
        double laL = ParMap["laL"][i];
        double m22Squared = ParMap["m22Squared"][i];

        int bfb = BoundFromBelow(la1, la2, la3, laL, Mh, m22Squared); // BFB_Test(la1, la2, la3, laL);
        int Pert = Perturbativity_Test(la1, la2, la3, la4, la5, laL);
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
            keepIndex.push_back(i);
            // AddToMap();
            // cout << "Got here\n";
        } else if (bfb == 0 && Pert == 0) {
            grBoth->AddPoint(la2, laL);
            // cout << "Zeros\n";
        } else {
            cout << "Should never get here\n";
        }
    }

    FilterParMap(keepIndex);
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

    while (N<20000) // 10000
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

void IDM::SavePars(const string &filename) {
    //Open the output file
    ofstream outputFile(filename);
    if (!outputFile.is_open()) {
        fprintf(stderr, "**Can not open file to save parameters\n");
        exit(0);
    }
    //Write column headings
	for (auto const &pair : ParMap) 
		outputFile << pair.first << ",";
	outputFile << "\n";
	// write data
	for (int i = 0; i < ParMap.begin()->second.size(); i++) {
		for (auto const &pair : ParMap) 
			outputFile << pair.second[i] << ",";
		outputFile << "\n";
	}
    // Close the file
    outputFile.close();
}

void IDM::ClearParMap() {
    cout << "Clearing Parameter Map\n";
    // Save map just in case if it is not empty
    if (!ParMap.empty()) {
        SavePars("data/Saved.csv");
    }
    // Clear map
    ParMap.clear();
    // Initialize map
    vector<string> parNames = {"la2", "la3", "la4", "la5", "laL", "MH", "MC", "MA", "m22Squared"};
    vector<double> values;
    values.clear();
    // Insert pairs of [Key,Values] of the parameters   
    for (auto &i : parNames)
        ParMap.insert(make_pair(i,values));
}

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
	/*
    for (auto &pair : ParMap) {
		cout << pair.first << ": ";
		for (auto& value : pair.second) {
			cout << value << " ";
		}
		cout << endl;
	}
    */
}

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
}
*/

void IDM::WriteElementToFile(string key, ofstream &file, int i) {
    // use the find function to search for the key and get the element at that key if it exists
    // map<string, vector<double>> myMap
    auto found_key = ParMap.find(key);
    if (found_key != ParMap.end())
        file << found_key->second[i] << "\t"; 
    // setprecision(n) to limit significant digits of number to n digits
    // file << setprecision(5) << found_key->second[i] << "\t"; 
}

/**
 * @brief Write ParMap to a .dat file formatted for Experimental constraints
 * 
 * @param filename 
 */
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
    string parNames[] = {"m11Sq", "MH", "MA", "MC", "la2", "laL", "la1", "la3", "la4", "la5"};
	double m11Sq = Pars.Getla1()*Pars.Getv()*Pars.Getv(); // m11^2 = la1*v^2
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
			if (par != "m11Sq" && par != "la1") {
				WriteElementToFile(par, file, i);
			} else if (par == "m11Sq") {
				file << m11Sq << "\t";
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
}

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

vector<vector<double>> readProfSTU() {
    ifstream infile("data/profSTUdata.dat");
    vector<double> S;
    vector<double> T;
    double s, t;
    while (infile >> s >> t) {
        S.push_back(s);
        T.push_back(t);
    }
    for (int i = 0; i < S.size(); i++) {
        cout << S[i] << '\t' << T[i] << endl;
    }
    vector<vector<double>> res = {S, T};
    return res;
}

void IDM::SXT() {
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

    for (int i = 0; i < max; i++) {

        double MH = ParMap["MH"][i];
        double MA = ParMap["MA"][i];
        double MC = ParMap["MC"][i];
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

    /* Graph prep before */
        double S, T, U;
        S = T = U = 0;
        ST(m11, MH, MA, MC, S, T, U);
        Svec.push_back(S);
        Tvec.push_back(T);
        // // cout << "Antes " << S << endl;
        // if (ST(m11, MH, MA, MC, S, T, U)) {
        //     // cout << "Depois " << S << endl;
        //     Svec.push_back(S);
        //     Tvec.push_back(T);
        // }
    }

    int Npoints = Svec.size();
    TGraph *gr = new TGraph(Npoints, &Svec[0], &Tvec[0]);
    // TGraph *gr = new TGraph(max, &ST[0][0], &ST[1][0]);

    string name = "SXT_12-03";
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