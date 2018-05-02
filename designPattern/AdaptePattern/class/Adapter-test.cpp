#include "Adapter.h"

using namespace std;

int main()
{
    //Adapter* adt = new Adapter();
    Target* adt = new Adapter();
    adt->Request();
    return 0;
}
