#ifndef STRINGMATCH_H_INCLUDED
#define STRINGMATCH_H_INCLUDED

#include <cstring>
//设文本串src的长度为src_len, 模式串patn的长度为patn_len;

//brute force algorithm
int bruteMatch(const char* src, const char* patn) {
    //成功返回第一次匹配的首元素位置，否则返回-1
    //O(m*n)
    int src_len = strlen(src), patn_len = strlen(patn);
    int match_index = -1;
    for(int i = 0; i < src_len; i++) {
        int j = 0;
        for(; j < patn_len; ++j) {
            if(patn[j] != src[i + j])
                break;
        }
        if(j >= patn_len) {
            match_index = i;
            break;
        }
    }
    return match_index;
}

//KMP algorithm
void buildNext(const char* patn, int* const next) {
    //KMP算法关键的next表
    int m = strlen(patn), j = 0;
    int t = next[0] = -1;
    while(j < m - 1) {
        if(0 > t || patn[j] == patn[t]) {   //t = -1表示假想最前端的通配字符一定匹配
            ++j; ++t;
            //next[j] = t;
            next[j] = (patn[j] != patn[t] ? t : next[t]);
        }
        else
            t = next[t];
    }
}

int KMPMatch(const char* src, const char* patn) {
    //成功返回第一次匹配的首元素位置，否则返回-1
    //O(m + n)
    int src_len = strlen(src), patn_len = strlen(patn);
    int next[patn_len];
    buildNext(patn, next);
    int i = 0, j = 0;
    while(i < src_len && j < patn_len) {
        if(0 > j || src[i] == patn[j]) {    //匹配
            ++i;
            ++j;
        }
        else {
            j = next[j];
        }
    }
    return j >= patn_len ? i - patn_len : -1;
}

//BM algorithm
void buildBC(const char* patn, int* const bc) {
    //坏字符 BC: bad character
    for(int j = 0; j < 256; ++j) {
        bc[j] = -1; //初始化，统一指向通配符
    }
    int patn_len = strlen(patn);
    for(int j = 0; j < patn_len; ++j) {
        bc[patn[j]] = j;   //画家算法，覆盖，使得记录的是最后出现的字符的位置
    }
}

void buildSS(const char* patn, int* const ss) {
    //构造最大匹配后缀长度表: ss表; O(patn_len)
    int patn_len = strlen(patn);
    ss[patn_len - 1] = patn_len;    //最后一个字符匹配的最长后缀就是整个串
    //一下从倒数第二个串自右往左扫描
    for(int lo = patn_len - 1, hi = patn_len - 1, j = lo - 1; j >= 0; --j) {
        if((lo < j) && (ss[patn_len - hi + j - 1] <= j - lo))
            ss[j] = ss[patn_len - hi + j - 1];
        else {
            hi = j;
            lo = lo < hi ? lo : hi;
            while((0 <= lo) && (patn[lo] == patn[patn_len - hi + lo - 1]))
                --lo;
            ss[j] = hi - lo;
        }
    }
}

void buildGS(const char* patn, int* const ss, int* const gs) {
    //构造gs表，good suffix; O(patn_len)
    int patn_len = strlen(patn);
    buildSS(patn, ss);
    for(int i = 0; i < patn_len; ++i) {
        gs[i] = patn_len;   //初始化
    }
    for(int i = 0, j = patn_len - 1; j >= 0; --j) {
        if(ss[j] == j + 1)  //patn[0, j] = patn[patn_len - j - 1, patn_len - 1]
            while(i < patn_len - 1 - j)
                gs[i++] = patn_len - 1 - j; //patn_len - 1 - j都是gs[i]的选择
    }
    for(int j = 0; j < patn_len - 1; ++j) {
        gs[patn_len - ss[j] - 1] = patn_len - 1 - j;  //patn_len - 1 - j都是gs[patn_len - ss[j] - 1]的选择
    }

}

int BMMatch(const char* src, const char* patn) {
    int src_len = strlen(src), patn_len = strlen(patn);
    int bc[256], ss[patn_len], gs[patn_len];
    buildBC(patn, bc);  //构造bc表
    buildGS(patn, ss, gs);  //构造gs表
    int i = 0;  //初始对齐位置
    while(i + patn_len <= src_len) {
        int j = patn_len - 1;   //从模式串最末尾的字符开始
        while(patn[j] == src[i + j])    //自右往左比较
            if(--j < 0) break;
        if(j < 0) break;
        else {
            int bc_j = j - bc[src[i + j]];  //bc表中的位移量
            i += gs[j] > bc_j ? gs[j] : bc_j; //选取bc表和gs表中的位移量较大者
        }
    }
    return i + patn_len <= src_len ? i : -1;
}

//KR(Karp-Rabin)算法
#define M 97    //散列表的长度，可以取更大的素数
#define R 256    //基数:对于二进制串，取2；十进制串，取10，ASCII码，串取128或者256
#define DIGIT(S, i) ((S)[i] - 'a')
typedef __int64 HashCode;   //用64位整数实现散列码
bool check1by1(const char* patn, const char* src, int i) {   //指纹相同时，确认是否真正匹配
    int m = strlen(patn);
    for(int j = 0; j < m; ++j, ++i) {
        if(patn[j] != src[i])
            return false;
    }
    return true;
}

HashCode prepare(int m) {
    //预处理：计算R^(m - 1)%M
    HashCode Dm = 1;
    for(int i = 1; i < m; ++i) {
        Dm = (R * Dm) % M;
    }
    return Dm;
}

void updateHash(HashCode& hashT, const char* src, int patn_len, int k, HashCode Dm) {
    //快速指纹更新算法
    hashT = (hashT - DIGIT(src, k - 1) * Dm) % M;   //右移一个单位时去掉最左边字符的贡献
    hashT = (hashT * R + DIGIT(src, k + patn_len - 1)) % M; //右移一个单位时增加最右边添加的字符的贡献
    if(hashT < 0) hashT += M;   //确保散列码落在合法区间里
}

int KRMatch(const char* src, const char* patn) {
    int src_len = strlen(src), patn_len = strlen(patn);
    HashCode Dm = prepare(patn_len), hashP = 0, hashS = 0;
    for(int i = 0; i < patn_len; ++i) {
        hashP = (hashP * R + DIGIT(patn, i)) % M;   //计算模式串对应的散列值
        hashS = (hashS * R + DIGIT(src, i)) % M;    //计算文本串中前patn_len的初始散列值
    }
    for(int k = 0; ; ) {
        if(hashP == hashS)  //散列值相同且进一步检查后，确认匹配
            if(check1by1(patn, src, k))
                return k;
        if(++k > src_len - patn_len)    //文本串的位数不足时，匹配失败
            return -1;
        else    //否则文本串往后移，更新子串散列值
            updateHash(hashS, src, patn_len, k, Dm);
    }
}
#endif // STRINGMATCH_H_INCLUDED
