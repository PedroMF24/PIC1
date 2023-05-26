#include "include/TestFuncs.h"


void TEST_GenParsSTUValues() {
    IDM pic;
    pic.GenWriteCheckedPars("data/test/TEST_FUNCTIONS.dat", 100, true);
    auto map = pic.GetParMap();
    auto pars = pic.GetPars();
    ReadDAT("data/test/TEST_FUNCTIONS.dat", map);
    WriteMapToFile("data/TEST_FUNCTIONS_WRITTEN.dat", map, pars);
    // pic.STU_BAD();
    pic.OverlapSXT("data/test/TEST_FUNCTIONS.dat", false, false);
}

void TEST_Multigraph() {
    
    Graph* grValues = ReadGraphData("data/test/TestData.dat", "OK", "MH", "MA");
    Graph* gr = ReadGraphData("data/test/TestData.dat", "Good", "MA", "MC");
    cout << grValues->GetTitle() << endl;
    // // grValues->DivYVec(gr->GetY());

    grValues->SetSaveOutputBit(false);
    grValues->SetOpenWindowBit(false);

    RootClass* root = new RootClass(grValues);
    root->ScatterPlot(4, true, 20);
    root->SetNewGraph(gr);
    root->ScatterPlot(2, true, 20);

    grValues->SetOpenWindowBit(true);
    root->MultiGraphPlot("MGraph title", "#font[12]{M_{H^{+}} [GeV]}", "#font[12]{M_{H^{+}} [GeV]}");

    delete gr;
    delete root;
    delete grValues;
}


pair<double,double> calculateStandardDeviation(const vector<double>& values) {
    // Calculate the mean of the values
    double sum = 0.0;
    for (double value : values) {
        sum += value;
    }
    double mean = sum / values.size();

    // Calculate the sum of squared differences from the mean
    double squaredDiffSum = 0.0;
    for (double value : values) {
        double diff = value - mean;
        squaredDiffSum += diff * diff;
    }

    // Calculate the variance and standard deviation
    double variance = squaredDiffSum / values.size();
    double standardDeviation = std::sqrt(variance);

    pair<double, double> result = make_pair(mean, standardDeviation);
    return result;
}

void TEST_laL() {
    // Remember to change CheckTeoCons in StoreCheckedPars !!!
    IDM pic;
    pic.GenWriteCheckedPars("data/test/TEST_FUNCTIONS.dat", 10000, true);
    auto map = pic.GetParMap();
    // auto pars = pic.GetPars();
    ReadDAT("data/test/TEST_FUNCTIONS.dat", map);

    int count = 0;
    int max =  map["MH"].size(); // ST[0].size(); // 
    cout << "Max " << max << endl;

    for (int i = 0; i < max; i++) {
        double laL = map["laL"][i];
        if (laL <= -1)
            count++;
    }
    cout << "laL <= -1 " << count << " times" << endl;
}

void TEST_Passed_U_STU(int nPoints) {
    IDM pic;
    pic.StoreParsTest(nPoints);
    // ReadDAT(filename, ParMap);
    auto map = pic.GetParMap();
    auto pars = pic.GetPars();
    int max =  map["MH"].size(); // ST[0].size(); // 
    cout << "Max points: " << max << endl;

    double la1 = pars.Getla1();
    double Mh = pars.GetMh();

    int U_kills = 0;

    for (int i = 0; i < max; i++) {
        double S,T,U;
        S = T = U = 0;
        double MH = map["MH"][i];
        double MA = map["MA"][i];
        double MC = map["MC"][i];
        // If not, it means U eliminates it
        int ST = pic.ST(Mh, MH, MA, MC, S, T, U);
        int STU = pic.STU_Test(Mh, MH, MA, MC, S, T, U);
        if (ST && !STU) {
            U_kills++;
        }
    }
    cout << "U killed " << U_kills << " points that passed ST" << endl;
}

void TEST_PassedSTU() {
    IDM pic;
    int N = 50;
    int nPoints = 10000;
    double all_passed = 0;
    vector<double> values;
    for (int i = 0; i < N; i++)
    {
        values.push_back(pic.InSTUEllipsis("ola", nPoints));
        //all_passed += pic.InSTUEllipsis("ola", nPoints);
    }
    auto result = calculateStandardDeviation(values);
    // double average = all_passed/(N*nPoints)*100;

    cout << "On average, " << result.first << " +/- " << result.second << " points pass STU" << endl;
    cout << "Percentage passed: " << (result.first/nPoints)*100 << "%" << " +/- " << (result.second / result.first) * 100 << "%" << endl;
}

void TEST_FirstPlot() {
    IDM pic;
    pic.StoreParsTest(10000);
    pic.FirstPlot("data/test/FirstPlot.dat");
}

void TEST_STU() {
    IDM pic;
    pic.OverlapSXT("data/test/TEST_FUNCTIONS.dat", false, false);
}


void TEST_ParameterGeneration() {
        Parameters pars;
    int i = 0;
    pars.SetScanBit(true);
    while (i<5)
    {
        cout << pars << endl;
        cout << pars.Getla3()+pars.Getla4()+pars.Getla5() << "\t" << pars.GetlaL() << endl; 
        pars.GenPars();
        i++;
    }
}