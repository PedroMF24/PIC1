#ifndef __IDM__
#define __IDM__


#include "Parameters.h"
#include "TheoConstraints.h"
#include "ExpConstraints.h"
#include "RootClass.h"
#include "FileStream.h"


// #include "TheoConstraints.h"
// #include "ExpConstraints.h"

#include <iomanip>

// IDMC test
// #include "DecayTable.h"
// #include "Constraints.h"
// #include "HBHS.h"
// #include "runTHDM.h"
// #include "SM.h"
// #include "THDM.h"
// #include "Util.h"

class IDM : public TheoCons, 
            public ExpCons 
{
    public:
    IDM();
    IDM(Parameters& Pars);
    ~IDM() = default;

    void GenNewPars();
    void StoreParsTest(int nPoints);
    void StoreCheckedPars(int nPoints);

    void FilterParMap(vector<int> keepIndex);
    void FirstPlot();
    
    void LimitsFromColliders();

    int CheckAllCons();

    void PrintParMap();
    void AddToMap();
    // void SavePars(const string &filename);
    void ClearParMap(); // Passa a receber um mapa
    // void ReadCSV(const string &filename);
    // void ReadDAT(const string &filename);

    // void WriteDat(const string &filename); // Write Map elements as they are to .dat file
    // void WriteElementToFile(string key, ofstream &file, int i); // Write parameters to run on experimental constraints 
    // void WriteMapToFile(const string &filename);

    void SXT(int nPoints);
    vector<pair<double,double>> GetParsSTU(int nPoints);
    void OverlapSXT(int nPoints);

    // void IDMC_Test();

    Parameters GetPars();
    vector<double> GetParMapVal(const string &name);


    void TM_Test();

    void ParsGraph();

    private:
    // Parameters generator class and Parameter values
    Parameters Pars;
    map<string, vector<double>> ParMap;

    // STU Matrices and Values
    // int nns = 4; // Number of neutral scalars
    // int ncs = 2; // Number of charged scalars
    double ImVdagV[4][4];
    complex<double> UdagU[2][2], VdagV[4][4], UdagV[2][4];
    double mneu[4], mch[2]; // Masses of neutral and charged scalars
    double S, T, U; // S T and U values
};
#endif