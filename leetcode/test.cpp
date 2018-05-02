#include "Function.h"
#include "Contest.h"
#include <cstring>
using namespace std;


int main()
{
    Contest g;
    Function f;
//46. Permutations
    vector<int> vec{2,3,1};
    auto vvec = f.permute(vec);
    for(auto V : vvec) {
        for(auto v : V)
            cout << v << ends;
        cout << endl;
    }
    return 0;
}
