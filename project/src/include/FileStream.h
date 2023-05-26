#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <iterator>
#include <iomanip>

#include "Parameters.h"
#include "Graph.h"
#include "TheoConstraints.h"

using namespace std;

/**
 * @brief Read and Write functions
 * 
 * @param values 
 * @param filename 
 */

// struct Graph
// {
//     string Title;

//     vector<double> x;
//     vector<double> y;

// };


// Save Parameters to a .csv file
void SavePars(const string &filename, map<string, vector<double>> &ParMap);

// Read and Write .dat files into or out of ParMap
void ReadDAT(const string &filename, map<string, vector<double>> &ParMap);
void WriteDat(const string &filename, map<string, vector<double>> &ParMap);

void ReadCSV(const string &filename, map<string, vector<double>> &ParMap);

// Write ST parameters in a .dat file
void WriteSTUPars(vector<pair<double,double>> &values, const string &filename);

// Read ST professor elipse points
vector<pair<double,double>> readProfSTU();

// Graph
Graph* ReadGraphData(const string& filename, const string &Title, const string& X, const string& Y);

// Write .dat file formatted for HiggsBounds
void WriteElementToFile(string key, ofstream &file, int i, map<string, vector<double>> &ParMap);
void WriteMapToFile(const string &filename, map<string, vector<double>> &ParMap, Parameters &Pars);

bool FileExists(const string& filename);
void WriteSTUToFile(ofstream &file, int i, map<string, vector<double>> &ParMap, Parameters &Pars);

void ReadMicrOMEGAsOutput(const string &filename);