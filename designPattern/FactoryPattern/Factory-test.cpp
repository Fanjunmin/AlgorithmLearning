#include "Factory.h"
using namespace std;

int main() {
    Factory *fac = new ConcreteFactory();
    Product *p = fac->CreateProduct();
    return 0;
}
