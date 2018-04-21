#ifndef CONTEST_H
#define CONTEST_H
#include <bits/stdc++.h>

using namespace std;

class Contest
{
public:
//contest 54
    //697. Degree of an Array
    int findShortestSubArray(vector<int>& nums) {
        map<int, int> myMap;
        for(auto x : nums)
            ++myMap[x];

    }
    //696. Count Binary Substrings
    int countBinarySubstrings(string s) {
        if(s.size() < 2) return 0;
        int zeroCount = 0, oneCount = 0, temp = 0;
        int Count = 0;
        s[0] == '1' ? oneCount = 1 : zeroCount = 1;
        //cout << zeroCount << ends << oneCount << ends << Count << endl;
        for(int i = 1; i != s.size(); ++i){
            if(s[i] == s[i - 1]){
                if(s[i] == '0'){
                    ++zeroCount;
                    if(zeroCount <= temp) ++Count;
                }
                else{
                    ++oneCount;
                    if(oneCount <= temp) ++Count;
                }
            }
            else{
                ++Count;
                if(s[i] == '0'){
                    temp = oneCount;
                    zeroCount = 1;
                }
                else{
                    temp = zeroCount;
                    oneCount = 1;
                }
            }
            //cout << zeroCount << ends << oneCount << ends << Count << endl;
        }
        return Count;
    }

    //698. Partition to K Equal Sum Subsets
    bool canPartitionKSubsets(vector<int>& nums, int k) {
        int sum = accumulate(nums.begin(), nums.end(), 0);
        int average = sum / k;
        if(sum % k || nums.size() < k || *max_element(nums.begin(), nums.end()) > average) return false;
        sort(nums.begin(), nums.end());
        //int leftIndex = 0, rightIndex = nums.size() - 1;
        for(auto iter = nums.rbegin(); iter != nums.rbegin(); ++iter){

        }
        return true;
    }

//contest 61
    //739. Daily Temperatures
    vector<int> dailyTemperatures(vector<int>& temperatures) {
        if(temperatures.empty()) return {};
        if(temperatures.size() == 1) return {0};
        for(int i = 0; i < temperatures.size(); ++i){
            int j = i;
            for(; j < temperatures.size(); ++j){
                if(temperatures[j] > temperatures[i]){
                    temperatures[i] = j - i;
                    break;
                }
            }
            if(j == temperatures.size()) temperatures[i] = 0;
        }
        return temperatures;
    }

    //738. Monotone Increasing Digits
    int isIncreasingDigits(vector<int> &vec){
        //find the first "first" number that is more than next number.
        for(int i = 1; i < vec.size(); ++i){
            if(vec[i - 1] > vec[i]){
                while(i - 1 >= 1 && vec[i - 1] == vec[i - 2]) i--;
                return i - 1;
            }
        }
        return vec.size();
    }

    int monotoneIncreasingDigits(int N) {
        if(N <= 10) return N - 1;
        vector<int> vec{N % 10};
        int sum = 0, copyN = N;
        while(N /= 10) vec.push_back(N % 10);
        reverse(vec.begin(), vec.end());
        int index = isIncreasingDigits(vec);
        if(index == vec.size()) return copyN;
        vec[index]--;
        for(int i = index + 1; i < vec.size(); ++i) vec[i] = 9;
        for(int i = 0; i < vec.size(); ++i) sum = sum * 10 + vec[i];
        return sum;
    }

//contest 64
    //747. Largest Number Greater Than Twice of Others
    int dominantIndex(vector<int>& nums) {
        if(nums.empty()) return -1;
        int max1 = nums[0], max2 = -1, index;
        for(int i = 1; i < nums.size(); ++i){
            if(nums[i] >= max1){
                max2 = max1;
                max1 = nums[i];
            }
            else if(nums[i] >= max2){
                max2 = nums[i];
            }
        }
        for(int i = 0; i < nums.size(); ++i){
            if(nums[i] == max1) index = i;
        }
        return max1 >= 2 * max2 ? index : -1;
    }

    //752. Open the Lock
    int openLock(vector<string>& deadends, string target) {
        string s = "0000";
        if(find(deadends.begin(), deadends.end(), s) == deadends.end()) return -1;
        map<string, int> myMap;
        myMap[s] = 0;
        for(auto x : deadends) myMap[x] = 0;


    }

//contest 70
    //779. K-th Symbol in Grammar
    int kthGrammar(int N, int K) {
        if(K == 1) return 0;
        int num = 0;
        for(int i = N - 1; i > 0; --i){
            if(K > pow(2, i)){
                K -= pow(2, i);
                ++num;
            }
            else if(K == pow(2, i)){
                K -= pow(2, i - 1);
                ++num;
            }
        }
        return num % 2;
    }
    //776. Split BST
    vector<TreeNode*> splitBST(TreeNode* root, int V) {

    }
    //778. Swim in Rising Water
    int swimInWater(vector<vector<int>>& grid) {

    }

//contest 72
    //784. Letter Case Permutation
    void letterBacktracking(string S, int index, vector<string> &letter){
        if(index == S.size()){
            //cout << S << endl;
            letter.push_back(S);
            return;
        }
        else{
            if(isdigit(S[index])) letterBacktracking(S, ++index, letter);
            else{
                int i = index + 1;
                letterBacktracking(S, i, letter);
                S[index] = islower(S[index]) ? toupper(S[index]) : tolower(S[index]);
                letterBacktracking(S, i, letter);
            }
        }
    }

    vector<string> letterCasePermutation(string S) {
        vector<string> letter;
        letterBacktracking(S, 0, letter);
        return letter;
    }

    //785. Is Graph Bipartite?
    bool isBipartite(vector<vector<int>>& graph) {
        int len = graph.size();
        vector<int> color(len, -1);
        for(int i = 0; i < len; ++i){
            if(color[i] == -1) color[i] = 1;
            for(int j = 0; j < graph[i].size(); ++j){
                int k = graph[i][j];
                if(color[k] == -1) color[k] = (color[i] == 1 ? 0 : 1);
                else if(color[k] == color[i]) return false;
            }
        }
        return true;
    }

    //786. K-th Smallest Prime Fraction
    vector<int> kthSmallestPrimeFraction(vector<int>& A, int K) {

    }

    //787. Cheapest Flights Within K Stops
    int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int K) {
    }


//Contest 74
    //792. Number of Matching Subsequences
    bool isSubseq(string S, string s){
        int len = s.size();
        int j = 0;
        for(int i = 0; i < len; ++i){
            while(j < S.size() && S[j] != s[i])
                ++j;
            if(j == S.size())
                return false;
            ++j;
        }
        return true;
    }
    int numMatchingSubseq(string S, vector<string>& words) {
        int count  = 0;
        for(auto word : words)
            count += isSubseq(S, word) ? 1 : 0;
        return count;
    }

    //793. Preimage Size of Factorial Zeroes Function
    int preimageSizeFZF(int K) {
        vector<int > five;
        while(K >= 5){
            five.push_back(K % 5);
            K /= 5;
        }

    }

    //795. Number of Subarrays with Bounded Maximum
    int numSubarrayBoundedMax(vector<int>& A, int L, int R) {
        //A=[1,1,2,2,1,1,2] L = 2, R = 3;
        vector<int> dp(A.size() + 1, 0);
        int count = 0;
        for(int i = 0; i < A.size(); ++i){
            if(A[i] > R) dp[i + 1] = 0;
            else if(A[i] >= L){
                int j = i;
                while(j >= 0 && A[j] <= R){
                    dp[i + 1] += 1;
                    --j;
                }
            }
            else{
                int j = i - 1;
                bool appear = false;
                while(j >= 0 && A[j] <= R){
                    if(A[j] >= L){
                        dp[i + 1] += 1;
                        appear = true;
                    }
                    else{
                        dp[i + 1] += appear ? 1 : 0;
                    }
                    --j;
                }
            }
        }
        for(int i = 0; i <= A.size(); ++i)
            count += dp[i];
        return count;
    }

//Contest 76
    //800. Similar RGB Color
    string minRGB(char str1, char str2) {
        int value = str1 <= '9' ? (str2 <= '9' ? (str1 - '0') * 16 + str2 - '0' : (str1 - '0') * 16 + str2 - 'a' + 10)
                    :  (str2 <= '9' ? (str1 - 'a' + 10) * 16 + str2 - '0' : (str1 - 'a' + 10) * 16 + str2 - 'a' + 10);
        int m = INT_MAX, index = 0;
        for(int i = 0; i < 16; ++i){
            int abs = value <= i * 16 + i ? i * 16 + i - value : value - i * 16 - i;
            if(abs <= m){
                m = abs;
                index = i;
            }
        }
        return string(2, index <= 9 ? index + '0' : index - 10 + 'a');
    }
    string similarRGB(string color) {
        string re = "#";
        re += minRGB(color[1], color[2]);
        re += minRGB(color[3], color[4]);
        re += minRGB(color[5], color[6]);
        return re;
    }

    //801. Minimum Swaps To Make Sequences Increasing
    int minSwap(vector<int>& A, vector<int>& B) {
        if(A.size() <= 1)
            return 0;
        int swaplen = 0;
        for(int i = 1; i < A.size(); ++i){
            if(A[i] <= A[i-1] || B[i] <= B[i-1]){
                ++swaplen;
                swap(A[i], B[i]);
            }
            else{
                if(i+1 < A.size() && A[i+1] <= A[i-1] || B[i+1] <= B[i]){

                }
            }
        }
        return swaplen;
    }
    //802. Find Eventual Safe States
    bool dfs(int node, int index, vector<vector<int>>& graph) {
        if(graph[index].empty())
            return false;
        for(auto x : graph[index]){
            if(x == node){
                return true;
            }
            else{
                dfs(node, x, graph);
            }
        }
        return false;
    }
    vector<int> eventualSafeNodes(vector<vector<int>>& graph) {
        vector<int> vec;
        int len = graph.size();
        for(int i = 0; i < len; ++i){
            if(!dfs(i, i, graph))
                vec.push_back(i);
        }
        return vec;
    }

//Contest 77
    //806. Number of Lines To Write String
    vector<int> numberOfLines(vector<int>& widths, string S) {
        int lines = 0, lastLine = 0, unitPlus = 0;
        for(auto s : S){
            unitPlus += widths[s - 'a'];
            if(unitPlus > 100) {
                ++lines;
                unitPlus = widths[s - 'a'];
            }
            else if(unitPlus == 100) {
                ++lines;
                unitPlus = 0;
            }
        }
        lines += (unitPlus == 100 ? 0 : 1);
        return  {lines, unitPlus};
    }

    //804. Unique Morse Code Words
    int uniqueMorseRepresentations(vector<string>& words) {
        vector<string> sv{".-","-...","-.-.","-..",".","..-.","--.","....","..",".---","-.-",".-..","--","-.",
                        "---",".--.","--.-",".-.","...","-","..-","...-",".--","-..-","-.--","--.."};
        set<string> ss{};
        for(auto s : words) {
            string temp = "";
            for(auto ch : s) temp += sv[ch - 'a'];
            ss.insert(temp);
        }
        return ss.size();
    }

    //807. Max Increase to Keep City Skyline
    int maxIncreaseKeepingSkyline(vector<vector<int>>& grid) {

    }

    //805. Split Array With Same Average
    /*
    double average(const vector<int>& A) {
        if(A.size() == 0) return 0;
        double sum = 0;
        for(auto a : A) sum += a;
        return sum / A.size();
    }
    bool sASA(const vector<int>& A, vector<int> vec, int ave, int index) {
        if(average(vec) == ave)
            return true;
        if(index == A.size())
            return false;
        for(int i = 0; i < A.size(); ++i) {
            sASA(A, vec, ave, i + 1);
            vec.pop_back();
        }
    }
    bool splitArraySameAverage(vector<int>& A) {
        int sum = 0, ave = average(A), index = 0;
        for(auto a : A) sum += a;
        if(sum % 2 == 1) return false;
        vector<int> vec{};
        return sASA(A, vec, ave, index);
    }
    */
//Contest 78
    //811. Subdomain Visit Count
    vector<string> subdomainVisits(vector<string>& cpdomains) {

    }
};
#endif // CONTEST_H
