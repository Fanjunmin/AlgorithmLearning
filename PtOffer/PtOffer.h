#ifndef PTOFFER_H
#define PTOFFER_H
#include <bits/stdc++.h>
using namespace std;

struct TreeNode {
	int val;
	struct TreeNode *left;
	struct TreeNode *right;
	TreeNode(int x) :
			val(x), left(NULL), right(NULL) {
	}
};

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

struct TreeLinkNode {
    int val;
    struct TreeLinkNode *left;
    struct TreeLinkNode *right;
    struct TreeLinkNode *next;
    TreeLinkNode(int x) :val(x), left(NULL), right(NULL), next(NULL) {

    }
};

struct RandomListNode {
    int label;
    struct RandomListNode *next, *random;
    RandomListNode(int x) :
            label(x), next(NULL), random(NULL) {
    }
};

class PtOffer
{
public:
/*********************************************************/
/*------------------------Array数组-----------------------*/
/**********************************************************/

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
    bool duplicate(int numbers[], int length, int* duplication) {
        //利用散列表map
        map<int, int> myMap;
        for(int i = 0; i < length; ++i) {
            ++myMap[numbers[i]];
            if(myMap[numbers[i]] == 2) {
                *duplication = numbers[i];
                return true;
            }
        }
        return false;
    }

    //顺时针打印矩阵
    vector<int> printMatrix(vector<vector<int> > matrix) {
        if(matrix.empty()) return {};
        int m = matrix.size(), n = matrix[0].size();
        vector<int> spiral(m * n);
        int  i = 0, j = 0, k = 0, index = 0;
        while(true) {
            for(int k = j; k < n; ++k) spiral[index++] = matrix[i][k];
            if(++i >= m) break;
            for(int k = i; k < m; ++k) spiral[index++] = matrix[k][n - 1];
            if(j >= --n) break;
            for(int k = n - 1; k >= j; --k) spiral[index++] = matrix[m - 1][k];
            if(i >= --m) break;
            for(int k = m - 1; k >= i; --k) spiral[index++] = matrix[k][j];
            if(++j >= n) break;
        }
        return spiral;
    }

    //和为S的连续正数序列
    vector<vector<int> > FindContinuousSequence(int sum) {
        if(sum < 2) return {};
        vector<vector<int> > result;
        int lo = 1, hi = 2, mid = (sum + 1) >> 1, S = lo + hi;
        while(lo < mid && hi < sum) {
            while(sum < S) {
                S -= lo;
                ++lo;
            }
            if(sum == S) {
                vector<int> vec(hi - lo + 1);
                iota(vec.begin(), vec.end(), lo);
                result.push_back(vec);
            }
            ++hi;
            S += hi;
        }
        return result;
    }

    //丑数
    int GetUglyNumber_Solution(int index) {
        if(index < 1) return 0;
        vector<int> vec(index, 1);
        int i = 0, j = 0, k = 0;
        for(int pos = 1; pos < index; ++pos) {
            vec[pos] = std::min(vec[i] * 2, std::min(vec[j] * 3, vec[k] * 5));
            if(vec[pos] == vec[i] * 2) ++i;
            if(vec[pos] == vec[j] * 3) ++j;
            if(vec[pos] == vec[k] * 5) ++k;
        }
        return vec[index - 1];
    }

    //和为S的两个数字
    vector<int> FindNumbersWithSum(vector<int> array,int sum) {
        vector<int> result;
        if(array.size() < 2) return result;
        map<int, int> myMap;
        int multi = INT_MAX;
        for(int i = 0; i < array.size(); ++i) {
            if(myMap[sum - array[i]] >= 1 && array[i] * (sum - array[i]) <= multi) {
                result.resize(2);
                result[1] = array[i];
                result[0] = sum - array[i];
            }
            myMap[array[i]] = 1;
        }
        return result;
    }

    //扑克牌顺子
    bool IsContinuous( vector<int> numbers ) {
        //O(nlog n)排序
        if(numbers.empty()) return false;
        if(numbers.size() == 1) return true;
        sort(numbers.begin(), numbers.end());
        int zeroCount = 0, distanceCount = 0;
        for(int i = 0; i < numbers.size(); ++i) {
            if(numbers[i] == 0) ++zeroCount;
            else {
                if(i + 1 < numbers.size()) {
                    if(numbers[i + 1] == numbers[i]) return false;
                    else distanceCount += (numbers[i + 1] - numbers[i] - 1);
                }
            }
        }
        return distanceCount <= zeroCount;
    }


    //数据流中的中位数
    priority_queue<int> priQue1;    //最小优先队列
    priority_queue<int, vector<int>, greater<int>> priQue2;  //最大优先队列
    int insertCount = 0;
    //必须满足：最大优先队列的top元素小于等于最小优先队列top元素
    void Insert(int num) {
        ++insertCount;
        if(insertCount % 2 == 0) {
            priQue1.push(num);
            priQue2.push(priQue1.top());
            priQue1.pop();
        }
        else {
            priQue2.push(num);
            priQue1.push(priQue2.top());
            priQue2.pop();
        }
    }
    double GetMedian() {
        if(priQue1.size() == priQue2.size()) return (priQue1.top() + priQue2.top()) / 2.0;
        else return priQue1.size() > priQue2.size() ? priQue1.top() : priQue2.top();
    }

    //最小的k个数
    vector<int> GetLeastNumbers_Solution(vector<int> input, int k) {
        int len = input.size();
        if(k > len) return {};
        for(int i = 0; i < k; ++i) {
            make_heap(input.begin(), input.end() - i, greater<int>());  //最小堆
            std::swap(input[0], input[len - i - 1]);
        }
        return vector<int>(input.end() - k, input.end());
    }

/************************************************************/
/*----------------------------字符串-------------------------*/
/************************************************************/

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

    //正则表达式匹配
    bool match(char* str, char* pattern) {
        //直接使用cpp11的正则表达式
        //动态规划或者递归脑子有点晕
        if(!str && !pattern) return false;
        regex re(pattern);
        return regex_match(str, re);
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


    //字符流中第一个不重复的字符
    list<char> dataList;
    map<char, int> countMap;
    void Insert(char ch) {
        //Insert one char from stringstream
        if(dataList.empty() || countMap[ch] == 0) {
            dataList.insert(dataList.end(), ch);
            countMap[ch] = 1;
        }
        else if(countMap[ch] == 1)
            dataList.remove(ch);
    }
    char FirstAppearingOnce() {
        //return the first appearence once char in current stringstream
        return dataList.empty() ? '#' : dataList.front();
    }

/**********************************************************/
/*----------------------Tree----------------------------*/
/**********************************************************/

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
    void FindPath(vector<vector<int> >&vvec, TreeNode* root, int expNum, vector<int> temp) {
        temp.push_back(root->val);
        if(!root->left && !root->right) {
            if(root->val == expNum) {
                vvec.push_back(temp);
                return;
            }
            return;
        }
        if(root->left) {
            FindPath(vvec, root->left, expNum - root->val, temp);
        }
        if(root->right) {
            FindPath(vvec, root->right, expNum - root->val, temp);
        }
        temp.pop_back();
    }

    vector<vector<int> > FindPath(TreeNode* root,int expectNumber) {
        vector<vector<int> > vvec;
        vector<int> vec;
        if(root) FindPath(vvec, root, expectNumber, vec);
        return vvec;
    }

    //二叉搜索树与双向链表
    /*
    //迭代版 不知道哪里出错
    void goLeft(TreeNode* root, stack<TreeNode*>& sta) {
        while(root) {
            sta.push(root);
            root = root->left;
        }
    }
    TreeNode* Convert(TreeNode* pRootOfTree) {
        if(!pRootOfTree) return pRootOfTree;
        stack<TreeNode*> sta;
        TreeNode* root = new TreeNode(-1), *temp = root; //哨兵节点,->right指向最左侧链最深节点
        while(true) {
            goLeft(pRootOfTree, sta);
            if(sta.empty()) break;
            TreeNode* nextRoot = sta.top();
            sta.pop();
            root->right = nextRoot;
            nextRoot->left = root;
            pRootOfTree = pRootOfTree->right;
            root = nextRoot;
        }
        return temp->right;
    }*/
    //递归版
    void recurConvert(TreeNode* root, TreeNode*& pre) {
        if(!root) return;
        recurConvert(root->left, pre);
        root->left = pre;
        if(pre) pre->right = root;
        pre = root;
        recurConvert(root->right, pre);
    }
    TreeNode* Convert(TreeNode* pRootOfTree) {
        if(!pRootOfTree) return pRootOfTree;
        TreeNode* pre = 0;
        recurConvert(pRootOfTree, pre);
        TreeNode* res = pRootOfTree;
        while(res ->left) res = res ->left;
        return res;
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
        int left, right;    //记录左右子树的高度
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

    //二叉树的下一个结点
    TreeLinkNode* GetNext(TreeLinkNode* pNode) {
        if(!pNode) return pNode;
        if(pNode->right) {
            //节点有右孩子，右孩子的最左节点即为下一个节点
            pNode = pNode->right;
            while(pNode->left) {
                pNode = pNode->left;
            }
            return pNode;
        }
        else {
            //没有右孩子
            TreeLinkNode* parent = pNode->next;
            if(parent) {
                //该节点是父节点的左孩子，父节点即为下一个节点
                if(parent->left == pNode) {
                    return parent;
                }
                //该节点是父节点的右孩子，沿父节点链上升
                else {
                    while(parent->next && parent == parent->next->right)
                        parent = parent->next;
                    return parent->next;
                }
            }
            else return NULL;
        }
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
    vector<vector<int> > Print2(TreeNode* pRoot) {
        int h = TreeDepth(pRoot);
        if(pRoot == NULL) return {};
        vector<int> v{};
        vector<vector<int>> vec(h, v);
        int index = 0;
        recursion(pRoot, vec, index);
        return vec;
    }

    //按之字形顺序打印二叉树
    vector<vector<int> > Print(TreeNode* pRoot) {
        vector<vector<int> > vvec = {};
        if(!pRoot) return vvec;
        stack<TreeNode*> oddSta;//设置两个栈存放不同层的树节点
        stack<TreeNode*> evenSta;
        oddSta.push(pRoot);
        while(!oddSta.empty() || !evenSta.empty()) {
            vector<int> vec = {};
            if(oddSta.empty()) {
                //栈1空，栈2的元素出栈并放入vec,右左孩子依次入栈1
                while(!evenSta.empty()) {
                    TreeNode* node = evenSta.top();
                    evenSta.pop();
                    vec.push_back(node->val);
                    if(node->right) oddSta.push(node->right);
                    if(node->left) oddSta.push(node->left);
                }
            }
            else {
                //栈2空，栈2的元素出栈并放入vec，左右孩子依次入栈2
                while(!oddSta.empty()) {
                    TreeNode* node = oddSta.top();
                    oddSta.pop();
                    vec.push_back(node->val);
                    if(node->left) evenSta.push(node->left);
                    if(node->right) evenSta.push(node->right);
                }
            }
            vvec.push_back(vec);
        }
        return vvec;
    }

    //二叉搜索树的第k个结点
    void KthNode(TreeNode* pRoot, vector<TreeNode*>& TN) {
        if(!pRoot) return;
        else {
            KthNode(pRoot->left, TN);
            TN.push_back(pRoot);
            KthNode(pRoot->right, TN);
        }
    }
    TreeNode* KthNode(TreeNode* pRoot, int k) {
        //中序遍历即有序
        vector<TreeNode*> TN;
        KthNode(pRoot, TN);
        return (TN.size() < k || k <= 0) ? NULL : TN[k - 1];
    }

    //序列化二叉树
        //采用先序遍历，用vector存储
    void Serialize(vector<int>& sto, TreeNode *root) {
        if(!root) sto.push_back(0xffff);
        else {
            sto.push_back(root->val);
            Serialize(sto, root->left);
            Serialize(sto, root->right);
        }
    }
    char* Serialize(TreeNode *root) {
        vector<int> sto;
        Serialize(sto, root);
        int* res = new int[sto.size()];
        for(int i = 0; i < sto.size(); ++i) res[i] = sto[i];
        return (char*)res;
    }
    TreeNode* Deserialize(int*& str) {
        if(*str == 0xffff) {
            ++str;
            return NULL;
        }
        TreeNode *res = new TreeNode(*str);
        ++str;
        res->left = Deserialize(str);
        res->right = Deserialize(str);
        return res;
    }
    TreeNode* Deserialize(char *str) {
        int *p = (int *)str;
        return Deserialize(p);
    }

/****************************************************************/
/*---------------------------回溯-------------------------------*/
/****************************************************************/

    //矩阵中的路径
    bool hasPath(char* matrix, int rows, int cols, char* str) {
        if(!str || rows <=0 || cols <= 0) return false;
        bool* flag = new bool[rows * cols];
        memset(flag, 0, rows * cols);
        for(int i = 0; i < rows; ++i) {
            for(int j = 0; j < cols; ++j) {
                if(hasPath(matrix, rows, cols, str, flag, i, j, 0)) return true;
            }
        }
        delete [] flag;
        return false;
    }

    bool hasPath(char* matrix, int rows, int cols, char* str, bool* flag, int x, int y, int index) {
        int m_index = x * cols + y;
        if(x < 0 || x >= rows || y < 0 || y >= cols || flag[m_index] || matrix[m_index] != str[index])
            //位置越界或者该位置已经访问或者字符不匹配
            return false;
        if(str[index + 1] == '\0') return true; //字符串到末尾
        flag[m_index] = true;
        if(hasPath(matrix, rows, cols, str, flag, x - 1, y, index + 1) ||
           hasPath(matrix, rows, cols, str, flag, x, y - 1, index + 1) ||
           hasPath(matrix, rows, cols, str, flag, x + 1, y, index + 1) ||
           hasPath(matrix, rows, cols, str, flag, x, y + 1, index + 1)) return true;
        flag[m_index] = false;
        return false;
    }

    //机器人的运动范围
    bool compVal(int x, int y, int threshold) {
        int result = 0;
        while(x) {
            result += x % 10;
            x /= 10;
        }
        while(y) {
            result += y % 10;
            y /= 10;
        }
        return result <= threshold;
    }

    int findById(vector<int> id, int p) {
        if(p == -1) return -1;
        else if(p == id[p]) return p;
        else return findById(id, id[p]);
    }

    void unionById(vector<int>& id, int p, int q) {
        int i = findById(id, p), j = findById(id, q);
        if(i == j) return;
        i <= j ? id[q] = i : id[p] = j;
    }

    int movingCount(int threshold, int rows, int cols) {
        vector<int> id(rows * cols);    //id为二维数组按行拉直
        int count = 0;
        for(int i = 0; i < rows; ++i) {
            for(int j = 0; j < cols; ++j) {
                //将不满足坐标和的id值设为-1，否则设为其下标
                id[i * cols + j] = (compVal(i, j, threshold) ? i * cols + j : -1);
            }
        }
        for(int i = 0; i < rows; ++i) {
            for(int j = 0; j < cols; ++j) {
                //union操作
                if(i + 1 < rows && compVal(i, j, threshold) && compVal(i + 1, j, threshold))
                    unionById(id, i * cols + j, (i + 1) * cols + j);
                if(j + 1 < cols && compVal(i, j, threshold) && compVal(i, j + 1, threshold))
                    unionById(id, i * cols + j, i * cols + j + 1);
            }
        }
        for(int i = 0; i < rows * cols; ++i) {
            //id为0的坐标即满足条件，能够机器人到达
            if(findById(id, i) == 0)
                ++count;
        }
        return count;
    }


/***************************************************************/
/*----------------------------栈和队列--------------------------*/
/****************************************************************/

    //滑动窗口的最大值
    vector<int> maxInWindows(const vector<int>& num, unsigned int size) {
        //使用队列
        if(num.empty() || num.size() < size || !size)
            //处理特殊情况：数组为空或者窗口长度大于数组长度或者窗口长度为空
            return {};
        deque<int> deq;
        vector<int> re;
        for(int i = 0; i < num.size(); ++i) {
            while(!deq.empty() && num[deq.back()] <= num[i]) deq.pop_back();
            while(!deq.empty() && i - deq.front() + 1 > size) deq.pop_front();
            deq.push_back(i);
            if(i + 1 >= size) re.push_back(num[deq.front()]);
        }
        return re;
    }

    //包含min函数的栈
    stack<int> dataStack, minStack;
    void push(int value) {
        dataStack.push(value);
        if(minStack.empty() || minStack.top() >= value) {
            minStack.push(value);
        }
    }
    void pop() {
        if(dataStack.top() == minStack.top()) {
            minStack.pop();
        }
        dataStack.pop();
    }
    int top() {
        return dataStack.top();
    }
    int min() {
        return minStack.top();
    }

    //栈的压入、弹出序列
    bool IsPopOrder(vector<int> pushV,vector<int> popV) {
        if(pushV.empty() || pushV.size() != popV.size()) return false;
        stack<int> sta;
        for(int i = 0, j = 0; i < pushV.size(); ++i) {
            sta.push(pushV[i]);
            while(j < popV.size() && sta.top() == popV[j]) {
                sta.pop();
                ++j;
            }
        }
        return sta.empty();
    }

/*****************************************************************/
/*-----------------------------链表-------------------------------*/
/******************************************************************/

    //从尾到头打印链表
    /*递归版本
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
    }*/
    vector<int> printListFromTailToHead(ListNode* head) {
        //非递归版本
        vector<int> vec;
        stack<int> sta;
        ListNode* temp = head;
        while(temp != NULL) {
            sta.push(temp->val);
            temp = temp->next;
        }
        while(!sta.empty()) {
            vec.push_back(sta.top());
            sta.pop();
        }
        return vec;
    }

    //链表中倒数第k个结点
    ListNode* FindKthToTail(ListNode* pListHead, unsigned int k) {
        //一个链表队{first, last}的距离为k,当last到达末位时，first即为倒数第k个结点
        ListNode* first = pListHead, *last = pListHead;
        while(k) {
            if(!last) break;
            last = last->next;
            --k;
        }
        if(k != 0) return NULL; //链表长度小于k
        while(last) {
            last = last->next;
            first = first->next;
        }
        return first;
    }

    //反转链表
    ListNode* ReverseList(ListNode* pHead) {
        //递归版；
        if(pHead == NULL || pHead->next == NULL)
            return pHead;
        ListNode *pReverseNode = ReverseList(pHead->next);
        //反转链表过程
        pHead->next->next = pHead;
        pHead->next = NULL;
        return pReverseNode;
    }
    /*
    ListNode* ReverseList(ListNode* pHead) {
        //非递归版
        if(pHead == NULL || pHead->next == NULL)
            return pHead;
        ListNode* pNode=pHead;//当前指针
        ListNode* pReverseHead=NULL;//新链表的头指针
        ListNode* pPrev=NULL;//当前指针的前一个结点

        while(pNode != NULL){//当前结点不为空时才执行
            ListNode* pNext=pNode->next;//链断开之前一定要保存断开位置后边的结点
            if(pNext==NULL)//当pNext为空时，说明当前结点为尾节点
                pReverseHead=pNode;
            pNode->next=pPrev;//指针反转
            pPrev=pNode;
            pNode=pNext;
        }
        return pReverseHead;
    }*/

    //合并两个排序的链表
    ListNode* Merge(ListNode* pHead1, ListNode* pHead2) {
        ListNode* result = new ListNode(0); //设定一个头节点,该节点之后开始合并
        ListNode* temp = result;    //只需返回temp节点的next
        while(pHead1 && pHead2) {
            if(pHead1->val <= pHead2->val) {
                result->next = pHead1;
                pHead1 = pHead1->next;
            }
            else {
                result->next = pHead2;
                pHead2 = pHead2->next;
            }
            result = result->next;
        }
        result->next = (pHead1 ? pHead1 : pHead2);
        return temp->next;
    }

    //复杂链表的复制
    RandomListNode* Clone(RandomListNode* pHead) {
        if(!pHead) return pHead;
        RandomListNode *cloneNode = pHead;
        //复制每个节点连接在其后面
        while(cloneNode) {
            RandomListNode* Node = new RandomListNode(cloneNode->label);
            //这个步骤就是将Node插入到cloneNode和cloneNode->next之间
            Node->next = cloneNode->next;
            cloneNode->next = Node;
            cloneNode = Node->next;
        }
        cloneNode = pHead;
        while(cloneNode) {
            //对指向random进行复制
            if(cloneNode->random)
                cloneNode->next->random = cloneNode->random->next;
            cloneNode = cloneNode->next->next;
        }
        //再进行拆分
        cloneNode = pHead->next;
        while(pHead->next) {
            RandomListNode* temp = pHead->next;
            pHead->next = temp->next;
            //temp->next = pHead->next->next;
            //pHead = pHead->next;
            pHead = temp;
        }
        return cloneNode;
    }

    //两个链表的第一个公共结点
    ListNode* FindFirstCommonNode( ListNode* pHead1, ListNode* pHead2) {
        ListNode *p1 = pHead1, *p2 = pHead2;
        while(p1 != p2) {
            //实际最多跑两趟，长度相同时第一趟就可以直接得到公共点
            //长度不同时，第二趟由于由于互换节点，长度差没有了
            p1 = p1 ? p1->next : pHead2;
            p2 = p2 ? p2->next : pHead1;
        }
        return p1;
    }

    //链表中环的入口结点
    ListNode* EntryNodeOfLoop(ListNode* pHead) {
        //使用双指针p1,p2; p1每次前进1个单位,p2每次前进2个单位
        //有环必然相遇，相遇之后将p2置为原点,再同时按步长1前进，再次相遇必然是环的入口
        ListNode* p1 = pHead, *p2 = pHead;
        while(p1 && p2) {
            p1 = p1->next;
            if(p2->next) p2 = p2->next->next;
            else return nullptr;
            if(p1 == p2) break;
        }
        if(!p1 || !p2) return nullptr;
        p2 = pHead;
        while(p1 != p2) {
            p1 = p1->next;
            p2 = p2->next;
        }
        return p1;
    }

    //删除链表中重复的结点
    ListNode* deleteDuplication(ListNode* pHead) {
        if(!pHead || !pHead->next) return pHead;
        ListNode* current;
        if(pHead->next->val == pHead->val) {
            current = pHead->next->next;
            while(current && current->val == pHead->val)
                current = current->next;
            return deleteDuplication(current);
        }
        else {
            current = pHead->next;
            pHead->next = deleteDuplication(current);
            return pHead;
        }
    }

/******************************************************/
/*--------------------math数学-------------------------*/
/******************************************************/

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

    //数值的整数次方
    /*递归版本
    double Power(double base, int exponent) {
        if(exponent == 0) return 1;
        else if(exponent < 0)return Power(1 / base, -exponent);
        else {
            double temp = Power(base, exponent/2) * Power(base, exponent/2);
            return temp * temp * (exponent % 2 ? base : 1);
        }
    }*/
    //位运算版本
    double Power(double base, int exponent) {
        if(exponent < 0) return Power(1 / base, -exponent);
        double re = 1;
        while(exponent){
            if(exponent & 1) re *= base;
            base *= base;
            exponent >>= 1;
        }
        return re;
    }

    //孩子们的游戏(圆圈中最后剩下的数)
    int LastRemaining_Solution(int n, int m) {
        //约瑟夫环问题 f(n, m)
        //递推关系为：f(1, m) = 0, f(n, m) = (f(n - 1, m) + m) % n;
        if(n < 1 || m < 1) return -1;
        int last = 0;
        for(int i = 2; i < n; ++i) {
            last = (last + m) % i;
        }
        return last;
    }

};

#endif // PTOFFER_H
