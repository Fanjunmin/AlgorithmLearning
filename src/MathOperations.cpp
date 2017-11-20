#include "MathOperations.h"

int MathOperations::addition(int a, int b){
    // a + b
    /*
    if(b == 0) return a; //没有进位的时候完成运算
    int sum, carry;
    sum = a ^ b;        //没有进位的加法运算
    carry = (a & b) << 1;   //进位（左移）
    return addition(sum, carry); //递归
    */
    return b == 0 ? a : addition(a ^ b, (a & b) << 1);
}

int MathOperations::substrction(int a, int b){
    // a - b
    /*
    int substractor = addition(~b, 1); //取b的补码（取反加一）
    return addition(a, substractor);
    */
    return addition(a, addition(~b, 1));
}

int MathOperations::absValue(int a){
    // a的绝对值|a|
    return a < 0 ? addition(~a, 1) : a;
}

int MathOperations::oppValue(int a){
    // a的相反数
    return addition(~a, 1);
}

int MathOperations::multiplication(int a, int b){
    // a * b
    //取绝对值
    int multiplicand = absValue(a), multiplier = absValue(b);
    int count = 0, product = 0;
    //用加法计算乘法
    while(count < multiplier){
        product = addition(product, multiplicand);
        count = addition(count, 1);
    }
    //符号判断
    return (a ^ b) >= 0 ? product : oppValue(product);

}

int MathOperations::division(int a, int b){
    int dividend = absValue(a), divisor = absValue(b);
    int quotient = 0, remainder = 0;    //商和余数
    while(divisor <= dividend){
        quotient = addition(quotient, 1);
        dividend = substrction(dividend, divisor);
    }
    //符号判断
    return (a ^ b) >= 0 ? quotient : oppValue(quotient);
}


