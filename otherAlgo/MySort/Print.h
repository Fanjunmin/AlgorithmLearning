#ifndef PRINT_H
#define PRINT_H
#include "Interval.h"
#include "ListNode.h"
using namespace std;
template <typename T, int N>
static void print(const T (&p)[N], std::ostream &os = cout){
    for(int i = 0; i < N; ++i)
        os << p[i] << " ";
}

template <typename T, int M, int N>
static void print(const T (&p)[M][N], std::ostream &os = cout){
    for(int i = 0; i < M; ++i){
        print(p[i], os);
        os << '\n';
    }
}

template <typename T>
static void print(vector<vector<T>> &vt, std::ostream &os = cout){
    for(auto x : vt){
        print(x, os);
        os << '\n';
    }
}

template <typename T>
static void print(vector<T> &vt, std::ostream &os = cout){
    for(auto x : vt)
        os << x << " ";
}

ListNode* vecToList(vector<int> &vec, ListNode *re){
    if(vec.empty()){
        re = NULL;
        return re;
    }
    else{
        ListNode *l = new ListNode(0);
        re = l;
        for(int i = 0; i < vec.size(); ++i){
            l->val = vec[i];
            if(i != vec.size() - 1){
                l->next = new ListNode(0);
                l = l->next;
            }
        }
        return re;
    }
}

ostream &print(ListNode *L, ostream &os){
    while(L != NULL){
        os << L->val << " ";
        L = L->next;
    }
    return os;
}
#endif // PRINT_H
