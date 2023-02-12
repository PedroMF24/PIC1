#include <iostream>

class GrandMother {
    public:
    int GetGMAge(){return GMage;}
    const char *GMname = "Avo";
    private:
    int GMage = 70;
    int wealth = 1000;
};

class Mother : public GrandMother {
    public:
    int GetMAge(){return Mage;}
    const char *Mname = "Mae";
    private:
    int Mage = 45;
};

class Father : protected GrandMother {
    public:
    int GetFAge(){return Fage;}
    const char *Fname = "Avo";
    private:
    int Fage = 48;
};

int main() 
{
    Mother M;
    GrandMother GM;

    std::cout << M.GetGMAge();
}