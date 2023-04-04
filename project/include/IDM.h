#ifndef __IDM__
#define __IDM__


#include "Parameters.h"
#include "TheoConstraints.h"
#include "ExpConstraints.h"
#include "RootClass.h"
#include "FileStream.h"

using namespace std;

// Weird try

/*
void IDM::FinalPlots(const string& Title, const string& XAxis, const string& YAxis, int N_points) {
    // Graph* grInfo = ReadGraphData(filename, Title, X, Y);
    // cout << "Making " << grInfo->GetTitle() << " final graph...\n";

    // StoreParsTest(N_points);


    // RootClass root(grInfo);
    Graph* grBFB = new Graph("BFB");
    Graph* grSTU = new Graph("STU");
    Graph* grUNI = new Graph("UNI");
    Graph* grPER = new Graph("PER");
    Graph* grTMI = new Graph("TMI");
    Graph* grEXP = new Graph("EXP");

    Graph* grOK = new Graph("OK");

    double Mh = Pars.GetMh();
    double v = Pars.Getv();
    double la1 = Pars.Getla1(); // (Mh/v)**2
    MyRandom* rd = new MyRandom();
    // int max = ParMap["MH"].size();

    // for (int i = 0; i < max; i++) {
    ClearParMap();
    cout << "Generating Parameters of final plots...\n";
    Pars.SetScanBit(true);
    bool do_first = true;
    int i = 0;
    int a, b, c, d, e, f, g;
    a = b = c = d = e = f = g = 0;
    while (i < N_points) {
        // Pars.GenPars();
        double la2, la3, la4, la5, laL, m22Squared, MH, MA, MC;

        la2 = rd->UniDist(0,4.5); // (-4*M_PI, 4*M_PI); // Perturbativity
        laL = rd->UniDist(-1.5,2); // -1.5,2 // -2,4*M_PI -> For HBS

        MH = rd->UniDist(0,1000);
        MA = rd->UniDist(0,1000);
        MC = rd->UniDist(70,1000); // IDM revisited >80

        // S T U Oblique parameters
        double S, T, U;

        i++;
        double X, Y;


        // Eq 9 paper principal: strong bounds provided by the total width of the electroweak gauge bosons
        // DMC  mass MH has to be bigger than the other masses

            while (!LEPAnalysis(MH, MA, MC)) // MH >= MA || MH >= MC || (MC - MH < 0.1)
            {
                MH = rd->UniDist(0,1000);
                // cout << "**MH " << MH << endl;
                // cout << MH << endl;
                MA = rd->UniDist(0,1000);
                MC = rd->UniDist(70,1000); // IDM revisited >80
                X = MH;
                Y = MA;
                grEXP->AddPoint(X, Y);
            }

        m22Squared = v*v*laL - 2*MH*MH; // v*v*laL - 4*MA*MA -  2*MH*MH;
    
        la3 = laL + 2*(MC*MC - MH*MH)/(v*v);
        la4 = (MA*MA -2*MC*MC + MH*MH)/(v*v); // laL + 2*(MC*MC - MH*MH)/(v*v)
        la5 = (MH*MH - MA*MA)/(v*v);

        // double la2 = Pars.Getla2();
        // double la3 = Pars.Getla3();
        // double la4 = Pars.Getla4();
        // double la5 = Pars.Getla5();
        // double laL = Pars.GetlaL();
        // double m22Squared = Pars.Getm22Squared();
        // double MH = Pars.GetMH(); // MHX CDM
        // double MA = Pars.GetMA(); // MH3 It is A in IDM paper
        // double MC = Pars.GetMC(); // MHC Charged Higgs

        X = MH;
        Y = MA;

        // int LEP = LEPAnalysis(MH, MA, MC);
        // if (!LEP) {
        //     if (f < 500) {
        //         grEXP->AddPoint(X, Y);
        //         f++;
        //         continue;
        //     }
        // }

        // Other conditions implicit in number generation
        int TMI = TwoMins_Test(la1, la2, Mh, m22Squared);
        int BFB = BFB_Test(la1, la2, la3, laL);                             // OK
        if (!(BFB && TMI)) {
            //if (a<500) {
                grBFB->AddPoint(X, Y);
                //a++;
                continue;
            //}
        }

        int PER = Perturbativity_Test(la1, la2, la3, la4, la5, laL);       // OK
        int UNI = ScatteringMatrixUnitary_Test(la1, la2, la3, la4, la5);
        if (!(UNI && PER)) {
            //if (b<500) {
                grUNI->AddPoint(X, Y);
                //b++;
                continue;
            //}
            // grUNI->AddPoint(X, Y);
        } 

        int STU = STU_Test(Mh, MH, MA, MC, S, T, U); // Mh = m11            // OK
        if (!STU) {
            //if (c<500) {
                grSTU->AddPoint(X, Y);
                //c++;
                continue;
            //}
        } 



        int HWD = HiggsWidth(MH, laL);
        int EWB = EWBosons(MH, MA, MC);
        int HCL = HChargedLifetime(MH, MA, MC);
        int LUX = LUXDMData(MH, Mh, laL);
        int WZD = WZDecayWidths(MH, MA);
        int ORD = RelicDensity(MH);

        int EXT = Extras(MC, MA);

        int HBS = HiggsBoundsSignals(MC, Mh, laL);

        int EXP = ORD && LUX && HWD && EWB && HCL && WZD && HBS && EXT; // LUX LEP

        if (!EXP) {
            //if (f < 500) {
                grEXP->AddPoint(X, Y);
                //f++;
                continue;
            //}
        }

        int GOOD = ORD && BFB && UNI && STU && LUX && HWD && EWB && HCL && WZD && HBS && EXT; // ; LEP && 

        if (GOOD) {
            grOK->AddPoint(X, Y);
            // i++;
        }

        

        if ( i%100 != 0 ) {
            if (!do_first) {
                // cout << "Done " << i << " points" << endl;
                do_first = true;
            }
        }

        // if (BFB == 0) {
        //     if (a<500) {
        //         grBFB->AddPoint(X, Y);
        //         a++;
        //     }
        // } 
        // else if (STU == 0) {
        //     if (c<500) {
        //         grSTU->AddPoint(X, Y);
        //         c++;
        //     }
        // } 
        // else if (PER == 0) {
        //     if (d<500) {
        //         grPER->AddPoint(X, Y);
        //         d++;
        //     }
        // } 
        // else if (TMI == 0) {
        //     if (e<500) {
        //         grTMI->AddPoint(X, Y);
        //         e++;
        //     }
        // } 
        // else if (UNI == 0) {
        //     if (b<500) {
        //         grUNI->AddPoint(X, Y);
        //         b++;
        //     }
        //     // grUNI->AddPoint(X, Y);
        // } 
        // else if (EXP == 0) { // else
        //     if (f<500) {
        //         grEXP->AddPoint(X, Y);
        //         f++;
        //     }
        // } 
        // else if (GOOD) {
        //     grOK->AddPoint(X, Y);
        //     i++;
        // } else {
        //     fprintf(stderr, "**Warning: FinalPlots, should never get here\n");
        // }
        
        if ( i%100 == 0 ) {
            if (do_first) {
                cout << "Done " << i << " points" << endl;
                do_first = false;
            }
        }
    }


        // double la2 = ParMap["la2"][i];
        // double la3 = ParMap["la3"][i];
        // double la4 = ParMap["la4"][i];
        // double la5 = ParMap["la5"][i];
        // double laL = ParMap["laL"][i];
        // double m22Squared = ParMap["m22Squared"][i];
        // double MH = ParMap["MH"][i]; // MHX CDM
        // double MA = ParMap["MA"][i]; // MH3 It is A in IDM paper
        // double MC = ParMap["MC"][i]; // MHC Charged Higgs

    // }
    
    RootClass root(grUNI); // 
    // grEXP->SetLegendBit(true);
    // grEXP->SetSaveOutputBit(true);

    const int Marker = 20;

    root.ScatterPlot(6, true, Marker);
    grUNI->SetLegendBit(true);
    grUNI->SetSaveOutputBit(true);

    root.SetNewGraph(grBFB);
    root.ScatterPlot(4, true, Marker);

    root.SetNewGraph(grSTU);
    root.ScatterPlot(3, true, Marker);

    // root.SetNewGraph(grPER);
    // root.ScatterPlot(877, true, Marker);

    // root.SetNewGraph(grTMI);
    // root.ScatterPlot(806, true, Marker);

    root.SetNewGraph(grEXP);
    root.ScatterPlot(7, true, Marker);

    root.SetNewGraph(grOK);
    root.ScatterPlot(2, true, Marker);

    root.MultiGraphPlot(Title, XAxis, YAxis);

    delete grBFB;
    delete grUNI;
    delete grSTU;
    delete grTMI;
    delete grPER;
    delete grEXP;
    delete grOK;

    delete rd;
}

*/



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
    // IDM(TApplication *app);
    IDM(Parameters& Pars);
    ~IDM() = default;

    void GenNewPars();
    void StoreParsTest(int nPoints);
    void StoreCheckedPars(int nPoints);
    void GenWriteCheckedPars(const string& filename, int nPoints);
    void WriteMicrOMEGAs(const string& filename, int nPoints);

    void FilterParMap(vector<int> keepIndex);
    void FirstPlot(const string& filename);
    
    void LimitsFromColliders();

    int CheckTeoCons();
    int CheckallCons();

    void PrintParMap();
    void AddToMap();
    // void SavePars(const string &filename);
    void ClearParMap(); // Passa a receber um mapa
    // void ReadCSV(const string &filename);
    // void ReadDAT(const string &filename);

    void AssignPars(double& la2, double& la3, double& la4, 
                    double& la5, double& laL, double& m22Sqr, 
                    double& MH, double& MA, double& MC, double i);

    // void WriteDat(const string &filename); // Write Map elements as they are to .dat file
    // void WriteElementToFile(string key, ofstream &file, int i); // Write parameters to run on experimental constraints 
    // void WriteMapToFile(const string &filename);

    void SXT(int nPoints);
    vector<pair<double,double>> GetParsSTU(int nPoints);
    void OverlapSXT(const string& filename);

    void FinalPlots(const string& Title, const string& XAxis, const string& YAxis, int N_points);

    // void IDMC_Test();

    const Parameters& GetPars() const ;
    vector<double> GetParMapVal(const string &name);
    const map<string, vector<double>>& GetParMap() const { return ParMap; }


    void TM_Test();

    void ParsGraph(const string& path, const string& Title, const string& xName, const string& yName);
    void STU_BAD();

    private:
    // TApplication* fApp;
    // Parameters generator class and Parameter values
    Parameters Pars;
    map<string, vector<double>> ParMap;

    // TApplication *fApp;
    // RootClass *fRoot;

    // STU Matrices and Values
    // int nns = 4; // Number of neutral scalars
    // int ncs = 2; // Number of charged scalars
    double ImVdagV[4][4];
    complex<double> UdagU[2][2], VdagV[4][4], UdagV[2][4];
    double mneu[4], mch[2]; // Masses of neutral and charged scalars
    double S, T, U; // S T and U values
};
#endif