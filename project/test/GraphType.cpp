#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <iterator>

using namespace std;

/**
 * @brief Read and Write functions
 * 
 * @param values 
 * @param filename 
 */

struct Graph
{
    string Name;

    vector<double> x;
    vector<double> y;
};


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

// 
Graph ReadGraphData(const string& filename, const string& X, const string& Y);

// Write .dat file formatted for HiggsBounds
void WriteElementToFile(string key, ofstream &file, int i, map<string, vector<double>> &ParMap);
// void WriteMapToFile(const string &filename, map<string, vector<double>> &ParMap, Parameters &Pars);


/*
Graph ReadGraphData(const string& filename, const string& X, const string& Y) {
    ifstream file(filename);
    if (!file.is_open()) {
        throw runtime_error("Could not open file " + filename);
    }

    // Read header line and find indices of columns for X and Y
    string header;
    getline(file, header);
    istringstream iss(header);
    vector<string> headers{istream_iterator<string>(iss), istream_iterator<string>()};
    auto it1 = find(headers.begin(), headers.end(), X);
    auto it2 = find(headers.begin(), headers.end(), Y);
    if (it1 == headers.end() || it2 == headers.end()) {
        throw runtime_error("Could not find specified column labels in file " + filename);
    }
    int index1 = distance(headers.begin(), it1);
    int index2 = distance(headers.begin(), it2);

    // Read data and populate Graph vectors
    Graph g;
    double value1, value2;
    while (file >> value1) {
        for (int i = 0; i < index2; i++) {
            file.ignore(numeric_limits<streamsize>::max(), ' ');
        }
        file >> value2;
        g.x.push_back(value1);
        g.y.push_back(value2);
        for (int i = index2 + 1; i < index1; i++) {
            file.ignore(numeric_limits<streamsize>::max(), ' ');
            file.ignore(numeric_limits<streamsize>::max(), ' ');
        }
    }

    return g;
}*/

Graph ReadGraphData(const std::string& filename, const std::string& X, const std::string& Y) {
    Graph gr;
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: could not open file " << filename << std::endl;
        return gr;
    }

    std::string line;
    std::getline(file, line);
    std::stringstream ss(line);
    std::string header;
    std::vector<std::string> headers;
    while (ss >> header) {
        headers.push_back(header);
    }

    int x_col = -1, y_col = -1;
    for (int i = 0; i < headers.size(); i++) {
        if (headers[i] == X) {
            x_col = i;
        }
        if (headers[i] == Y) {
            y_col = i;
        }
    }
    if (x_col == -1) {
        std::cerr << "Error: could not find column " << X << " in file " << filename << std::endl;
        return gr;
    }
    if (y_col == -1) {
        std::cerr << "Error: could not find column " << Y << " in file " << filename << std::endl;
        return gr;
    }

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string val;
        int col = 0;
        double x, y;
        while (ss >> val) {
            if (col == x_col) {
                x = std::stod(val);
            }
            if (col == y_col) {
                y = std::stod(val);
            }
            col++;
        }
        gr.x.push_back(x);
        gr.y.push_back(y);
    }
    file.close();

    return gr;
}

int main() {
    Graph GR = ReadGraphData("data/PassedTeoCons/PassedTeoCons.dat", "MA", "laL");
    cout << "MA" << endl;
    for (auto &value : GR.x)
    {
        cout << value << endl;
    }
    cout << "laL" << endl;

    for (auto &value : GR.y)
    {
        cout << value << endl;
    }
}