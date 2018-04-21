#ifndef PTOFFER_H
#define PTOFFER_H
#include <bits/stdc++.h>
#include "TreeNode.h"
#include "ListNode.h"
using namespace std;
class PtOffer
{
public:
//Tree
    //���������
    int TreeDepth(TreeNode* pRoot)
    {
        return pRoot == NULL ? 0 : 1 + max(TreeDepth(pRoot->left), TreeDepth(pRoot->right));
    }

    //�������ľ���
    void Mirror(TreeNode *pRoot) {
        if(pRoot && (pRoot->left || pRoot->right)){
            swap(pRoot->left, pRoot->right);
            if(pRoot->left) Mirror(pRoot->left);
            if(pRoot->right) Mirror(pRoot->right);
        }
    }

    //ƽ�������
    bool IsBalanced(TreeNode* pRoot, int& pDepth){
        if(pRoot == NULL){
            pDepth = 0;
            return true;
        }
        int left, right;
        if(IsBalanced(pRoot->left, left) && IsBalanced(pRoot->right, right)) {
            int diff = left - right;
            if(-1 <= diff && diff <= 1) {
                pDepth = 1 + (left > right ? left : right);
                return true;
            }
        }
        return false;
    }

    bool IsBalanced_Solution(TreeNode* pRoot) {
        int pDepth = 0;
		return IsBalanced(pRoot, pDepth);
    }

    //�ԳƵĶ�����
    bool isSymmetrical(TreeNode* lChild, TreeNode* rChild){
        if (lChild == NULL && rChild == NULL) return true;
        else if (lChild && rChild) {
            if(lChild->val != rChild->val) return false;
            else{
                return isSymmetrical(lChild->left, rChild->right) && isSymmetrical(lChild->right, rChild->left);
            }
        }
        else return false;
    }

    bool isSymmetrical(TreeNode* pRoot){
        if(pRoot == NULL) return true;
        return isSymmetrical(pRoot->left, pRoot->right);
    }

    //�Ѷ�������ӡ�ɶ���
    void recursion(TreeNode* pRoot, vector<vector<int>> &vec, int index){
        if(pRoot == NULL) return;
        else vec[index].push_back(pRoot->val);
        recursion(pRoot->left, vec, index + 1);
        recursion(pRoot->right, vec, index + 1);
    }
    vector<vector<int> > Print(TreeNode* pRoot) {
        int h = TreeDepth(pRoot);
        if(pRoot == NULL) return {};
        vector<int> v{};
        vector<vector<int>> vec(h, v);
        int index = 0;
        recursion(pRoot, vec, index);
        return vec;
    }

    //��ά�����еĲ���
    bool Find(int target, vector<vector<int> > array) {
        int rowLen = array.size() - 1   ;
        int colLen = array.empty() ? 0 : array[0].size() - 1;
        int i = rowLen, j = 0;
        while(i >= 0 && j <= colLen){
            if(array[i][j] == target)
                return true;
            else if(array[i][j] < target)
                ++j;
            else
                --i;
        }
        return false;
    }

    //��ת����˳����
    string ReverseSentence(string str) {
        reverse(str.begin(), str.end());
        string::iterator firstIter = str.begin(), secondIter = str.begin();
        while(secondIter < str.end()){
            if(*secondIter == ' '){
                reverse(firstIter, secondIter);
                firstIter = secondIter + 1;
            }
            ++secondIter;
        }
        reverse(firstIter, str.end());
        return str;
    }

    //��ֵ�������η�
        //�ݹ�汾
        double Power(double base, int exponent) {
            if(exponent == 0)
                return 1;
            else if(exponent < 0)
                return Power(1 / base, -exponent);
            else{
                double temp = Power(base, exponent/2) * Power(base, exponent/2);
                return temp * temp * (exponent % 2 ? base : 1);
            }
        }
        //λ����汾
        double Power2(double base, int exponent) {
            if(exponent < 0)
                return Power(1 / base, -exponent);
            double re = 1;
            while(exponent){
                if(exponent & 1)
                    re *= base;
                base *= base;
                exponent >>= 1;
            }
            return re;
        }
    //��������˳��ʹ����λ��ż��ǰ��
    void reOrderArray(vector<int> &array) {
        //������ð������ǰż����ͽ�������
        int len = array.size();
        for(int i = 0; i < len - 1; ++i){
            for(int j = 0; j < len - i - 1; ++j){
                if((array[j] % 2 == 0) && (array[j + 1] % 2 == 1))
                    swap(array[j], array[j + 1]);
            }
        }
    }

    //쳲���������
    int Fibonacci(int n) {
        int pre = 0, last = 1;  //������¼f(n-2)��f(n-1)
        if(n == 0) return pre;
        while(--n){
            last += pre;
            pre = last - pre;
        }
        return last;
    }

    //�����г��ִ�������һ�������
    int MoreThanHalfNum_Solution(vector<int> numbers) {
        //ʹ��map
        typedef map<int, int> intIntMap;
        typedef pair<int, int> intIntPair;
        intIntMap m;
        for(auto number : numbers)
            ++m[number];
        auto iter = max_element(m.begin(), m.end(),[](intIntPair a, intIntPair b){return a.second < b.second;});
        return iter->second > numbers.size() / 2 ? iter->first : 0;
    }

    //�滻�ո�
    void replaceSpace(char *str,int length) {
        if(str == NULL) return;
        int spaceCount = 0;
        for(int i = 0; *(str+i) != '\0'; ++i){
            if(*(str+i) == ' ')
                ++spaceCount;
        }
        int index = length - 1;
        for(int j = length - 1; j >= 0; --j){
            if(*(str+j) == ' '){
                for(int k = index; k > j; --k){
                    *(str+k+2*length) = *(str+k);   //����2*lengthλ
                }
                *(str+j+2*length-2) = '%';
                *(str+j+2*length-1) = '2';
                *(str+j+2*length) = '0';    //��' '����Ϊ'%20'
                --length;
                index = j - 1;
            }
            cout << str << endl;
        }
	}

	//��β��ͷ��ӡ����
	void print(ListNode* head, vector<int> &vec){
        if(head == NULL)
            return;
        print(head->next, vec);
        vec.push_back(head->val);
	}
    vector<int> printListFromTailToHead(ListNode* head) {
        vector<int> vec;
        print(head, vec);
        return vec;
    }

    //��ת����
    ListNode* ReverseList(ListNode* pHead) {
        //�ݹ�棻
        if(pHead == NULL || pHead->next == NULL)
            return pHead;
        ListNode *pReverseNode = ReverseList(pHead->next);
        pHead->next->next = pHead;
        pHead->next = NULL;
        return pReverseNode;
    }
    ListNode* ReverseList2(ListNode* pHead) {
        //�ǵݹ��
        if(pHead == NULL || pHead->next == NULL)
            return pHead;
        ListNode* pNode=pHead;//��ǰָ��
        ListNode* pReverseHead=NULL;//�������ͷָ��
        ListNode* pPrev=NULL;//��ǰָ���ǰһ�����

        while(pNode!=NULL){//��ǰ��㲻Ϊ��ʱ��ִ��
            ListNode* pNext=pNode->next;//���Ͽ�֮ǰһ��Ҫ����Ͽ�λ�ú�ߵĽ��
            if(pNext==NULL)//��pNextΪ��ʱ��˵����ǰ���Ϊβ�ڵ�
                pReverseHead=pNode;
            pNode->next=pPrev;//ָ�뷴ת
            pPrev=pNode;
            pNode=pNext;
        }
        return pReverseHead;
    }

    //��С��k����
    void heapify(vector<int> A, int i, int n) {
        int leftChild = 2 * i + 1;
        int rightChild = 2 * i + 2;
        int max = i;
        if(leftChild < n && A[leftChild] < A[max])
            max = leftChild;
        if(rightChild < n && A[rightChild] < A[max])
            max = rightChild;
        if(max != i) {
            swap(A[i], A[max]);
            heapify(A, max, n);
        }
    }

    int buildHeap(vector<int> A) {
        int len = A.size();
        for(int i = len / 2 - 1; i >= 0; --i) {
            heapify(A, i, len);
        }
        return len;
    }
    vector<int> GetLeastNumbers_Solution(vector<int> input, int k) {
        int len = buildHeap(input);
        while(k--) {
            swap(input[0], input[--len]);
            heapify(input, 0, len);
        }
        vector<int> re(input.rbegin(), input.rbegin()+k);
        return re;
    }
};

#endif // PTOFFER_H
