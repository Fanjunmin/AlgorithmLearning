#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include <math.h>
#include <stack>
#include <set>


using namespace std;
 //* Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Function{
public:
    template <typename T, int N>
    void print(const T (&p)[N], std::ostream &os = cout){
        for(int i = 0; i < N; ++i)
            os << p[i] << " ";
    }

    template <typename T>
    void print(vector<T> &vt, std::ostream &os = cout){
        for(auto x : vt)
            os << x << " ";
    }

//1. Two Sum
    vector<int> twoSum(vector<int>& nums, int target) {
        map<int, int> myMap;//key:the value of vector;value:the index of vector
        for(int i = 0; i != nums.size(); ++i){
            auto iter = myMap.find(target - nums[i]);
            if(iter == myMap.end()){
                //add the element which was not found in myMap;
                myMap[nums[i]] = i;
            }
            else{
                //return the two right element;
                return {iter->second, i};
            }
        }
    }

//2. Add Two Numbers
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        int carry_bit = 0;
        ListNode l(0), *p = &l;
        while(l1 || l2 || carry_bit){ //节点非空或者要进位
            int sum = (l1 ? l1->val : 0) + (l2 ? l2->val : 0) + carry_bit;
            if(sum >= 10){
                carry_bit = 1;
                sum -= 10;
            }
            else carry_bit = 0;
            p->next = new ListNode(sum);
            p = p->next;
            l1 = l1 ? l1->next : l1;
            l2 = l2 ? l2->next : l2;
        }
        return l.next;
    }

//3. Longest Substring Without Repeating Characters
    int lengthOfLongestSubstring(string s){
        if(s.size() == 0) return 0;
        //i和j分别表示首位和末位，s[i,j] is substring without repeating characters
        int maxLen = 0, i = 0;
        vector<int> vec; //存储不同的substring的长度
        map<char, int> myMap;
        for(int j = 0; j != s.size(); ++j){
            if(myMap.count(s[j]) && myMap.find(s[j])->second >= i){
                //如果范围[i,j)存在该字符，且坐标为k
                i = myMap.find(s[j])->second + 1; //更新i为k+1
            }
            maxLen = max(maxLen, j + 1 - i); //更新maxLen
            myMap[s[j]] = j;//无论是否存在，都要更新map
        }
        return maxLen;
    }

//4. Median of Two Sorted Arrays
    double findKth(vector<int>::iterator iter1, int m, vector<int>::iterator iter2, int n, int k){
        //function findKth 找到第k小的数 复杂度O(logk)
        //m=nums1.size(), n = nums2.size()，假定m<=n
        if(m > n) return findKth(iter2, n, iter1, m, k);
        if(m == 0) return *(iter2+k-1); //num1为空时
        if(k == 1) return min(*iter1, *iter2); //k=1时
        int pa = min(k/2, m), pb = k - pa;
        if(*(iter1+pa-1) < *(iter2+pb-1))
            //nums1前pa个元素必然小于第k小的元素，可以直接忽略
            return findKth(iter1+pa, m-pa, iter2, n, k-pa);
        else if(*(iter1+pa-1) > *(iter2+pb-1))
            //nums2前pb个元素必然小于第k小的元素，可以直接忽略
            return findKth(iter1, m,iter2+pb, n-pb ,k-pb);
        else
            //直接找到第k小的元素
            return *(iter1+pa-1);
    }

    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        /*
        //STL中的merge函数,线性时间
        int length = nums1.size() + nums2.size();
        vector<int> merge_nums(length);
        merge(nums1.begin(), nums1.end(), nums2.begin(), nums2.end(), merge_nums.begin());
        if(length % 2)
            return merge_nums[length / 2];
        else
            return (merge_nums[length/2]+merge_nums[length/2-1])/2.0;
        */
        //findKth
        vector<int>::iterator iter1 = nums1.begin(), iter2= nums2.begin();
        int len1 = nums1.size(), len2 = nums2.size();
        int length = len1 + len2;
        if(length % 2)
            return findKth(iter1, len1, iter2, len2, length/2+1);
        else
            return (findKth(iter1, len1, iter2, len2, length/2+1)
                    +findKth(iter1, len1, iter2, len2, length/2))/2.0;
    }

//5. Longest Palindromic Substring
    string longestPalindrome(string s) {
        //时间复杂度O(n^2) 空间复杂度O(n^2)
        int len = s.size();
        if(len <= 1) return s;
        else{
            int dp[len][len]; //存储状态
            for(int i = 0; i < len; ++i){
                for(int j = 0; j < len; ++j){
                    dp[i][j] = 0;
                }
            }
            int Max = 0, startIndex = 0, endIndex = 0; //存储最大长度和下标
            /*状态示意图
               1 0 0 0 0 0 0 ...
                 1 0 0 0 0 0 ...
                   1 2 0 0 0 ...
                     1 0 0 0 ...
                       1 2 0 ...
                         1 0 ...
                           ...
                           ...
            */
            for(int i = 0; i < len; ++i){
                dp[i][i] = 1; //对角线一定为1
                if(i-1 >= 0 && s[i] == s[i-1]) dp[i-1][i] = 2; //相邻为2或0
            }
            for(int k = 2; k < len; ++k){ //沿着第三条对角线开始（斜向）遍历
                for(int i = 0; i < len; ++i){
                    int j = i + k;
                    if(s[i] == s[j] && j < len && dp[i+1][j-1]){
                        dp[i][j] = dp[i+1][j-1] + 2;//状态转移方程
                    }
                }
            }
            for(int i = 0; i < len; ++i){
                for(int j = i; j < len; ++j){
                    if(dp[i][j] >= Max){ //更新长度和下标
                        startIndex = i;
                        endIndex = j;
                        Max = dp[i][j];
                    }
                }
            }
            return s.substr(startIndex, endIndex - startIndex + 1);
        }
    }

//6. ZigZag Conversion
    string convert(string s, int numRows){
        if(numRows == 1) return s; //仅有一行时，直接输出
        vector<string> vs{numRows,""};
        string S = "";
        for(int i = 0; i < s.size(); ++i){
            int re = i % (2 * numRows - 2); //每(2*numRows-2)个字符循环
            if(re >= numRows - 1) re = 2*(numRows - 1) - re; //对字符分类
            vs[re] += s[i];
        }
        for(auto x : vs) S += x;
        return S;
    }

//7. Reverse Integer
    int reverse(int x) {
        long long res = 0;
        while(x){ //reverse过程
            res = res*10 + x%10;
            x /= 10;
        }
        return (res<INT_MIN || res>INT_MAX) ? 0 : res;
    }

//8.String to Integer (atoi)
    int myAtoi(string str) {
        int index = 0; //记录第一个非空格字符的位置
        long sum = 0; //记录数字
        bool negetive = false; //记录正负号
        for(int i = 0; i < str.size(); ++i){
            if(str[i] != ' '){
                index = i;
                break;
            }
        }
        if(str[index] == '+' || str[index] == '-' || (str[index] <= '9' && str[index] >= '0')){
            negetive = str[index] == '-' ? true : false; //正负号处理
            if(str[index] == '+' || str[index] == '-') ++index; //是否有正负号处理
            for(int j = index; j < str.size(); ++j){
                if(str[j] <= '9' && str[j] >= '0'){
                    sum = sum * 10 + static_cast<int>(str[j] - 48);
                    if(sum > INT_MAX || sum < INT_MIN) break;
                }
                else break;
            }
            sum = negetive ? -sum : sum;
            if(sum > INT_MAX) return INT_MAX;
            if(sum < INT_MIN) return INT_MIN;
            return sum;
        }
        return 0;
    }

//9. Palindrome Number
    bool isPalindrome(int x) {
        if(x < 0) return false;
        else{
            long reverseX = 0;
            int y = x;
            while(x){ //翻转整数
                reverseX = reverseX * 10 + x % 10;
                x /= 10;
            }
            return reverseX == y;
        }
    }

//10. Regular Expression Matching
    bool isMatch(string s, string p) {

    }

//11. Container With Most Water
    int maxArea(vector<int>& height) {
        auto volume = [height](int i, int j)->int{return min(height[i], height[j]) * (j - i);}; //体积函数
        int leftIndex = 0, rightIndex = height.size();
        int v = volume(0, height.size()-1); //初始体积
        //cout << v << endl;
        while(rightIndex > leftIndex){
            height[leftIndex] > height[rightIndex] ? --rightIndex : ++leftIndex; //从两段向中间移动
            v = max(v, volume(leftIndex, rightIndex)); //更新体积
        }
        return v;
    }

//12. Integer to Roman
    /*
    I(1), X(10), C(100), M(1000), V(5), L(50), D(500)
    1.相同的数字连写,所表示的数等于这些数字相加得到的数,如 Ⅲ=3;
    2.小的数字在大的数字的右边,所表示的数等于这些数字相加得到的数,如 Ⅷ=8、Ⅻ=12;
    3.小的数字(限于 Ⅰ、X 和 C)在大的数字的左边，所表示的数等于大数减小数得到的数,如 Ⅳ=4、Ⅸ=9；
    */
    int power(int p, int n){
        int k = 1;
        while(n--)
            k *= p;
        return k;
    }

    string intToRoman(int num) {
        map<int, string> myMap{{0, ""}, {1, "I"}, {10, "X"}, {100, "C"}, {1000, "M"},
            {2000, "MM"}, {3000, "MMM"}, {4, "IV"},{6, "VI"},{9, "IX"}, {90, "XC"},
            {900, "CM"}, {40, "XL"},{60, "LX"},{400, "CD"},{600, "DC"}};
        vector<int> nums{2,3,5,7,8};
        for(auto num : nums){
            if(num < 4){
                myMap[num] = string(num, 'I');
                myMap[num * 10] = string(num, 'X');
                myMap[num * 100] = string(num, 'C');
            }
            else{
                myMap[num] = "V" + string(num - 5, 'I');
                myMap[num * 10] = "L" + string(num - 5, 'X');
                myMap[num * 100] = "D" + string(num - 5, 'C');

            }
        } //以上建表
        string s = "";
        for(int i = 3; i >= 0; --i){
            int a = num / power(10, i);
            s += myMap[a * power(10, i)];
            num -= a * power(10, i);
        }
        return s;
    }

//13. Roman to Integer
    int romanToInt(string s) {
        map<int, string> myMap{{0, " "}, {1, "I"}, {10, "X"}, {100, "C"}, {1000, "M"},
            {2000, "MM"}, {3000, "MMM"}, {4, "IV"},{6, "VI"},{9, "IX"}, {90, "XC"},
            {900, "CM"}, {40, "XL"},{60, "LX"},{400, "CD"},{600, "DC"}};
        vector<int> nums{2,3,5,7,8}; //小的变动{0, ""}->{0, " "}
        for(auto num : nums){
            if(num < 4){
                myMap[num] = string(num, 'I');
                myMap[num * 10] = string(num, 'X');
                myMap[num * 100] = string(num, 'C');
            }
            else{
                myMap[num] = "V" + string(num - 5, 'I');
                myMap[num * 10] = "L" + string(num - 5, 'X');
                myMap[num * 100] = "D" + string(num - 5, 'C');

            }
        } //以上建表
        map<string, int> Map;
        for(auto iter = myMap.begin(); iter != myMap.end(); ++iter)
            Map[iter->second] = iter->first; //key, value反过来
        s += " "; //尾部处理
        int sum = 0, dis = 0;
        if(s.size() <= 2) return Map[s];
        for(int i = 2; i < s.size();){
            //遍历字符串，依次在Map中搜索3,2,1个字符
            dis = static_cast<int>(s.size() - i);
            if(Map.count(s.substr(i-2, 3))){
                sum += Map[s.substr(i-2, 3)];
                dis = min(3, dis);
            }
            else if(Map.count(s.substr(i-2, 2))){
                sum += Map[s.substr(i-2, 2)];
                dis = min(2, dis);
            }
            else{
                sum += Map[s.substr(i-2, 1)];
                dis = min(1, dis);
            }
            i += dis;
        }
        return sum;
    }

//14. Longest Common Prefix
    string common_string(string &s1, string &s2){
        //求两个字符串的两个最长公共前缀
        string s = "";
        for(int i = 0; i < min(s1.size(), s2.size()); ++i){
            if(s1[i] == s2[i]) s += string(1, s1[i]);
            else break;
        }
        return s;
    }

    string longestCommonPrefix(vector<string>& strs) {
        //LCP(s1,s2,...,sn) = LCP(LCP((s1,s2),s3)...,Sn)
        string s = "";
        if(strs.size() == 0) return s;
        s = strs[0];
        for(int i = 1; i != strs.size(); ++i){
            s = common_string(s, strs[i]);
        }
        return s;
    }

//15. 3Sum
    set<vector<int>> twoSum(vector<int>::iterator iter1, vector<int>::iterator iter2, int target){
        //twosum:给定target, 返回{target,a,b}的vector组成的set,其中a+b=target
        //利用HashMap,复杂度O(n);
        set<vector<int>> svi{};
        if(iter2 - iter1 < 2) return svi;
        else{
            set<int> mySet{};
            for(auto iter = iter1; iter != iter2; ++iter){
                auto it = mySet.find(target - *iter);
                if(it == mySet.end()) mySet.insert(*iter);
                else svi.insert({-target, target - *iter, *iter});
            }
            return svi;
        }
    }

    vector<vector<int>> threeSum(vector<int>& nums) {
        //3sum 复杂度O(n^2)
        sort(nums.begin(), nums.end()); //排序
        vector<vector<int>> vvi{};
        set<vector<int>> svi{};
        if(nums.size() < 3) return vvi;
        else{
            for(auto iter = nums.begin(); iter != nums.end();){
                auto vi = twoSum(iter + 1, nums.end(), -(*iter));
                for(auto it = vi.begin(); it != vi.end(); ++it){
                    svi.insert(*it);
                }
                //重复元素只需考虑第一个
                auto it = find(nums.rbegin(), nums.rend(), *iter); //查找最后一个相同的元素
                if(it == nums.rend()) ++iter;
                else iter = it.base(); //更新迭代器
            }
            copy(svi.begin(), svi.end(), back_inserter(vvi));
            return vvi;
        }
    }

//16. 3Sum Closest
    int closest(vector<int>::iterator iter1, vector<int>::iterator iter2, int target){
        //closest 找到3个数的和与target的距离最小
        //两个迭代器依次从头部和尾部向中间移动
        auto iter = iter1; //初始迭代器
        int posi_error = INT_MAX, nege_error = INT_MIN, sum;//sum与target的差值
        ++iter1; //头部迭代器
        --iter2; //尾部迭代器
        while(iter2 > iter1){
            sum = *iter + *iter1 + *iter2;
            if(sum == target) return sum;
            else if(sum > target){
                --iter2;//尾部迭代器向前移
                if(sum - target <= posi_error) posi_error = sum - target;//更新差值
            }
            else{
                ++iter1;//头部迭代器向后移
                if(sum - target >= nege_error) nege_error = sum - target;//更新差值
            }
        }
        //cout << posi_error << ends << nege_error << ends << sum << endl;
        if(posi_error == INT_MAX) return target + nege_error;
        else if(nege_error == INT_MIN) return target + posi_error;
        else{
            return abs(nege_error) <= abs(posi_error) ? target + nege_error : target + posi_error;
        }
    }

    int threeSumClosest(vector<int>& nums, int target) {
        sort(nums.begin(), nums.end());
        int m = INT_MAX, t; //m:差值
        for(auto iter = nums.begin(); iter != nums.end() - 2; ++iter){
            int sum = closest(iter, nums.end(), target);
            //cout << sum << endl;
            if(sum == target) return target;
            if(abs(sum - target) <= m){
                t = sum;
                m = abs(sum - target);
            }
        }
        return t;
    }

//17. Letter Combinations of a Phone Number
    void backTrack(vector<string> &vs, string s, int index, string digits){
        //回溯法
        map<char, string> myMap{{'2', "abc"}, {'3', "def"}, {'4', "ghi"}, {'5', "jkl"},
            {'6', "mno"}, {'7', "pqrs"}, {'8', "tuv"}, {'9', "wxyz"}};
        if(index == digits.size()){
            vs.push_back(s);
        }
        else{
            string S = myMap[digits[index]];
            for(int i = 0; i != S.size(); ++i){
                string s_replace = s;
                s_replace += S[i];
                backTrack(vs, s_replace, index + 1, digits);
            }
        }
    }

    vector<string> letterCombinations(string digits) {
        vector<string> sv{};
        if(digits.size() == 0) return sv;
        string s{};
        int index = 0;
        backTrack(sv, s, index, digits);
        return sv;
    }

//18. 4sum
    vector<vector<int>> fourSum(vector<int>& nums, int target) {

    }

//19. Remove Nth Node From End of List
    int length(ListNode* head){
        //the length of ListNode
        int len = 1;
        while(head = head->next) ++len;
        return len;
    }

    ListNode* removeNthFromEnd(ListNode* head, int n) {
        int len = length(head), c = 0;
        ListNode l(0), *p = &l;
        while(head){
            if(c == len - n){
                head = head->next;
                if(head){
                    p->next = new ListNode(head->val);
                    p = p->next;
                }
            }
            else{
                p->next = new ListNode(head->val);
                p = p->next;
                head = head->next;
                ++c;
            }
        }
        return l.next;
    }

//20. Valid Parentheses
    bool isValid(string s) {
        stack<char> cs;
        for(auto x : s){
            if(x == ')' && (cs.size() == 0 || cs.top() != '(')) return false;
            if(x == ']' && (cs.size() == 0 || cs.top() != '[')) return false;
            if(x == '}' && (cs.size() == 0 || cs.top() != '{')) return false;
            if(x == '(' || x == '[' || x == '{') cs.push(x);
            if(x == ')' || x == ']' || x == '}') cs.pop();
            cout << cs.size() << ends;
        }
        cout << endl;
        return cs.empty();
    }

//21. Merge Two Sorted Lists
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        ListNode l(0), *p = &l;
        while(l1 && l2){
            if(l1->val <= l2->val){
                p->next = l1;
                l1 = l1->next;
            }
            else{
                p->next = l2;
                l2 = l2->next;
            }
            p = p->next;
        }
        if(l1) p->next = l1;
        if(l2) p->next = l2;
        return l.next;
    }

//22. Generate Parentheses
    void genbackTrack(vector<string> &vs, string s, int left, int right){
        if(!left && !right){
            vs.push_back(s);
        }
        else{
            if(left <= right && left) genbackTrack(vs, s + "(", left - 1, right);
            if(left <= right && right) genbackTrack(vs, s + ")", left, right - 1);
        }

    }

    vector<string> generateParenthesis(int n) {
        //(2n)!/(n!*(n+1)!)
        string s = "";
        vector<string> vs{};
        int left = n, right = n;
        genbackTrack(vs, s, left, right);
        return vs;
    }

//23. Merge k Sorted Lists
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        ListNode *l = nullptr;
        for(int i = 0; i != lists.size(); ++i){
            l = mergeTwoLists(l, lists[i]);
        }
        return l;
    }

//24. Swap Nodes in Pairs
    ListNode* swapPairs(ListNode* head) {
        int len = length(head);
        if(len < 2) return head;
        else{

        }

    }

//26. Remove Duplicates from Sorted Array
    int removeDuplicates(vector<int>& nums) {
        if(nums.size() == 0) return 0;
        int i = 0, j = 0;
        while(++j < nums.size())
            if(nums[j] != nums[i]) nums[++i] = nums[j];
        return i+1;
    }

//27. Remove Element
    int removeElement(vector<int>& nums, int val) {
        int index = 0;
        for(int i = 0; i != nums.size(); ++i){
            if(nums[i] != val){
                nums[index] = nums[i];
                ++index;
            }
        }
        return index;
    }

//28. Implement strStr()
//KMP
    int next(string needle){
        int len = needle.size();
        vector<int> iv(len - 1, 0);
        for(int i = 1; i != len; ++i){
            string s1(needle, 0, i), s2(needle, len - i,i);
            iv[i] = s1 == s2 ? i : 0;
        }
        return *max_element(iv.begin(), iv.end());
    }

    string diff_index(string s1, string s2){
        int i = 0;
        for(; i != s2.size(); ++i){
            if(s2[i] != s1[i]) break;
        }
        return i ? s1.substr(0, i) : "";
    }

    /*
    int strStr(string haystack, string needle) {
        int len = needle.size();
        if(len == 0) return 0;
        if(len > haystack.size()) return -1;
        for(int i = 0; i < haystack.size() - len;){
            string s = haystack.substr(i, len);
            if(s == needle) return i;
            else{
                int index = diff_index(s, needle);
                int next =
            }
        }
        return -1;
    }
    */
//29. Divide Two Integers
    long long abs(long long x){
        return x < 0 ? -x : x;
    }

    int divide(int dividend, int divisor) {
        if(divisor == 0 || (dividend == INT_MIN && divisor == -1)) return INT_MAX;
        int sign = (dividend ^ divisor) < 0 ? -1 : 1;
        long long dd = abs(dividend);
        long long dr = abs(divisor);
        if(dd < dr) return 0;
        int quoient = 0;
        while(dd >= dr){
            int p = 1;
            long long temp = dr;
            while(dd >= (temp << 1)){
                temp <<= 1;
                p <<= 1;
            }
            dd -=temp;
            quoient += p;
        }
        return sign == -1 ? -quoient : quoient;
    }

//30. Substring with Concatenation of All Words
    vector<int> findSubstring(string s, vector<string>& words) {

    }

//31. Next Permutation
    void nextPermutation(vector<int>& nums) {
        //next_permutation(nums.begin(), nums.end()); //library function in STL
        int len = nums.size();
        int i = len - 2, j = len - 1, k = len;
        while(i >= 0 && nums[i] >= nums[i + 1]) --i;
        if(i == -1){
            while(j >= ++i){
                swap(nums[i], nums[j]);
                --j;
            }
        }
        else{
            for(; j > i; --j) if(nums[j] > nums[i]) break;
            for(; j > i; --j) if(nums[j] < nums[j - 1]) break;
            j == i ? swap(nums[i], nums[i + 1]) : swap(nums[i], nums[j]);
            sort(nums.begin() + i + 1, nums.end());
            //for(auto x : nums) cout << x << ends;
        }
    }

//32. Longest Valid Parentheses
    int longestValidParentheses(string s) {
        int len = s.size(), maxLen = 0;
        if(len < 2) return 0;
        stack<int> si;
        si.push(-1);
        for(int i = 0; i < len; ++i){
            cout << si.top() << ends;
            if(s[i] == '(') si.push(i);
            else{
                si.pop();
                if(si.empty()) si.push(i);
                else maxLen = max(maxLen, i - si.top());
            }
        }
        cout << endl;
        return si.empty() ? len : maxLen;

    }

//35. Search Insert Position
    int binary_search(vector<int>& nums, int lo, int hi, int target){
        if(hi == lo + 1) return target <= nums[lo] ? lo : hi;
        int mi = (lo + hi) / 2;
        return target >= nums[mi] ? binary_search(nums, mi, hi, target) : binary_search(nums, lo, mi, target);
    }

    int searchInsert(vector<int>& nums, int target) {
        return binary_search(nums, 0, nums.size(), target);
    }

//36. Valid Sudoku
    bool isValidsub(vector<char> &cv){
        //check suboard is valid
        map<char, int> myMap;
        for(auto x : cv){
            if(x != '.'){
                ++myMap[x];
                if(myMap[x] > 1) return false;
            }
        }
        return true;
    }

    bool isValidSudoku(vector<vector<char>>& board) {
        //check every row
        for(auto x : board){
            if(!isValidsub(x)) return false;
        }
        //check every column
        for(int i = 0; i < 9; ++i){
            vector<char> cv = {};
            for(int j = 0; j < 9; ++j){
                cv.push_back(board[j][i]);
            }
            if(!isValidsub(cv)) return false;
        }
        //check every suboard
        for(int i = 1; i < 9; i += 3){
            for(int j = 1; j < 9; j += 3){
                vector<char> cv = {board[i][j],board[i][j+1],board[i][j-1],
                    board[i+1][j],board[i+1][j+1],board[i+1][j-1],
                    board[i-1][j],board[i-1][j+1],board[i-1][j-1]};
                if(!isValidsub(cv)) return false;
            }
        }
        return true;
    }

//38. Count and Say
    string countAndSay(int n) {
        if(n == 0) return "";
        if(n == 1) return "1";
        string str = "11";
        while(n > 2){
            string s = "";
            int num = 1;    //count the number of duplicate numbers
            for(int i = 0; i < str.size(); ++i){
                if(i + 1 < str.size() && str[i + 1] != str[i]){
                    s += to_string(num) + to_string(static_cast<int>(str[i]) - 48); //cast to string
                    num = 1;
                }
                else if(i + 1 < str.size() && str[i + 1] == str[i]){
                    num++;
                }
                else{
                    s += to_string(num) + to_string(static_cast<int>(str[i]) - 48);
                }
            }
            --n;
            str = s;
        }
        return str;
    }

//39. Combination Sum
    void combinSum(int index, vector<vector<int>> &ivv, vector<int> iv, int target, vector<int>& candidates){
        if(target < 0 || index > candidates.size()) return;
        if(0 == target) ivv.push_back(iv);
        if(0 < target){
            for(int i = index; i < candidates.size(); ++i){
                iv.push_back(candidates[i]);
                int S = target - candidates[i];
                combinSum(i, ivv, iv, S, candidates);
                iv.pop_back();
            }
        }
    }

    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        vector<vector<int>> ivv{};
        vector<int> iv{};
        combinSum(0, ivv, iv, target, candidates);
        return ivv;
    }

//40. Combination Sum II
    void combinSum2(int index, vector<vector<int>> &ivv, vector<int> iv, int target, vector<int>& candidates){
        if(target < 0 || index > candidates.size()) return;
        if(0 == target) ivv.push_back(iv);
        if(0 < target){
            for(int i = index; i < candidates.size(); ++i){
                iv.push_back(candidates[i]);
                int S = target - candidates[i];
                combinSum(i + 1, ivv, iv, S, candidates);
                if(S < 0) iv.pop_back();
            }
        }
    }

    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        vector<vector<int>> ivv{};
        vector<int> iv{};
        combinSum2(0, ivv, iv, target, candidates);
        return ivv;
    }

//41. First Missing Positive
    int firstMissingPositive(vector<int>& nums) {
        int len = nums.size();
        for(int i = 0; i != len; ++i){
            while(nums[i] > 0 && nums[i] - 1 < len && nums[nums[i] - 1] <= nums[i])
                swap(nums[i], nums[nums[i] - 1]);
        }
        for(int i = 0; i != len; ++i){
            if(nums[i] != i + 1) return i + 1;
        }
        return len + 1;
    }

//42. Trapping Rain Water
    int trap(vector<int>& height) {
        int len = height.size();
        if(len < 3) return 0;
        int li = 0, ri = len - 1, vol = 0;
        //find the bounds index of left and right
        while(li < ri && height[li] <= height[li + 1]) ++li;
        while(li < ri && height[ri] <= height[ri - 1]) --ri;
        //
        while(li < ri){
            int lh = height[li], rh = height[ri];
            if(lh < rh){
                while(li < ri && lh >= height[++li]){
                    vol += (lh - height[li]);
                }
            }
            else{
                while(li < ri && rh >= height[--ri]){
                    vol += (rh - height[ri]);
                }
            }
        }
        return vol;
    }

//43. Multiply Strings
    string multi(string num, char ch, int index){
        //return reverse of num * ch * 10^index
        string s = string(index, '0');
        int len = num.size() - 1, carry = 0, rem = 0;
        for(int i = len; i >= 0; --i){
            int mu = (num[i] - 48) * (ch - 48) + carry;
            rem = mu % 10;
            carry = mu / 10;
            s += to_string(rem);
        }
        if(carry) s += to_string(carry);
        return s;
    }

    string addstring(string s1, string s2){
        int len1 = s1.size(), len2 = s2.size();
        int add = 0, carry = 0, rem = 0;
        string s{};
        for(int i = 0; i < max(len1, len2); ++i){
            if(i >= len1){
                add = s2[i] - 48 + carry;
                rem = add % 10;
                carry = add / 10;
            }
            else if(i >= len2){
                add = s1[i] - 48 + carry;
                rem = add % 10;
                carry = add / 10;
            }
            else{
                add = s1[i] - 48 + s2[i] - 48 + carry;
                rem = add % 10;
                carry = add / 10;
            }
            s += to_string(rem);
        }
        if(carry) s += to_string(carry);
        return s;
    }

    string multiply(string num1, string num2) {
        if(num1 == "0" || num2 == "0") return "0";
        string as = "", s;
        int len = num2.size();
        for(int i = 0; i < len; ++i){
            s = multi(num1, num2[i], len - 1 - i);
            as = addstring(as, s);
        }
        std::reverse(as.begin(), as.end());
        return as;
    }

//46. Permutations
    void getpermute(vector<vector<int>> &ivv, vector<int> &nums, vector<int> iv, int beg){
        if(iv.size() == nums.size()){
            ivv.push_back(iv);
            return;
        }
        for(int i = beg; i < nums.size(); ++i){
            iv.push_back(nums[i]);
            swap(nums[i], nums[beg]);
            getpermute(ivv, nums, iv, beg + 1);
            //reset
            iv.pop_back();
            swap(nums[i], nums[beg]);
        }
    }

    vector<vector<int>> permute(vector<int>& nums) {
        vector<vector<int>> ivv{};
        vector<int> iv{};
        int beg = 0;
        getpermute(ivv, nums, iv, beg);
        return ivv;
    }

//47. Permutations II
    /*use set and PermutationsI
    void getPermuteUnique(set<vector<int>> &isv, vector<int> &nums, vector<int> iv, int beg){
        if(iv.size() == nums.size()){
            isv.insert(iv);
            return;
        }
        for(int i = beg; i < nums.size(); ++i){
            iv.push_back(nums[i]);
            swap(nums[i], nums[beg]);
            getPermuteUnique(isv, nums, iv, beg + 1);
            //reset
            iv.pop_back();
            swap(nums[i], nums[beg]);
        }
    }
    vector<vector<int>> permuteUnique(vector<int>& nums) {
        //sort(nums.begin(), nums.end());
        set<vector<int>> isv{};
        vector<int> iv{};
        int beg = 0;
        getPermuteUnique(isv, nums, iv, beg);
        vector<vector<int>> ivv{};
        for(auto x : isv) ivv.push_back(x);
        return ivv;
    }
    */

    void getPermuteUnique(vector<vector<int>> &ivv, vector<int> &nums, vector<int> iv, int beg){
        if(iv.size() == nums.size()){
            ivv.push_back(iv);
            return;
        }
        for(int i = beg; i < nums.size(); ++i){
            if(i != beg && nums[i] == nums[beg]) continue;
            iv.push_back(nums[i]);
            swap(nums[i], nums[beg]);
            getPermuteUnique(ivv, nums, iv, beg + 1);
            iv.pop_back();
            swap(nums[i], nums[beg]);
        }
    }

    vector<vector<int>> permuteUnique(vector<int>& nums){
        sort(nums.begin(), nums.end());
        vector<vector<int>> ivv{};
        vector<int> iv{};
        getPermuteUnique(ivv, nums, iv, 0);
        return ivv;
    }

//48. Rotate Image
    void rotate(vector<vector<int>>& matrix) {
        int len = matrix.size();
        std::reverse(matrix.begin(), matrix.end());
        //take the transpose of matrix
        for(int i = 0; i < len; ++i){
            for(int j = 0; j < i; ++j){
                swap(matrix[i][j], matrix[j][i]);
            }
        }
    }

//50. Pow(x, n)
    double myPow(double x, int n) {
        //if(x == 0 || x == 1) return x;
        if(n == 0) return 1;
        //INT_MAX = - INT_MIN - 1
        if(n < 0){
            return n == INT_MIN ? 1 / x * myPow(1 / x, -n - 1) : myPow(1 / x, -n);
        }
        return n % 2 ? myPow(x * x, n / 2) * x: myPow(x * x, n / 2);
    }

//204. Count Primes
    int countPrimes(int n) {
        if(n == 0 || n == 1 || n == 2) return 0;
        vector<int> vec(n - 2, false);
        for(int i = 2; i < n; i += 2){

        }
    }

//372. Super Pow
    int getVectorIntoValue(vector<int> &b){
        if(b.size() == 0) return 0;
        int v = 0;
        for(auto x : b){
            v = v * 10 + x;
        }
        return v;
    }

    int remind(vector<int> &b, int a = 1440){
        vector<int> iv{};
        std::reverse(b.begin(), b.end());
        int re = 0;
        while(b.size() != 0){
            int v = getVectorIntoValue(iv);
            while(v < a && b.size() != 0){
                iv.push_back(b.back());
                b.pop_back();
                v = getVectorIntoValue(iv);
            }
            iv = {};
            re = v % a;
            if(b.size() == 0) break;
            int copyre = re;
            while(copyre){
                b.push_back(copyre % 10);
                copyre /= 10;
            }
        }
        return re;
    }

    int superPow(int a, vector<int>& b) {
        //1337 = 7 * 191
        //Eulor function E(1337) = E(7) * E(191) = 6 * 190 = 1140
        //a^1140 = (a mod 1337)^ 1140 = 1 mod 1337
        a = a % 1337;
        int mul = 1;
        int rem = remind(b, 1140);
        while(rem){
            mul *= a;
            if(mul >= 1337) mul %= 1337;
            --rem;
        }
        return mul;
    }

//338. Counting Bits
    vector<int> countBits(int num) {
        vector<int> vec(num + 1, 0);
        for(int i = 1; i <= num; ++i){
            int x = i;
            while(x){
                ++vec[i];
                //turn the last "1" of x into "0";
                x = x & (x - 1);
            }
        }
        return vec;
    }

//541. Reverse String II
    string reverseStr(string s, int k) {
        if(s.size() < k){
            std::reverse(s.begin(), s.end());
            return s;
        }
        for(int i = 0; i < s.size(); i += 2 * k){
            //use No.557 function reverseString;
            if(i + k <= s.size()) reverseString(s, i, i + k);
            else reverseString(s, i, s.size());
        }
        return s;
    }

//557. Reverse Words in a String III
    void reverseString(string &s, int beg, int en){
        while(beg <= --en){
            swap(s[beg], s[en]);
            ++beg;
        }
    }

    string reverseWords(string s) {
        int beg = 0;
        for(int i = 0; i < s.size(); ++i){
            if(s[i] == ' '){
                reverseString(s, beg, i);
                beg = i + 1;
            }
        }
        reverseString(s, beg, s.size());
        return s;
    }

};

