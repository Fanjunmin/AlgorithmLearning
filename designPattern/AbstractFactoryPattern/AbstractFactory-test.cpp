#include <bits/stdc++.h>
#include "Product.h"
#include "AbstractFactory.h"
//抽象工厂模式(Abstract factory pattern): 为一组(多类)相关或者相依赖的对象提供创建接口，但是具体化的工作延迟到子类

int main()
{
    AbstractFactory* cf1 = new ConcreteFactory1();
    cf1->CreateProductA();
    cf1->CreateProductB();

    AbstractFactory* cf2 = new ConcreteFactory2();
    cf2->CreateProductA();
    cf2->CreateProductB();
    return 0;
}
