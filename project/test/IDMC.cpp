#include "src/RootClass.h"
#include "src/IDM.h"

using namespace std;

int main() 
{

    Parameters Pars;
    IDM pic(Pars);

    pic.StorePars(10000);
    cout << "Starting Test\n";
    pic.IDMC_Test();
    cout << "After test\n";
    return 0;
}