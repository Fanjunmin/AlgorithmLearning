#ifndef STRINGMATCH_H_INCLUDED
#define STRINGMATCH_H_INCLUDED

#include <cstring>
//设待匹配串的长度为n, 匹配串的长度为m;
//brute force algorithm
int brute_match(const char* src, const char* patn) {
    //成功返回第一次匹配的首元素位置，否则返回-1
    //O(m*n)
    int src_len = strlen(src), patn_len = strlen(patn);
    int match_index = -1;
    for(int i = 0; i < src_len; i++) {
        int j = 0;
        for(; j < patn_len; ++j) {
            if(*(patn + j) != *(src + i + j))
                break;
        }
        if(j >= patn_len) {
            match_index = i;
            break;
        }
    }
    return match_index;
}

int KMP_match(const char* src, const char* patn) {

}

void build_next(const char* patn, int *next) {
    int m = strlen(patn), j = 0;
    int t = next[0] = -1;
    while(j < m - 1) {
        if(0 > t || patn[j] == patn[t]) {
            ++j;
            ++t;
            next[j] = (patn[j] != patn[t] ? t : next[t]);
        }
        else
            t = next[t];
    }
}

#endif // STRINGMATCH_H_INCLUDED
