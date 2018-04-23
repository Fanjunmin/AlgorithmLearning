#include "Function.h"
#include "Contest.h"
#include <cstring>
using namespace std;


int main()
{
    Contest g;
    Function f;
    //g.shortestToChar("asd", 'a');
    //vector<int> vec{1,2,4,4,7}, vec2{1,3,4,1,3};
    //cout << g.flipgame(vec, vec2);
    vector<int> vec = {45,42,2,18,23,1170,12,41,40,9,47,24,33,28,10,32,29,17,46,11,759,37,6,26,21,49,31,14,19,8,13,7,27,22,3,36,34,38,39,30,43,15,4,16,35,25,20,44,5,48};
    cout << g.numFactoredBinaryTrees(vec);
    return 0;
}
