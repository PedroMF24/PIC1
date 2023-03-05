#include "src/RootClass.h"

int main() {
    TApplication app("app", nullptr, nullptr);
    TCanvas *c = new TCanvas("c", "multigraph", 800, 800);
    TMultiGraph *mg = new TMultiGraph();

    string name = "Test";
    mg->SetTitle(name.c_str());

    vector<TGraph *> gr;

    int N = 0;
    // vector<int> bits;
    const vector<string> names = {"Allowed", "Positivity", "Perturbativity", "Both"}

    for (int i = 0; i < names.size(); i++) {
        gr[i] = new TGraph();
        gr[i]->SetTitle(names[i]);
        // bit.push_back(0); // initialize bits vector and give it proper size
    }

for (auto &graph : gr)
{
    
}

    while (N<100) // 10000
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
            cout << "Got here\n";
        } else if (bfb == 0 && Pert == 0) {
            grBoth->AddPoint(Pars.Getla2(), Pars.GetlaL());
            cout << "Zeros\n";
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
    // c->Update();

    string dir = "bin/Plots/";
    name.append(".png");
    dir.append(name);
    c->SaveAs(dir.c_str());

    TRootCanvas *rc = (TRootCanvas *)c->GetCanvasImp();
    rc->Connect("CloseWindow()", "TApplication", gApplication, "Terminate()");
    app.Run();
}