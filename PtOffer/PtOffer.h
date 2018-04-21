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
    //二叉树深度
    int TreeDepth(TreeNode* pRoot)
    {
        return pRoot == NULL ? 0 : 1 + max(TreeDepth(pRoot->left), TreeDepth(pRoot->right));
    }

    //二叉树的镜像
    void Mirror(TreeNode *pRoot) {
        if(pRoot && (pRoot->left || pRoot->right)){
            swap(pRoot->left, pRoot->right);
            if(pRoot->left) Mirror(pRoot->left);
            if(pRoot->right) Mirror(pRoot->right);
        }
    }

    //平衡二叉树
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

    //对称的二叉树
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

    //把二叉树打印成多行
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

    //二维数组中的查找
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

    //翻转单词顺序列
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

    //数值的整数次方
        //递归版本
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
        //位运算版本
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
    //调整数组顺序使奇数位于偶数前面
    void reOrderArray(vector<int> &array) {
        //类似与冒泡排序，前偶后奇就交换相邻
        int len = array.size();
        for(int i = 0; i < len - 1; ++i){
            for(int j = 0; j < len - i - 1; ++j){
                if((array[j] % 2 == 0) && (array[j + 1] % 2 == 1))
                    swap(array[j], array[j + 1]);
            }
        }
    }

    //斐波那契数列
    int Fibonacci(int n) {
        int pre = 0, last = 1;  //用来记录f(n-2)和f(n-1)
        if(n == 0) return pre;
        while(--n){
            last += pre;
            pre = last - pre;
        }
        return last;
    }

    //数组中出现次数超过一半的数字
    int MoreThanHalfNum_Solution(vector<int> numbers) {
        //使用map
        typedef map<int, int> intIntMap;
        typedef pair<int, int> intIntPair;
        intIntMap m;
        for(auto number : numbers)
            ++m[number];
        auto iter = max_element(m.begin(), m.end(),[](intIntPair a, intIntPair b){return a.second < b.second;});
        return iter->second > numbers.size() / 2 ? iter->first : 0;
    }

    //替换空格
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
                    *(str+k+2*length) = *(str+k);   //后移2*length位
                }
                *(str+j+2*length-2) = '%';
                *(str+j+2*length-1) = '2';
                *(str+j+2*length) = '0';    //将' '代替为'%20'
                --length;
                index = j - 1;
            }
            cout << str << endl;
        }
	}

	//从尾到头打印链表
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

    //反转链表
    ListNode* ReverseList(ListNode* pHead) {
        //递归版；
        if(pHead == NULL || pHead->next == NULL)
            return pHead;
        ListNode *pReverseNode = ReverseList(pHead->next);
        pHead->next->next = pHead;
        pHead->next = NULL;
        return pReverseNode;
    }
    ListNode* ReverseList2(ListNode* pHead) {
        //非递归版
        if(pHead == NULL || pHead->next == NULL)
            return pHead;
        ListNode* pNode=pHead;//当前指针
        ListNode* pReverseHead=NULL;//新链表的头指针
        ListNode* pPrev=NULL;//当前指针的前一个结点

        while(pNode!=NULL){//当前结点不为空时才执行
            ListNode* pNext=pNode->next;//链断开之前一定要保存断开位置后边的结点
            if(pNext==NULL)//当pNext为空时，说明当前结点为尾节点
                pReverseHead=pNode;
            pNode->next=pPrev;//指针反转
            pPrev=pNode;
            pNode=pNext;
        }
        return pReverseHead;
    }

    //最小的k个数
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
