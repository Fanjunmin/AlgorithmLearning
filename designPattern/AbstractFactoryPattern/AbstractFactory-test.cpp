#include <bits/stdc++.h>
#include "Product.h"
#include "AbstractFactory.h"
//���󹤳�ģʽ(Abstract factory pattern): Ϊһ��(����)��ػ����������Ķ����ṩ�����ӿڣ����Ǿ��廯�Ĺ����ӳٵ�����

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
