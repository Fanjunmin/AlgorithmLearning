#ifndef KMP_H_INCLUDED
#define KMP_H_INCLUDED

int KMP_search(const char* src, int slen, const char* patn, int plen,
                const int* nextval, int pos) {
    int i = pos, j = 0;
    while(i < slen && j < plen) {
        if(j == -1 || src[i] == patn[j]) {
            ++i; ++j;
        }
        else {
            j = nextval[j];
        }
    }
    if(j >= plen)
        return i - plen;
    else
        return -1;
}

void get_nextval(const char* ptrn, int plen, int* nextval) {
    int i = 0;
    nextval[i] = -1;
    int j = -1;
    while(i < plen - 1) {
        if(j == -1 || ptrn[i] == ptrn[j]) {
            ++i; ++j;
            if(ptrn[i] != ptrn[j])
                nextval[i] = j;
            else
                nextval[i] = nextval[j];
        }
        else {
            j = nextval[j];
        }
    }
}
#endif // KMP_H_INCLUDED
