#ifndef PTOFFER_H
#define PTOFFER_H
#include "TreeNode.h"
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
    int balancedHeight(TreeNode* pRoot){
        //����ƽ���������������߶ȣ����򷵻�-1
        if(pRoot == NULL) return 0;
        else{
            if(pRoot->left == NULL && pRoot->right == NULL){
                return 1;
            }
            else if(pRoot->left != NULL && pRoot->right == NULL){
                return balancedHeight(pRoot->left) == 1 ? 2 : -1;
            }
            else if(pRoot->left == NULL && pRoot->right != NULL){
                return balancedHeight(pRoot->right) == 1 ? 2 : -1;
            }
            else{
                int a = balancedHeight(pRoot->right);
                int b = balancedHeight(pRoot->left);
                if(a != -1 && b != -1 && abs(a - b) <= 1) return max(a, b) + 1;
                else return -1;
            }
        }
    }
    bool IsBalanced_Solution(TreeNode* pRoot) {
		return balancedHeight(pRoot) == -1 ? false : true;
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

    //�ԳƵĶ�����
    void Traversal(TreeNode* pRoot, vector<int> &vec, int order){
        if(pRoot == NULL) return;
        vec.push_back(pRoot->val);
        if(order){
        	Traversal(pRoot->left, vec, order);
        	Traversal(pRoot->right, vec, order);
        }
        else{
            Traversal(pRoot->right, vec, order);
        	Traversal(pRoot->left, vec, order);
        }
    }
    bool isSymmetrical(TreeNode* pRoot){
		vector<int> vec0, vec1;
        Traversal(pRoot, vec0, 0);
        Traversal(pRoot, vec1, 1);
        return vec0 == vec1;
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
        //int len = numbers.size() % 2 ?  numbers.size() / 2 + 1 : numbers.size() / 2;
        return iter->second > numbers.size() / 2 ? iter->first : 0;
    }

};

#endif // PTOFFER_H
