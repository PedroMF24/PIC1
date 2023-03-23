#include <iostream>
#include <stdlib.h>
#include <vector>
#include <string>

#include <map>
#include <algorithm>
#include <iterator>
#include <functional>
#include <unordered_map>

#include "TH1F.h"
#include "TGraph.h"
#include "TMultiGraph.h"
#include "TCanvas.h"
#include "TRandom3.h"
#include "TApplication.h"
#include "TRootCanvas.h"
#include "TLegend.h"

using namespace std;

class RootClass {
    public:
    RootClass() = default;
    ~RootClass() = default;
    void ScatterPlot(string Title, int nPoints);
    void FirstPlot(string Title);

    void LinePlot(vector<double> x, vector<double> y);
    void ScatterPlot(vector<double> x, vector<double> y);

    // Histograms
    // Fits
    // Legends
    
    // Relative to the size of the graph, values range from 0 to 1
    void MakeLegend(TLegend *leg, int x1, int x2, int y1, int y2, string type, string entry, string opt);

    // void GraphPlot(vector<double> x, vector<double> y, bool DrawBit, string ColorKey, string MarkerStyle, bool Add2Vec);
    void GraphPlot(vector<double> x, vector<double> y, bool DrawBit, int ColorKey, int MarkerStyle, bool Add2Vec);
    void AddToGraphVector(TGraph *gr);
    void FreeGraphVector();
    void MultiGraphPlot();

    void SaveOutput(TCanvas *c);

    void ClearLegend();
    void ResetCanvas(int &x, int &y, TCanvas *c);

    private:
    string Title = "Title";
    string XAxis = "X";
    string YAxis = "Y";

    string outDir = "bin/Plots/";
    string outFileExt = ".png";

    vector<TGraph *> grVec;

    string DrawOpt = "AP";

    bool LegendBit = true;
    bool SaveOutputBit = true;
    bool OpenWindowBit = true;

    // ColorPalette
    unordered_map<string, int> ColorPalette;

    // TCanvas *c = new TCanvas("c", "canvas", 1200, 800);
    // TLegend *Legend = nullptr;

    // TApplication app("app", nullptr, nullptr);
    // TApplication app {"app", nullptr, nullptr};
    // TRootCanvas *rc = (TRootCanvas *)c->GetCanvasImp();
};

void RootClass::SaveOutput(TCanvas *c) {
    string OutputPath = outDir;
    OutputPath.append(Title.c_str());
    OutputPath.append(outFileExt.c_str());
    c->Update();
    c->SaveAs(OutputPath.c_str());
    cout << "Saving " << Title << " in " << OutputPath << endl;
}

void RootClass::AddToGraphVector(TGraph *gr) {
    grVec.push_back(gr);
}

void RootClass::FreeGraphVector() {
    cout << "Freeing Graph Vector memory..." << endl;
    for (auto it = grVec.begin(); it != grVec.end(); ++it) {
        delete *it;
    }
    grVec.clear();
}


void RootClass::MultiGraphPlot() {

    TCanvas *c = new TCanvas("c", "canvas", 1200, 800);
    TMultiGraph *mg = new TMultiGraph();
    mg->SetTitle(Title.c_str());

    int i = 0;
    for (const auto& gr : grVec)
        mg->Add(gr);

    mg->GetXaxis()->SetTitle(XAxis.c_str());
    mg->GetYaxis()->SetTitle(YAxis.c_str());
    mg->Draw(DrawOpt.c_str());

    if (SaveOutputBit)
        SaveOutput(c);

    if (OpenWindowBit) {
        TApplication app("app", nullptr, nullptr);
        TRootCanvas *rc = (TRootCanvas *)c->GetCanvasImp();
        rc->Connect("CloseWindow()", "TApplication", gApplication, "Terminate()");
        app.Run();
    }
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

void RootClass::GraphPlot(vector<double> x, vector<double> y, bool DrawBit, int ColorKey, int MarkerStyle, bool Add2Vec) {
    cout << "Making " << Title << " graph..." << endl;
    TApplication app("app", nullptr, nullptr);
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
        grVec.push_back(gr);

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

    //if (OpenWindowBit) {
        // if (rc == nullptr) {
        //     std::cerr << "Error: TRootCanvas pointer is null\n";
        //     return;
        // }
        // TApplication app("app", nullptr, nullptr);
        TRootCanvas *rc = (TRootCanvas *)c->GetCanvasImp();
        rc->Connect("CloseWindow()", "TApplication", gApplication, "Terminate()");
        app.Run();
    //}
}

// void RootClass::MakeLegend(TLegend *leg, int x1, int x2, int y1, int y2, string type, string entry, string opt) {
//     // if (!leg)
//     //     leg = new TLegend(x1, x2, y1, y2); // 0.1,0.7,0.48,0.9
//     leg->SetHeader(Title.c_str(), "C"); // option "C" allows to center the header
//     // leg->AddEntry(h1,"Histogram filled with random numbers","f");
//     // leg->AddEntry("f1","Function abs(#frac{sin(x)}{x})","l");
//     // leg->AddEntry("gr","Graph with error bars","lep");
//     leg->AddEntry(type.c_str(), entry.c_str(), opt.c_str());
//     leg->Draw();
// }

// void RootClass::ClearLegend(TLegend *leg) {
//     if (leg) {
//         delete leg; // free memory if it was allocated
//         leg = nullptr; // set pointer to null
//     }
// }

void RootClass::ResetCanvas(int &x, int &y, TCanvas *c) {
    c->Clear();
    delete c;
    // c->Resize(800, 800);
    c = new TCanvas("c", "canvas", x, y);
}


int main() {

    // map<string, vector<double>> myMap = {
    //     {"vector1", {1.0, 2.0, 3.0}},
    //     {"vector2", {4.0, 5.0, 6.0}},
    //     {"vector3", {7.0, 8.0, 9.0}}
    // };

    vector<double> x = {1.0, 2.0, 3.0};
    vector<double> y = {4.0, 5.0, 10.0};

    vector<double> w = {7.0, 8.0, 9.0};
    vector<double> z = {1.0, 5.0, 4.0};

    RootClass root;
    root.GraphPlot(x, y, true, 2, 20, false);
    cout << "Seg" << endl;
    return 0;
}