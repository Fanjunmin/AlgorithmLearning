#include <bits/stdc++.h>
#include "Product.h"
#include "Factory.h"
//����ģʽ(factory pattern):����ʹ�����һ�����Ľӿڣ����Ǿ��廯�Ĺ����ӳٵ�����

int main()
{
    Factory* fac = new ConcreteFactory();
    Product* p = fac->CreateProduct();
    return 0;
}
