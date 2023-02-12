#ifndef __IDM__
#define __IDM__

#include "TheoConstraints.h"
#include "ExpConstraints.h"
#include "Parameters.h"
#include "RootClass.h"

class IDM : public TheoCons { //, public ExpCons
    public:
    IDM();
    IDM(Parameters& Pars);
    ~IDM() = default;

    void GenNewPars();
    void FirstPlot(int bit);

    void PrintParMap();
    void AddToMap();
    void SavePars(const string &filename);
    void ClearParMap();
    void ReadCSV(const string &filename);

    Parameters GetPars();

    private:
    Parameters Pars;
    map<string, vector<double>> ParMap;

};
#endif