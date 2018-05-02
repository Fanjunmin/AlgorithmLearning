#ifndef SINGLETON_H_INCLUDED
#define SINGLETON_H_INCLUDED

class Singleton
{
public:
    static Singleton& getInstance() {
        static Singleton s;
        return s;
    }
private:
    Singleton() {}
    Singleton(const Singleton&);
    void operator=(const Singleton&);
};


#endif // SINGLETON_H_INCLUDED
