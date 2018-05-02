#include <bits/stdc++.h>
#include "Singleton.h"

//单例模式保证一个类只有一个实例，并提供一个全局访问点

int main()
{
    Singleton& s = Singleton::getInstance();
    //Singleton s1 = s;
    return 0;
}
