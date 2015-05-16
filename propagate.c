#include <stdio.h>
#include "sha2.h"

int main() {

	char bitChar;
	int bit[4][2];
	int nComb;

	if (bitChar = '?') {
		nComb = 4;
		bit[0][0] = 0;
		bit[0][1] = 0;
		bit[1][0] = 1;
		bit[1][1] = 1;
		bit[2][0] = 0;
		bit[2][1] = 1;
		bit[3][0] = 1;
		bit[3][1] = 0;
	}

	if (bitChar = '-') {
		nComb = 2;
		bit[0][0] = 0;
		bit[0][1] = 0;
		bit[1][0] = 1;
		bit[1][1] = 1;
	}

	if (bitChar = 'x') {
		nComb = 2;
		bit[0][0] = 1;
		bit[0][1] = 0;
		bit[1][0] = 0;
		bit[1][1] = 1;

	}

	




}