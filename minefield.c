#include <stdio.h>
#include "sha2.h"

int main() {


	srand(time(NULL));

	unsigned int m1[64] = {0};
	unsigned int m2[64] = {0};

	/* Initialized the two message words */

	expandWord(m1);
	expandWord(m2);

	unsigned int a1[64] = {0};
	unsigned int a2[64] = {0};
	unsigned int e1[64] = {0};
	unsigned int e2[64] = {0};

	// ***** Add initialization vectors here.

	// Starting the notation.

	char a[64][32];
	char e[64][32];
	char m[64][32];

	initialPop(e) // Initially populate all message words with ?

	return 0;
}

int expandWord(unsigned int test[]) {
	int i;
	for(i=16;i<64;i++)
		test[i] = (s1(test[i-2])) + test[i-7] + (s0(test[i-15])) + test[i-16];

	return 0;
}

int updateReg(unsigned int A[], unsigned int E[], unsigned int m[], int n) {

	// Compute the register value E[n], having already computed the others.
	// Pass parameters as: updateReg (a1, e1, m1, n) or updateReg(a2, e2, m2, n)

		E[n] = E[n-4] + S1(E[n-1]) + ch(E[n-1], E[n-2], E[n-3]) + A[n-4] + k[n] + m[n];
		A[n] = -A[n-4] + S0(A[n-1]) + mj(A[n-1]), A[n-2], A[n-3]) + E[n];
}


int chooseQuesToDash(int n, unsigned int m[] ) {

	if (n>=16) 
		return -1;
	// maintain array of all '?' bits at this point.
	int quesBits[32];
	int i;
	for(i=0;i<32;i++)
		quesBits[i] = -1;
	int j = 0;
	for(i=0;i<32;i++){
		if (m[n][i] == '?') {
			quesBits[j] = i;
			j++;
		}
	}

	//Now we know which bits of 'm' are '?'
	// Let us now choose randomly a bit amongst these.
	int chooseBit = rand() % j;
	m[n][chooseBit] = '-';	
}
// The above function takes as input the characteristic of 'm' at a particular stage,
// chooses a random '?' bit and imposes '-' on that.

// Now we need a function to propagate this '-' condition.

// So, first, let us write a function to update a particular bit of A and E depending on M. n - step number
int updateBit (int bitPos, int step, unsigned int A[], unsigned int E[], unsigned int m[], char mChar[][32], char aChar[][32], char eChar[][32]) {

	// Let us build the bitPos - bit of A and E.
	int bitE, bitA, bitEC, bitAC;
	int chBit1 = extractBit(E, step - 1, bitPos);
	int chBit2 = extractBit(E, step - 2, bitPos);
	int chBit3 = extractBit(E, step - 3, bitPos);

	int chBit = ch(chBit1, chBit2, chBit3);

	int constBit = extractBit(k, step, bitPos);
	int wordBit = extractBit(m, step, bitPos);
	int EBit_4 = extractBit(E, step - 4, bitPos);
	int ABit_4 = extractBit(A, step - 4, bitPos);

	int sBit1 = extractBit(E, step - 1, (bitPos - 6) % 32);
	int sBit2 = extractBit(E, step - 1, (bitPos - 11) % 32);
	int sBit3 = extractBit(E, step - 1, (bitPos - 25) % 32);

	int sBit = sBit1 ^ sBit2 ^ sBit3; 

	int bitECarry = extractBit(ECarry, step, bitPos-1);

	int bitE = EBit_4 ^ sBit ^ chBit ^ ABit_4 ^ constBit ^ wordBit ^ bitECarry;

	int bitEC = (EBit_4 + sBit + chBit + ABit_4 + constBit + wordBit + bitECarry) >> 1;
	// Dropped the last bit to generate the carry.

	int SBit1 = extractBit(A, step - 1, (bitPos - 2) % 32);
	int SBit2 = extractBit(A, step - 1, (bitPos - 13) % 32);
	int SBit3 = extractBit(A, step - 1, (bitPost - 22) % 32);

	int SBit = SBit1 ^ SBit2 ^ SBit3;

	int bitACarry = extractBit(ACarry, step, bitPos - 1);

	int mjBit1 = extractBit(A, step - 1, bitPos);
	int mjBit2 = extractBit(A, step - 2, bitPos);
	int mjBit3 = extractBit(A, step - 3, bitPos);

	int mjBit = mj(mjBit1, mjBit2, mjBit3);

	int bitA = (-ABit_4) ^ SBit ^ bitE ^ mjBit;
	int bitACarry = ((-ABit_4) + SBit + bitE + mjBit) >> 1;

}

int extractBit (unsigned int reg[], int step, int pos) {
	
	int bit = ((reg[step] >> pos) & 1)
	return bit;
}

int setBit (unsigned int reg[], int step, int pos, int bit) {

	bit = bit << pos; // shift bit to the required position.
	reg[step] = reg[step] | bit; // 0110 | 0010 = 01 1 0, 0110 | 1000 = 1110 and so on.

	return 0;
}

