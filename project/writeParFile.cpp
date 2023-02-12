#include <fstream> 
#include <string> 
#include <vector> 

void writeParFile(std::vector<int> index, std::vector<double> params1, std::vector<double> params2, std::vector<double> params3, std::vector<double> params4, std::vector<double> params5, std::vector<double> params6, std::string filename) 
{
    std::ofstream parFile; 
    parFile.open(filename); 
    for (int i = 0; i < index.size(); i++) 
    { 
        parFile << index[i] << "\t\t" << params1[i] << "\t" << params2[i] << "\t" << params3[i] << "\t" << params4[i] << "\t" << params5[i] << "\t" << params6[i] << "\n"; 
    }
    parFile.close(); 
}
