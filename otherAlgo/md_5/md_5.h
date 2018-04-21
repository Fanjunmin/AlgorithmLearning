#ifndef MD_5_H_INCLUDED
#define MD_5_H_INCLUDED
#define A 0x67452301L
#define B 0x0EFCDAB89L
#define C 0x98BADCFEL
#define D 0x10325476L
#define F(X,Y,Z) ((X & Y) | ((~X) & Z))
#define G(X,Y,Z) ((X & Z) | (Y & (~Z)))
#define H(X,Y,Z) (X ^ Y ^ Z)
#define I(X,Y,Z) (Y ^ (X | (~Z)))




#endif // MD_5_H_INCLUDED
