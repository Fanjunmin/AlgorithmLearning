#ifndef MYSTRINGFUNC_H
#define MYSTRINGFUNC_H

#include <assert.h>
#include <cstddef>
class MyStringFunc
{
public:
    //�����ַ����ĳ���:strlen
    std::size_t myStrlen(const char* str){
        std::size_t length = 0;
        while(*str++ != '\0')
            ++length;
        return length;
    }

    //ʵ���ַ����Ŀ���:strcpy
    char* myStrcpy(char* dest, const char* src){
        //dest: ָ��Ҫд����ַ������ָ��
        //src: ָ������Դ�Ŀ���ֹ�ֽ��ַ�����ָ��
        //��dest���鲻��������Ϊδ����;���ַ����ص�����Ϊδ���塣
        assert(dest != NULL && src != NULL);
        char *temp = dest;
        while((*dest++ = *src++) != '\0');
        return temp;
    }
    char* myStrncpy(char* dest, const char* src, std::size_t count){
        assert(dest != NULL && src != NULL);
        char *temp = dest;
        int offset = 0;
        if(myStrlen(src) < count){
            offset = count - myStrlen(src);
            count = myStrlen(src);
        }
        while(count--)
            *dest++ = *src++;
        while(offset--)
            *dest++ = '\0';
        return temp;
    }

    //ʵ���ַ�����ƴ��:strcat
    char *myStrcat( char *dest, const char *src ){
        //dest ָ��Ҫ�󸽵��Ŀ���ֹ�ֽ��ַ�����ָ��
        //src ָ����Ϊ������Դ�Ŀ���ֹ�ֽ��ַ�����ָ��
        //���ַ����ص�����Ϊδ���塣
        assert(dest != NULL && src != NULL);
        char* temp = dest;
        while(*dest)
            ++dest;
        while(*dest++ = *src++);
        return temp;
    }
    char *myStrncat( char *dest, const char *src, std::size_t count ){
        assert(dest != NULL && src != NULL);
        char* temp = dest;
        while(*dest)
            ++dest;
        while(count-- && (*dest++ = *src++));
        *dest = '\0';
        return temp;
    }

    //ʵ���ַ����ıȽ�:strcmp
    int myStrcmp(const char* lhs, const char* rhs){
        //lhs, rhs ָ����ȽϵĿ���ֹ�ֽ��ַ�����ָ��
        while(*lhs == *rhs){
            if(*lhs == '\0')
                return 0;
            ++lhs;
            ++rhs;
        }
        return *lhs - *rhs;
    }

    //��destǰ��count���ַ���Ϊ�ַ�c.����dest��ֵ.
    void *myMemset(void *dest, int c, size_t count) {
        assert(dest != NULL);
        void *s = dest;
        while (count--) {
           *(char *)s = (char) c;
           s = (char *)s + 1;
        }
        return dest;
    }

    //��src����count�ֽڵ��ַ���dest. ��memmove����һ��, ֻ�ǲ��ܴ���src��dest�����ص�.����dest��ֵ
    void *myMemcpy(void *dest, const void *src, size_t count) {
        assert(dest != NULL && src != NULL);
        void *s = dest;
        while (count--) {
            *(char *)s = *(char *)src;
            s = (char *)s + 1;
            src = (const char *)src + 1;
        }
        return dest;
    }

    //��src����count�ֽڵ��ַ���dest. ���src��dest�����ص�, �������Զ�����.����dest��ֵ.
    void *myMemmove(void *dest, const void *src, size_t count) {
        assert(dest != NULL && src != NULL);
        void *s = dest;
        if (s <= src || (char *)s >= (char *)src + count) {
            while (count--) {
                *(char *)s = *(char *)src;
                s = (char *)s + 1;
                src = (char *)src + 1;
            }
        }
        else {
            //�ڴ�����ص�֮�󣬴Ӻ���ǰcopy;
            s = (char *)s + count - 1;
            src = (char *)src + count - 1;
            while (count--) {
                *(char *)s = *(char *)src;
                s = (char *)s - 1;
                src = (char *)src - 1;
            }
        }
        return dest;
    }

};

#endif // MYSTRINGFUNC_H
