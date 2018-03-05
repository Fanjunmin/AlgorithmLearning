# Some codes of algorithm
## There are some head files including:
- Include/TreeNode.h: the head file of the tree node.
- Include/ListNode.h: the head file of the list node.
- Include/Interval.h: the head file of the Interval.

These are all for algorithm problems in [leetcode](https://leetcode.com/problemset/all/).

## Another two head files:
- Include/Function.h: the head file of problems solutions. At the begining of every function, there is a annotation for the problem's No. and title. For example:
```
//1. Two Sum
    vector<int> twoSum(vector<int>& nums, int target) {
        map<int, int> myMap;
        //key:the value of vector;value:the index of vector
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
```
- Include/Contest.h: the head file of contest problems solutions, these sloutions may repeat the Function.h's solutions. At the begining, there is Contest's NO. then there is a annotation for the problem's number and title. For example:
```
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
    ...
    
```
## The rest head files
- Include/MathOperations.h: head file of math operations function definitions without math operations including: addition(+), substrction(-), absValue(||), oppValue(-), multiplication(*) and division(/).

- Include/MySort.h: head file of some sort functions, including: BubbleSort, SelectionSort, InsertionSort, ShellSort, MergeSort, QuickSort and HeapSort.

- Include/PtOffer.h: head file of solutions of problems in book named "剑指Offer:名企面试官精讲典型编程题" in [Nowcoder](https://www.nowcoder.com/ta/coding-interviews).

- Include/Print.h: head file of "print" functions. 