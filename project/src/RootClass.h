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

#include "FileStream.h"
#include "StopWatch.h"

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
    // RootClass() = default;
    RootClass(Graph newGraph);
    // RootClass(Graph newGraph, TApplication *app);
    // RootClass(bool newSaveOutputBit, bool newOpenWindowBit, bool newLegendBit);
    ~RootClass() = default;

    void SetNewGraph(Graph newGraph);

    void ScatterPlot(string Title, int nPoints);
    void FirstPlot(string Title);

    void CurvePlot(vector<double> &x, vector<double> &y);
    void ScatterPlot(int ColorKey, bool Add2Vec);

    void SetOutDir(string newOutDir);
    void SetOutFileExt(string newOutFileExt);
    // void SetTitle(string newTitle);
    // void SetXAxis(string newXAxis);
    // void SetYAxis(string newYAxis);

    // Histograms
    // Fits
    // Legends
    
    // Relative to the size of the graph, values range from 0 to 1


    // void GraphPlot(vector<double> x, vector<double> y, bool DrawBit, string ColorKey, string MarkerStyle, bool Add2Vec);
    // void GraphPlot(vector<double> x, vector<double> y, bool DrawBit, int ColorKey, int MarkerStyle, bool Add2Vec);
    void GraphPlot(bool DrawBit, int ColorKey, int MarkerStyle, bool Add2Vec);
    void AddToGraphVector(Graph g, TGraph *gr);
    void FreeGraphVector();
    void MultiGraphPlot(const string Title);


    private:

    Graph graph;

    string outDir = "bin/Plots/";
    string outFileExt = ".png";
    
    // TApplication *app;
    // vector<pair<string, TGraph *>> grVec;
    vector<pair<Graph, TGraph *>> grVec;

    string DrawOpt = "AP";

    const double LegendPos[4][4] = 
    {{0.1,0.7,0.3,0.9},     // Fit left up
    {0.7,0.7,0.9,0.9},      // Fit right up
    {0.9,0.7,0.99,0.9},     // Fit side up
    {0.9,0.7,0.99,0.9},     // Fit side up
    };


    /* TO USE WITH GRAPH STRUCT, NOT WITH CLASS */
    // string Title = "Title";
    // string XAxis = "X";
    // string YAxis = "Y";
    // bool LegendBit = false;
    // bool SaveOutputBit = true;
    // bool OpenWindowBit = true;

    // ColorPalette
    unordered_map<string, int> ColorPalette;

    // TApplication *fApp;

    void SaveOutput(TCanvas *c);
    void ClearLegend();
    void ShowPlot(TCanvas *c, TApplication *app);
    void DeleteCanvas(TCanvas *c);
    void DeleteApp(TApplication *app);
    // void MakeLegend(TLegend *leg, const double* LegendPos, TGraph* gr, string opt);
    void MakeLegend(TLegend *leg, const double* LegendPos, vector<pair<TGraph *, string>> legend_entries, string opt);

    // TCanvas *c = new TCanvas("c", "canvas", 1200, 800);
    // TLegend *Legend = nullptr;

    // TApplication app("app", nullptr, nullptr);
    // TApplication app {"app", nullptr, nullptr};
    // TRootCanvas *rc = (TRootCanvas *)c->GetCanvasImp();
};
#endif