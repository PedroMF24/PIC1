// #include "src/TheoConstraints.h"
// // #include "src/ExpConstraints.h"
// #include "src/RootClass.h"
// #include "src/Parameters.h"
#include "../src/include/IDM.h"
// #include "src/SM.h"
#include "../src/include/TestFuncs.h"
#include "../src/include/StopWatch.h"

// int main() {
//     StandardModel SM;
//     cout << SM.Get("pi");
// }






/*
 * auto execution_time = measure_time(my_function, arg1, arg2, ...);

    cout << "Execution time: " << execution_time << " ms" << endl;
*/


int main(int argc, char **argv)
{

    StopWatch clock;
    clock.StartTimer();

    // TEST_GenParsSTUValues();
    // TEST_Multigraph();
    // TEST_FirstPlot();

    IDM pic;
    // pic.StorePars(10000);
    // pic.SXT();
    /* ======================================================================================== */
    
    // pic.WriteMicrOMEGAs("data/input-mO.dat", 5000);
    // Graph* gr = ReadGraphData("data/PassedTeoCons/Good/PassedTeoCons.dat", "MH-MA", "MH", "MA");
    // gr = ReadGraphData("data/PassedTeoCons/Good/PassedTeoCons.dat", "", "MH", "MC");
    // ReadGraphData("data/PassedTeoCons/Good/PassedTeoCons.dat", "", "MH", "laL");
    // ReadGraphData("data/PassedTeoCons/Good/PassedTeoCons.dat", "", "MC", "laL");
    // gr = ReadGraphData("data/PassedTeoCons/Good/PassedTeoCons.dat", "MA-laL", "MA", "laL");
    // ReadGraphData("data/PassedTeoCons/Good/PassedTeoCons.dat", "", "MA", "MC");
    // RootClass root(gr);
    // gr->SetOpenWindowBit(false);
    // gr->SetSaveOutputBit(true);
    // root.ScatterPlot(2, false, 20);
    // 
    // root.ScatterPlot(2, false, 20);
    // 
    // root.ScatterPlot(2, false, 20);
    // ;
    // root.ScatterPlot(2, false, 20);
    // 
    // root.ScatterPlot(2, false, 20);
    // /* ======================================================================================== */

    // DO FINAL PLOTS
//     double MH, MA, MC, laL;
//     pic.FinalPlots("F_MC-MH", "MH", MH, "MC", MC, 500);
//     pic.FinalPlots("F_MC-MA", "MA", MA, "MC", MC, 500);
//     pic.FinalPlots("F_MA-MH", "MH", MH, "MA", MA, 500);
//     pic.FinalPlots("F_laL-MH", "MH", MH, "laL", laL, 500);
//     pic.FinalPlots("F_laL-MC", "MC", MC, "laL", laL, 500);
//     pic.FinalPlots("F_laL-MA", "MA", MA, "laL", laL, 500);

// //  DO TEO FINAL PLOTS
//     // double MH, MA, MC, laL;
//     pic.FinalTeoPlots("MC-MH", "MH", MH, "MC", MC, 500);
//     pic.FinalTeoPlots("MC-MA", "MA", MA, "MC", MC, 500);
//     pic.FinalTeoPlots("MA-MH", "MH", MH, "MA", MA, 500);
//     pic.FinalTeoPlots("laL-MH", "MH", MH, "laL", laL, 500);
//     pic.FinalTeoPlots("laL-MC", "MC", MC, "laL", laL, 500);
//     pic.FinalTeoPlots("laL-MA", "MA", MA, "laL", laL, 500);



    // IDM pic;
    // pic.Omegas("scripts/output-mO.dat");






    // root.ScatterPlot(2, false, 20);

    // delete gr;
    /*    */

    //IDM pic;
    //pic.WriteMicrOMEGAs("scripts/input-mO.dat", 1000);

    // Differença para o SM, S e T estao correlacionados
    // 
    // Graph* gr = ReadGraphData("data/PassedTeoCons/PassedTeoCons.dat", "Scatter", "MH", "MA");
    // gr->SetOpenWindowBit(true);
    // RootClass* root = new RootClass(gr);
    // root->ScatterPlot(2, true);
    // delete gr;
    // pic.FinalPlots("", "MA", "MC", 5000);

    /* Make overlap S vs T plane */
    // IDM pic;
    // pic.GenWriteCheckedPars("data/PassedTeoCons/PassedTeoCons.dat", 10000);
    //  "data/PassedTeoCons/PassedTeoCons.dat"
    // pic.OverlapSXT("data/STU/STU_PointsPars.dat", false);
    // pic.OverlapSXT("data/STU/STU_PointsPars.dat", true);



    clock.StopTimer();
    clock.PrintTime();

    return 0;
}
    // idm.TM_Test();

    // SXT ANTIGO
    // // Parameters Pars;
    // // IDM pic(Pars);
    // // pic.StorePars(10000);
    // // pic.SXT();

    // Parameters Pars;
    // IDM pic(Pars);
    // pic.StorePars(20);
    // pic.WriteDat("data/Verify_STU.dat");
    // pic.SXT();

    // STORE PARAMETERS TO TEST STU
    // Parameters Pars;
    // IDM pic(Pars);
    // pic.StorePars(5); // Dei store no ParMap
    // pic.WriteMapToFile("data/STU_test.dat"); // Escrevi no ficheiro
    // pic.ReadDAT("data/STU_test.dat"); // Li e dei store outra vez, ptt tenho de limpar antes dentro de Read
    // vector<double> test = pic.GetParMapVal("MH");

    // for (auto &val : test)
    // {
    //     cout << val << " ";
    // }

    // READS AND STORES SUCCESSFULLY
    // Parameters Pars;
    // IDM pic(Pars);
    // pic.ReadDAT("data/STU_test.dat");
    // vector<double> test = pic.GetParMapVal("MH");
    // for (auto &val : test)
    // {
    //     cout << val << " ";
    // }



    // ==================================================================
    

    // Parameters Pars;
    // // TheoCons TC(Pars);

    // IDM pic(Pars);
    // pic.StorePars(20);
    // // pic.WriteMapToFile("data/dat_test.dat");
    // pic.FirstPlot();



    //cout << "Ended first plot!\n";
    //pic.LimitsFromColliders();

    // TApplication app("app", nullptr, nullptr);
    // TCanvas *c = new TCanvas("c", "multigraph", 800, 800);
    // TMultiGraph *mg = new TMultiGraph();

    // string name = "Title";
    // mg->SetTitle(name.c_str());


    // int N = 0;
    // vector<double> la2;
    // vector<double> laL;

    // TGraph *grCheck = new TGraph();
    // grCheck->SetTitle("Allowed");
    // TGraph *grBFB = new TGraph();
    // grBFB->SetTitle("Positivity");

    // TGraph *grPert = new TGraph();
    // grPert->SetTitle("Perturbativity");

    // while (N<10000)
    // {
    //     TC.GenNewPars();
    //     int BFB = TC.BFB();
    //     int Pert = TC.Perturbativity();
    //     int TwoMins = TC.TwoMins();

    //     int check = BFB && Pert; // & TwoMins;

    //     if (BFB == 1 && Pert == 0)
    //     {
    //         grPert->AddPoint(TC.GetPars().Getla2(), TC.GetPars().GetlaL());
    //     } else if (BFB == 0 && Pert == 1) 
    //     {
    //         grBFB->AddPoint(TC.GetPars().Getla2(), TC.GetPars().GetlaL());
    //     } else if (check) {
    //         grCheck->AddPoint(TC.GetPars().Getla2(), TC.GetPars().GetlaL());
    //         cout << "Got here\n";
            
    //     } else {
    //         cout << "Weirdge\n";
    //     }
    //     N++;
    // }

    // grCheck->SetMarkerColor(2);
    // grCheck->SetMarkerStyle(20);

    // grBFB->SetMarkerColor(4);
    // grBFB->SetMarkerStyle(20);

    // grPert->SetMarkerColor(3);
    // grPert->SetMarkerStyle(20);

    // mg->Add(grCheck);
    // mg->Add(grBFB);
    // mg->Add(grPert);
    
    // mg->Draw("AP");

    // c->BuildLegend();
    // c->Update();

    // string dir = "bin/Plots/";
    // name.append(".png");
    // dir.append(name);
    // c->SaveAs(dir.c_str());

    // TRootCanvas *rc = (TRootCanvas *)c->GetCanvasImp();
    // rc->Connect("CloseWindow()", "TApplication", gApplication, "Terminate()");
    // app.Run();


    // Parameters P1, P2;
    // P1.ImportPars("data/dataTest.par");
    // cout << P1;
    // TheoCons TC(P1);
    // // cout << P1;
    // cout << TC.CheckAllTheoCons();



    // Test Parameters '=' operator
    // Parameters P1;
    // Parameters P2;
    // cout << "P1 " << P1.Getla2() << endl;
    // cout << "P2 " << P2.Getla2() << endl;
    // P2 = P1;
    // cout << "new P2 " << P2.Getla2() << endl;
    

    // while (1) /*vector.size() < N*/
    // {
    //     Parameters Pars;

    //     ExpCons EC(Pars);
    //     TheoCons TC(Pars);
    // }
    
    // for (int i = 0; i < 10; i++)
    // {
    //     cout << Rd.UniDist(0,1) << endl;
    // }
    

    // int i = 0;
    // while (i<10)
    // {
    //     cout << "Generating m22Squared, la3, la4, la5" << endl;
    //     // P.GenPars();
    //     // cout << P.Getla1() << endl;
    //     // cout << P.Getla2() << endl;
    //     // cout << P.GetlaL() << endl;
    //     // cout << P.GetMH() << endl;
    //     cout << P.Getm22Squared() << endl;
    //     cout << P.Getla3() << endl;
    //     cout << P.Getla4() << endl;
    //     cout << P.Getla5() << endl;
    //     cout << "---" << endl;
    //     i++;
    // }

    // printf("m22^2 = %lf\n", Exp.Getm22Squared());

    // RootClass R;
    // R.ScatterPlot("Ola", 10000);


/* Timer testing */

// using namespace chrono;

// template<typename F, typename... Args>
// auto measure_time(F&& func, Args&&... args)
// {
//     auto start = chrono::high_resolution_clock::now();
//     invoke(forward<F>(func), forward<Args>(args)...);
//     auto end = chrono::high_resolution_clock::now();
//     return chrono::duration_cast<chrono::milliseconds>(end - start).count();
// }



    // auto start = high_resolution_clock::now();

    // IDM idm;
    // idm.StoreCheckedPars(10000);
    // // idm.TM_Test();

    
    // // your main code goes here

    
    // auto stop = high_resolution_clock::now();
    // auto duration = duration_cast<microseconds>(stop - start);

    // cout << "Execution time: " << duration.count() << " microseconds" << endl;

/* Try to make a set_precision for decimal spaces */

// string setprecision_decimal(double value, int precision)
// {
//     stringstream ss;
//     ss << fixed << setprecision(precision) << value;
//     string result = ss.str();
//     if (precision > 0 && result.back() == '0') {
//         // Remove trailing zeros if any
//         size_t pos = result.find_last_not_of('0');
//         if (pos != string::npos && result[pos] == '.') {
//             pos--; // Keep the decimal point
//         }
//         result.erase(pos+1);
//     }
//     return result;
// }
