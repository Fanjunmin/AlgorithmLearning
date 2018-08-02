#ifndef LEETCODEINNOWCODER_H_INCLUDED
#define LEETCODEINNOWCODER_H_INCLUDED
#include <bits/stdc++.h>
using namespace std;

//Definition for 2-dimension matrix
struct Matrix {
    /*[m00, m01]
      [m10, m11]*/
    int m00, m01, m10, m11;
    Matrix(int a = 0, int b = 0, int c = 0, int d = 0) :
        m00(a), m01(b), m10(c), m11(d) { }
    Matrix& operator*(const Matrix& rhs) {
        int a = this->m00 * rhs.m00 + this->m01 * rhs.m10;
        int b = this->m00 * rhs.m01 + this->m01 * rhs.m11;
        int c = this->m10 * rhs.m00 + this->m11 * rhs.m10;
        int d = this->m10 * rhs.m01 + this->m11 * rhs.m11;
        this->m00 = a; this->m01 = b;
        this->m10 = c; this->m11 = d;
        return *this;
    }
};

//Definition for binary tree
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

//Definition for singly-linked list.
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
    TreeLinkNode(int x) :val(x), left(NULL), right(NULL), next(NULL) { }
};

class Solution {
public:
    //按照通过率由高到低

    // maximum-depth-of-binary-tree
    int maxDepth(TreeNode *root) {
        return root ? 1 + std::max(maxDepth(root->left),maxDepth(root->right)) : 0;
    }

    // reverse-integer
    int reverse(int x) {
        long re = 0;
        while(x) {
            re = re * 10 + x % 10;
            x /= 10;
            if(re > INT_MAX || re < INT_MIN) return 0;
        }
        return static_cast<int>(re);
    }

    // single-number
    int singleNumber(int A[], int n) {
        for(int i = 1; i < n; ++i) {
            A[0] ^= A[i];
        }
        return A[0];
    }

    //4. best-time-to-buy-and-sell-stock-ii
    int maxProfit(vector<int> &prices) {
        if(prices.size() < 2) return 0;
        int profit = 0;
        for(int i = 1; i < prices.size(); ++i) {
            if(prices[i] > prices[i - 1])
                profit += prices[i] - prices[i - 1];
        }
        return profit;
    }

    // container-with-most-water
    int maxArea(vector<int>& height) {
        auto volume = [height](int i, int j)->int{return min(height[i], height[j]) * (j - i);}; //体积函数
        int leftIndex = 0, rightIndex = height.size()-1;
        int v = volume(0, height.size()-1); //初始体积
        while(rightIndex > leftIndex){
            height[leftIndex] > height[rightIndex] ? --rightIndex : ++leftIndex; //从两段向中间移动
            v = max(v, volume(leftIndex, rightIndex)); //更新体积
        }
        return v;
    }

    // integer-to-roman
    string intToRoman(int num) {
        //I(1), X(10), C(100), M(1000), V(5), L(50), D(500)
        map<int, string> myMap{ {0, ""}, {1, "I"}, {2, "II"}, {3, "III"}, {4, "IV"}, {5, "V"}, {6, "VI"}, {7,"VII"}, {8, "VIII"}, {9, "IX"},
            {10, "X"}, {20, "XX"}, {30, "XXX"}, {40, "XL"}, {50, "L"}, {60, "LX"}, {70,"LXX"}, {80, "LXXX"}, {90, "XC"},
            {100, "C"}, {200, "CC"}, {300, "CCC"}, {400, "CD"}, {500, "D"}, {600, "DC"}, {700,"DCC"}, {800, "DCCC"}, {900, "CM"},
            {1000, "M"}, {2000, "MM"}, {3000, "MMM"} };
        string re = "";
        int bit = 1000;
        while(num) {
            if(num / bit) {
                int temp = num / bit * bit;
                re += myMap[temp];
                num -= temp;
            }
            else {
                bit /= 10;
            }
        }
        return re;
    }

    // linked-list-cycle
    bool hasCycle(ListNode *head) {
        ListNode* head1 = head, *head2 = head;
        while(head1 && head2) {
            head1 = head1->next;
            if(head2->next) head2 = head2->next->next;
            else return false;
            if(head1 == head2) return true;
        }
        return false;
    }

    // populating-next-right-pointers-in-each-node
    void connect(TreeLinkNode *root) {
        if(!root) return;
        if(root->left && root->right) root->left->next = root->right;
        if(root->next && root->right) root->right->next = root->left;
        connect(root->left);
        connect(root->right);
    }

    // palindrome-number
    bool isPalindrome(int x) {
        if(x < 0) return false;
        long re = 0, temp = x;
        while(temp) {
            re = re * 10 + temp % 10;
            temp /= 10;
            if(re > INT_MAX) return false;
        }
        return re == x;
    }

    // best-time-to-buy-and-sell-stock
    int maxProfit1(vector<int> &prices) {
        //注意函数名，这里为了避免重复写成了maxProfit1(),实际应该是maxProfit()
        if(prices.size() < 2) return 0;
        int dp[prices.size()];
        int minIndex = 0, profit = 0;
        for(int i = 1; i < prices.size(); ++i) {
            if(prices[i] > prices[minIndex]) profit = max(profit, prices[i] - prices[minIndex]);
            else minIndex = i;
        }
        return profit;
    }

    // unique-binary-search-trees
    /*
    //11. unique-binary-search-trees
    int numTrees(int n) {
        //catalan number (2n)!/((n+1)!(n)!)
        if(n < 2) return 1;
        long long sum = 1;
        for(int i = 2; i <= n; ++i) sum *= n + i;
        for(int i = 2; i <= n; ++i) sum /= i;
        return sum;
    }*/
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

    // search-insert-position
    int searchInsert(int A[], int n, int target) {
        //使用库函数lower_bound()
        //return lower_bound(A, A + n, target) - A;
        int lo = 0, hi = n;
        while(lo < hi) {
            int mid = (lo + hi) >> 1;
            if(A[mid] == target) return mid;
            else if(A[mid] < target) lo = mid + 1;
            else hi = mid;
        }
        return lo;
    }

    // maximum-subarray
    int maxSubArray(int A[], int n) {
        if(n < 1) return 0;
        int maxSub = A[0], temp = A[0];
        for(int i = 1; i < n; ++i) {
            temp = A[i] + max(0, temp);
            maxSub = max(maxSub, temp);
        }
        return maxSub;
    }

    // rotate-image
    void rotate(vector<vector<int> > &matrix) {
        if(matrix.empty()) return;
        for(int  i = 0; i < matrix.size(); ++i) {
            for(int j = i; j < matrix.size(); ++j) {
                swap(matrix[j][i], matrix[i][j]);
            }
        }
        for(int i = 0; i < matrix.size(); ++i) {
            int lo = 0, hi = matrix.size() - 1;
            while(hi >= lo) {
                swap(matrix[i][lo], matrix[i][hi]);
                ++lo;
                --hi;
            }
        }
    }

    //roman-to-integer
    int romanToInt(string s) {
        //I(1), X(10), C(100), M(1000), V(5), L(50), D(500)
        map<string, int> myMap{ {"", 0}, {"I", 1}, {"II", 2}, {"III", 3}, {"IV", 4}, {"V", 5}, {"VI", 6}, {"VII", 7}, {"VIII", 8}, {"IX", 9},
            {"X", 10}, {"XX", 20}, {"XXX", 30}, {"XL", 40}, {"L", 50}, {"LX", 60}, {"LXX", 70}, {"LXXX", 80}, {"XC", 90},
            {"C", 100}, {"CC", 200}, {"CCC", 300}, {"CD", 400}, {"D", 500}, {"DC", 600}, {"DCC", 700}, {"DCCC", 800}, {"CM", 900},
            {"M", 1000}, {"MM", 2000}, {"MMM", 3000} };
        if(s.size() <= 1) return myMap[s];
        int number = 0;
        for(int i = 0; i < s.size();) {
            if(i + 3 < s.size() && myMap[s.substr(i, 4)]) {
                number += myMap[s.substr(i, 4)];
                i += 4;
            }
            else if(i + 2 < s.size() && myMap[s.substr(i, 3)]) {
                number += myMap[s.substr(i, 3)];
                i += 3;
            }
            else if(i + 1 < s.size() && myMap[s.substr(i, 2)]) {
                number += myMap[s.substr(i, 2)];
                i += 2;
            }
            else if(i < s.size() && myMap[s.substr(i, 1)]) {
                number += myMap[s.substr(i, 1)];
                ++i;
            }
        }
        return number;
    }

    //climbing-stairs
    /*对数算法，利用矩阵的快速幂
    Matrix fast_multi(int n) {
        Matrix m(1, 1, 1, 0), result(1, 0, 0, 1);
        while(n) {
            if(n & 1) result = result * m;
            m = m * m;
            n >>= 1;
        }
        return result;
    }
    int climbStairs(int n) {
        Matrix m = fast_multi(n);
        return m.m00;
    }*/
    int climbStairs(int n) {
        //Fibonacci sequence: 0, 1, 1, 2, 3, 5, 8, 13, 21, ...
        //dp time:O(n) space O(1);
        if(n <= 2) return n;
        int first = 1, second = 2, temp;
        for(int i = 2; i < n; ++i) {
            temp = second;
            second += first;
            first = temp;
        }
        return second;
    }

    //binary-tree-inorder-traversal 中序遍历
    void goLeft(TreeNode *root, stack<TreeNode*>& sta) {
        while(root) {
            sta.push(root);
            root = root->left;
        }
    }
    vector<int> inorderTraversal(TreeNode *root) {
        vector<int> result;
        stack<TreeNode *> sta;
        while(true) {
            goLeft(root, sta);
            if(sta.empty()) break;
            root = sta.top();
            sta.pop();
            result.push_back(root->val);
            root = root->right;
        }
        return result;
    }

};
#endif // LEETCODEINNOWCODER_H_INCLUDED
