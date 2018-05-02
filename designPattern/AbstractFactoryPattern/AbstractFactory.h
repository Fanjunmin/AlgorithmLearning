#ifndef ABSTRACTFACTORY_H_INCLUDED
#define ABSTRACTFACTORY_H_INCLUDED

class AbstractProductA;
class AbstractProductB;

class AbstractFactory
{
public:
    virtual ~AbstractFactory();
    virtual AbstractProductA* CreateProductA() = 0;
    virtual AbstractProductB* CreateProductB() = 0;

protected:
    AbstractFactory();
};
AbstractFactory::AbstractFactory() { }
AbstractFactory::~AbstractFactory() { }

class ConcreteFactory1 : public AbstractFactory
{
public:
    ConcreteFactory1();
    ~ConcreteFactory1();
    AbstractProductA* CreateProductA();
    AbstractProductB* CreateProductB();
};
ConcreteFactory1::ConcreteFactory1() { }
ConcreteFactory1::~ConcreteFactory1() { }
AbstractProductA* ConcreteFactory1::CreateProductA() {
    return new ProductA1();
}
AbstractProductB* ConcreteFactory1::CreateProductB() {
    return new ProductB1();
}


class ConcreteFactory2 : public AbstractFactory
{
public:
    ConcreteFactory2();
    ~ConcreteFactory2();
    AbstractProductA* CreateProductA();
    AbstractProductB* CreateProductB();
};
ConcreteFactory2::ConcreteFactory2() { }
ConcreteFactory2::~ConcreteFactory2() { }
AbstractProductA* ConcreteFactory2::CreateProductA() {
    return new ProductA2();
}
AbstractProductB* ConcreteFactory2::CreateProductB() {
    return new ProductB2();
}
#endif // ABSTRACTFACTORY_H_INCLUDED
