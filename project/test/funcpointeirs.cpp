#include <iostream>
#include <string>
#include <vector>
#include <functional>


class Pars
{
    public:
    double la1 = 3;
    double la2 = 2;
    double la3 = 3;

    Pars()=default;
    ~Pars()=default;
};

int c1(Pars pars) {
    if (pars.la1 < pars.la2)
        return 1;
    else 
        return 0;
}

int c2(Pars pars) {
    if (pars.la2 <= pars.la3)
        return 1;
    else 
    return 0;
}

int c3(Pars pars) {
    if (pars.la1 == pars.la2 || pars.la2 == pars.la3)
        return 1;
    else
        return 0;
}

using namespace std;

using Condition = pair<string, function<int(const Pars&)>>;

bool mainFunction(const Pars& pars, const vector<Condition>& conditions) {
    bool result = true;
    for (const auto& condition : conditions) {
        if (!condition.second(pars)) {
            result = false;
            cout << "Condition " << condition.first << " failed" << endl;
            break;
        }
        // result &= condition.second(pars);
    }
    return result;
}


int main() {

    Pars pars;
    vector<Condition> conditions = {{"c1", c1}, {"c2", c2}, {"c3", c3}};
    bool result = mainFunction(pars, conditions);
    cout << result << endl;
}
