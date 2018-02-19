#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include <math.h>
#include <stack>
#include <set>
#include <numeric>

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
        map<int, vector<pair<int, int>>> myMap;
        vector<int> price(n, -1);
        for(int i = 0; i < flights.size(); ++i){
            myMap[flights[0]].push_back(make_pair(flights[i][1],flights[i][2]));
        }
        price[src] = 0;
        for(auto x : myMap[src]){
            for(auto t : x){
                if(price(t.first) == -1)
                    price(t.first) = t.second;
            }
        }
    }
};

