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
    vector<int> can{1,2,3,4,5};
    auto ivv = f.combinationSum2(can, 8);
    for(auto x : ivv){
        f.print(cout, x);
        cout << endl;
    }
}
