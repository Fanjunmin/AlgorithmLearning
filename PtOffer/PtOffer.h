#ifndef PTOFFER_H
#define PTOFFER_H
#include <bits/stdc++.h>
#include "TreeNode.h"
#include "ListNode.h"
using namespace std;
class PtOffer
{
public:
//**********************************************************
//------------------------Array数组-------------------------
//**********************************************************
    //二维数组中的查找
    bool Find(int target, vector<vector<int> > array) {
        //从左下角开始查找，小于target上移，大于target右移
        int rowLen = array.size();
        int colLen = array.empty() ? 0 : array[0].size();
        int i = rowLen - 1, j = 0;
        while(i >= 0 && j < colLen){
            if(array[i][j] == target)
                return true;
            else if(array[i][j] < target)
                ++j;
            else
                --i;
        }
        return false;
    }

    //旋转数组的最小数字
    /*顺序查找版本O(n)
    int minNumberInRotateArray(vector<int> rotateArray) {
        if(rotateArray.empty())
            return 0;
        int i= 1;
        for(; i < rotateArray.size(); ++i) {
            if(rotateArray[i] < rotateArray[i - 1])
                break;
        }
        return rotateArray[i];
    }*/
    int minNumberInRotateArray(vector<int> rotateArray) {
        //二分查找版本O(log n)~O(n)
        if(rotateArray.empty())
            return 0;
        int left = 0, mid = 0, right = rotateArray.size() - 1;
        while(rotateArray[left] >= rotateArray[right]) {
            //第一个元素严格小于最后一个元素则说明没有发生旋转
            if(left + 1 == right) {
                mid = right;
                break;
            }
            mid = (left + right) / 2;
            if(rotateArray[mid] == rotateArray[left] && rotateArray[mid] == rotateArray[right]) {
                //最特殊的情况：三个数完全相等,这个时候需要顺序查找第一个小于其的数并返回
                for(int i = left + 1; i < right; ++i) {
                    if(rotateArray[i] < rotateArray[mid]) {
                        return rotateArray[i];
                    }
                }
            }
            if(rotateArray[mid] >= rotateArray[left]) {
                left = mid;
            }
            else if(rotateArray[mid] <= rotateArray[right]){
                right = mid;
            }
        }
        return rotateArray[mid];
    }

    //调整数组顺序使奇数位于偶数前面
    /*
    //使用STL标准库函数partition()
    void reOrderArray(vector<int> &array) {
        stable_partition(array.begin(), array.end(), [](int x){return x % 2 == 1;});
    }
    */
    void reOrderArray(vector<int> &array) {
        //类似与冒泡排序(冒泡排序是稳定的排序)，前偶后奇就交换相邻
        int len = array.size();
        for(int i = 0; i < len - 1; ++i){
            for(int j = 0; j < len - i - 1; ++j){
                if((array[j] % 2 == 0) && (array[j + 1] % 2 == 1))
                    swap(array[j], array[j + 1]);
            }
        }
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

    //连续子数组的最大和
    int FindGreatestSumOfSubArray(vector<int> array) {
        //采用动态规划策略,F[i]表示array[0, i]中连续子数组的最大和
        //F[i] = max(array[i], F[i] + array[i])
        if(array.empty()) return 0;
        int MaxSum = array[0], temp = array[0];
        for(int i = 1; i < array.size(); ++i) {
            temp = temp >= 0 ? temp + array[i] : array[i];
            MaxSum = MaxSum >= temp ? MaxSum : temp;
        }
        return MaxSum;
    }

    //把数组排成最小的数
    string PrintMinNumber(vector<int> numbers) {
        //利用to_string()转化为string类型
        //对于任意两个string x,y 利用x+y和y+x的比较进行排序
        if(numbers.empty()) return "";
        vector<string> svec(numbers.size());
        transform(numbers.begin(), numbers.end(), svec.begin(), [](int x){ return to_string(x);});
        sort(svec.begin(), svec.end(), [](string x, string y){ return (x + y) < (y + x);});
        for(int i= 1; i < svec.size(); ++i) {
            svec[0] += svec[i];
        }
        return svec[0];
    }

    //数组中的逆序对
    /*
    //brute force 超时
    int InversePairs(vector<int> data) {
        if(data.empty()) return 0;
        const int p = 1000000007;
        int sum = 0;
        for(int i = 0; i < data.size(); ++i) {
            for(int j = 0; j < data.size(); ++j) {
                if(i < j && data[i] > data[j]) {
                    sum += 1;
                    sum %= p;
                }
            }
        }
        return sum;
    }*/
    long mergeCount(vector<int>& data, int lo, int hi) {
        //data[lo, hi]
        if(hi == lo) return 0;
        int mid = (lo + hi) / 2;
        long leftCount = mergeCount(data, lo, mid), rightCount = mergeCount(data, mid + 1, hi), countSum = 0;
        int* temp = new int[hi - lo + 1];    //临时数组
        int i = mid, j = hi, k = hi - lo;
        while(i >= lo && j >= mid + 1) {
            if(data[i] > data[j]) {
                //从末尾进行比较，如果前一个区间元素大于后一个区间，则存在(j - mid)个逆序对
                countSum += (j - mid);
                temp[k--] = data[i--];
            }
            else {
                temp[k--] = data[j--];
            }
        }
        //将剩余元素放入临时数组中,[lo, mid]和[mid+1, hi]中至少有一个区间为空
        for(; j >= mid + 1; --j)    temp[k--] = data[j];
        for(; i >= lo; --i)  temp[k--] = data[i];
        for(int l = lo; l <= hi; ++l)  data[l] = temp[l - lo];
        delete []temp;
        return (countSum + leftCount + rightCount) % 1000000007;
    }
    int InversePairs(vector<int> data) {
        //采用归并排序的原理：O(nlog n)
        if(data.empty()) return 0;
        return mergeCount(data, 0, data.size() - 1);
    }

    //数字在排序数组中出现的次数
    /*
    //使用STL算法count 循序查找O(n)
    int GetNumberOfK(vector<int> data, int k) {
        return count(data.begin(), data.end(), k);
    }
    //利用STL的multimap容器底层以红黑树为基础,构造成本O(n),查询成本O(log n)
    int GetNumberOfK(vector<int> data, int k) {
        multiset<int> msData(data.begin(), data.end());
        return msData.count(k);
    }
    //利用STL库函数lower_bound()和upperBound(),O(log n)
    int GetNumberOfK(vector<int> data ,int k) {
        auto iter1 = lower_bound(data.begin(), data.end(), k);
        auto iter2 = upper_bound(data.begin(), data.end(), k);
        return static_cast<int>(iter2 - iter1);
    }
    */
    int GetNumberOfK(vector<int> data ,int k) {
        //二分查找非递归版本
        auto iter1 = lower_bound(data.begin(), data.end(), k);
        auto iter2 = upper_bound(data.begin(), data.end(), k);
        return static_cast<int>(iter2 - iter1);
    }

    //数组中只出现一次的数字
    /*
    //利用散列表map
    void FindNumsAppearOnce(vector<int> data,int* num1,int *num2) {
        map<int, int> myMap;
        for(auto d : data) ++myMap[d];
        int s[2], i = 0;
        for(auto mm : myMap) {
            if(mm.second == 1)
                s[i++] = mm.first;
        }
        *num1 = s[0];
        *num2 = s[1];
    }*/
    void FindNumsAppearOnce(vector<int> data,int* num1,int *num2) {
        //利用位运算^性质 a^b^b = b^a^b = a
        if(!data.empty()) {
            int result = 0;
            for(auto d : data) result ^= d; //d = num1 * num2
            int n = result - (result & (result - 1));    //将最低位的1在第k位，其余设为0
            *num1 = *num2 = 0;
            for(auto d : data) {
                //对于data中的出现两次的数，相同的数的第k位必然相同
                //分组依据:这个数与n按位与是否为0
                if(d & n) *num1 ^= d;
                else *num2 ^= d;
            }
        }
    }

    //数组中重复的数字
    /*
    //利用散列表map
    bool duplicate(int numbers[], int length, int* duplication) {
        map<int, int> myMap;
        for(int i = 0; i < length; ++i) {
            ++myMap[numbers[i]];
            if(myMap[numbers[i]] == 2) {
                *duplication = numbers[i];
                return true;
            }
        }
        return false;
    }*/
    //利用交换
    bool duplicate(int numbers[], int length, int* duplication) {
        int num;
         for(int i = 0; i < length; ++i) {
            num = numbers[i];
            if(i != num) {

            }
         }
        return false;
    }

//************************************************************
//----------------------------字符串--------------------------
//************************************************************

    //左旋转字符串
    /*
    //O(n)空间复杂度
    string LeftRotateString(string str, int n) {
        if(str.empty()) return str;
        int len = str.size();
        n %= len;
        string re1(str.begin(), str.begin() + n), re2(str.begin() + n, str.end());
        return re2 + re1;
    }
    //STL rotate()函数,根据不同的迭代器调用不同底层实现,string的迭代器为随机访问迭代器
    //forward iterator:依次一个一个慢慢交换
    //bidirectional iterator:三次reverse
    //rand access iterator:利用卡前段和后段最大公因子
    string LeftRotateString(string str, int n) {
        if(str.empty()) return str;
        n %= str.size();
        rotate(str.begin(), str.begin() + n, str.end());
        return str;
    }
    */
    string LeftRotateString(string str, int n) {
        if(str.empty()) return str;
        int len = str.size();
        n %= len;
        int re = len - n, i = 0, j = n;
        while(n <= re) {
            for(; i < n; ++i, ++j) swap(str[i], str[j]);
            re -= n;
        }
        //cout << str << i << j << re << endl;
        while(re--) {
            swap(str[i++], str[j++]);
        }
        return str;
    }

    //表示数值的字符串
    bool isNumeric(char* string) {
        //考察所有的非法情况
        if(string == NULL) return false;
        bool hasE = false, hasDot = false, hasSign = false; //标识是否有E，小数点，符号位
        int len = strlen(string);
        for(int i = 0; i < len; ++i) {
            if(string[i] == 'e' || string[i] == 'E') {
                if(i + 1 == len || hasE) return false;  //e后面必须接数字且不能出现两个以上e
                hasE = true;
            }
            else if(string[i] == '+' || string[i] == '-') {
                if(!hasSign && i > 0 && string[i - 1] != 'e' && string[i - 1] != 'E') {
                    //第一次出现符号位，必须是首位或者是e后面一位
                    return false;
                }
                if(hasSign && string[i - 1] != 'e' && string[i - 1] != 'E') {
                    //i 必然大于 0
                    //已经出现过符号位，则出现的符号位必须在e后面一位
                    return false;
                }
                hasSign = true;
            }
            else if(string[i] == '.') {
                if(hasDot || hasE) return false;    //小数点只能出现一次，并且e后面并不能出现小数点
                hasDot = true;
            }
            else if(string[i] > '9' || string[i] < '0') {
                return false;
            }
        }
        return true;
    }

    //把字符串转换成整数
    long power(int e, int m) {
        //求幂e^m
        return m == 0 ? 1 : (m % 2 ? power(e, m / 2) * e : power(e, m / 2));
    }

    int StrToInt(string str) {
        if(str.empty()) return 0;
        int hasE = 0, hasSign = 0;
        long coe = 0, exp = 0;
        for(int i = 0; i < str.size(); ++i) {
            if(i == 0 && (str[i] == '+' || str[i] == '-')) {
                //首位出现正负符号
                if(str[0] == '+') hasSign = 1;
                else if(str[0] == '-') hasSign = -1;
            }
            else if(i != 0 && (str[i] == '+' || str[i] == '-')) return 0; //非首位出现符号位，返回0
            else if(str[i] == 'e' || str[i] == 'E') {
                //如果出现多次e返回0
                if(hasE == 1) return 0;
                else hasE = 1;
            }
            else if(hasE == 0 && str[i] <= '9' && str[i] >= '0') {
                //系数部分叠加
                coe = (10 * coe + str[i] - '0');
                if((hasSign == 0 || hasSign == 1) && coe > INT_MAX) return 0;
                else if(hasSign == -1 && -coe < INT_MIN) return 0;
            }
            else if(hasE == 1 && str[i] <= '9' && str[i] >= '0') {
                //指数部分叠加
                exp = (10 * exp + str[i] - '0');
                coe *= power(10, exp);
                if((hasSign == 0 || hasSign == 1) && coe > INT_MAX) return 0;
                else if(hasSign == -1 || -coe < INT_MIN) return 0;
            }
            else return 0;
        }
        if(hasSign == -1) return -coe;
        else return coe;
    }

    //字符串的排列
    void pBackTracking(set<string>& strSet, string& str, int beg) {
        if(beg == str.size()) {
            strSet.insert(str);
            return;
        }
        for(int i = beg; i < str.size(); ++i) {
            swap(str[i], str[beg]);
            pBackTracking(strSet, str, beg + 1);
            swap(str[i], str[beg]);
        }
    }

    vector<string> Permutation(string str) {
        if(str.empty()) return {};
        set<string> strSet;
        pBackTracking(strSet, str, 0);
        vector<string> strVec(strSet.begin(), strSet.end());
        return strVec;
    }

    //替换空格
    void replaceSpace(char *str,int length) {
        //length 字符串长度
        if(str == NULL) return;
        int spaceLen = 0;
        for(int i = 0; str[i] != '\0'; ++i){
            if(*(str+i) == ' ') ++spaceLen;
        }
        for(int j = strlen(str) - 1; j >= 0; --j){
            int i = j + 2 * spaceLen;
            if(str[j] == ' '){
                //将空格设置为"%20"
                str[i - 2] = '%';
                str[i - 1] = '2';
                str[i] = '0';
                --spaceLen;
            }
            else {
                str[i] = str[j];
            }
        }
	}

    //第一个只出现一次的字符
    int FirstNotRepeatingChar(string str) {
        map<char, int> myMap;
        for(int i = 0; i < str.size(); ++i) {
            ++myMap[str[i]];
        }
        for(int i = 0; i < str.size(); ++i) {
            if(myMap[str[i]] == 1)
                return i;
        }
        return -1;
    }


//*********************************************************
//----------------------Tree树-----------------------------
//*********************************************************

    //重建二叉树
    TreeNode* reConstructBinaryTree(vector<int> pre,vector<int> vin) {
        if(pre.empty() || vin.empty() || pre.size() != vin.size())
            return NULL;
        if(pre.size() == 1) {
            TreeNode* node = new TreeNode(pre[0]);
            return node;
        }
        TreeNode* node = new TreeNode(pre[0]);
        int i = 0;
        for(; i < vin.size(); ++i) {
            if(vin[i] == pre[0])    //找到头节点
                break;
        }
        //分组递归
        vector<int> leftPre(pre.begin() + 1, pre.begin() + i + 1);
        vector<int> rightPre(pre.begin() + i + 1, pre.end());
        vector<int> leftVin(vin.begin(), vin.begin() + i);
        vector<int> rightVin(vin.begin() + i + 1, vin.end());
        node->left = reConstructBinaryTree(leftPre, leftVin);
        node->right = reConstructBinaryTree(rightPre, rightVin);
        return node;
    }

    //树的子结构
    bool HasSubtree(TreeNode* pRoot1, TreeNode* pRoot2) {
        //约定空树不是任意一个树的子结构
        if(!pRoot2 || !pRoot1) return false;
        return isSubtree(pRoot1, pRoot2)
            || HasSubtree(pRoot1->left, pRoot2)
            || HasSubtree(pRoot1->right, pRoot2);
    }

    bool isSubtree(TreeNode* pRoot1, TreeNode* pRoot2) {
        //判断头节点pRoot2所在的树是否是头节点pRoot1所在的树的子树
        if(!pRoot2) return true;
        if(!pRoot1) return false;
        return pRoot1->val != pRoot2->val ? false :
            isSubtree(pRoot1->left, pRoot2->left)
            && isSubtree(pRoot1->right, pRoot2->right);
    }

    //二叉树的镜像
    void Mirror(TreeNode *pRoot) {
        if(pRoot && (pRoot->left || pRoot->right)){
            swap(pRoot->left, pRoot->right);
            if(pRoot->left) Mirror(pRoot->left);
            if(pRoot->right) Mirror(pRoot->right);
        }
    }

    //从上往下打印二叉树
    vector<int> PrintFromTopToBottom(TreeNode* root) {
        //使用队列
        if(!root) return {};
        queue<TreeNode*> que;
        que.push(root);
        vector<int> vec;
        while(!que.empty()) {
            TreeNode* temp = que.front();
            vec.push_back(temp->val);
            que.pop();
            if(temp->left) que.push(temp->left);
            if(temp->right) que.push(temp->right);
        }
        return vec;
    }

    //二叉搜索树的后序遍历序列
    bool judgeBST(vector<int> sequence) {
        if(sequence.empty()) return true;
        int head = sequence.back(), i = 0;  //头节点必定为最后一个元素
        for(; i < sequence.size() - 1; ++i) {
            //找到后序遍历的右子树的第一个结点
            if(sequence[i] > head)  break;
        }
        for(int j = i;j < sequence.size() - 1; ++j) {
            //在右子树中若出现小于等于head的值，则返回false
            if(sequence[j] <= head) return false;
        }
        vector<int> leftSeq(sequence.begin(), sequence.begin() + i);    //左子树序列
        vector<int> rightSeq(sequence.begin() + i, sequence.end() - 1); //右子树序列
        //递归
        return judgeBST(leftSeq) && judgeBST(rightSeq);
    }

    bool VerifySquenceOfBST(vector<int> sequence) {
        if(sequence.empty()) return false;
        return judgeBST(sequence);
    }

    //二叉树中和为某一值的路径
    vector<vector<int> > FindPath(TreeNode* root,int expectNumber) {

    }

    //二叉树深度
    int TreeDepth(TreeNode* pRoot) {
        return pRoot == NULL ? 0 : 1 + max(TreeDepth(pRoot->left), TreeDepth(pRoot->right));
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
