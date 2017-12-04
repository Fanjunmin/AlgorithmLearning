#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include <math.h>
#include <stack>
#include <set>
#include <numeric>
#include <Function.h>

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
};

