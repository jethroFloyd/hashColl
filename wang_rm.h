#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define left(x, y) (((x) << (y)) | ((x) >> (32 - (y))))
#define right(x, y) (((x) >> (y)) | ((x) << (32 - (y))))
#define f(x, y, z) ((x & y) | ( ~x & z))
#define g(x, y, z) ((x & y) | (y & z) | (z & x))
#define h(x, y, z) (x ^ y ^ z)

#define	genReg(i)		Reg[i] = left(Reg[i-4] + g(Reg[i-1],Reg[i-2],Reg[i-3]) + X0[(((i-17)*4)%15)] + rt2, s[i])
#define genReg1(i)		Reg1[i] = left(Reg1[i-4] + g(Reg1[i-1],Reg1[i-2],Reg1[i-3]) + X1[(((i-17)*4)%15)] + rt2, s[i])
#define genRegh(i)		Reg[i] = left(Reg[i-4] + h(Reg[i-1], Reg[i-2], Reg[i-3]) + X0[j[i-33]] + rt3, s[i])
#define genRegh1(i)		Reg1[i] = left(Reg[i-4] + h(Reg1[i-1], Reg1[i-2], Reg1[i-3]) + X1[j[i-33]] + rt3, s[i])
#define	msgMod(i)		X0[i-1] = right(Reg[i],s[i]) - f(Reg[i-1],Reg[i-2],Reg[i-3]) - Reg[i-4]
#define	msgMod1(i)		X1[i-1] = right(Reg1[i],s[i]) - f(Reg1[i-1],Reg1[i-2],Reg1[i-3]) - Reg1[i-4]
#define msgcheck(i)		{msgMod(i);msgMod1(i);if(check(i))goto beginning;}
#define OR(i)           	|(1<<(i-1))
#define AND(i)          	&~(1<<(i-1))
#define Prev(i,j,k)     	Reg[i] |= Reg[j] & (1<<(k-1))
#define NOT(i,j,k,l,m,n)        Reg1[i] = (((((Reg[i] ^ (1<<(j-1)))^(1<<(k-1)))^(1<<(l-1)))^(1<<(m-1)))^(1<<(n-1))) 

unsigned int Reg[49], Reg1[49];
unsigned int X0[16], X1[16];
unsigned int A = 0x67452301;
unsigned int B = 0xefcdab89;
unsigned int C = 0x98badcfe;
unsigned int D = 0x10325476;
unsigned int rt2 = 0x5a827999;
unsigned int rt3 = 0x6ed9eba1;
int s[49];
int j[16];

int check(int i)

{
	if(X0[i-1]==X1[i-1])
		return 0;
	else
		return 1;
}
