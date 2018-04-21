#ifndef FUNCTION_H
#define FUNCTION_H

#include <bits/stdc++.h>
#include "ListNode.h"
#include "Interval.h"
#include "TreeNode.h"
using namespace std;

class Function{
public:
    vector<vector<int>> getZigzag(int l){
        vector<vector<int>> vec(l, vector<int>(l, 0));
        for(int i = 0; i < l; ++i){
            for(int j = 0; j < l; ++j){
                int k = i + j;
                if(k < l) vec[i][j] = k * (k + 1) / 2 + (k % 2 ? i : j);
                else vec[i][j] = l * (l - 1) - (2 * l - k - 2) * (2 * l - k - 1 ) / 2 + ((l ^ k) % 2 ? i : j);
            }
        }
        return vec;
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
    bool isMatch2(string s, string p) {

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
        /*
        // DP O(n^2)
        int len = s.size(), maxLen = 0;
        if(len < 2) return 0;
        bool dp[len][len];
        for(int k = 0; k < len; ++k){
            for(int i = 0; i + k < len; ++i){
                int j = k + i;
                if((j - i) % 2 == 0) dp[i][j] = 0;
                else{
                    if(s[i] == '(' && s[j] == ')'){
                        if(i == j - 1) dp[i][j] = 1;
                        else{
                            dp[i][j] = (dp[i + 1][j - 1]) || (dp[i][i + 1] && dp[i + 2][j])
                                        || (dp[j - 1][j] && dp[i][j - 2]);
                        }
                    }
                    else dp[i][j] = 0;
                }
                maxLen = max(maxLen, dp[i][j] ? j - i + 1 : 0);
            }
        }
        return maxLen;
        */
        //DP O(n)
        int len = s.size(), maxLen = 0;
        if(len < 2) return 0;
        vector<int> dp(len, 0);
        for(int i = 1; i < len; ++i){
            if(s[i] == ')'){
                if(s[i - 1] == '('){
                    dp[i] = 2 + (i >= 2 ? dp[i - 2] : 0);
                }
                else{
                    int sym = i - 1 - dp[i - 1];
                    if(sym >= 0 && s[sym] == '('){
                        dp[i] = dp[i - 1] + 2 + (sym >= 1 ? dp[sym - 1] : 0);
                    }
                }
            }
            maxLen = max(maxLen, dp[i]);
        }
        return maxLen;
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
    void combinSum(int index, vector<vector<int>> &ivv, vector<int> iv, int target, const vector<int>& candidates){
        if(0 == target){
            ivv.push_back(iv);
            return;
        }
        for(int i = index; i < candidates.size(); ++i){
            int S = target - candidates[i];
            if(S < 0) break;
            iv.push_back(candidates[i]);
            combinSum(i, ivv, iv, S, candidates);
            iv.pop_back();
        }
    }

    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        vector<vector<int>> ivv{};
        vector<int> iv{};
        sort(candidates.begin(), candidates.end());
        combinSum(0, ivv, iv, target, candidates);
        return ivv;
    }

//40. Combination Sum II
    void combinSum2(int index, vector<vector<int>> &ivv, vector<int> iv, int target, const vector<int>& candidates){
        if(0 == target){
            ivv.push_back(iv);
            return;
        }
        for(int i = index; i < candidates.size(); ++i){
            int S = target - candidates[i];
            if(S < 0) break;
            if(i == index || candidates[i] != candidates[i - 1]){
                iv.push_back(candidates[i]);
                combinSum2(i + 1, ivv, iv, S, candidates);
                iv.pop_back();
            }
        }
    }

    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        vector<vector<int>> ivv{};
        vector<int> iv{};
        sort(candidates.begin(), candidates.end());
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

//44. Wildcard Matching
    bool isMatch(string s, string p) {
        if(s == "")
            return (p == "" || p == "*" ? true : false);
        if(p == "") return false;
        int str_len = s.size(), pat_len = p.size();
        vector<vector<int> > dp(pat_len, vector<int>(str_len, 0));
        if(p[0] == '?' || p[0] == s[0])  dp[0][0] = 1;
        for(int j = 0; j < str_len; ++j) {
            if(p[0] == '*') dp[0][j] = 1;
        }
        for(int i = 1; i < pat_len; ++i) {
            if(p[i] == '*' && dp[i - 1][0] == 1)
                dp[i][0] = 1;
            else if(p[i] == s[0] || p[i] == '?') {
                int j = i - 1;
                while(j >= 0 && dp[j][0] == 1 && p[j] == '*') {
                    --j;
                }
                if(j < 0)   dp[i][0] = 1;
            }

        }
        for(int i = 1; i < pat_len; ++i) {
            for(int j = 1; j < str_len; ++j) {
                if(p[i] == '*') {
                    if(dp[i - 1][j - 1] == 1 || dp[i][j - 1] == 1 || dp[i - 1][j] == 1)
                        dp[i][j] = 1;
                }
                else if(p[i] == '?' || p[i] == s[j]) {
                    dp[i][j] = dp[i - 1][j - 1];
                }
            }
        }
        for(int i = 0; i < pat_len; ++i) {
            for(int j = 0; j < str_len; ++j) {
                cout << dp[i][j] << ends;
            }
            cout <<endl;
        }
        return dp[pat_len - 1][str_len - 1]== 1 ? true : false;
    }

//45. Jump Game II
    int jump(vector<int>& nums) {
        int maxReach = 0, jumpCount = 0, curEnd = 0;
        if(nums.size() < 2) return nums.size();
        for(int i = 0; i < nums.size(); ++i){
            maxReach = max(maxReach, i + nums[i]);
            if(i == curEnd){
                jumpCount++;
                curEnd = maxReach;
            }
        }
        return jumpCount;
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

//49. Group Anagrams
    //bool mapEqual(map<char, int> &map1, map<char, int> &map2);
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        map<map<char, int>, vector<string>> myMap;
        for(int i = 0; i < strs.size(); ++i){
            map<char, int> map1{};
            for(auto str : strs[i]) ++map1[str];
            myMap[map1].push_back(strs[i]);
        }
        vector<vector<string>> vec(myMap.size(), vector<string>{});
        int k = 0;
        for(auto iter = myMap.begin(); iter != myMap.end(); ++iter){
            vec[k++] = iter->second;
        }
        return vec;
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

//51. N-Queens
    bool isConfilct(vector<int> vec, int index){
        for(int i = 0; i < index; ++i){
            if(vec[i] == vec[index] || index - i == abs(vec[i] - vec[index])) return true;
        }
        return false;
    }

    void returnArray(int index, int n, vector<vector<int>> &vvec, vector<int> vec){
        //the Kth element in vec means Kth queen's location is (K, vec[K]);
        if(index == n){
            vvec.push_back(vec);
            return;
        }
        for(int j = 0; j < n; ++j){
            vec[index] = j;
            if(!isConfilct(vec, index)) returnArray(index + 1, n, vvec, vec);
        }
    }

    vector<vector<string>> solveNQueens(int n) {
        vector<vector<int>> vvec{};
        vector<int> vec(n, 0);
        returnArray(0, n, vvec, vec);
        vector<vector<string>> vvecstr{};
        for(auto x : vvec){
            vector<string> vecstr(n, string(n, '.'));
            for(int i = 0; i < n; ++i){
                vecstr[i][x[i]] = 'Q';
            }
            vvecstr.push_back(vecstr);
        }
        return vvecstr;
    }

//52. N-Queens II
    //*with bit maniplutation
    void test(int row, int ld, int rd, int &sum, int n){
        cout << row << ends << ld << ends << rd << endl;
        int upperlim = (1 << n) - 1;
        if(row != upperlim){
            long pos = upperlim & (~(row | ld | rd));//pos二进制中的1表示某一行的这个位置不能放
            while(pos){
                long p = pos & (~pos + 1);//找到从右数的第一个1
                pos -= p;//去掉从右数的第一个1
                test(row + p, (ld + p) << 1, (rd + p) >> 1, sum, n);//对下一行有影响，要移动一位
            }
        }
        else sum++;
    }
    //*/
    int totalNQueens(int n) {
        /*
        //use No.51 function returnArray;
        vector<vector<int>> vvec{};
        vector<int> vec(n, 0);
        returnArray(0, n, vvec, vec);
        return vvec.size();
        */
        //*
        int sum = 0;
        test(0, 0, 0, sum, n);
        return sum;
        //*/
    }

//53. Maximum Subarray
    int maxSubArray(vector<int>& nums) {
        //state transition equation:
        //maxSubArray(nums[0,i])=max(0,maxSubArray(nums[0,i-1]))+nums[i]
        if(nums.empty()) return 0;
        int maxSum =nums[0], temp = nums[0];
        for(int i = 1; i < nums.size(); ++i){
            temp = max(0, temp) + nums[i];
            maxSum = max(maxSum, temp);
        }
        return maxSum;
    }

//54. Spiral Matrix
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        if (matrix.empty()) return {};
        int m = matrix.size(), n = matrix[0].size();
        vector<int> spiral(m * n, 0);
        int  i = 0, d = m - 1, j = 0, r = n - 1, k = 0;
        while (true) {
            for (int col = j; col <= r; col++) spiral[k++] = matrix[i][col]; // turn right
            if (++i > d) break;
            for (int row = i; row <= d; row++) spiral[k++] = matrix[row][r]; // turn down
            if (--r < j) break;
            for (int col = r; col >= j; col--) spiral[k++] = matrix[d][col]; //turn left
            if (--d < i) break;
            for (int row = d; row >= i; row--) spiral[k++] = matrix[row][j]; //turn right
            if (++j > r) break;
        }
        return spiral;
    }

//55. Jump Game
    bool canJump(vector<int>& nums) {
        if(nums.size() == 1) return true;
        int pre = nums.size() - 1;
        for(int i = nums.size() - 2; i >= 0; --i){
            //from back to front, if we can reach from position i;
            //Then judge any position that can reach to i;
            if(nums[i] + i >= pre) pre = i;
        }
        //if start position is 0
        return !pre;
    }

//56. Merge Intervals
    vector<Interval> merge(vector<Interval>& intervals) {
        if(intervals.empty()) return intervals;
        //sort by first element:start
        sort(intervals.begin(), intervals.end(),
             [](Interval &Int1, Interval &Int2){return Int1.start < Int2.start;});
        //why "<=" Runtime error
        vector<Interval> re{};
        re.push_back(intervals[0]);
        //[a1,b1],[a2,b2]
        //a2 > b1, put[a2, b2] in vector re;
        //a2 <= b1, change[a1, b1] into [a1, max(b1, b2)]
        for(int i = 1; i < intervals.size(); ++i){
            if(intervals[i].start > re.back().end) re.push_back(intervals[i]);
            else re.back().end = max(re.back().end, intervals[i].end);
        }
        return re;
    }

//57. Insert Interval
    vector<Interval> insert(vector<Interval>& intervals, Interval newInterval) {
        if(intervals.empty()){
            intervals.push_back(newInterval);
            return intervals;
        }
        sort(intervals.begin(), intervals.end(), [](Interval a, Interval b){return a.start < b.start;});
        int i = 0, j = intervals.size() - 1;
        //find the first and last position which are overlaped
        for(; i < intervals.size(); ++i){
            if(newInterval.start <= intervals[i].end){
                newInterval.start = min(newInterval.start, intervals[i].start);
                break;
            }
        }
        for(; j >= 0; --j){
            if(newInterval.end >= intervals[j].start){
                newInterval.end = max(newInterval.end, intervals[j].end);
                break;
            }
        }
        //get rid of position from i to j and insert newInterval into position i
        intervals.erase(intervals.begin() + i, intervals.begin() + j + 1);
        intervals.insert(intervals.begin() + i, newInterval);
        return intervals;
    }

//58. Length of Last Word
    int lengthOfLastWord(string s) {
        if(s.empty()) return 0;
        int i = s.size() - 1, count = 0;
        for(; i >= 0; --i){
            if(s[i] != ' ') break;
        }
        for(; i >= 0; --i){
            if(s[i] != ' ') ++count;
            else break;
        }
        return count;
    }

//59. Spiral Matrix II
    vector<vector<int>> generateMatrix(int n) {
        if (n == 0) return {};
        vector<vector<int>> matrix(n, vector<int>(n, 0));
        int  i = 0, d = n - 1, j = 0, r = n - 1, k = 1;
        while (true) {
            for (int col = j; col <= r; col++) matrix[i][col] = k++; // turn right
            if (++i > d) break;
            for (int row = i; row <= d; row++) matrix[row][r] = k++; // turn down
            if (--r < j) break;
            for (int col = r; col >= j; col--) matrix[d][col] = k++; //turn left
            if (--d < i) break;
            for (int row = d; row >= i; row--) matrix[row][j] = k++; //turn right
            if (++j > r) break;
        }
        return matrix;
    }

//60. Permutation Sequence
    int factorial(int n){
        if(n == 0) return 1;
        return n * factorial(n - 1);
    }

    string getPermutation(int n, int k) {
        //position in [l*(n-1)!, (l+1)*(n-1)!) must begin with l+1
        //then get rid of beginning and iterate
        string s = "";
        vector<int> vec{1,2,3,4,5,6,7,8,9};
        --k;
        for(int i = n - 1; i >= 0; --i){
            int fact = factorial(i);
            s.append(to_string(vec[k / fact]));
            vec.erase(vec.begin() + k / fact);  //if get number m then get rid of it
            k %= fact;            //change k into k%fact
        }
        return s;
    }

//62. Unique Paths
    int uniquePaths(int m, int n) {
        /*iteration  Time Limit Exceeded
        if(m == 1 || n == 1) return 1;
        return uniquePaths(m - 1, n) + uniquePaths(m, n - 1);
        */
        //dp
        if(m == 1 || n == 1) return 1;
        int arr[m][n] = {};
        for(int i = 0; i < m; ++i) arr[i][0] = 1;
        for(int i = 0; i < n; ++i) arr[0][i] = 1;
        for(int i = 1; i < m; ++i){
            for(int j = 1; j < n; ++j){
                arr[i][j] = arr[i - 1][j] + arr[i][j - 1];
            }
        }
        return arr[m - 1][n - 1];
    }

//63. Unique Paths II
    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
        int m = obstacleGrid.size(), n = obstacleGrid[0].size();
        int arr[m][n] = {0};
        int a = 0, b = 0;
        for(;a < m; ++a) if(obstacleGrid[a][0] == 1) break;
        for(int i = 0; i < m; ++i) arr[i][0] = i < a ? 1 : 0;
        for(;b < n; ++b) if(obstacleGrid[0][b] == 1) break;
        for(int i = 0; i < n; ++i) arr[0][i] = i < b ? 1 : 0;
        for(int i = 1; i < m; ++i){
            for(int j = 1; j < n; ++j){
                if(obstacleGrid[i][j] == 1) arr[i][j] = 0;
                else arr[i][j] = arr[i - 1][j] + arr[i][j - 1];
            }
        }
        return arr[m - 1][n - 1];
    }

//64. Minimum Path Sum
    int minPathSum(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        for(int i = 1; i < m; ++i) grid[i][0] += grid[i - 1][0];
        for(int i = 1; i < n; ++i) grid[0][i] += grid[0][i - 1];
        for(int i = 1; i < m; ++i){
            for(int j = 1; j < n; ++j){
                grid[i][j] += min(grid[i - 1][j], grid[i][j - 1]);
            }
        }
        return grid[m - 1][n - 1];
    }

//66. Plus One
    vector<int> plusOne(vector<int>& digits) {
        if(digits.empty()) return {1};
        int carry = 1;
        for(int i = digits.size() - 1; i >= 0; --i){
            int sum = digits[i] + carry;
            digits[i] = sum % 10;
            carry = sum / 10;
        }
        if(carry) digits.insert(digits.begin(), 1);
        return digits;
    }

//67. Add Binary
    string addBinary(string a, string b) {
        int len1 = a.size(), len2 = b.size();
        if(len1 < len2) return addBinary(b, a);
        int carry = 0;
        for(int i = 0; i < len1; ++i){
            if(len2 - i - 1 >= 0){
                int sum = a[len1 - i - 1] + b[len2 - i - 1] + carry - 96;
                a[len1 - i - 1] = sum % 2 + 48;
                carry = sum / 2;
            }
            else{
                int sum = a[len1 - i - 1] + carry - 48;
                a[len1 - i - 1] = sum % 2 + 48;
                carry = sum / 2;
            }
        }
        if(carry) a.insert(a.begin(), '1');
        return a;
    }

//69. Sqrt(x)
    int mySqrt(int x) {
        if(x == 0 || x == 1) return x;
        int root, lhs = 0, rhs = x;
        while(lhs + 1 < rhs){
            root = (lhs + rhs) / 2;
            if(root == x / root) return root; //must not use root * root == x
            root > x / root ? rhs = root : lhs = root;
        }
        return rhs > x / rhs ? lhs : rhs;
    }

//70. Climbing Stairs
    int climbStairs(int n) {
        if(n <= 2) return n;
        vector<int> dp(n, 1);
        dp[1] = 2;
        for(int i = 2; i < n; ++i){
            dp[i] = dp[i - 1] + dp[i - 2];
        }
        return dp[n - 1];
    }

//71. Simplify Path
    string simplifyPath(string path) {
        if(path.empty()) return path;
        int i = path.size() - 1;
        for(; i >= 0; --i){
            if(path[i] == '/') break;
        }
        int j = i - 1;
        for(; j >= 0; --j){
            if(path[j] == '/') break;
        }
        string s = j >= 0 ? path.substr(j, i - j) : "";
        return s;
    }

//72. Edit Distance
    int minDistance(string word1, string word2) {
        int len1 = word1.size() + 1, len2 = word2.size() + 1;
        vector<vector<int>> dp(len1, vector<int>(len2, 0));
        for(int i = 0; i < len1; ++i) dp[i][0] = i;
        for(int j = 0; j < len2; ++j) dp[0][j] = j;
        for(int i = 1; i < len1; ++i){
            for(int j = 1; j < len2; ++j){
                if(word1[i - 1] == word2[j - 1]) dp[i][j] = dp[i - 1][j - 1];
                else dp[i][j] = 1 + min(dp[i][j - 1], min(dp[i - 1][j - 1], dp[i - 1][j]));
            }
        }
        return dp[len1 - 1][len2 - 1];
    }

//73. Set Matrix Zeroes
    void setZeroes(vector<vector<int>>& matrix) {
        set<int> row, col;
        //record the position
        for(int i = 0; i < matrix.size(); ++i){
            for(int j = 0; j < matrix[0].size(); ++j){
                if(matrix[i][j] == 0){
                    row.insert(row.begin(), i);
                    col.insert(col.begin(), j);
                }
            }
        }
        for(auto r : row){
            for(int j = 0; j < matrix[0].size(); ++j){
                matrix[r][j] = 0;
            }
        }
        for(auto c : col){
            for(int i = 0; i < matrix.size(); ++i){
                matrix[i][c] = 0;
            }
        }
    }

//74. Search a 2D Matrix
    bool binary_search(vector<int> vec, vector<int>::iterator iter1, vector<int>::iterator iter2, const int &T){
        if(vec.empty()) return false;
        while(iter1 < iter2){
            int dis = iter2 - iter1;
            if(dis == 1) return *iter1 == T;
            auto mid = iter1 + dis / 2;
            if(*mid == T) return true;
            else if(*mid < T) iter1 = mid;
            else iter2 = mid;
        }
    }

    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        if(matrix.empty() || matrix[0].empty()) return false;
        int row = matrix.size() - 1;
        int rowbegin = 0;
        while(rowbegin <= row){
            if(target > matrix[row].back() ||target < matrix[rowbegin].front()){
                return false;
            }
            else if(target >= matrix[row].front() && target <= matrix[row].back()){
                return binary_search(matrix[row], matrix[row].begin(), matrix[row].end(), target);
            }
            else if(target >= matrix[rowbegin].front() && target <= matrix[rowbegin].back()){
                return binary_search(matrix[rowbegin],matrix[rowbegin].begin(), matrix[rowbegin].end(), target);
            }
            else{
                if(row == rowbegin + 1) return false;
                else{
                    int mid = (row + rowbegin) / 2;
                    target >= matrix[mid].front() ? rowbegin = mid : row = mid;
                }
            }
        }
    }

//75. Sort Colors
    void quickSort(vector<int> &nums, int lo, int hi){
        if(lo >= hi) return;
        int i = lo, j = hi, key = nums[lo];
        while(i < j){
            while(i < j && nums[j] >= key) --j;
            while(i < j && nums[i] <= key) ++i;
            if(i < j) swap(nums[i], nums[j]);
        }
        cout << i << " " << nums[i] << endl;
        nums[lo] = nums[i];
        nums[i] = key;
        quickSort(nums, lo, i - 1);
        quickSort(nums, i + 1, hi);
    }

    void sortColors(vector<int>& nums) {
        quickSort(nums, 0, nums.size() - 1);
    }

//77. Combinations
    void combineTrack(vector<vector<int>> &vvec, vector<int> &vec, int beg, int n, int k){
        if(vec.size() == k){
            vvec.push_back(vec);
            return;
        }
        for(int i = beg; i <= n; ++i){
            vec.push_back(i);
            combineTrack(vvec, vec, i + 1, n, k);
            vec.pop_back();
        }
    }

    vector<vector<int>> combine(int n, int k) {
        if(n <= 0 || k > n) return {};
        vector<vector<int>> vvec{};
        vector<int> vec{};
        combineTrack(vvec, vec, 1, n, k);
        cout << vvec.size();
        return vvec;
    }

//78. Subsets
    void subsetsTrack(vector<vector<int>> &vvec, vector<int>& nums, vector<int> vec, int beg){
        if(beg == nums.size()){
            vvec.push_back(vec);
            return;
        }
        else{
            subsetsTrack(vvec, nums, vec, beg + 1);
            vec.push_back(nums[beg]);
            subsetsTrack(vvec, nums, vec, beg + 1);
        }
    }

    vector<vector<int>> subsets(vector<int>& nums) {
        vector<vector<int>> vvec{};
        vector<int> vec{};
        subsetsTrack(vvec, nums, vec, 0);
        return vvec;
    }

//79. Word Search
    bool wordSearch(vector<vector<char>>& board, string word, int x, int y, int beg, bool sign){
        //judge position(x,y) in board exist word?
        sign = board[x][y] != word[beg] ? false : true;
        cout << beg << " " << sign << endl;
        //if(!sign) return false;
        if(sign && beg == word.size() - 1) return true;
        if(x - 1 >= 0 && sign) wordSearch(board, word, x - 1, y, beg + 1, sign);
        if(x + 1 < board.size() && sign) wordSearch(board, word, x + 1, y, beg + 1, sign);
        if(y - 1 >= 0 && sign) wordSearch(board, word, x, y - 1, beg + 1, sign);
        if(y + 1 < board[0].size() && sign) wordSearch(board, word, x, y + 1, beg + 1, sign);
    }

    bool exist(vector<vector<char>>& board, string word) {
        if(board.size() == 0 || board[0].size() == 0 || word == "") return false;
        for(int i = 0; i < board.size(); ++i){
            for(int j = 0; j < board[0].size(); ++j){
                bool sign;
                if(wordSearch(board, word, i , j, 0, sign)) return true;
            }
        }
        return false;
    }

//80. Remove Duplicates from Sorted Array II
    int removeDuplicates2(vector<int>& nums) {
        map<int, int> myMap;
        int sum = 0;
        for(auto num : nums){
            if(myMap[num] < 2) ++myMap[num];
        }
        auto iter = myMap.begin();
        while(iter != myMap.end()){
            sum += iter->second;
            ++iter;
        }
        return sum;
    }

//82. Remove Duplicates from Sorted List II
    ListNode* deleteDuplicates1(ListNode* head) {
        //recursion
        if(head == NULL || head->next == NULL) return head;
        ListNode *i = head, *j = head->next;
        while(j != NULL && i->val == j->val) j = j->next;
        if(j && i->next == j){
            head->next = deleteDuplicates1(j);
            return head;
        }
        else return deleteDuplicates1(j);
    }

//83. Remove Duplicates from Sorted List
    ListNode* deleteDuplicates(ListNode* head) {
        if(head == NULL) return head;
        ListNode *temp = head, *i = head, *j = head;
        while(j != NULL){
            if(j->val != i->val){
                i->next = j;
                i = i->next;
            }
            j = j->next;
        }
        i->next = NULL;
        return temp;
    }

//84. Largest Rectangle in Histogram
    int largestRectangleArea(vector<int>& heights) {
        if(heights.empty()) return 0;
        if(heights.size() == 1) return heights[0];
        heights.push_back(0);   //put 0 back of heights
        int area = 0;
        stack<int> myStack{};
        for(int i = 0; i < heights.size(); ++i){
            //it means the index from bottom to top of myStack, by mapping, heights[index] is from small to large
            //if we find the top one index in myStack, heights[index] is larger than heights[i], begin to compute
            while(!myStack.empty() && heights[myStack.top()] >= heights[i]){
                int index = myStack.top();
                myStack.pop();
                int s = myStack.empty() ? -1 : myStack.top();
                area = max(area, heights[index] * (i - s - 1));
            }
            myStack.push(i);
        }
        return area;
    }

//85. Maximal Rectangle
    int maximalRectangle(vector<vector<char>>& matrix) {
        if(matrix.size() == 0 || matrix[0].size() == 0) return 0;
        int m = matrix.size(), n = matrix[0].size(), Max = 0;
        vector<int> vec(n, 0);
        for(int i = 0; i < m; ++i){
            for(int j = 0; j < n; ++j){
                vec[j] = matrix[i][j] == '1' ? vec[j] + 1 : 0;
            }
            Max = max(Max, largestRectangleArea(vec));
        }
        return Max;
    }

//88. Merge Sorted Array
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        vector<int> vec(nums1.begin(), nums1.begin() + m);
        int i = 0, j = 0;
        while(i + j < m + n){
            if(i >= m || (j < n && nums2[j] <= vec[i])){
                nums1[i + j] = nums2[j];
                ++j;
            }
            else{
                nums1[i + j] = vec[i];
                ++i;
            }
        }
    }

//89. Gray Code
    vector<int> grayCode(int n) {
        if(n == 0) return {0};
        int j = 0;
        vector<int> vec(power(2, n), 0);
        while(j++ < n){
            int m = power(2, j);
            for(int i = m / 2; i < m; ++i){
                vec[i] = m / 2 + vec[m - i - 1];
            }
        }
        return vec;
    }

//94. Binary Tree Inorder Traversal
    void goLeft(TreeNode* root, stack<TreeNode*> &s){
        //从某个节点从发，沿左分子一直深入，并记入栈
        while(root){
            s.push(root);
            root = root->left;
        }
    }

    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> vec{};
        stack<TreeNode*> s;
        while(true){
            goLeft(root, s);
            if(s.empty()) break;
            root = s.top();
            s.pop();
            vec.push_back(root->val);
            root = root->right;
        }
        return vec;
    }

//95. Unique Binary Search Trees II
    vector<TreeNode*> generateTrees(int n) {

    }

//96. Unique Binary Search Trees
    int numTrees(int n) {
        //dynamic program
        //G(n) means all BSTs, F(i,n) means BSTs with root i;
        //G(n)=F(1,n)+F(2,n)+...+F(n,n) and F(i,n)=G(i-1)*G(n-i) with G(0)=G(1)=1
        if(n < 2) return 1;
        vector<int> G(n + 1, 0), F(n + 1, 0);
        G[0] = G[1] = 1;
        for(int i = 2; i <= n; ++i){
            for(int j = 1; j <= i; ++j){
                F[j] = G[j - 1] * G[i - j];
                G[i] += F[j];
            }
        }
        return G[n];
    }

//97. Interleaving String
    bool isInterleave(string s1, string s2, string s3) {
        if(s1.size() + s2.size() != s3.size()) return false;
        bool dp[s1.size() + 1][s2.size() + 1]{};
    }
//98. Validate Binary Search Tree
    void ts(TreeNode* root, vector<int>& vec){
        //中序遍历保存到vec
        if(root){
            ts(root->left, vec);
            vec.push_back(root->val);
            ts(root->right, vec);
        }
    }
    bool isValidBST(TreeNode* root) {
        //中序遍历是一个递增序列
        if(root == NULL) return true;
        vector<int> vec;
        ts(root, vec);
        for(int i = 1; i < vec.size(); ++i){
            if(vec[i] <= vec[i - 1]) return false;
        }
        return true;
    }

//100. Same Tree
    bool isSameTree(TreeNode* p, TreeNode* q) {
        if(p == NULL && q == NULL) return true;
        else if(p && q) return p->val == q->val && isSameTree(p->left, q->left) && isSameTree(p->right, q->right);
        else return false;
    }
//101. Symmetric Tree
    bool isSymmetric(TreeNode* lChild, TreeNode* rChild) {
        if(!lChild && !rChild) return true;
        else if(lChild && !rChild || (!lChild && rChild)) return false;
        else{
            if(lChild->val != rChild->val) return false;
            else{
                return isSymmetric(lChild->left, rChild->right) && isSymmetric(rChild->left, lChild->right);
            }
        }
    }
    bool isSymmetric(TreeNode* root) {
        if(!root) return false;
        return isSymmetric(root->left, root->right);
    }
//102. Binary Tree Level Order Traversal
    void levelOrderPush(TreeNode* root, vector<vector<int>>& vvec, int index){
        if(root){
            vvec[index].push_back(root->val);
            levelOrderPush(root->left, vvec, index + 1);
            levelOrderPush(root->right, vvec, index + 1);
        }
    }
    vector<vector<int>> levelOrder(TreeNode* root) {
        int len = maxDepth(root);
        vector<vector<int>> vvec(len, vector<int>{});
        levelOrderPush(root, vvec, 0);
        return vvec;
    }

//104. Maximum Depth of Binary Tree
    int maxDepth(TreeNode* root) {
        if(root == NULL) return 0;
        return 1 + max(maxDepth(root->left), maxDepth(root->right));
    }

//121. Best Time to Buy and Sell Stock
    int maxProfit(vector<int>& prices) {

    }

//136. Single Number
    //with map
    /*
    int singleNumber(vector<int>& nums) {
        map<int, int> myMap;
        for(auto num : nums) myMap[num]++;
        for(auto iter = myMap.begin(); iter != myMap.end(); ++iter){
            if(iter->second != 2) return iter->first;
        }
    }*/
    //use xor for any N:0^N=N,N^N=0;
    int singleNumber(vector<int>& nums){
        int result = 0;
        for(auto num : nums) result ^= num;
        return result;
    }

//137. Single Number II
    int singleNumberII(vector<int>& nums) {
        int a = 0, b = 0;
        for(auto num : nums){
            a = (a ^ num) & ~b;
            b = (b ^ num) & ~a;
        }
        return a;
    }
//151. Reverse Words in a String
    void reverseWords2(string &s) {
        std::reverse(s.begin(), s.end());
        int beg = 0;
        for(int i = 0; i < s.size(); ++i){
            if(s[i] == ' ' && i > beg){
                std::reverse(s.begin() + beg, s.begin() + i);
                beg = i + 1;
            }
        }
        std::reverse(s.begin() + beg, s.end());
    }

//191. Number of 1 Bits
    int hammingWeight(uint32_t n) {
        int count = 0;
        while(n){
            count++;
            n = n & (n - 1);
        }
        return count;
    }

//231. Power of Two
    bool isPowerOfTwo(int n) {
        if(n <= 0) return false;
        return !(n & (n - 1));
    }

//233. Number of Digit One
    int countDigitOne(int n) {
        if(n < 1) return 0;
        int hi = n, lo, mi, count = 0, base = 1;
        while(hi){
            lo = n % base;
            mi = hi % 10;
            hi /= 10;
            count += base * hi;
            if(mi > 1) count += base;
            else if(mi == 1) count += lo + 1;
            base *= 10;
        }
        return count;
    }

//371. Sum of Two Integers
    int getSum(int a, int b) {
        //return b == 0 ? a : getSum(a ^ b, (a & b) << 1);
        if(b == 0) return a; //没有进位的时候完成运算
        int sum, carry;
        sum = a ^ b;        //没有进位的加法运算
        carry = (a & b) << 1;   //进位（左移）
        return getSum(sum, carry); //递归
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

    int remainder(vector<int> &b, int a = 1440){
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
        int rem = remainder(b, 1140);
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

//378. Kth Smallest Element in a Sorted Matrix
    void kmerge(vector<int> &v1, vector<int> &v2){

    }
    int kthSmallest(vector<vector<int>>& matrix, int k) {

    }

//451. Sort Characters By Frequency
    string frequencySort(string s) {
        map<char, int> myMap;
        for(auto c : s) myMap[c]++;
        vector<pair<char, int>> vp(myMap.begin(), myMap.end());
        sort(vp.begin(), vp.end(), [](pair<char, int> a, pair<char, int> b){return a.second > b.second;});
        s = "";
        for(auto c : vp) s += string(c.second, c.first);
        return s;
    }

//524. Longest Word in Dictionary through Deleting
    typedef map<char, int> Cim;
    bool fitWord(Cim &cim, string s2){
        Cim cim2;
        for(auto s : s2)
            ++cim2[s];
        for(auto iter = cim2.begin(); iter != cim2.end(); ++iter){
            if(iter->second > cim[iter->first])
                return false;
        }
        return true;
    }
    string findLongestWord(string s, vector<string>& d) {
        vector<string> S;
        Cim cim;
        int len = 0;
        for(auto i : s)
            ++cim[i];
        for(auto i : d){
            if(fitWord(cim, i))
                S.push_back(i);
        }
        for(auto i : S){
            len = len < i.size() ? i.size() : len;
        }
        string T(len, 'z');
        for(auto i : S){
            if(i.size() == len)
                T = T < i ? T : i;
        }
        return T;
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

//573. 复数乘法
    pair<int, int> string_to_complex(string a) {
        int re_a = 0, im_a = 0;
        int sra = 1, sia = 1;
        int plus_index = 10, start = 0;
        if(a[0] == '-'){
            sra = -1;
            start = 1;
        }
        for(int i = start; i < a.size() - 1; ++i){
            if(a[i] == '+')
                plus_index = i;
            else if(i < plus_index){
                re_a = re_a * 10 + a[i] - '0';
            }
            else{
                if(a[i] == '-')
                    sia = -1;
                else{
                    im_a = 10 * im_a + a[i] - '0';
                }
            }
        }
        return pair<int, int>(sra * re_a, sia * im_a);
    }


    string complexNumberMultiply(string a, string b) {
        pair<int, int> c_a = string_to_complex(a);
        pair<int, int> c_b = string_to_complex(b);
        int re = c_a.first * c_b.first - c_a.second * c_b.second;
        int im = c_a.first * c_b.second + c_a.second * c_b.first;
        cout << re << im << endl;
        string s = to_string(re);
        s += '+'; s += to_string(im); s += 'i';
        return s;
    }
//640. Solve the Equation
    string solveEquation(string equation) {

    }

//647. Palindromic Substrings
    int countSubstrings(string s) {
        if(s.empty())
            return 0;
        int len = s.size(), count = 0;
        for(int i = 0; i < len; ++i){
            count += countSub(s, i, i);
            count += countSub(s, i, i+1);
        }
        return count;
    }
    int countSub(string s, int lo, int hi){
        int count = 0;
        while(lo >= 0 && hi < s.size() && s[lo--] == s[hi++]){
            ++count;
        }
        return count;
    }

//652. Find Duplicate Subtrees
    string collectId(TreeNode* root, unordered_map<string, vector<TreeNode*> > &myMap){
        if(!root) return "";
        string id = "." + collectId(root->left, myMap) + to_string(root->val)
            + collectId(root->right, myMap) + ".";
        myMap[id].push_back(root);
        return id;
    }

    vector<TreeNode*> findDuplicateSubtrees(TreeNode* root) {
        vector<TreeNode*> sub{};
        unordered_map<string, vector<TreeNode*> > myMap;
        collectId(root, myMap);
        for(auto iter = myMap.begin(); iter != myMap.end(); ++iter){
            if((iter->second).size() > 1)
                sub.push_back((iter->second)[0]);
        }
        return sub;
    }

//672. Bulb Switcher II
    int flipLights(int n, int m) {
        if(!m || !n) return 0;
        if(n == 1) return 2;
        if(m == 1) return n == 2 ? 3 : 4;
        if(n == 2) return 4;
        return  m == 2 ? 7 : 8;
    }

//712. Minimum ASCII Delete Sum for Two Strings
    int minimumDeleteSum(string s1, string s2) {

    }

//728. Self Dividing Numbers
    bool selfDividingNumber(int num){
        int copyNum = num;
        while(num){
            int bit = num % 10;
            num /= 10;
            if(bit && (copyNum % bit) || !bit) return false;
        }
        return true;
    }

    vector<int> selfDividingNumbers(int left, int right) {
        vector<int> vec{};
        for(int i = left; i <= right; ++i){
            if(selfDividingNumber(i)) vec.push_back(i);
        }
        return vec;
    }

};

#endif // FUNCTION_H

