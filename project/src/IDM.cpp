#include "IDM.h"

IDM::IDM() {
    Pars.GenPars();
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

void IDM::GenNewPars() {
    Pars.GenPars();
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
    cout << "Generating and storing Parameters...\n";
    for (int i = 0; i < nPoints; i++) {
        Pars.GenPars();
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
    int N = 0;
    int max = ParMap["MH"].size();

    for (int i = 0; i < max; i++) {

        double la2 = ParMap["la2"][i];
        double la3 = ParMap["la3"][i];
        double laL = ParMap["laL"][i];


        int bfb = BFB_Test(la1, la2, la3, laL);
        int Pert = Perturbativity_Test(la2);
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
            cout << "Weirdge\n";
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

// void IDM::SavePars(const string &filename) {
//     //Open the output file
//     ofstream outputFile(filename);
//     if (!outputFile.is_open()) {
//         fprintf(stderr, "**Can not open file to save parameters\n");
//         exit(0);
//     }
//     //Write column headings
// 	for (auto const& [key, value] : ParMap) 
// 		outputFile << key << ",";
// 	outputFile << "\n";
// 	// write data
// 	for (int i = 0; i < ParMap.begin()->second.size(); i++) {
// 		for (auto const& [key, value] : ParMap) 
// 			outputFile << value[i] << ",";
// 		outputFile << "\n";
// 	}

//     // for (auto iter = ParMap.begin(); iter != ParMap.end(); ++iter) {
//     //     string key = iter->first;
//     //     outputFile << key << ",";
//     // }
//     // outputFile << "\n";
//     // // write data
//     // for (auto iter = ParMap.begin(); iter != ParMap.end(); ++iter) {
//     //     vector<double> value = iter->second;
//     //     for (int i = 0; i < value.size(); i++) 
//     //         outputFile << value[i] << ",";
//     //     outputFile << "\n";
//     // }
    
//     //Close the file
//     outputFile.close();
// }

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