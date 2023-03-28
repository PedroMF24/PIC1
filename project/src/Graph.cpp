#include "Graph.h"

Graph::Graph(string newTitle, string newXAxisTitle, vector<double> newX, string newYAxisTitle, vector<double> newY)
{
    Title = newTitle;
    XAxisTitle = newXAxisTitle;
    YAxisTitle = newYAxisTitle;
    X = newX;
    Y = newY;
}

Graph& Graph::operator=(const Graph &obj) { // Works!

    if (this != &obj) {
        Title = obj.Title;
        XAxisTitle = obj.XAxisTitle;
        YAxisTitle = obj.YAxisTitle;

        X = obj.X;
        Y = obj.Y;

        LegendBit = obj.LegendBit;
        SaveOutputBit = obj.SaveOutputBit;
        OpenWindowBit = obj.OpenWindowBit;
    }
    return *this;
}

ostream& operator<< (std::ostream& s, const Graph& p) {
    s << "Title: " << p.GetTitle() << endl;
    s << "X Title: " << p.GetXAxisTitle() << endl;
    s << "Y Title: " << p.GetYAxisTitle() << endl;
    vector<double> X = p.GetX();
    vector<double> Y = p.GetY();
    if (X.size() == Y.size()) {
        for (int i = 0; i < X.size(); i++)
            cout << "X: " << X[i] << "\t" << "Y: " << Y[i] << endl;
    } else {
        fprintf(stderr, "**X Y vectors of Graph do not have the same size");
        exit(0);
    }
    return s;
}

void Graph::AddToX(double x) {
    X.push_back(x);
}

void Graph::AddToY(double y) {
    Y.push_back(y);
}

vector<double> Graph::GetX() const {
    return X;
}

vector<double> Graph::GetY() const {
    return Y;
}

string Graph::GetTitle() const {
    return Title;
}

string Graph::GetXAxisTitle() const {
    return XAxisTitle;
}

string Graph::GetYAxisTitle() const {
    return YAxisTitle;
}

bool Graph::GetLegendBit() const {
    return LegendBit;
}

bool Graph::GetSaveOutputBit() const {
    return SaveOutputBit;
}

bool Graph::GetOpenWindowBit() const {
    return OpenWindowBit;
}

void Graph::SetTitle(string newTitle) {
    Title = newTitle;
}

void Graph::SetXAxis(string newXAxis) {
    XAxisTitle = newXAxis;
}

void Graph::SetYAxis(string newYAxis) {
    YAxisTitle = newYAxis;
}

// void Graph::SetDrawOpt(string newDrawOpt) {
//     DrawOpt = newDrawOpt;
// }

void Graph::SetLegendBit(bool newLegendBit) {
    LegendBit = newLegendBit;
}

void Graph::SetSaveOutputBit(bool newSaveOutputBit) {
    SaveOutputBit = newSaveOutputBit;
}

void Graph::SetOpenWindowBit(bool newOpenWindowBit) {
    OpenWindowBit = newOpenWindowBit;
}