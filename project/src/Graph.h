#ifndef __GRAPH__
#define __GRAPH__

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Graph {

public:
    Graph() = default;
    Graph(string newTitle, string newXAxisTitle, vector<double> newX, string newYAxisTitle, vector<double> newY);
    ~Graph() = default;

    Graph& operator=(const Graph& obj);

    void SetTitle(string newTitle);
    void SetXAxis(string newXAxis);
    void SetYAxis(string newYAxis);
    // void SetDrawOpt(string newDrawOpt);

    void SetLegendBit(bool newLegendBit);
    void SetSaveOutputBit(bool newSaveOutputBit);
    void SetOpenWindowBit(bool newOpenWIndowBit);

    void AddToX(double x);
    void AddToY(double y);

    vector<double> GetX() const ;
    vector<double> GetY() const ;
    string GetTitle() const ;
    string GetXAxisTitle() const ;
    string GetYAxisTitle() const ;
    bool GetLegendBit() const ;
    bool GetSaveOutputBit() const ;
    bool GetOpenWindowBit() const ;

private:
    string Title = "Test";
    string XAxisTitle = "X";
    vector<double> X;
    string YAxisTitle = "Y";
    vector<double> Y;

    // string DrawOpt = "AP";

    bool LegendBit = true;
    bool SaveOutputBit = true;
    bool OpenWindowBit = true;
};
#endif