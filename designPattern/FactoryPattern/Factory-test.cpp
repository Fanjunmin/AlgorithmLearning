#include <bits/stdc++.h>
#include "Product.h"
#include "Factory.h"
//工厂模式(factory pattern):定义和创建了一类对象的接口，但是具体化的工作延迟到子类

int main()
{
    Factory* fac = new ConcreteFactory();
    Product* p = fac->CreateProduct();
    return 0;
}
