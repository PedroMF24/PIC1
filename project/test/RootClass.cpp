#include "RootClass.h"

using namespace std;

vector<double> x,y;

void RootClass::ScatterPlot(string Title, int nPoints)
{
    TApplication app("app", nullptr, nullptr);
    TCanvas *c = new TCanvas("c", "multigraph", 800, 800);
    TMultiGraph *mg = new TMultiGraph();

    string name = Title;
    mg->SetTitle(name.c_str());
    int pNumber = 2;

    TRandom3* rand = new TRandom3(0);

    for (int i = 0; i < nPoints; i++)
    {
        x.push_back(rand->Rndm()*1000);
        y.push_back(rand->Rndm()*1000);
    }

    TGraph *graph[pNumber+1];
    // initialize graph[0] = null pointer
    graph[0] = NULL; // Make it so that graph[1] corresponds to particle 1
    // create pNumber TGraphs
    for (int i = 1; i <= pNumber; i++)  
        graph[i] = new TGraph();
    // Add points of selected particles to graphs
    for (int i = 0; i < x.size(); i++)   
    {
        //graph[1]->AddPoint(dt*i, mT[P1][i]);
        //graph[2]->AddPoint(dt*i, mT[P2][i]);
        if (x[i] > 500 && y[i] > 500)
            graph[1]->AddPoint(x[i], y[i]);
        else 
            graph[2]->AddPoint(x[i], y[i]);
    }
    // Edit graphs
    for (int i = 1; i <= pNumber ; i++) // 
    {
        // graph[i]->SetLineColor(i+1);
        graph[i]->SetMarkerColor(i+1);
        graph[i]->SetMarkerStyle(20);
        // graph[i]->SetLineWidth(4);
        // graph[i]->SetFillStyle(0);
        mg->Add( graph[i] );
    }   

    mg->Draw("AP");

    c->Update();

    string dir = "bin/Plots/";
    name.append(".png");
    dir.append(name);
    c->SaveAs(dir.c_str());

    TRootCanvas *rc = (TRootCanvas *)c->GetCanvasImp();
    rc->Connect("CloseWindow()", "TApplication", gApplication, "Terminate()");
    app.Run();
}

void RootClass::FirstPlot(string Title) 
{
    
}