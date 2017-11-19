#include <iostream>
#include <vector>
#include <string>
#include <typeinfo>
#include "Function.h"
#include <math.h>
#include <set>
#include "Contest.h"
using namespace std;

int main()
{
    Function f;
    Contest g;
    vector<int> iv{1,2,3,4,5,6};
    //cout << f.getVectorIntoValue(iv);
    cout << f.superPow(7, iv);
    //cout << f.remind(iv, 12);
}
