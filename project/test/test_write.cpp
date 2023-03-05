#include "src/TheoConstraints.h"
// #include "src/ExpConstraints.h"
// #include "src/RootClass.h"
#include "src/Parameters.h"
#include "src/IDM.h"

int main()
{
    Parameters Pars;
    // TheoCons TC(Pars);

    IDM pic(Pars);
    // pic.FirstPlot();
    // pic.SavePars("data/OKStep1.csv");
    pic.ReadCSV("data/test.csv");

    // pic.PrintParMap();
    // pic.GetPars().WriteFile("data/OKStep1.csv");
    return 0;
}