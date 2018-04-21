#include "MathOperations.h"
#include <iostream>
using namespace std;

int main()
{
    MathOperations mo;
    int a = 10, b = 3, c = -3;
    cout << "addition(a, b) : " << mo.addition(a, b) << ends <<" a + b : " << (a + b) << endl;
    cout << "substrction(a, b) : " << mo.substrction(a, b) << ends << " a - b : " << (a - b) << endl;
    cout << "absValue(c) : " << mo.absValue(c) << ends << " |c| : " << (c < 0 ? -c : c) << endl;
    cout << "oppValue(c) : " << mo.oppValue(c) << ends << " -c : " << (-c) << endl;
    cout << "multiplication(a, b) : " << mo.multiplication(a, b) << ends << " a * b : " << (a * b) << endl;
    cout << "division(a, b) : " << mo.division(a, b) << ends << " a / b : " << (a / b) << endl;
    return 0;
}
