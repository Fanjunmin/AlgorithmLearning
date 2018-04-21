#ifndef FRACTION_H_INCLUDED
#define FRACTION_H_INCLUDED

class Fraction
{
public:
    explicit Fraction (int num, int den = 1)
        : m_numberator (num), m_denominator (den) { }
    //转换函数conversion function
    operator double () const {
        return static_cast<double> (m_numberator) / m_denominator;
    }


    //Fraction operator+ (const Fraction& f){
    //    return Fraction(2, 3);
    //}

private:
    int m_numberator;   //分子
    int m_denominator;  //分母
};

#include <iostream>

#endif // FRACTION_H_INCLUDED
