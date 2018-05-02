#ifndef FACTORY_H_INCLUDED
#define FACTORY_H_INCLUDED
#include <iostream>

class Product;

class Factory
{
public:
    virtual ~Factory() = 0;
    virtual Product* CreateProduct() = 0;
protected:
    Factory();
};
Factory::Factory() { }
Factory::~Factory() { }

class ConcreteFactory : public Factory
{
public:
    ~ConcreteFactory();
    ConcreteFactory();
    Product* CreateProduct();
};
ConcreteFactory::ConcreteFactory() {
    std::cout << "ConcreteFactory..." << std::endl;
}
ConcreteFactory::~ConcreteFactory() { }
Product* ConcreteFactory::CreateProduct() {
    return new ConcreteProduct();
}
#endif // FACTORY_H_INCLUDED
