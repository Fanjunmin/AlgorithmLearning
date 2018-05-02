#include <iostream>
#include "auto_ptr.h"

using namespace std;
int main()
{
    string s = "string";
    auto_ptr<string> sa(&s);
    cout << *(sa.get());
    return 0;
}
