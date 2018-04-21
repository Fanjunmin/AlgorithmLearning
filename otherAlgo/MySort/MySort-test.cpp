#include "MySort.h"
#include <iostream>
#include "Print.h"
using namespace std;

int main()
{
    MySort ms;
    int A[10] = {2,5,8,1,3,7,9,4,6,0};
    ms.BubbleSort(A, 10);
    print(A, cout); cout << endl;

    int B[10] = {2,5,8,1,3,7,9,4,6,0};
    ms.SelectionSort(B, 10);
    print(B, cout); cout << endl;

    int C[10] = {2,5,8,1,3,7,9,4,6,0};
    ms.InsertionSort(C, 10);
    print(C, cout); cout << endl;

    int D[10] = {2,5,8,1,3,7,9,4,6,0};
    ms.ShellSort(D, 10);
    print(D, cout); cout << endl;

    int E[10] = {2,5,8,1,3,7,9,4,6,0};
    ms.MergeSort(E, 0, 9);
    print(E, cout); cout << endl;

    int F[10] = {2,5,8,1,3,7,9,4,6,0};
    ms.QuickSort(F, 0, 9);
    print(F, cout); cout << endl;

    int G[10] = {2,5,8,1,3,7,9,4,6,0};
    ms.HeapSort(G, 10);
    print(G, cout); cout <<endl;
    return 0;
}
