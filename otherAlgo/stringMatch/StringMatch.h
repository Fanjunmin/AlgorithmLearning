#ifndef STRINGMATCH_H_INCLUDED
#define STRINGMATCH_H_INCLUDED

#include <cstring>
//���ı���src�ĳ���Ϊsrc_len, ģʽ��patn�ĳ���Ϊpatn_len;

//brute force algorithm
int bruteMatch(const char* src, const char* patn) {
    //�ɹ����ص�һ��ƥ�����Ԫ��λ�ã����򷵻�-1
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
    //KMP�㷨�ؼ���next��
    int m = strlen(patn), j = 0;
    int t = next[0] = -1;
    while(j < m - 1) {
        if(0 > t || patn[j] == patn[t]) {   //t = -1��ʾ������ǰ�˵�ͨ���ַ�һ��ƥ��
            ++j; ++t;
            //next[j] = t;
            next[j] = (patn[j] != patn[t] ? t : next[t]);
        }
        else
            t = next[t];
    }
}

int KMPMatch(const char* src, const char* patn) {
    //�ɹ����ص�һ��ƥ�����Ԫ��λ�ã����򷵻�-1
    //O(m + n)
    int src_len = strlen(src), patn_len = strlen(patn);
    int next[patn_len];
    buildNext(patn, next);
    int i = 0, j = 0;
    while(i < src_len && j < patn_len) {
        if(0 > j || src[i] == patn[j]) {    //ƥ��
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
    //���ַ� BC: bad character
    for(int j = 0; j < 256; ++j) {
        bc[j] = -1; //��ʼ����ͳһָ��ͨ���
    }
    int patn_len = strlen(patn);
    for(int j = 0; j < patn_len; ++j) {
        bc[patn[j]] = j;   //�����㷨�����ǣ�ʹ�ü�¼���������ֵ��ַ���λ��
    }
}

void buildSS(const char* patn, int* const ss) {
    //�������ƥ���׺���ȱ�: ss��; O(patn_len)
    int patn_len = strlen(patn);
    ss[patn_len - 1] = patn_len;    //���һ���ַ�ƥ������׺����������
    //һ�´ӵ����ڶ�������������ɨ��
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
    //����gs��good suffix; O(patn_len)
    int patn_len = strlen(patn);
    buildSS(patn, ss);
    for(int i = 0; i < patn_len; ++i) {
        gs[i] = patn_len;   //��ʼ��
    }
    for(int i = 0, j = patn_len - 1; j >= 0; --j) {
        if(ss[j] == j + 1)  //patn[0, j] = patn[patn_len - j - 1, patn_len - 1]
            while(i < patn_len - 1 - j)
                gs[i++] = patn_len - 1 - j; //patn_len - 1 - j����gs[i]��ѡ��
    }
    for(int j = 0; j < patn_len - 1; ++j) {
        gs[patn_len - ss[j] - 1] = patn_len - 1 - j;  //patn_len - 1 - j����gs[patn_len - ss[j] - 1]��ѡ��
    }

}

int BMMatch(const char* src, const char* patn) {
    int src_len = strlen(src), patn_len = strlen(patn);
    int bc[256], ss[patn_len], gs[patn_len];
    buildBC(patn, bc);  //����bc��
    buildGS(patn, ss, gs);  //����gs��
    int i = 0;  //��ʼ����λ��
    while(i + patn_len <= src_len) {
        int j = patn_len - 1;   //��ģʽ����ĩβ���ַ���ʼ
        while(patn[j] == src[i + j])    //��������Ƚ�
            if(--j < 0) break;
        if(j < 0) break;
        else {
            int bc_j = j - bc[src[i + j]];  //bc���е�λ����
            i += gs[j] > bc_j ? gs[j] : bc_j; //ѡȡbc���gs���е�λ�����ϴ���
        }
    }
    return i + patn_len <= src_len ? i : -1;
}

//KR(Karp-Rabin)�㷨
#define M 97    //ɢ�б�ĳ��ȣ�����ȡ���������
#define R 256    //����:���ڶ����ƴ���ȡ2��ʮ���ƴ���ȡ10��ASCII�룬��ȡ128����256
#define DIGIT(S, i) ((S)[i] - 'a')
typedef __int64 HashCode;   //��64λ����ʵ��ɢ����
bool check1by1(const char* patn, const char* src, int i) {   //ָ����ͬʱ��ȷ���Ƿ�����ƥ��
    int m = strlen(patn);
    for(int j = 0; j < m; ++j, ++i) {
        if(patn[j] != src[i])
            return false;
    }
    return true;
}

HashCode prepare(int m) {
    //Ԥ��������R^(m - 1)%M
    HashCode Dm = 1;
    for(int i = 1; i < m; ++i) {
        Dm = (R * Dm) % M;
    }
    return Dm;
}

void updateHash(HashCode& hashT, const char* src, int patn_len, int k, HashCode Dm) {
    //����ָ�Ƹ����㷨
    hashT = (hashT - DIGIT(src, k - 1) * Dm) % M;   //����һ����λʱȥ��������ַ��Ĺ���
    hashT = (hashT * R + DIGIT(src, k + patn_len - 1)) % M; //����һ����λʱ�������ұ���ӵ��ַ��Ĺ���
    if(hashT < 0) hashT += M;   //ȷ��ɢ�������ںϷ�������
}

int KRMatch(const char* src, const char* patn) {
    int src_len = strlen(src), patn_len = strlen(patn);
    HashCode Dm = prepare(patn_len), hashP = 0, hashS = 0;
    for(int i = 0; i < patn_len; ++i) {
        hashP = (hashP * R + DIGIT(patn, i)) % M;   //����ģʽ����Ӧ��ɢ��ֵ
        hashS = (hashS * R + DIGIT(src, i)) % M;    //�����ı�����ǰpatn_len�ĳ�ʼɢ��ֵ
    }
    for(int k = 0; ; ) {
        if(hashP == hashS)  //ɢ��ֵ��ͬ�ҽ�һ������ȷ��ƥ��
            if(check1by1(patn, src, k))
                return k;
        if(++k > src_len - patn_len)    //�ı�����λ������ʱ��ƥ��ʧ��
            return -1;
        else    //�����ı��������ƣ������Ӵ�ɢ��ֵ
            updateHash(hashS, src, patn_len, k, Dm);
    }
}
#endif // STRINGMATCH_H_INCLUDED
