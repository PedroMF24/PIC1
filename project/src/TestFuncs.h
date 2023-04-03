#ifndef __TESTFUNCS__
#define __TESTFUNCS__

#include "IDM.h"
#include "StopWatch.h"

/* Gen and write parameters directly using operator overloading */
void TEST_GenParsSTUValues();

/* TO WORK WITH MULTIGRAPH, EDIT OPTIONS OF THE FIRST GRAPH ADDED TO THE GRAPH VECTOR */
void TEST_Multigraph();

/* Test FirstPlot, which is laL x la2 to see exclusion due to Perturbativity and BFB */
void TEST_FirstPlot();

/* Test if STU values are being calculated correctly and stores points with and STU values in file s*/
void TEST_STU();

/* Test lambda parameters generation by checking if la3+la4+la5 = laL */
void TEST_ParameterGeneration();

#endif