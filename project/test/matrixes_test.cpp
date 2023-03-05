#include <iostream>

using namespace std;

double arr[3] = {1,2,3};
double matrix[3][3] = {{1,2,3},{4,5,6},{7,8,9}};
double result[3];

int main() {

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            cout << matrix[i][j] << '\t';
        }
        cout << endl;
    }
    

    for (int i = 0; i < 3; i++) {
        result[i] = 0;
    for (int j = 0; j < 3; j++) {
        result[i] += matrix[i][j] * arr[j];
    }
    }
    for (auto &value : result)
    {
        cout << value << " ";
    }
    
}