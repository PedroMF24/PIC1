#include <iostream>
#include <stdlib.h>
#include <vector>
#include <string>

#include <map>
#include <algorithm>
#include <iterator>
#include <functional>

using namespace std;

class MyClass
{
public:
    // Constructor
    MyClass()
    {
        // Add functions to map
        func_ptr_map["foo"] = &MyClass::foo;
        func_ptr_map["bar"] = &MyClass::bar;
    }

    // Function declarations
    int foo(int x);
    int bar(int x);
    map<string, int (MyClass::*)(int)> GetFuncs() { return func_ptr_map; }
    // Getter function
    int GetFunc(string name, int x) { return (this->*func_ptr_map[name])(x); }

    
private:
    // Map of function pointers
    map<string, int (MyClass::*)(int)> func_ptr_map;
};

// map<string, TGraph* > func_graph_map;
    // if (!check) {
    //     cout << "Not met" << endl;
    //     func_ptr_map[func_ptr.first].AddPoint(l2,m22Squared)
    //     break;
    // }

vector<int> bits = {1,2,1,1,0,1};

// Finds the first number 1 in a vector
int findBit(vector<int> vec) {
    int counter = count(vec.begin(), vec.end(), 0);
    if (counter == 1) 
    { 
        auto it = find(vec.begin(), vec.end(), 0);
        if (it != vec.end())
            return distance(vec.begin(), it);
    }
    else if (counter > 1 || counter <= 0)
        return -1;
    return 0;
}

int main()
{
    // Create an object of MyClass
    // MyClass my_obj;
    // int check = 1;

    // // Call functions through map
    // for (const auto& func_ptr : my_obj.GetFuncs()) {
    //     int result = (my_obj.*func_ptr.second)(4);
    //     check *= result;
    //     /*
    //     if (!check) {
    //         cout << "Not met" << endl;
    //         break;
    //     }*/
    //     cout << "Result of " << func_ptr.first << ": " << result << endl;
	// //cout << func_ptr.first << " " << result << endl;
    // }
    // cout << "After for: " << my_obj.GetFunc("foo", 4) << endl;
    int a = findBit(bits);
    cout << a;
    return 0;
}

int GraphColors[] = {1,2,3,4,5,6,7,8,9,28,30,31,32,33,38,40,41,42,46};
string ColorNames[] = {"Black", "Red", "Green", "Blue", "Yellow", "Pink", "Cyan", "DarkGreen", "Purple", "Brown", "PaleGreen", "GrayGreen", "CamoGreen", "Blueish", "PalePurple", "Golden", "PaleOrange", "PaleRed"};

int MyClass::foo(int x)
{
    if (x%2 == 0)
        return 1;
    else
        return 0;
}

int MyClass::bar(int x)
{
    if (x%2 != 0)
        return 1;
    else
        return 0;
}
