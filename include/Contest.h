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
};

