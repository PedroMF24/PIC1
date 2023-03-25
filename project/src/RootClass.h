#ifndef __ROOTCLASS__
#define __ROOTCLASS__

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
    void AddToGraphVector(string Name, TGraph *gr);
    void FreeGraphVector();
    void MultiGraphPlot();

    void ClearLegend();
    void ShowPlot(TCanvas *c, TApplication *app);
    void ResetCanvas(TCanvas *c);

    private:
    string Title = "Title";
    string XAxis = "X";
    string YAxis = "Y";

    string outDir = "bin/Plots/";
    string outFileExt = ".png";

    // TApplication *app;
    vector<pair<string, TGraph *>> grVec;

    string DrawOpt = "AP";

    bool LegendBit = false;
    bool SaveOutputBit = true;
    bool OpenWindowBit = true;

    // ColorPalette
    unordered_map<string, int> ColorPalette;

    void SaveOutput(TCanvas *c);

    // TCanvas *c = new TCanvas("c", "canvas", 1200, 800);
    // TLegend *Legend = nullptr;

    // TApplication app("app", nullptr, nullptr);
    // TApplication app {"app", nullptr, nullptr};
    // TRootCanvas *rc = (TRootCanvas *)c->GetCanvasImp();
};
#endif