#ifndef PRODUCT_H_INCLUDED
#define PRODUCT_H_INCLUDED
#include <iostream>

class AbstractProductA
{
public:
    virtual ~AbstractProductA();

protected:
    AbstractProductA();
};
AbstractProductA::AbstractProductA() { }
AbstractProductA::~AbstractProductA() { }

class AbstractProductB
{
public:
    virtual ~AbstractProductB();

protected:
    AbstractProductB();
};
AbstractProductB::AbstractProductB() { }
AbstractProductB::~AbstractProductB() { }

class ProductA1 : public AbstractProductA
{
public:
    ProductA1();
    ~ProductA1();
};
ProductA1::ProductA1() {
    std::cout << "ProductA1..." << std::endl;
}
ProductA1::~ProductA1() { }

class ProductA2 : public AbstractProductA
{
public:
    ProductA2();
    ~ProductA2();
};
ProductA2::ProductA2() {
    std::cout << "ProductA2..." << std::endl;
}
ProductA2::~ProductA2() { }

class ProductB1 : public AbstractProductB
{
public:
    ProductB1();
    ~ProductB1();
};
ProductB1::ProductB1() {
    std::cout << "ProductB1..," << std::endl;
}
ProductB1::~ProductB1() { }

class ProductB2 : public AbstractProductB
{
public:
    ProductB2();
    ~ProductB2();
};
ProductB2::ProductB2() {
    std::cout << "ProductB2..." << std::endl;
}
ProductB2::~ProductB2() { }
#endif // PRODUCT_H_INCLUDED
