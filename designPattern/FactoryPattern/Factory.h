//Factory.h
#ifndef _FACTORY_H_
#define _FACTORY_H_
#include "Product.h"
//class Product;
class Factory {
public:
    virtual ~Factory() = 0;
    virtual Product* CreateProduct() = 0;
protected:
    Factory() {}
};
class ConcreteFactory : public Factory {
public:
    virtual ~ConcreteFactory() {}
    ConcreteFactory() {
        std::cout << "ConcreteFactory..." << std::endl;
    }
    Product* CreateProduct() {
        return new ConcreteProduct();
    }
};
Factory::~Factory(){}
#endif // _FACTORY_H_
