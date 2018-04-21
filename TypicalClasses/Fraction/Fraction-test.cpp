#include <iostream>
#include "Fraction.h"

using namespace std;
int main()
{
    Fraction f(3, 5), g(2);
    cout << (4 + f) << endl;    //调用operator double()将f转换为double
    //Fraction d2 = f + 4;
    return 0;
}
