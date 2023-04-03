#include "TestFuncs.h"


void TEST_GenParsSTUValues() {
    IDM pic;
    pic.GenWriteCheckedPars("data/test/TEST_FUNCTIONS.dat", 100);
    auto map = pic.GetParMap();
    auto pars = pic.GetPars();
    ReadDAT("data/test/TEST_FUNCTIONS.dat", map);
    WriteMapToFile("data/TEST_FUNCTIONS_WRITTEN.dat", map, pars);
    // pic.STU_BAD();
    pic.OverlapSXT("data/test/TEST_FUNCTIONS.dat");
}


void TEST_Multigraph() {
    
    Graph* grValues = ReadGraphData("data/test/TEST_FUNCTIONS.dat", "Teste", "MH", "MA");
    Graph* gr = ReadGraphData("data/test/TEST_FUNCTIONS.dat", "Scatter", "MA", "MC");
    cout << grValues->GetTitle() << endl;
    // // grValues->DivYVec(gr->GetY());

    grValues->SetSaveOutputBit(false);
    grValues->SetOpenWindowBit(false);

    RootClass* root = new RootClass(grValues);
    root->ScatterPlot(4, true);
    root->SetNewGraph(gr);
    root->ScatterPlot(2, true);

    grValues->SetOpenWindowBit(true);
    root->MultiGraphPlot("MGraph title", "ola", "adeus");

    delete gr;
    delete root;
    delete grValues;
}

void TEST_FirstPlot() {
    IDM pic;
    pic.StoreParsTest(10000);
    pic.FirstPlot("data/test/FirstPlot.dat");
}

void TEST_STU() {
    IDM pic;
    pic.OverlapSXT("data/test/TEST_FUNCTIONS.dat");
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