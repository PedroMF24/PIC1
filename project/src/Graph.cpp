#include "../include/Graph.h"

Graph::Graph(const string& newTitle, const string& newXAxisTitle, vector<double>& newX, 
             const string& newYAxisTitle, vector<double>& newY)
{
    Title = newTitle;
    XAxisTitle = newXAxisTitle;
    YAxisTitle = newYAxisTitle;
    X = newX;
    Y = newY;
}

Graph::Graph(bool newLegendBit, bool newSaveOutputBit, bool newOpenWindowBit) {
    LegendBit = newLegendBit;
    SaveOutputBit = newSaveOutputBit;
    OpenWindowBit = newOpenWindowBit;
}

Graph::Graph(const string& newTitle, vector<double>& newX, vector<double>& newY) {
    Title = newTitle;
    X = newX;
    Y = newY;
}

Graph::Graph(const string& newTitle) {
    Title = newTitle;
}


void  Graph::DivYVec(vector<double> vec) {
    if (Y.size() == vec.size()) {
        for (int i = 0; i < Y.size(); i++) {
            if (vec[i] != 0) {
                Y[i] /= vec[i]; 
            } else {
                fprintf(stderr, "**Div2YVec by zero");
                exit(0);
            }
        }
    } else {
        fprintf(stderr, "**DivYVec, vectors do not have same size");
        exit(0);
    }
}


Graph& Graph::operator=(const Graph &obj) { // Works!

    if (this != &obj) {
        Title = obj.Title;
        XAxisTitle = obj.XAxisTitle;
        YAxisTitle = obj.YAxisTitle;

        X = obj.X;
        Y = obj.Y;

        DrawOpt = obj.DrawOpt;
        LegendBit = obj.LegendBit;
        SaveOutputBit = obj.SaveOutputBit;
        OpenWindowBit = obj.OpenWindowBit;
    }
    return *this;
}

Graph Graph::operator+(const Graph& obj) {
    Graph result;
    result.SetTitle(this->GetTitle() + " + " + obj.GetTitle());
    result.SetXAxis(this->GetXAxisTitle() + " + " + obj.GetXAxisTitle());
    result.SetYAxis(this->GetYAxisTitle() + " + " + obj.GetYAxisTitle());
    if (this->GetX().size() == this->GetY().size()) {
        for (int i = 0; i < this->GetX().size(); i++) {
            result.AddToX(this->GetX()[i] + obj.GetX()[i]);
            result.AddToY(this->GetY()[i] + obj.GetY()[i]);
        }
    } else {
        fprintf(stderr, "**Sum of Graphs of different sizes");
        exit(0);
    }
    return result;
}

Graph Graph::operator-(const Graph& obj) {
    Graph result;
    result.SetTitle(this->GetTitle() + " - " + obj.GetTitle());
    result.SetXAxis(this->GetXAxisTitle() + " - " + obj.GetXAxisTitle());
    result.SetYAxis(this->GetYAxisTitle() + " - " + obj.GetYAxisTitle());

    if (this->GetX().size() == this->GetY().size()) {
        for (int i = 0; i < this->GetX().size(); i++) {
            result.AddToX(this->GetX()[i] - obj.GetX()[i]);
            result.AddToY(this->GetY()[i] - obj.GetY()[i]);
        }
    } else {
        fprintf(stderr, "**Subtraction of Graphs of different sizes");
        exit(0);
    }
    return result;
}

Graph Graph::operator/(const Graph& obj) {
    Graph result;
    result.SetTitle(this->GetTitle() + " / " + obj.GetTitle());
    result.SetXAxis(this->GetXAxisTitle() + " / " + obj.GetXAxisTitle());
    result.SetYAxis(this->GetYAxisTitle() + " / " + obj.GetYAxisTitle());

    if (this->GetX().size() == this->GetY().size()) {
        for (int i = 0; i < this->GetX().size(); i++) {
            if (obj.GetX()[i] != 0 && obj.GetY()[i] != 0) {
            result.AddToX(this->GetX()[i] / obj.GetX()[i]);
            result.AddToY(this->GetY()[i] / obj.GetY()[i]);
            } else {
                fprintf(stderr, "**Division of Graph by zero");
                exit(0);
            }
        }
    } else {
        fprintf(stderr, "**Division of Graphs of different sizes");
        exit(0);
    }
    return result;
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

void Graph::AddPoint(double x, double y) {
    X.push_back(x);
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

string Graph::GetDrawOpt() const {
    return DrawOpt;
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

void Graph::SetX(vector<double> newX) {
    // Graph& gr
    // X = gr.GetX();
    X = newX;
}

void Graph::SetY(vector<double> newY) {
    // Y = gr.GetY();
    Y = newY;
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