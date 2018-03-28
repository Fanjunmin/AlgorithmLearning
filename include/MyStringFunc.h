#ifndef MYSTRINGFUNC_H
#define MYSTRINGFUNC_H

#include <assert.h>
#include <cstddef>
class MyStringFunc
{
public:
    //计算字符串的长度:strlen
    std::size_t myStrlen(const char* str){
        std::size_t length = 0;
        while(*str++ != '\0')
            ++length;
        return length;
    }

    //实现字符串的拷贝:strcpy
    char* myStrcpy(char* dest, const char* src){
        //dest: 指向要写入的字符数组的指针
        //src: 指向复制来源的空终止字节字符串的指针
        //若dest数组不够大则行为未定义;若字符串重叠则行为未定义。
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

    //实现字符串的拼接:strcat
    char *myStrcat( char *dest, const char *src ){
        //dest 指向要后附到的空终止字节字符串的指针
        //src 指向作为复制来源的空终止字节字符串的指针
        //若字符串重叠则行为未定义。
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

    //实现字符串的比较:strcmp
    int myStrcmp(const char* lhs, const char* rhs){
        //lhs, rhs 指向待比较的空终止字节字符串的指针
        while(*lhs == *rhs){
            if(*lhs == '\0')
                return 0;
            ++lhs;
            ++rhs;
        }
        return *lhs - *rhs;
    }

    //将dest前面count个字符置为字符c.返回dest的值.
    void *myMemset(void *dest, int c, size_t count) {
        assert(dest != NULL);
        void *s = dest;
        while (count--) {
           *(char *)s = (char) c;
           s = (char *)s + 1;
        }
        return dest;
    }

    //从src复制count字节的字符到dest. 与memmove功能一样, 只是不能处理src和dest出现重叠.返回dest的值
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

    //从src复制count字节的字符到dest. 如果src和dest出现重叠, 函数会自动处理.返回dest的值.
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
            //内存出现重叠之后，从后往前copy;
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
