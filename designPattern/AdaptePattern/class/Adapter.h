#ifndef ADAPTER_H_INCLUDED
#define ADAPTER_H_INCLUDED
#include <iostream>

class Target
{
public:
    Target();
    virtual ~Target();
    virtual void Request();
};
Target::Target() { }
Target::~Target() { }
void Target::Request() {
    std::cout << "Target::Request" << std::endl;
}

class Adaptee
{
public:
    Adaptee();
    ~Adaptee();
    void SpecificRequest();
};
Adaptee::Adaptee() { }
Adaptee::~Adaptee() { }
void Adaptee::SpecificRequest() {
    std::cout << "Adaptee::SpecificRequest" << std::endl;
}


class Adapter : public Target, private Adaptee
{
public:
    Adapter();
    ~Adapter();
    void Request();
};
Adapter::Adapter() { }
Adapter::~Adapter() { }
void Adapter::Request() {
    this->SpecificRequest();
}

#endif // ADAPTER_H_INCLUDED
