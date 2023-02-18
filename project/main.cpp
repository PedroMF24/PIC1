#include "src/TheoConstraints.h"
// #include "src/ExpConstraints.h"
#include "src/RootClass.h"
#include "src/Parameters.h"
#include "src/IDM.h"

int main()
{
    Parameters Pars;
    // TheoCons TC(Pars);

    IDM pic(Pars);
    pic.StorePars(10000);
    pic.FirstPlot();
    //cout << "Ended first plot!\n";
    //pic.LimitsFromColliders();

    // TApplication app("app", nullptr, nullptr);
    // TCanvas *c = new TCanvas("c", "multigraph", 800, 800);
    // TMultiGraph *mg = new TMultiGraph();

    // string name = "Title";
    // mg->SetTitle(name.c_str());


    // int N = 0;
    // vector<double> la2;
    // vector<double> laL;

    // TGraph *grCheck = new TGraph();
    // grCheck->SetTitle("Allowed");
    // TGraph *grBFB = new TGraph();
    // grBFB->SetTitle("Positivity");

    // TGraph *grPert = new TGraph();
    // grPert->SetTitle("Perturbativity");

    // while (N<10000)
    // {
    //     TC.GenNewPars();
    //     int BFB = TC.BFB();
    //     int Pert = TC.Perturbativity();
    //     int TwoMins = TC.TwoMins();

    //     int check = BFB && Pert; // & TwoMins;

    //     if (BFB == 1 && Pert == 0)
    //     {
    //         grPert->AddPoint(TC.GetPars().Getla2(), TC.GetPars().GetlaL());
    //     } else if (BFB == 0 && Pert == 1) 
    //     {
    //         grBFB->AddPoint(TC.GetPars().Getla2(), TC.GetPars().GetlaL());
    //     } else if (check) {
    //         grCheck->AddPoint(TC.GetPars().Getla2(), TC.GetPars().GetlaL());
    //         cout << "Got here\n";
            
    //     } else {
    //         cout << "Weirdge\n";
    //     }
    //     N++;
    // }

    // grCheck->SetMarkerColor(2);
    // grCheck->SetMarkerStyle(20);

    // grBFB->SetMarkerColor(4);
    // grBFB->SetMarkerStyle(20);

    // grPert->SetMarkerColor(3);
    // grPert->SetMarkerStyle(20);

    // mg->Add(grCheck);
    // mg->Add(grBFB);
    // mg->Add(grPert);
    
    // mg->Draw("AP");

    // c->BuildLegend();
    // c->Update();

    // string dir = "bin/Plots/";
    // name.append(".png");
    // dir.append(name);
    // c->SaveAs(dir.c_str());

    // TRootCanvas *rc = (TRootCanvas *)c->GetCanvasImp();
    // rc->Connect("CloseWindow()", "TApplication", gApplication, "Terminate()");
    // app.Run();

    return 0;
}

    // Parameters P1, P2;
    // P1.ImportPars("data/dataTest.par");
    // cout << P1;
    // TheoCons TC(P1);
    // // cout << P1;
    // cout << TC.CheckAllTheoCons();



    // Test Parameters '=' operator
    // Parameters P1;
    // Parameters P2;
    // cout << "P1 " << P1.Getla2() << endl;
    // cout << "P2 " << P2.Getla2() << endl;
    // P2 = P1;
    // cout << "new P2 " << P2.Getla2() << endl;
    

    // while (1) /*vector.size() < N*/
    // {
    //     Parameters Pars;

    //     ExpCons EC(Pars);
    //     TheoCons TC(Pars);
    // }
    
    // for (int i = 0; i < 10; i++)
    // {
    //     cout << Rd.UniDist(0,1) << endl;
    // }
    

    // int i = 0;
    // while (i<10)
    // {
    //     cout << "Generating m22Squared, la3, la4, la5" << endl;
    //     // P.GenPars();
    //     // cout << P.Getla1() << endl;
    //     // cout << P.Getla2() << endl;
    //     // cout << P.GetlaL() << endl;
    //     // cout << P.GetMH() << endl;
    //     cout << P.Getm22Squared() << endl;
    //     cout << P.Getla3() << endl;
    //     cout << P.Getla4() << endl;
    //     cout << P.Getla5() << endl;
    //     cout << "---" << endl;
    //     i++;
    // }

    // printf("m22^2 = %lf\n", Exp.Getm22Squared());

    // RootClass R;
    // R.ScatterPlot("Ola", 10000);