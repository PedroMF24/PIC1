#ifndef __ROOTCLASS__
#define __ROOTCLASS__

#include <iostream>
#include <stdlib.h>
#include <vector>
#include <string>

#include "TH1F.h"
#include "TGraph.h"
#include "TMultiGraph.h"
#include "TCanvas.h"
#include "TRandom3.h"
#include "TApplication.h"
#include "TRootCanvas.h"

using namespace std;

class RootClass {
    public:
    RootClass() = default;
    ~RootClass() = default;
    void ScatterPlot(string Titlen, int nPoints);
    void FirstPlot(string Title);

    private:

};
#endif