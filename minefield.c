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

// This is done by the update Control Unit.
int updateControlUnit (/* whatevre */) {
	// n is the current step number.
	


}

