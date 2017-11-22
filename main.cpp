#include <iostream>
#include <vector>
#include <string>
#include <typeinfo>
#include "Function.h"
#include <math.h>
#include <set>
#include "Contest.h"
#include "MathOperations.h"
using namespace std;


int main()
{
    Function f;
    Contest g;
    vector<vector<int>> obstacleGrid = {{0,0,0},{0,1,0},{0,0,0}};
    //f.print(obstacleGrid);
    cout << f.uniquePathsWithObstacles(obstacleGrid);

}
