#ifndef MATHOPERATIONS_H
#define MATHOPERATIONS_H

//Math operations only with bit operations
class MathOperations
{
public:
    static int addition(int a, int b){
        // a + b
        /*
        if(b == 0) return a; //û�н�λ��ʱ���������
        int sum, carry;
        sum = a ^ b;        //û�н�λ�ļӷ�����
        carry = (a & b) << 1;   //��λ�����ƣ�
        return addition(sum, carry); //�ݹ�
        */
        return b == 0 ? a : addition(a ^ b, (a & b) << 1);
    }

    static int substrction(int a, int b){
        // a - b
        /*
        int substractor = addition(~b, 1); //ȡb�Ĳ��루ȡ����һ��
        return addition(a, substractor);
        */
        return addition(a, addition(~b, 1));
    }

    static int absValue(int a){
        // a�ľ���ֵ|a|
        return a < 0 ? addition(~a, 1) : a;
    }

    static int oppValue(int a){
        // a���෴��
        return addition(~a, 1);
    }

    static int multiplication(int a, int b){
        // a * b
        //ȡ����ֵ
        int multiplicand = absValue(a), multiplier = absValue(b);
        int count = 0, product = 0;
        //�üӷ�����˷�
        while(count < multiplier){
            product = addition(product, multiplicand);
            count = addition(count, 1);
        }
        //�����ж�
        return (a ^ b) >= 0 ? product : oppValue(product);
    }

    static int division(int a, int b){
        // a / b
        int dividend = absValue(a), divisor = absValue(b);
        int quotient = 0, remainder = 0;    //�̺�����
        while(divisor <= dividend){
            quotient = addition(quotient, 1);
            dividend = substrction(dividend, divisor);
        }
        //�����ж�
        return (a ^ b) >= 0 ? quotient : oppValue(quotient);
    }
};

#endif // MATHOPERATIONS_H
