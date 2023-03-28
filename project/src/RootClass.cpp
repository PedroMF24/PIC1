#include "RootClass.h"

using namespace std;


RootClass::RootClass(Graph newGraph) {
    graph = newGraph;
}

void RootClass::SetNewGraph(Graph newGraph) {
    graph = newGraph;
}

void RootClass::SaveOutput(TCanvas *c) {
    string OutputPath = outDir;
    // OutputPath.append(Title.c_str());
    OutputPath.append(graph.GetTitle().c_str());
    OutputPath.append(outFileExt.c_str());
    c->Update();
    // if (!c) {
    //     std::cerr << "**Error: canvas is null" << std::endl;
    //     return;
    // }

    // if (OutputPath.empty()) {
    //     std::cerr << "**Error: output path is empty" << std::endl;
    //     return;
    // }  

    c->SaveAs(OutputPath.c_str());

    cout << "Saving " << graph.GetTitle() << " in " << OutputPath << endl;
}

void RootClass::AddToGraphVector(Graph g, TGraph *gr) {
    grVec.emplace_back(g, gr);
}

void RootClass::FreeGraphVector() {
    cout << "Freeing Graph Vector memory..." << endl;
    for (auto it = grVec.begin(); it != grVec.end(); ++it) {
        delete it->second;
    }
    grVec.clear();
}


void RootClass::MultiGraphPlot(const string Title) {
    cout << "Making " << Title << " Multigraph..." << endl;

    TApplication *app = nullptr;
    if (0) 
        app = new TApplication("app", nullptr, nullptr);

    TCanvas *c = new TCanvas("c", "canvas", 1200, 800);
    TMultiGraph *mg = new TMultiGraph();
    // mg->SetTitle(Title.c_str());

    int i = 0;

    // TLegend *legend = new TLegend(0.1,0.7,0.3,0.9);

    if (grVec.empty()) {
        fprintf(stderr, "**Vector of TGraphs is empty, can not do Multigraph");
        exit(0);
    }

    TLegend *leg = nullptr;
    vector<pair<TGraph *, string>> legend_entries;
    for (const auto& pair : grVec) {
        if (pair.first.GetLegendBit()) {
            legend_entries.emplace_back(pair.second, pair.first.GetTitle());
        }
        mg->Add(pair.second);
    }
    if (1) 
        MakeLegend(leg, LegendPos[3], legend_entries, "p");

    mg->GetXaxis()->SetTitle("X");
    mg->GetYaxis()->SetTitle("Y");
    mg->Draw(DrawOpt.c_str());

    if (1)
        SaveOutput(c);

    if (0) { // OpenWindowBit
        ShowPlot(c, app);
    }
    DeleteCanvas(c);
}


// void RootClass::GraphPlot(vector<double> x, vector<double> y, bool DrawBit, string ColorKey, string MarkerStyle, bool Add2Vec) {
//     cout << "Making " << Title << " graph..." << endl;
//     int nPoints = x.size();
//     TGraph *gr = new TGraph(nPoints, &x[0], &y[0]);
//     gr->SetMarkerColor(ColorKey.c_str());
//     gr->SetMarkerStyle(MarkerStyle.c_str());

//     if (Add2Vec)
//         grVec.push_back(gr);

//     if (DrawBit)
//         gr->Draw(DrawOpt.c_str());

//     if (OpenWindowBit) {
//         rc->Connect("CloseWindow()", "TApplication", gApplication, "Terminate()");
//         app.Run();
//     }
// }


/*
void RootClass::GraphPlot(vector<double> x, vector<double> y, bool DrawBit, int ColorKey, int MarkerStyle, bool Add2Vec, TApplication* app) {
    cout << "Making " << Title << " graph..." << endl;
    TCanvas *c = new TCanvas("c", "canvas", 1200, 800);
    int nPoints = x.size();
    TGraph *gr = new TGraph(nPoints, &x[0], &y[0]);
    // rest of the code...
    ShowPlot(c, app);
}

void RootClass::ShowPlot(TCanvas *c, TApplication* app) {
    TRootCanvas *rc = (TRootCanvas *)c->GetCanvasImp();
    rc->Connect("CloseWindow()", "TApplication", app, "Terminate()");
    app->Run();
}

int main() {
    TApplication *app = new TApplication("app", nullptr, nullptr);
    // rest of the code...
    RootClass myObject;
    myObject.GraphPlot(x, y, true, 1, 1, true, app);
    // rest of the code...
    delete app;
    return 0;
}

*/


/**
 * @brief Make general graph with graph struct
 * 
 */

/*
void RootClass::GraphPlot(vector<double> x, vector<double> y, bool DrawBit, int ColorKey, int MarkerStyle, bool Add2Vec) {
    cout << "Making " << Title << " graph..." << endl;
    // if (OpenWindowBit) {
    TApplication *app = nullptr;
    if (OpenWindowBit) 
        app = new TApplication("app", nullptr, nullptr);
    // //     if (!app)
    // //         app = new TApplication("app", nullptr, nullptr);
    // // }
    // }
    // cout << "ok?" << endl;
    TCanvas *c = new TCanvas("c", "canvas", 1200, 800);
    int nPoints = x.size();

    TGraph *gr = new TGraph(nPoints, &x[0], &y[0]);

    gr->SetTitle(Title.c_str());
    gr->GetXaxis()->CenterTitle();
    gr->GetXaxis()->SetTitle(XAxis.c_str());
    gr->GetYaxis()->SetTitle(YAxis.c_str());
    gr->SetMarkerColor(ColorKey);
    gr->SetMarkerStyle(MarkerStyle);

    
    if (Add2Vec)
        grVec.emplace_back(Title, gr);

    if (DrawBit)
        gr->Draw(DrawOpt.c_str());

    if(LegendBit) {
        TLegend *leg = new TLegend(0.1,0.7,0.3,0.9);
        leg->SetHeader("Legend", "C"); // ,"C"
        leg->AddEntry(gr,"olaaa","lp");
        leg->Draw();
        // MakeLegend(leg, 0.1,0.7,0.48,0.9, "gr", "ola", "l");
    }

    if (SaveOutputBit)
        SaveOutput(c);

    // if (OpenWindowBit) {
    //     TRootCanvas *rc = (TRootCanvas *)c->GetCanvasImp();
    //     rc->Connect("CloseWindow()", "TApplication", gApplication, "Terminate()");
    //     app.Run();
    // }
    // DeleteCanvas(1,2,c);

    // cout << "gets here" << endl;
    if (OpenWindowBit) 
        ShowPlot(c, app);
    cout << "explodes" << endl;

    // DeleteCanvas(c);
}*/

void RootClass::GraphPlot(bool DrawBit, int ColorKey, int MarkerStyle, bool Add2Vec) {
    cout << "Making " << graph.GetTitle() << " graph..." << endl;
    // if (OpenWindowBit) {
    TApplication *app = nullptr;
    if (graph.GetOpenWindowBit()) 
        app = new TApplication("app", nullptr, nullptr);
    // //     if (!app)
    // //         app = new TApplication("app", nullptr, nullptr);
    // // }
    // }
    // cout << "ok?" << endl;
    TCanvas *c = new TCanvas("c", "canvas", 1200, 800);
    int nPoints = graph.GetX().size();

    vector<double> x = graph.GetX();
    vector<double> y = graph.GetY();

    TGraph *gr = new TGraph(nPoints, &x[0], &y[0]);

    // gr->SetTitle(graph.GetTitle().c_str());
    gr->GetXaxis()->CenterTitle();
    gr->GetXaxis()->SetTitle(graph.GetXAxisTitle().c_str());
    gr->GetYaxis()->SetTitle(graph.GetYAxisTitle().c_str());
    gr->SetMarkerColor(ColorKey);
    gr->SetMarkerStyle(MarkerStyle);

    
    if (Add2Vec)
        grVec.emplace_back(graph, gr);

    if (DrawBit)
        gr->Draw(DrawOpt.c_str());

    if(graph.GetLegendBit()) {
        TLegend *leg = nullptr; // = new TLegend(LegendPos[3][0], LegendPos[3][1], LegendPos[3][2], LegendPos[3][3]);
        // leg->SetHeader("Legend", "C"); // ,"C"
        // leg->AddEntry(gr,"olaaa","lp");
        // leg->Draw();
        // vector<pair<TGraph *, string>> legend_entries;
        // legend_entries.emplace_back(gr, graph.GetTitle());
        // for (auto &value : LegendPos[3])
        // {
        //     cout << value << " " << endl;
        // }
        
        vector<pair<TGraph *, string>> legend_entries;
        legend_entries.emplace_back(gr, graph.GetTitle());
        MakeLegend(leg, LegendPos[3], legend_entries, "lp");
        // MakeLegend(leg, LegendPos[3], gr, "lp"); // 
    }

    // {
    //     leg = new TLegend(LegendPos[3][0], LegendPos[3][1], LegendPos[3][2], LegendPos[3][3]);
    // }

    if (graph.GetSaveOutputBit())
        SaveOutput(c);

    // if (OpenWindowBit) {
    //     TRootCanvas *rc = (TRootCanvas *)c->GetCanvasImp();
    //     rc->Connect("CloseWindow()", "TApplication", gApplication, "Terminate()");
    //     app.Run();
    // }
    // DeleteCanvas(1,2,c);

    // cout << "gets here" << endl;
    if (graph.GetOpenWindowBit()) 
        ShowPlot(c, app);
        
    DeleteCanvas(c);
    // DeleteApp(app);
}

void RootClass::ShowPlot(TCanvas *c, TApplication *app) {
    // TApplication app("app", nullptr, nullptr);
    
    TRootCanvas *rc = (TRootCanvas *)c->GetCanvasImp();
    // WRONG rc->Connect("CloseWindow()", "TCanvas", c, "Terminate()");
    rc->Connect("CloseWindow()", "TApplication", gApplication, "Terminate()");
    
    // cout << "in showplot" << endl;
    app->Run(kTRUE);
    // if (app) {
    //     app->Run();
    // }
}

void RootClass::DeleteApp(TApplication *app) {
    delete app;
    app = nullptr;
}

// TLegend *leg, const double* LegendPos, vector<pair<TGraph *, string>> legend_entries, string opt
// Use template here, probably... maye not all the uses of the MakeLegend will get TGraphs*
/*void RootClass::MakeLegend(TLegend *leg, const double* LegendPos, TGraph* gr, string opt) {
    if (!leg)
        leg = new TLegend(LegendPos[0], LegendPos[1], LegendPos[2], LegendPos[3]); // 0.1,0.7,0.48,0.9
    leg->SetHeader("Legend", "C"); // option "C" allows to center the header , graph.GetTitle().c_str()
    // leg->AddEntry(h1,"Histogram filled with random numbers","f");
    // leg->AddEntry("f1","Function abs(#frac{sin(x)}{x})","l");
    // leg->AddEntry("gr","Graph with error bars","lep");
    // for (auto &leg_entry : legend_entries) // leg_entry.first
        // leg->AddEntry(leg_entry.first, leg_entry.second.c_str(), opt.c_str());
    leg->AddEntry(gr, "ola", opt.c_str());
    leg->Draw();
}*/

void RootClass::MakeLegend(TLegend *leg, const double* LegendPos, vector<pair<TGraph *, string>> legend_entries, string opt) {
    if (!leg)
        leg = new TLegend(LegendPos[0], LegendPos[1], LegendPos[2], LegendPos[3]); // 0.1,0.7,0.48,0.9
    leg->SetHeader("Legend", "C"); // option "C" allows to center the header , graph.GetTitle().c_str()
    // leg->AddEntry(h1,"Histogram filled with random numbers","f");
    // leg->AddEntry("f1","Function abs(#frac{sin(x)}{x})","l");
    // leg->AddEntry("gr","Graph with error bars","lep");
    for (auto &leg_entry : legend_entries) // leg_entry.first
        leg->AddEntry(leg_entry.first, leg_entry.second.c_str(), opt.c_str());
    // leg->AddEntry(gr, "ola", opt.c_str());
    leg->Draw();
}

// void RootClass::ClearLegend(TLegend *leg) {
//     if (leg) {
//         delete leg; // free memory if it was allocated
//         leg = nullptr; // set pointer to null
//     }
// }

void RootClass::DeleteCanvas(TCanvas *c) {
    c->Clear();
    // c->cd();
    // gPad->SetLogy();
    // gPad->Update();
    // c->Print(OutputPath.c_str());
    c->Close(); // add this line to delete the canvas object
    delete c;   // add this line to delete the canvas object
    // c->Resize(800, 800);
    // c = new TCanvas("c", "canvas", x, y);
}


void RootClass::SetOutDir(string newOutDir) {
    outDir = newOutDir;
}

void RootClass::SetOutFileExt(string newOutFileExt) {
    outFileExt = newOutFileExt;
}

/**
 * @brief 
 * 
 */


void RootClass::ScatterPlot(int ColorKey, bool Add2Vec) {
cout << "Making " << graph.GetTitle() << " scatter plot..." << endl;
    // if (OpenWindowBit) {
    TApplication *app = nullptr;
    if (graph.GetOpenWindowBit()) 
        app = new TApplication("app", nullptr, nullptr);

    TCanvas *c = new TCanvas("c", "canvas", 1200, 800);
    int nPoints = graph.GetX().size();

    vector<double> x = graph.GetX();
    vector<double> y = graph.GetY();

    TGraph *gr = new TGraph(nPoints, &x[0], &y[0]);

    // gr->SetTitle(graph.GetTitle().c_str());
    gr->GetXaxis()->CenterTitle();
    gr->GetXaxis()->SetTitle(graph.GetXAxisTitle().c_str());
    gr->GetYaxis()->SetTitle(graph.GetYAxisTitle().c_str());
    gr->SetMarkerColor(ColorKey);
    gr->SetMarkerStyle(20);

    
    if (Add2Vec)
        grVec.emplace_back(graph, gr);

    gr->Draw("AP");

    if(graph.GetLegendBit()) {
        TLegend *leg = nullptr;
        vector<pair<TGraph *, string>> legend_entries;
        legend_entries.emplace_back(gr, graph.GetTitle());
        // MakeLegend(leg, LegendPos[3], legend_entries, "p");
    }

    if (graph.GetSaveOutputBit())
        SaveOutput(c);

    // cout << "gets here" << endl;
    if (graph.GetOpenWindowBit()) 
        ShowPlot(c, app);
        
    DeleteCanvas(c);
    DeleteApp(app);

}

// vector<double> x,y;

// void RootClass::ScatterPlot(string Title, int nPoints)
// {
//     TApplication app("app", nullptr, nullptr);
//     TCanvas *c = new TCanvas("c", "multigraph", 800, 800);
//     TMultiGraph *mg = new TMultiGraph();

//     string name = Title;
//     mg->SetTitle(name.c_str());
//     int pNumber = 2;

//     TRandom3* rand = new TRandom3(0);

//     for (int i = 0; i < nPoints; i++)
//     {
//         x.push_back(rand->Rndm()*1000);
//         y.push_back(rand->Rndm()*1000);
//     }

//     TGraph *graph[pNumber+1];
//     // initialize graph[0] = null pointer
//     graph[0] = NULL; // Make it so that graph[1] corresponds to particle 1
//     // create pNumber TGraphs
//     for (int i = 1; i <= pNumber; i++)  
//         graph[i] = new TGraph();
//     // Add points of selected particles to graphs
//     for (int i = 0; i < x.size(); i++)   
//     {
//         //graph[1]->AddPoint(dt*i, mT[P1][i]);
//         //graph[2]->AddPoint(dt*i, mT[P2][i]);
//         if (x[i] > 500 && y[i] > 500)
//             graph[1]->AddPoint(x[i], y[i]);
//         else 
//             graph[2]->AddPoint(x[i], y[i]);
//     }
//     // Edit graphs
//     for (int i = 1; i <= pNumber ; i++) // 
//     {
//         // graph[i]->SetLineColor(i+1);
//         graph[i]->SetMarkerColor(i+1);
//         graph[i]->SetMarkerStyle(20);
//         // graph[i]->SetLineWidth(4);
//         // graph[i]->SetFillStyle(0);
//         mg->Add( graph[i] );
//     }   

//     mg->Draw("AP");

//     c->Update();

//     string dir = "bin/Plots/";
//     name.append(".png");
//     dir.append(name);
//     c->SaveAs(dir.c_str());

//     TRootCanvas *rc = (TRootCanvas *)c->GetCanvasImp();
//     rc->Connect("CloseWindow()", "TApplication", gApplication, "Terminate()");
//     app.Run();
// }

// void RootClass::FirstPlot(string Title) 
// {
    
// }