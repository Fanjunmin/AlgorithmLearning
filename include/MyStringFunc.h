#ifndef MYSTRINGFUNC_H
#define MYSTRINGFUNC_H


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
        if(dest == NULL || src == NULL)
            return NULL;
        char *temp = dest;
        while((*dest++ = *src++) != '\0');
        return temp;
    }
    char* myStrncpy(char* dest, const char* src, std::size_t count){
        if(dest == NULL || src == NULL)
            return NULL;
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
        if(dest == NULL || src == NULL)
            return NULL;
        char* temp = dest;
        while(*dest)
            ++dest;
        while(*dest++ = *src++);
        return temp;
    }
    char *myStrncat( char *dest, const char *src, std::size_t count ){
        if(dest == NULL || src == NULL)
            return NULL;
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
};

#endif // MYSTRINGFUNC_H
