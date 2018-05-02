#ifndef PRODUCT_H_INCLUDED
#define PRODUCT_H_INCLUDED
#include <iostream>

class Product
{
public:
    virtual ~Product() = 0;
protected:
    Product();
};
Product::Product() { }
Product::~Product() { }

class ConcreteProduct : public Product
{
public:
    ~ConcreteProduct();
    ConcreteProduct();
};
ConcreteProduct::~ConcreteProduct() { }
ConcreteProduct::ConcreteProduct() {
    std::cout << "ConcreteProduct..." << std::endl;
}
#endif // PRODUCT_H_INCLUDED
