#ifndef MYSTRINGFUNC_H
#define MYSTRINGFUNC_H


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

    //ʵ���ַ�����ƴ��:strcat
    char *myStrcat( char *dest, const char *src ){
        //dest ָ��Ҫ�󸽵��Ŀ���ֹ�ֽ��ַ�����ָ��
        //src ָ����Ϊ������Դ�Ŀ���ֹ�ֽ��ַ�����ָ��
        //���ַ����ص�����Ϊδ���塣
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
};

#endif // MYSTRINGFUNC_H
