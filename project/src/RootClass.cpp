#include "include/RootClass.h"

using namespace std;

RootClass::RootClass(Graph* newGraph) {
    graph = newGraph;
}

// RootClass::RootClass(Graph newGraph, TApplication *app) {
//     graph = newGraph;
//     fApp = app;
// }

void RootClass::SetNewGraph(Graph* newGraph) {
    graph = newGraph;
}

void RootClass::SaveOutput(TCanvas *c, const string& Name) {
    string OutputPath = outDir;
    // OutputPath.append(Title.c_str());
    if (grVec.empty()) {
        OutputPath.append(graph->GetTitle().c_str());
        OutputPath.append(outFileExt.c_str());
        cout << "Saving " << graph->GetTitle() << " in " << OutputPath << endl;
    } else {    
        OutputPath.append(Name);
        OutputPath.append(outFileExt.c_str());
        cout << "Saving " << "Multigraph" << " in " << OutputPath << endl;
    }

    // c->Update();
    // auto timestamp = std::to_string(std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count());
    // c->SaveAs(("bin/Plots/Scatter_" + timestamp + ".png").c_str());

    // if (!c) {
    //     std::cerr << "**Error: canvas is null" << std::endl;
    //     return;
    // }

    // if (OutputPath.empty()) {
    //     std::cerr << "**Error: output path is empty" << std::endl;
    //     return;
    // }  

    c->SaveAs(OutputPath.c_str());

    
}

void RootClass::AddToGraphVector(Graph* g, TGraph *gr) {
    grVec.emplace_back(g, gr);
}

void RootClass::FreeGraphVector() {
    cout << "Freeing Graph Vector memory..." << endl;
    for (auto it = grVec.begin(); it != grVec.end(); ++it) {
        delete it->second;
    }
    grVec.clear();
}


void RootClass::MultiGraphPlot(const string& Title, const string& X, const string& Y) {
    cout << "Making " << Title << " Multigraph..." << endl;

    if (grVec.empty()) {
        fprintf(stderr, "**Vector of TGraphs is empty, can not do Multigraph");
        exit(0);
    }
    Graph *grExample = grVec[0].first;

    TApplication *app = nullptr;
    if (grExample->GetOpenWindowBit()) 
        app = new TApplication("app", nullptr, nullptr);

    TCanvas *c = new TCanvas("c", "canvas", 1200, 800);
    c->SetMargin(0.125, 0.12, 0.12, 0.1);
    // c->SetFillColor(0);
    // c->SetBorderMode(0);
    // c->SetBorderSize(2);
    // c->SetFrameBorderSize(3);
    // c->SetFrameBorderMode(2);
    // c->SetBottomMargin(-2);

    TMultiGraph *mg = new TMultiGraph();
    // mg->SetTitle(Title.c_str());

    int i = 0;

    // TLegend *legend = new TLegend(0.1,0.7,0.3,0.9);

    TLegend *leg = nullptr;
    vector<pair<TGraph *, string>> legend_entries;
    for (const auto& pair : grVec) {
        if (1) { // pair.first->GetLegendBit()
            pair.second->SetTitle(pair.first->GetTitle().c_str());
            legend_entries.emplace_back(pair.second, pair.first->GetTitle());
        }
        mg->Add(pair.second);
        // for (auto &val : pair.first->GetY())
        // {
        //     if (val < 0) cout << val << endl;
        // }
    }
    mg->GetXaxis()->SetTitleSize(0.045);
    mg->GetYaxis()->SetTitleSize(0.045);
    mg->GetXaxis()->SetLabelSize(0.045);
    mg->GetYaxis()->SetLabelSize(0.045);
    mg->GetXaxis()->SetTitleOffset(1.3);
    mg->GetXaxis()->SetTitle((Decode2Latex(X)).c_str());
    mg->GetXaxis()->CenterTitle();
    mg->GetYaxis()->SetTitle((Decode2Latex(Y)).c_str());



    // Debug
    // cout << "Min Y value: " << mg->GetYaxis()->GetXmin() << endl;
    // cout << "Max Y value: " << mg->GetYaxis()->GetXmax() << endl;
    // c->SetLogy();
    // cout << "Is log scale enabled? " << c->GetLogy() << endl;


// mg->GetXaxis()->SetTitle(X.c_str());
// mg->GetXaxis()->CenterTitle();
// mg->GetYaxis()->SetTitle(Y.c_str());

bool LogScale = false;
if (LogScale) {
    double ymin = 1e-7; // set a small positive number
    double ymax = mg->GetYaxis()->GetXmax(); // use the current max value of Y-axis
    mg->GetYaxis()->SetRangeUser(ymin, ymax); // set Y-axis range

    c->SetLogy();
    mg->Draw(grExample->GetDrawOpt().c_str());
    c->Update();

    cout << "Min Y value: " << mg->GetYaxis()->GetXmin() << endl;
    cout << "Max Y value: " << mg->GetYaxis()->GetXmax() << endl;
    cout << "Is log scale enabled? " << c->GetLogy() << endl;
}

    // c->SetLogy();
    mg->Draw(grExample->GetDrawOpt().c_str()); // DrawOpt.c_str()
    // c->Update();

    if (1) {
        MakeLegend(leg, LegendPos[5], legend_entries, "p");
    }

    if (grExample->GetSaveOutputBit())
        SaveOutput(c, Title);

    if (grExample->GetOpenWindowBit()) { // OpenWindowBit
        ShowPlot(c, app);
    }
    DeleteCanvas(c);
}


// void RootClass::GraphPlot(vector<double> x, vector<double> y, bool DrawBit, string ColorKey, string MarkerStyle, bool Add2Vec) {
//     cout << "Making " << Title << " graph->.." << endl;
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
    cout << "Making " << Title << " graph->.." << endl;
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
    cout << "Making " << Title << " graph->.." << endl;
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
    cout << "Making " << graph->GetTitle() << " graph->.." << endl;
    // if (OpenWindowBit) {
    TApplication *app = nullptr;
    if (graph->GetOpenWindowBit()) 
        app = new TApplication("app", nullptr, nullptr);
    // //     if (!app)
    // //         app = new TApplication("app", nullptr, nullptr);
    // // }
    // }
    // cout << "ok?" << endl;
    TCanvas *c = new TCanvas("c", "canvas", 1200, 800);
    int nPoints = graph->GetX().size();

    vector<double> x = graph->GetX();
    vector<double> y = graph->GetY();

    TGraph *gr = new TGraph(nPoints, &x[0], &y[0]);

    // gr->SetTitle(graph->GetTitle().c_str());
    gr->GetXaxis()->CenterTitle();
    gr->GetXaxis()->SetTitle(graph->GetXAxisTitle().c_str());
    gr->GetYaxis()->SetTitle(graph->GetYAxisTitle().c_str());
    gr->SetMarkerColor(ColorKey);
    gr->SetMarkerStyle(MarkerStyle);

    
    if (Add2Vec)
        grVec.emplace_back(graph, gr);

    if (DrawBit)
        gr->Draw(DrawOpt.c_str());

    if(graph->GetLegendBit()) {
        TLegend *leg = nullptr; // = new TLegend(LegendPos[3][0], LegendPos[3][1], LegendPos[3][2], LegendPos[3][3]);
        // leg->SetHeader("Legend", "C"); // ,"C"
        // leg->AddEntry(gr,"olaaa","lp");
        // leg->Draw();
        // vector<pair<TGraph *, string>> legend_entries;
        // legend_entries.emplace_back(gr, graph->GetTitle());
        // for (auto &value : LegendPos[3])
        // {
        //     cout << value << " " << endl;
        // }
        
        vector<pair<TGraph *, string>> legend_entries;
        legend_entries.emplace_back(gr, graph->GetTitle());
        MakeLegend(leg, LegendPos[3], legend_entries, "lp");
        // MakeLegend(leg, LegendPos[3], gr, "lp"); // 
    }

    // {
    //     leg = new TLegend(LegendPos[3][0], LegendPos[3][1], LegendPos[3][2], LegendPos[3][3]);
    // }

    if (graph->GetSaveOutputBit())
        SaveOutput(c, graph->GetTitle());

    // if (OpenWindowBit) {
    //     TRootCanvas *rc = (TRootCanvas *)c->GetCanvasImp();
    //     rc->Connect("CloseWindow()", "TApplication", gApplication, "Terminate()");
    //     app.Run();
    // }
    // DeleteCanvas(1,2,c);

    // cout << "gets here" << endl;
    if (graph->GetOpenWindowBit()) 
        ShowPlot(c, app);
        
    DeleteCanvas(c);
    //DeleteApp(app);
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
    leg->SetHeader("Legend", "C"); // option "C" allows to center the header , graph->GetTitle().c_str()
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
    // leg->SetHeader("Legend", "C"); // option "C" allows to center the header , graph->GetTitle().c_str()
    // leg->AddEntry(h1,"Histogram filled with random numbers","f");
    // leg->AddEntry("f1","Function abs(#frac{sin(x)}{x})","l");
    // leg->AddEntry("gr","Graph with error bars","lep");
    leg->SetTextSize(0.04*1.1);
    for (auto &leg_entry : legend_entries) // leg_entry.first
        leg->AddEntry(leg_entry.first,leg_entry.second.c_str(), opt.c_str());
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


void RootClass::ScatterPlot(const int  ColorKey, bool Add2Vec, const int Marker) {
cout << "Making " << graph->GetTitle() << " scatter plot..." << endl;

    // if (OpenWindowBit) {
    TApplication *app =  nullptr; // fApp
    if (graph->GetOpenWindowBit()) 
        app = new TApplication("app", nullptr, nullptr);

    TCanvas *c = new TCanvas("c", "canvas", 1200, 800);
    c->SetMargin(0.125, 0.12, 0.12, 0.1);

    int nPoints = graph->GetX().size();

    vector<double> x = graph->GetX();
    vector<double> y = graph->GetY();

    TGraph *gr = new TGraph(nPoints, &x[0], &y[0]);

    gr->SetTitle(""); // graph->GetTitle().c_str()
    gr->GetXaxis()->CenterTitle();
    // gr->GetXaxis()->SetTitle(graph->GetXAxisTitle().c_str());
    // gr->GetYaxis()->SetTitle(graph->GetYAxisTitle().c_str());
    gr->SetMarkerStyle(Marker); // 20
    // gr->SetMarkerSize(10);
    gr->SetMarkerColor(ColorKey);

    gr->SetMinimum(gr->GetYaxis()->GetXmin());
    gr->SetMaximum(gr->GetYaxis()->GetXmax());

    gr->GetXaxis()->SetTitleSize(0.045);
    gr->GetYaxis()->SetTitleSize(0.045);
    gr->GetXaxis()->SetLabelSize(0.045);
    gr->GetYaxis()->SetLabelSize(0.045);
    gr->GetXaxis()->SetTitleOffset(1.3);
    gr->GetXaxis()->SetTitle((Decode2Latex(graph->GetXAxisTitle())).c_str());
    gr->GetYaxis()->SetTitle((Decode2Latex(graph->GetYAxisTitle())).c_str());

    
    if (Add2Vec)
        grVec.emplace_back(graph, gr);

    gr->Draw("AP");

    if(graph->GetLegendBit()) {
        TLegend *leg = nullptr;
        vector<pair<TGraph *, string>> legend_entries;
        legend_entries.emplace_back(gr, graph->GetTitle());
        // MakeLegend(leg, LegendPos[3], legend_entries, "p");
    }

    if (graph->GetSaveOutputBit())
        SaveOutput(c, graph->GetTitle());

    // cout << "gets here" << endl;
    if (graph->GetOpenWindowBit()) 
        ShowPlot(c, app);
        
    DeleteCanvas(c);
    // DeleteApp(app);

}

string RootClass::Decode2Latex(string name) {
    switch (name[0]) {
            case 'M':
                if (name == "MH") return "#font[12]{M_{H} [GeV]}";
                else if (name == "MA") return "#font[12]{M_{A} [GeV]}";
                else if (name == "MC") return "#font[12]{M_{H^{+}} [GeV]}";
                else if (name == "MC - MH") return "#font[12]{M_{H^{+}} - M_{H} [GeV]}";
                else if (name == "MA - MH") return "#font[12]{M_{A} - M_{H} [GeV]}";
                else if (name == "MC - MA") return "#font[12]{M_{H^{+}} - M_{A} [GeV]}";
                break;
            case 'l':
                if (name == "laL") return "#lambda_{345}";
                else if (name == "la2") return "#lambda_{2}";
                break;
            default:
                return name;
                break;
        }
    return name;
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