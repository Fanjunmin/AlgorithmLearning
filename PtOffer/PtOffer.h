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
//------------------------Array����-------------------------
//**********************************************************
    //��ά�����еĲ���
    bool Find(int target, vector<vector<int> > array) {
        //�����½ǿ�ʼ���ң�С��target���ƣ�����target����
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

    //��ת�������С����
    /*˳����Ұ汾O(n)
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
        //���ֲ��Ұ汾O(log n)~O(n)
        if(rotateArray.empty())
            return 0;
        int left = 0, mid = 0, right = rotateArray.size() - 1;
        while(rotateArray[left] >= rotateArray[right]) {
            //��һ��Ԫ���ϸ�С�����һ��Ԫ����˵��û�з�����ת
            if(left + 1 == right) {
                mid = right;
                break;
            }
            mid = (left + right) / 2;
            if(rotateArray[mid] == rotateArray[left] && rotateArray[mid] == rotateArray[right]) {
                //��������������������ȫ���,���ʱ����Ҫ˳����ҵ�һ��С�������������
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

    //��������˳��ʹ����λ��ż��ǰ��
    /*
    //ʹ��STL��׼�⺯��partition()
    void reOrderArray(vector<int> &array) {
        stable_partition(array.begin(), array.end(), [](int x){return x % 2 == 1;});
    }
    */
    void reOrderArray(vector<int> &array) {
        //������ð������(ð���������ȶ�������)��ǰż����ͽ�������
        int len = array.size();
        for(int i = 0; i < len - 1; ++i){
            for(int j = 0; j < len - i - 1; ++j){
                if((array[j] % 2 == 0) && (array[j + 1] % 2 == 1))
                    swap(array[j], array[j + 1]);
            }
        }
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

    //���������������
    int FindGreatestSumOfSubArray(vector<int> array) {
        //���ö�̬�滮����,F[i]��ʾarray[0, i]�����������������
        //F[i] = max(array[i], F[i] + array[i])
        if(array.empty()) return 0;
        int MaxSum = array[0], temp = array[0];
        for(int i = 1; i < array.size(); ++i) {
            temp = temp >= 0 ? temp + array[i] : array[i];
            MaxSum = MaxSum >= temp ? MaxSum : temp;
        }
        return MaxSum;
    }

    //�������ų���С����
    string PrintMinNumber(vector<int> numbers) {
        //����to_string()ת��Ϊstring����
        //������������string x,y ����x+y��y+x�ıȽϽ�������
        if(numbers.empty()) return "";
        vector<string> svec(numbers.size());
        transform(numbers.begin(), numbers.end(), svec.begin(), [](int x){ return to_string(x);});
        sort(svec.begin(), svec.end(), [](string x, string y){ return (x + y) < (y + x);});
        for(int i= 1; i < svec.size(); ++i) {
            svec[0] += svec[i];
        }
        return svec[0];
    }

    //�����е������
    /*
    //brute force ��ʱ
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
        int* temp = new int[hi - lo + 1];    //��ʱ����
        int i = mid, j = hi, k = hi - lo;
        while(i >= lo && j >= mid + 1) {
            if(data[i] > data[j]) {
                //��ĩβ���бȽϣ����ǰһ������Ԫ�ش��ں�һ�����䣬�����(j - mid)�������
                countSum += (j - mid);
                temp[k--] = data[i--];
            }
            else {
                temp[k--] = data[j--];
            }
        }
        //��ʣ��Ԫ�ط�����ʱ������,[lo, mid]��[mid+1, hi]��������һ������Ϊ��
        for(; j >= mid + 1; --j)    temp[k--] = data[j];
        for(; i >= lo; --i)  temp[k--] = data[i];
        for(int l = lo; l <= hi; ++l)  data[l] = temp[l - lo];
        delete []temp;
        return (countSum + leftCount + rightCount) % 1000000007;
    }
    int InversePairs(vector<int> data) {
        //���ù鲢�����ԭ��O(nlog n)
        if(data.empty()) return 0;
        return mergeCount(data, 0, data.size() - 1);
    }

    //���������������г��ֵĴ���
    /*
    //ʹ��STL�㷨count ѭ�����O(n)
    int GetNumberOfK(vector<int> data, int k) {
        return count(data.begin(), data.end(), k);
    }
    //����STL��multimap�����ײ��Ժ����Ϊ����,����ɱ�O(n),��ѯ�ɱ�O(log n)
    int GetNumberOfK(vector<int> data, int k) {
        multiset<int> msData(data.begin(), data.end());
        return msData.count(k);
    }
    //����STL�⺯��lower_bound()��upperBound(),O(log n)
    int GetNumberOfK(vector<int> data ,int k) {
        auto iter1 = lower_bound(data.begin(), data.end(), k);
        auto iter2 = upper_bound(data.begin(), data.end(), k);
        return static_cast<int>(iter2 - iter1);
    }
    */
    int GetNumberOfK(vector<int> data ,int k) {
        //���ֲ��ҷǵݹ�汾
        auto iter1 = lower_bound(data.begin(), data.end(), k);
        auto iter2 = upper_bound(data.begin(), data.end(), k);
        return static_cast<int>(iter2 - iter1);
    }

    //������ֻ����һ�ε�����
    /*
    //����ɢ�б�map
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
        //����λ����^���� a^b^b = b^a^b = a
        if(!data.empty()) {
            int result = 0;
            for(auto d : data) result ^= d; //d = num1 * num2
            int n = result - (result & (result - 1));    //�����λ��1�ڵ�kλ��������Ϊ0
            *num1 = *num2 = 0;
            for(auto d : data) {
                //����data�еĳ������ε�������ͬ�����ĵ�kλ��Ȼ��ͬ
                //��������:�������n��λ���Ƿ�Ϊ0
                if(d & n) *num1 ^= d;
                else *num2 ^= d;
            }
        }
    }

    //�������ظ�������
    /*
    //����ɢ�б�map
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
    //���ý���
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
//----------------------------�ַ���--------------------------
//************************************************************

    //����ת�ַ���
    /*
    //O(n)�ռ临�Ӷ�
    string LeftRotateString(string str, int n) {
        if(str.empty()) return str;
        int len = str.size();
        n %= len;
        string re1(str.begin(), str.begin() + n), re2(str.begin() + n, str.end());
        return re2 + re1;
    }
    //STL rotate()����,���ݲ�ͬ�ĵ��������ò�ͬ�ײ�ʵ��,string�ĵ�����Ϊ������ʵ�����
    //forward iterator:����һ��һ����������
    //bidirectional iterator:����reverse
    //rand access iterator:���ÿ�ǰ�κͺ���������
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

    //��ʾ��ֵ���ַ���
    bool isNumeric(char* string) {
        //�������еķǷ����
        if(string == NULL) return false;
        bool hasE = false, hasDot = false, hasSign = false; //��ʶ�Ƿ���E��С���㣬����λ
        int len = strlen(string);
        for(int i = 0; i < len; ++i) {
            if(string[i] == 'e' || string[i] == 'E') {
                if(i + 1 == len || hasE) return false;  //e�������������Ҳ��ܳ�����������e
                hasE = true;
            }
            else if(string[i] == '+' || string[i] == '-') {
                if(!hasSign && i > 0 && string[i - 1] != 'e' && string[i - 1] != 'E') {
                    //��һ�γ��ַ���λ����������λ������e����һλ
                    return false;
                }
                if(hasSign && string[i - 1] != 'e' && string[i - 1] != 'E') {
                    //i ��Ȼ���� 0
                    //�Ѿ����ֹ�����λ������ֵķ���λ������e����һλ
                    return false;
                }
                hasSign = true;
            }
            else if(string[i] == '.') {
                if(hasDot || hasE) return false;    //С����ֻ�ܳ���һ�Σ�����e���沢���ܳ���С����
                hasDot = true;
            }
            else if(string[i] > '9' || string[i] < '0') {
                return false;
            }
        }
        return true;
    }

    //���ַ���ת��������
    long power(int e, int m) {
        //����e^m
        return m == 0 ? 1 : (m % 2 ? power(e, m / 2) * e : power(e, m / 2));
    }

    int StrToInt(string str) {
        if(str.empty()) return 0;
        int hasE = 0, hasSign = 0;
        long coe = 0, exp = 0;
        for(int i = 0; i < str.size(); ++i) {
            if(i == 0 && (str[i] == '+' || str[i] == '-')) {
                //��λ������������
                if(str[0] == '+') hasSign = 1;
                else if(str[0] == '-') hasSign = -1;
            }
            else if(i != 0 && (str[i] == '+' || str[i] == '-')) return 0; //����λ���ַ���λ������0
            else if(str[i] == 'e' || str[i] == 'E') {
                //������ֶ��e����0
                if(hasE == 1) return 0;
                else hasE = 1;
            }
            else if(hasE == 0 && str[i] <= '9' && str[i] >= '0') {
                //ϵ�����ֵ���
                coe = (10 * coe + str[i] - '0');
                if((hasSign == 0 || hasSign == 1) && coe > INT_MAX) return 0;
                else if(hasSign == -1 && -coe < INT_MIN) return 0;
            }
            else if(hasE == 1 && str[i] <= '9' && str[i] >= '0') {
                //ָ�����ֵ���
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

    //�ַ���������
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

    //�滻�ո�
    void replaceSpace(char *str,int length) {
        //length �ַ�������
        if(str == NULL) return;
        int spaceLen = 0;
        for(int i = 0; str[i] != '\0'; ++i){
            if(*(str+i) == ' ') ++spaceLen;
        }
        for(int j = strlen(str) - 1; j >= 0; --j){
            int i = j + 2 * spaceLen;
            if(str[j] == ' '){
                //���ո�����Ϊ"%20"
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

    //��һ��ֻ����һ�ε��ַ�
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
//----------------------Tree��-----------------------------
//*********************************************************

    //�ؽ�������
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
            if(vin[i] == pre[0])    //�ҵ�ͷ�ڵ�
                break;
        }
        //����ݹ�
        vector<int> leftPre(pre.begin() + 1, pre.begin() + i + 1);
        vector<int> rightPre(pre.begin() + i + 1, pre.end());
        vector<int> leftVin(vin.begin(), vin.begin() + i);
        vector<int> rightVin(vin.begin() + i + 1, vin.end());
        node->left = reConstructBinaryTree(leftPre, leftVin);
        node->right = reConstructBinaryTree(rightPre, rightVin);
        return node;
    }

    //�����ӽṹ
    bool HasSubtree(TreeNode* pRoot1, TreeNode* pRoot2) {
        //Լ��������������һ�������ӽṹ
        if(!pRoot2 || !pRoot1) return false;
        return isSubtree(pRoot1, pRoot2)
            || HasSubtree(pRoot1->left, pRoot2)
            || HasSubtree(pRoot1->right, pRoot2);
    }

    bool isSubtree(TreeNode* pRoot1, TreeNode* pRoot2) {
        //�ж�ͷ�ڵ�pRoot2���ڵ����Ƿ���ͷ�ڵ�pRoot1���ڵ���������
        if(!pRoot2) return true;
        if(!pRoot1) return false;
        return pRoot1->val != pRoot2->val ? false :
            isSubtree(pRoot1->left, pRoot2->left)
            && isSubtree(pRoot1->right, pRoot2->right);
    }

    //�������ľ���
    void Mirror(TreeNode *pRoot) {
        if(pRoot && (pRoot->left || pRoot->right)){
            swap(pRoot->left, pRoot->right);
            if(pRoot->left) Mirror(pRoot->left);
            if(pRoot->right) Mirror(pRoot->right);
        }
    }

    //�������´�ӡ������
    vector<int> PrintFromTopToBottom(TreeNode* root) {
        //ʹ�ö���
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

    //�����������ĺ����������
    bool judgeBST(vector<int> sequence) {
        if(sequence.empty()) return true;
        int head = sequence.back(), i = 0;  //ͷ�ڵ�ض�Ϊ���һ��Ԫ��
        for(; i < sequence.size() - 1; ++i) {
            //�ҵ�����������������ĵ�һ�����
            if(sequence[i] > head)  break;
        }
        for(int j = i;j < sequence.size() - 1; ++j) {
            //����������������С�ڵ���head��ֵ���򷵻�false
            if(sequence[j] <= head) return false;
        }
        vector<int> leftSeq(sequence.begin(), sequence.begin() + i);    //����������
        vector<int> rightSeq(sequence.begin() + i, sequence.end() - 1); //����������
        //�ݹ�
        return judgeBST(leftSeq) && judgeBST(rightSeq);
    }

    bool VerifySquenceOfBST(vector<int> sequence) {
        if(sequence.empty()) return false;
        return judgeBST(sequence);
    }

    //�������к�Ϊĳһֵ��·��
    vector<vector<int> > FindPath(TreeNode* root,int expectNumber) {

    }

    //���������
    int TreeDepth(TreeNode* pRoot) {
        return pRoot == NULL ? 0 : 1 + max(TreeDepth(pRoot->left), TreeDepth(pRoot->right));
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
