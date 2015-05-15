#include <stdio.h>
#include "sha2.h"

int main() {

	unsigned int m1[64] = {0};
	unsigned int m2[64] = {0};

	/* Initialized the two message words */

	expandWord(m1);
	expandWord(m2);

	unsigned int a1[64] = {0};
	unsigned int a2[64] = {0};
	unsigned int e1[64] = {0};
	unsigned int e2[64] = {0};

	// Add initialization vectors here.

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

