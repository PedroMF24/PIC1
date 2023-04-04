#include <iostream>
#include <stdlib.h>
#include <vector>
#include <string>
#include <map>
#include <iomanip>

#include <sstream>
#include <fstream>

// Define the Parameters class
using namespace std;

class Parameters {
    public:
    Parameters();
    ~Parameters() = default;

    Parameters& operator=(const Parameters& obj);
    // copy constructor
    Parameters(const Parameters& newPars);
    // Print Parameters
    friend std::ostream& operator<<(ostream& s, const Parameters& p);

    void ScanSetup();
    void GenPars();
    void ImportPars(const string &filename);
    void SetPars();

    double GetMh() const;
    double Getv() const;
    double Getla1() const;
    double Getla2() const;
    double GetlaL() const;
    double GetMH() const;
    double GetMA() const;
    double GetMC() const;

    double Getm22Squared() const;
    double Getla3() const;
    double Getla4() const;
    double Getla5() const;

    vector<string> GetParNames();

    void SetScanBit(bool bit) { scan_setup = bit; }

    private:
    double Mh = 125.1;
    double v = 246;
    double la1 = 0; // (Mh/v)**2

    // Mass Basis
    double MH = 0; // MHX CDM
    double MA = 0; // MH3 It is A in IDM paper
    double MC = 0; // MHC Charged Higgs
    double la2 = 0; // lambda_2
    double laL = 0; // la3 + la4 + la5

    // Coupling Parameters Basis
    double m22Squared = 0;
    double la3 = 0;
    double la4 = 0;
    double la5 = 0;

    bool scan_setup = true;

    vector<string> ParNames = {"mh", "MH", "MA", "MC", "la2", "laL", "la1", "la3", "la4", "la5"};

    // MyRandom Rd;
};
// Define a function pointer type that takes a Parameters reference and returns an int
typedef int (*ConstraintFunc)(const Parameters&);

// Define your constraint functions
int constraint1(const Parameters& params) {
    // Implementation of constraint1 using params
    return 1;
}

int constraint2(const Parameters& params) {
    // Implementation of constraint2 using params
    return 0;
}

int constraint3(const Parameters& params) {
    // Implementation of constraint3 using params
    return 1;
}

int main() {
    // Create an instance of Parameters
    Parameters params;

    // Create a vector of function pointers
    std::vector<ConstraintFunc> constraints;

    // Add the constraint functions to the vector
    constraints.push_back(constraint1);
    constraints.push_back(constraint2);
    constraints.push_back(constraint3);

    // Call each constraint function with the Parameters instance
    int constraints_passed = 1;
    int i = 0;
    for (const auto& constraint : constraints) {
        constraints_passed &= constraint(params);
        i++;
    }

    // constraints_passed will contain the result of ANDing all the constraint function results
    return constraints_passed;
}