/*The following lines of code attempt to break the MD4 hashing algorithm by finding a collision. This code implements the attack described by Hans Dobberten in his paper "Cryptanalysis of MD4"
*/

/*Include the necessary header files and MD4 function definitions and constants. */
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#define K1 0x0
#define rt2 0x5a827999
#define rt3 0x6ed9eba1
unsigned int hexrandom();

unsigned int f(unsigned int X, unsigned int Y, unsigned int Z)
{
        return ((X & Y)|(~X & Z));
}

unsigned int g(unsigned int X, unsigned int Y, unsigned int Z)
{
        return ((X&Y)|(X&Z)|(Y&Z));
}

unsigned int h(unsigned int X, unsigned int Y, unsigned int Z)
{
        return ((X^Y^Z));
}
unsigned int shift(unsigned int X, int S) 
{ 
	return ((X<<S)|(X>>(32-S))); 
}

#define R1(A,B,C,D,i,s)      A = shift(((A) +(f(B,C,D)) + (X[i])),(s))
#define R2(A,B,C,D,i,s)      A = shift(((A) + (g(B,C,D)) + (X[i]) + (rt2)),(s))
#define R3(A,B,C,D,i,s)      A = (shift(((A) + (h(B,C,D)) + (X[i]) + (rt3)),(s)))

/*The hexrev function shifts values by corresponding to little-bit-endian and big-byte-endian-ness. Before printing a value, send it here for correcting the endian-ness.*/
unsigned int hexrev(unsigned int x) 


{
	unsigned int a = x;
	unsigned int a1,a2,a3,a4,ans;
	a1 = a % 0x100;
	a = a/0x100;
	a2 = a%0x100;
	a = a/0x100;
	a3 = a%0x100;
	a = a/0x100;
	a4 = a%0x100;
	ans=a4+a3*0x100+a2*0x10000+a1*0x1000000;
	return ans;
}

/*The function twopower for any integer i generates 2^(4i).*/

unsigned int twopower(int j)

{
	unsigned int a=1;
	int i = 4*j;
	while(i)
	{
		a = 2*a;
		i--;
	}
	return a;
}

/*The function hexrand generates one random bit leaving the first 4i bits. */

unsigned int hexrand(int i)

{
	unsigned int a,b;
	int j = 4*i;
	srand(time(NULL));
	a = 1 + rand() % j; 
	a = 32 - a;
	b = 1;
	while(a)
	{
		b = 2*b;
		a--;
	}
	
	return b;
}


/*The function md4 computes the MD4 hash value for an input 512-bit block. */

unsigned int md4(unsigned int block[16])

{
	unsigned int X[16];
	int i;
	for(i=0;i<16;i++)
		X[i] = block[i];

	unsigned int A = hexrev(0x01234567);
	unsigned int B = hexrev(0x89abcdef);
	unsigned int C = hexrev(0xfedcba98);
	unsigned int D = hexrev(0x76543210);
	
	unsigned int P,Q,R,S;
	P = A;
	Q = B;
	R = C;
	S = D;

	R1(A,B,C,D,  0,  3);
        R1(D,A,B,C,  1,  7);
        R1(C,D,A,B,  2, 11);
        R1(B,C,D,A,  3, 19);
        R1(A,B,C,D,  4,  3);
        R1(D,A,B,C,  5,  7);
        R1(C,D,A,B,  6, 11);
        R1(B,C,D,A,  7, 19);
        R1(A,B,C,D,  8,  3);
        R1(D,A,B,C,  9,  7);
        R1(C,D,A,B, 10, 11);
        R1(B,C,D,A, 11, 19);
        R1(A,B,C,D, 12,  3);
        R1(D,A,B,C, 13,  7);
        R1(C,D,A,B, 14, 11);
        R1(B,C,D,A, 15, 19);

	R2(A,B,C,D,  0,  3);
	R2(D,A,B,C,  4,  5);
        R2(C,D,A,B,  8,  9);
        R2(B,C,D,A, 12, 13);
        R2(A,B,C,D,  1,  3);
        R2(D,A,B,C,  5,  5);
        R2(C,D,A,B,  9,  9);
        R2(B,C,D,A, 13, 13);
        R2(A,B,C,D,  2,  3);
        R2(D,A,B,C,  6,  5);
        R2(C,D,A,B, 10,  9);
        R2(B,C,D,A, 14, 13);
        R2(A,B,C,D,  3,  3);
        R2(D,A,B,C,  7,  5);
        R2(C,D,A,B, 11,  9);
        R2(B,C,D,A, 15, 13);

	R3(A,B,C,D,  0,  3);
        R3(D,A,B,C,  8,  9);
        R3(C,D,A,B,  4, 11);
        R3(B,C,D,A, 12, 15);
        R3(A,B,C,D,  2,  3);
        R3(D,A,B,C, 10,  9);
        R3(C,D,A,B,  6, 11);
        R3(B,C,D,A, 14, 15);
        R3(A,B,C,D,  1,  3);
        R3(D,A,B,C,  9,  9);
        R3(C,D,A,B,  5, 11);
        R3(B,C,D,A, 13, 15);
        R3(A,B,C,D,  3,  3);
        R3(D,A,B,C, 11,  9);
        R3(C,D,A,B,  7, 11);
        R3(B,C,D,A, 15, 15);
        A += P;
        B += Q;
        C += R;
        D += S;
	
	printf("\nThe input message is:\n");
	for(i=0;i<16;i++)
		printf("%#x ", X[i]);

	printf("\nThe MD4 Hash is:\n %#x %#x %#x %#x \n", hexrev(A), hexrev(B), hexrev(C), hexrev(D));
}

int main()

{	
	int firstroundcount = 0;
	int secondroundcount_a = 0;
	int secondroundcount_b = 0;
	int i;
	unsigned int A_b, B_b, C_b, D_b, Z_b, W_b;
	unsigned int As, Bs, Cs, Ds, Z, W, Zb, Wb, Csb, Bsb,V,Vb;

	srand(time(NULL));
	/*initializes the seed of the random function. to generate further numbers, use /variable = 1 + rand()%0x10000000;/ */
	/*Step 1A of inner collision searching: #generate A1, B1, C1, D1, Z and W randomly.*/
	generate: As = 1 + rand()%0x10000000;
	Bs = 1 + rand()%0x10000000;
	Cs = 1 + rand()%0x10000000;
	Ds = 1 + rand()%0x10000000;
	Z  = 1 + rand()%0x10000000;
	W  = 1 + rand()%0x10000000;
	/*Step 1B of inner collision searching: Compute Zb, Wb, V and Vb*/
	Bsb = (Bs) - 1<<25;
	Csb = (Cs) + 1<<5;
	Zb = Z - g(Csb, Ds, As) + g(Cs, Ds, As) +shift(Bsb,19) -shift(Bs,19) - 1;
	Wb = W - g(Ds, As, Zb) + g(Ds, As, Z) +shift(Csb,23) - shift(Cs,23);
	V = shift(W,1) - shift(Wb,21);
	Vb = V - g(As, Zb, Wb) + g(As, Z, W);

	/*Step 1C of inner collision searching: Test if equation 23 is satisfied. Else go to #generate. */
	if(((g(Z,W,V))-(g(Zb,Wb,Vb)))==1)
	{	
		printf("First step Satisfied with %d iterations and g value as %#x. Proceeding to second step.\n", firstroundcount, ((g(Z,W,V)-g(Zb,Wb,Vb))));
		/*Step 2A: Take the values found in step 1 as the basic values for step 2, denoted by X_b. */
		assign:A_b = As;
		B_b = Bs;
		C_b = Cs;
		D_b = Ds;
		Z_b = Z;
		W_b = W;
		 
		/*We call function hexrandom() to change one random bit.*/
		A_b = ((A_b)^(hexrandom()));
		B_b = ((B_b)^(hexrandom()));
		C_b = ((C_b)^(hexrandom()));
		D_b = ((D_b)^(hexrandom()));
		Z_b = ((Z_b)^(hexrandom()));
		W_b = ((W_b)^(hexrandom()));
		/*Step 2C: Compute the associated Zb, Wb, V and Vb. */	
		compute:Zb = Z - g(Csb, D_b, A_b) + g(C_b, D_b, A_b) +shift(Bsb,19) - shift(B_b,19) - 1;
		Wb = W - g(D_b, A_b, Zb) + g(D_b, A_b, Z_b) +shift(Csb,23) -shift(C_b,23);
		V = shift(W_b,21) - shift(Wb,21);
		Vb = V - g(A_b, Zb, Wb) + g(A_b, Z_b, W_b);\
		Csb = shift(Csb, -23);
		Bsb = shift(Bsb, -19);
		Wb = shift(Wb, -21);
		/*Now test if equation 23 still holds.*/
		if(((g(Z_b, W_b,V))-(g(Zb,Wb,Vb)))==1)
		{	
			unsigned int equation24 = (f(Wb, Vb, -1))-(f(W_b,V,0)) - shift(Zb,13) + shift(Z_b,13);
			/*check if equation 24 has last 4i bits as zero. If zero, then set these as the new base values and compute.*/
			for(i=1;i<9;i++)
			{
				unsigned int divider = 1<<(4*i);
				/*Check if last 4i bits of equation 24 are zero or not. If not zero, then start step 2 again with newest base
					values. If they are zero, then set these as the new basic values, continue with for loop.*/
				if(((equation24)%divider)!=0)
				{
					secondroundcount_b++;
					goto assign;
				}
				else
				{
					As = A_b;
					Bs = B_b;
					Cs = C_b;
					Ds = D_b;
					Z = Z_b;
					W = W_b;
				}
			} 
		}
		/*The set of values with which the registers exit the loop are the required solutions.*/
		else
		{
		//	printf("\n%#x\n", (g(Z_b,W_b,V)-g(Zb,Wb,Vb)));
			secondroundcount_a++;
		//	printf("\nLooping Second Round.. %d\n", secondroundcount_a);
			goto assign;
		}
		
		/*Find an admissible inner collision.*/
		if((g(Bs, Cs, Ds))==(g(Bsb, Csb, Ds)))
		{
			/*End of Step 2: An Admissible Inner Collision has been found. */
			/*Now compute the message values by satisfying equations 9 to 17 and 22.*/
			unsigned int X[16];
			unsigned int A,C,D;
			unsigned int U = 0;
			unsigned int Ub = 0xffffffff;
			unsigned int B = 0;
			C = shift(V,25) - shift(Vb,25);
			X[12] = 1 + rand() % 0x10000000;
			X[13] = 1 + rand() % 0x10000000;
			X[14] = shift(W,21) - C - f(V,U,B);
			X[15] = shift(Z,13) - B - f(W,V,U);
			X[0]  = shift(As,29) - U - g(Z,W,V) - K1;
			X[4]  = shift(Ds,27) - V - g(As,Z,W) - K1;
			X[8]  = shift(Cs,23) - W - g(Ds,As,Z) - K1;
			X[12] = shift(Bs,19) - Z - g(Cs,Ds,As) - K1;
			D = shift(V,25) - f(U,B,C) - X[13];
			A = shift(U,19) - f(B,C,D) - X[12];

			/*End of computing message values. */
			/*Beginning of Round 3: Finding initial values.*/
			
			X[1] = 1 + rand() % 0x10000000;
			X[2] = 1 + rand() % 0x10000000;
			X[3] = 1 + rand() % 0x10000000;
			X[5] = 1 + rand() % 0x10000000;
			
			/*Compute Rounds 0 to 5.*/
			unsigned int IV1 = hexrev(0x01234567);
			unsigned int IV2 = hexrev(0x89abcdef);
			unsigned int IV3 = hexrev(0xfedcba98);
			unsigned int IV4 = hexrev(0x76543210);
			
			unsigned int P,Q,R,S;
			P = IV1;
			Q = IV2;
			R = IV3;
			S = IV4;
			
			R1(IV1, IV2, IV3, IV4, 0, 3);
			R1(IV1, IV2, IV3, IV4, 1, 7);
			R1(IV1, IV2, IV3, IV4, 2, 11);
			R1(IV1, IV2, IV3, IV4, 3, 19);
			R1(IV1, IV2, IV3, IV4, 4, 3);
			R1(IV1, IV2, IV3, IV4, 5, 7);
			/*Rounds 0 to 5 computed*/
			unsigned int C6 = shift(A,29) - IV1 - X[8];
			unsigned int B7 =0xffffffff;
			X[6] = -IV3 - f(IV4, IV1, IV2) + shift(C6,21);
			X[7] = -IV2 - f(C6,IV4,IV1) - 1;
			X[9] = shift(D,25) - IV4 - f(A, -1, C6);
			X[10] = shift(C,21) - C6 - f(D,A,-1);
			X[11] = shift(B,13) + 1 - f(C,D,A);
			
			/*End of assignment of initial values. */
			
			unsigned int X_new[16];
			for(i=0;i<16;i++)
				X_new[i] = X[i];
			X_new[12] = X[12] + 1;
			
			md4(X);
			md4(X_new);	
			
			long int total = secondroundcount_a + secondroundcount_b + firstroundcount;
			int power = 0;
			long int total2 = total;
			while(total2)
			{
				total2 = total2/2;
				power++;
			}

			printf("\nWe found a collision after %ld iterations. This is around 2^%d.\n", total, power);
		}
		else
		{
			secondroundcount_a++;
			goto assign;
		}		
		

	}
		
	else 
	{
	//	printf("\n%#x\n", ((g(Z,W,V))-(g(Zb,Wb,Vb))));
		firstroundcount++;
		goto generate;
	}
	
		
	
}

unsigned int hexrandom()
{
	unsigned int a=0;
	srand(time(NULL));

	a = rand() % 32;
	return (1<<a);
}
