#ifndef COMPLEX_H_INCLUDED
#define COMPLEX_H_INCLUDED

#include <cmath>
class complex;
//ʵ��"+="�ľ��庯��
complex& __doapl (complex* ths, const complex& r);
//ʵ��"-="�ľ��庯��
complex& __doami (complex* ths, const complex& r);
//ʵ��"*="�ľ��庯��
complex& __doaml (complex* ths, const complex& r);

class complex
{
public:
    //defalut ctor
    complex(double r = 0, double i = 0)
        : re (r), im (i)
    {   }
    //���������
    complex& operator += (const complex&);
    complex& operator -= (const complex&);
    complex& operator *= (const complex&);
    //��ȡʵ�����鲿
    double real () const { return re; }
    double imag () const { return im; }
private:
    double re, im;

    friend complex& __doapl (complex*, const complex&);
    friend complex& __doami (complex*, const complex&);
    friend complex& __doaml (complex*, const complex&);
};

inline complex&
__doapl (complex* ths, const complex& r)
{
    ths->re += r.re;
    ths->im += r.im;
    return *ths;
}

inline complex&
__doami (complex* ths, const complex& r)
{
    ths->re -= r.re;
    ths->im -= r.im;
    return *ths;
}

inline complex&
__doaml (complex* ths, const complex& r)
{
    double f = ths->re * r.re - ths->im * r.im;
    ths->im = ths->re * r.im + ths->im * r.re;
    ths->re = f;
    return *ths;
}

inline complex&
complex::operator += (const complex& r)
{
    return __doapl (this, r);
}

inline complex&
complex::operator -= (const complex& r)
{
    return __doami (this, r);
}

inline complex&
complex::operator *= (const complex& r)
{
    return __doaml (this, r);
}

//��ȡʵ��
inline double
real (const complex& r)
{
    return r.real ();
}

//��ȡ�鲿
inline double
imag (const complex& r)
{
    return r.imag ();
}

//�����"+"����
inline complex
operator + (const complex& r)
{
    return r;
}

inline complex
operator + (const complex& x, const complex& y)
{
    return complex (real (x) + real (y), imag (x) + imag (y));
}

inline complex
operator + (double x, const complex& y)
{
    return complex (x + real (y), imag (y));
}

inline complex
operator + (const complex& x, double y)
{
    return complex(real (x) + y, imag (x));
}

//�����"-"����
inline complex
operator - (const complex& r)
{
    return complex(-real (r), -imag (r));
}

inline complex
operator - (const complex& x, const complex& y)
{
    return complex (real (x) - real (y), imag (x) - imag (y));
}

inline complex
operator - (double x, const complex& y)
{
    return complex (x - real (y), -imag (y));
}

inline complex
operator - (const complex& x, double y)
{
    return complex(real (x) - y, imag (x));
}

//�����"*"����
inline complex
operator * (const complex& x, const complex& y)
{

    return complex (real (x) * real (y) - imag (x) * imag (y),
                    real (x) * imag( y) + real (y) * imag (x));
}

inline complex
operator * (double x, const complex& y)
{
    return complex (x * real (y), x * imag (y));
}

inline complex
operator * (const complex& x, double y)
{
    return complex(y * real (x), y * imag (x));
}

//����
inline double norm (const complex& r);


//�����"/"����
inline complex
operator / (const complex& x, const complex& y)
{
    double r = (real (x) * real (y) + imag (x) * imag (y)) / norm (y);
    double i = (-real (x) * imag (y) + imag (x) * real (y)) / norm (y);
    return complex (r, i);
}

inline complex
operator / (const complex& x, double y)
{
    return complex (real (x) / y, imag (x) / y);
}

inline complex
operator / (double x, const complex& y)
{
    return complex (x * real (y) / norm (y), -x * imag (y) / norm (y));
}

//�����"=="����
inline bool
operator == (const complex& x, const complex& y)
{
    return real (x) == real (y) && imag (x) == imag (y);
}

inline bool
operator == (const complex& x, double y)
{
    return real (x) == y && imag (x) == 0;
}

inline bool
operator == (double x, const complex& y)
{
    return x == real (y) && 0 == imag (y);
}

//�����"!="����
inline bool
operator != (const complex& x, const complex& y)
{
    return real (x) != real (y) || imag (x) != imag (y);
}

inline bool
operator != (const complex& x, double y)
{
    return real (x) != y || imag (x) != 0;
}

inline bool
operator != (double x, const complex& y)
{
    return x != real (y) || 0 != imag (y);
}

//����
inline complex
conj (const complex& r)
{
    return complex(real (r), -imag (r));
}

//����
inline double
norm (const complex& r)
{
    return real (r) * real (r) + imag (r) * imag (r);
}

//������ת��
inline complex
polar (double r, double t)
{
    return complex (r * sin (t), r * cos (t));
}

#endif // COMPLEX_H_INCLUDED
