#include "src/ExpConstraints.h"
#include "src/RootClass.h"


int main()
{
    ExpCons Exp;
    MyRandom Rd;

    for (int i = 0; i < 10; i++)
    {
        cout << Rd.UniDist(0,1) << endl;
    }
    

    int i = 0;
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



    return 0;
}