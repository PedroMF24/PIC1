#include <map>
#include <algorithm>
#include <iterator>
#include <functional>
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <string>
#include <list>

using namespace std;

int isEven(int x)
{
    if (x%2 == 0)
        return 1;
    else
        return 0;
}


void removePointFromMapVectors(map<string, vector<double>> &myMap, int pos) {
    for (auto& pair : myMap) {
        auto iter = pair.second.begin() + pos;
        if (iter != pair.second.end()) {
            pair.second.erase(iter);
        } else { 
            fprintf(stderr, "**removePoint error\n");
            exit(0);
        }
    }
}

void printMap(const map<string, vector<double>> &myMap) {
    for (const auto& pair : myMap) {
        cout << pair.first << ": ";
        for (const auto& value : pair.second) {
            cout << value << " ";
        }
        cout << endl;
    }
}

int main() {
    map<string, vector<double>> myMap;
    myMap["A"] = {9,4,5,6,7,71};
    myMap["B"] = {1,2,3,4,5,6};
    myMap["C"] = {1,2,3,4,5,6};
    for (auto iter = myMap["A"].begin(); iter != myMap["A"].end();) {
        int check = isEven(*iter);
        cout << "Iterator " << " Content " << *iter << endl;
        cout << check << endl;
        if (check) {
            cout << *iter << " is Even!\n";
            ++iter;
        } else {
            removePointFromMapVectors(myMap, iter - myMap["A"].begin());
        }
    }
    printMap(myMap);
}