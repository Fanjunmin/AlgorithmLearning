#include "leetcodeInNowcoder.h"

using namespace std;
int main()
{
    Solution s;
//2. reverse-integer
    //cout << s.reverse(12345);

//6. integer-to-roman
    //cout << s.intToRoman(0);

//9. palindrome-number
    //cout << s.isPalindrome(1233291);

//10. best-time-to-buy-and-sell-stock
    //vector<int> vec{7,1,5,3,6,4};
    //cout << s.maxProfit1(vec);

//roman-to-integer
    //cout << s.romanToInt("MMMCCCXCVI");

//climbing-stairs
    Matrix m = s.fast_multi(2);
    cout << m.m00 << ends << m.m01 << ends << m.m10 << ends << m.m10 << endl;
    cout << s.climbStairs(3);
    return 0;
}
