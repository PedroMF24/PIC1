#include <iostream>
#include <vector>
#include <fstream>
#include <map>

#include "Parameters.h"

using namespace std;

/**
 * @brief Read and Write functions
 * 
 * @param values 
 * @param filename 
 */

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

// Write .dat file formatted for HiggsBounds
void WriteElementToFile(string key, ofstream &file, int i, map<string, vector<double>> &ParMap);
void WriteMapToFile(const string &filename, map<string, vector<double>> &ParMap, Parameters &Pars);



