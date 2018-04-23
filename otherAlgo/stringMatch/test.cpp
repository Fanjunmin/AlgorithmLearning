#include "StringMatch.h"
#include <bits/stdc++.h>

using namespace std;
void print(int i) {
    cout << i << " ";
}
int main()
{
    char *S = "ababacadasda";
    char *s1 = "fda";
    char *s2 = "das";
    cout << bruteMatch(S, s1) << ' ' << bruteMatch(S, s2) << endl;
    cout << KMPMatch(S, s1) << ' ' << KMPMatch(S, s2) << endl;
    cout << KRMatch(S, s1) << ' ' << KRMatch(S, s2) << endl;
    cout << BMMatch(S, s1) << ' ' << BMMatch(S, s2) << endl;
    return 0;
}
