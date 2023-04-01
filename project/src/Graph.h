#ifndef __GRAPH__
#define __GRAPH__

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Graph {

public:
    Graph() = default;
    Graph(const string& newTitle);
    Graph(const string& newTitle, const string& newXAxisTitle, vector<double>& newX, 
            const string& newYAxisTitle, vector<double>& newY);
    Graph(const string& newTitle, vector<double>& newX, vector<double>& newY);
    Graph(bool newLegendBit, bool newSaveOutputBit, bool newOpenWindowBit);
    ~Graph() = default;

    Graph& operator=(const Graph& obj);
    Graph operator+(const Graph& obj);
    Graph operator-(const Graph& obj);
    Graph operator/(const Graph& obj);
    // Graph& operator*(const Graph& obj);
    // Graph& operator^(const Graph& obj);

    // Graph& operator==(const Graph& obj);


    friend std::ostream& operator<<(ostream& s, const Graph& p);

    void SetTitle(string newTitle);
    void SetXAxis(string newXAxis);
    void SetYAxis(string newYAxis);
    // void SetDrawOpt(string newDrawOpt);

    void SetLegendBit(bool newLegendBit);
    void SetSaveOutputBit(bool newSaveOutputBit);
    void SetOpenWindowBit(bool newOpenWIndowBit);
    void SetX(vector<double> newX);
    void SetY(vector<double> newY);

    // void SumX2Vec(vector<double> vec);
    void  DivYVec(vector<double> vec);


    void AddToX(double x);
    void AddToY(double y);
    void AddPoint(double x, double y);

    vector<double> GetX() const ;
    vector<double> GetY() const ;
    string GetTitle() const ;
    string GetXAxisTitle() const ;
    string GetYAxisTitle() const ;
    string GetDrawOpt() const ;
    bool GetLegendBit() const ;
    bool GetSaveOutputBit() const ;
    bool GetOpenWindowBit() const ;

private:
    string Title = "Test";
    string XAxisTitle = "X";
    vector<double> X;
    string YAxisTitle = "Y";
    vector<double> Y;

    string DrawOpt = "AP";

    bool LegendBit = false;
    bool SaveOutputBit = false;
    bool OpenWindowBit = false;
};
#endif