//Product.h
#ifndef _PRODUCT_H_
#define _PRODUCT_H_
#include <iostream>
class Product {
public:
    virtual ~Product() = 0;
protected:
    Product() {}  //���ι��캯��
};
class ConcreteProduct : public Product {
public:
    virtual ~ConcreteProduct() {}
    ConcreteProduct() {
        std::cout << "ConcreteProduct..." << std::endl;
    }
};
Product::~Product() {}
#endif //_PRODUCT_H_
