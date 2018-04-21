#include "KMP.h"
#include "StringMatch.h"
#include <bits/stdc++.h>

using namespace std;
void print(int i) {
    cout << i << " ";
}
int main()
{
    char *S = "ababaca";
    char *s = "aca";
    cout << brute_match(S, s);
    return 0;
}
