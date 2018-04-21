#include "MyStringFunc.h"
#include <iostream>
#include <memory.h>
using namespace std;

int main()
{
    MyStringFunc msf;
    char dest[25] = {'a', 'b'}, *src = "hijklmn";
    cout << "myStrlen(src) = " << msf.myStrlen(src) << endl; //myStrlen(src) = 7
    cout << "myStrcpy(dest, src) = " << msf.myStrcpy(dest, src) << endl;   //myStrcpy(dest, src) = hijklmn
    cout << "myStrcpy(dest, src, 2) = " << msf.myStrncpy(dest, src, 2) << endl; //myStrcpy(dest, src, 2) = hijklmn
    cout << "myStrcat(dest, src) = " << msf.myStrcat(dest, src) << endl;    //myStrcat(dest, src) = hijklmnhijklmn
    cout << "myStrncat(dest, src, 2) = " << msf.myStrncat(dest, src, 2) << endl;    //myStrncat(dest, src, 2) = hijklmnhijklmnhi
    cout << "myStrcmp(dest, src) = " << msf.myStrcmp(dest, src) << endl;    //myStrcmp(dest, src) = 104 = 'h'-'\0'

    char data[10] = {};
    msf.myMemset(data, 97, sizeof(data));
    //memset(data, 'a', sizeof(data));
    cout << "myMemset(data, 97, 3) : " << endl;
    for(int i = 0; i < 10; ++i)
        cout << data[i] << ' '; //a a a a a a a a a a
    cout << endl;
    char *s = "bbbb";
    msf.myMemcpy(data, s, 5);
    for(int i = 0; i < 10; ++i)
        cout << data[i] << ' '; //b b b b   a a a a a
    cout << endl;

    //出现内存重叠如果采用memcpy
    /*
    msf.myMemcpy(data + 2, data, 5);
    for(int i = 0; i < 10; ++i)
        cout << data[i] << ' '; //b b b b b b b a a a
    cout << endl;
    */

    msf.myMemmove(data + 2, data, 5);
    for(int i = 0; i < 10; ++i)
        cout << data[i] << ' '; //b b b b b b   a a a
    cout << endl;
    return 0;
}
