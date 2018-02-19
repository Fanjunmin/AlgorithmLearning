#include "Function.h"
#include "Contest.h"
#include "MathOperations.h"
#include "Print.h"
#include "PtOffer.h"
using namespace std;


int main()
{
    Contest g;
    vector<vector<int>> vec = {{1,3},{0,2},{1,3},{0,2}};
    cout << g.isBipartite(vec);
    return 0;
}
