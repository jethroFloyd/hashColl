/** 
 * Code to Propagate Conditions
 *
 * Author: Ritobroto Maitra, ritobrotomaitra [at] gmail.com
 * Mentor: Dr. Somitra Sanadhya, somitra [at] iiitd.ac.in
 *
 * Code is as yet unoptimized.
 *
 */


#include <stdio.h>
#include "sha2.h"
#include <string.h>

typedef struct bitStyle {

	unsigned int bit1:1;
	unsigned int bit2:2;
} bitStyle;

typedef struct bitPattern {

	bitStyle bits[4];
	int count;
	char name;
} bitPattern;

int main() {

	bitStyle ZZ;
	ZZ.bit1 = 0;
	ZZ.bit2 = 0;

	bitStyle OZ;
	OZ.bit1 = 1;
	OZ.bit2 = 0;

	bitStyle ZO;
	ZO.bit1 = 0;
	ZO.bit2 = 1;
	
	bitStyle OO;
	OO.bit1 = 1;
	OO.bit2 = 1;

	bitPattern patternMS[16]; /* Pattern Mother Set */
	
	
	patternMS[0].name='?';
	patternMS[0].count=4;
	patternMS[0].bits[0]=ZZ;
	patternMS[0].bits[1]=ZO;
	patternMS[0].bits[2]=OZ;
	patternMS[0].bits[3]=OO;

	patternMS[1].name='-';
	patternMS[1].count=2;
	patternMS[1].bits[0]=ZZ;
	patternMS[1].bits[1]=OO;

	patternMS[2].name='x';
	patternMS[2].count=2;
	patternMS[2].bits[0]=OZ;
	patternMS[2].bits[1]=ZO;

	patternMS[3].name='0';
	patternMS[3].count=1;
	patternMS[3].bits[0]=ZZ;

	patternMS[4].name='u';
	patternMS[4].count=1;
	patternMS[4].bits[0]=OZ;

	patternMS[5].name='n';
	patternMS[5].count=1;
	patternMS[5].bits[0]=ZO;

	patternMS[6].name='1';
	patternMS[6].count=1;
	patternMS[6].bits[0]=OO;

	patternMS[7].name='#';
	patternMS[7].count=0;

	patternMS[8].name='3';
	patternMS[8].count=2;
	patternMS[8].bits[0]=ZZ;
	patternMS[8].bits[1]=OZ;

	patternMS[9].name='5';
	patternMS[9].count=2;
	patternMS[9].bits[0]=ZZ;
	patternMS[9].bits[1]=ZO;

	patternMS[10].name='7';
	patternMS[10].count=3;
	patternMS[10].bits[0]=ZZ;
	patternMS[10].bits[1]=OZ;
	patternMS[10].bits[2]=ZO;

	patternMS[11].name='A';
	patternMS[11].count=2;
	patternMS[11].bits[0]=OZ;
	patternMS[11].bits[1]=OO;

	patternMS[12].name='B';
	patternMS[12].count=3;
	patternMS[12].bits[0]=ZZ;
	patternMS[12].bits[1]=OZ;
	patternMS[12].bits[2]=OO;

	patternMS[13].name='C';
	patternMS[13].count=2;
	patternMS[13].bits[0]=ZO;
	patternMS[13].bits[1]=OO;

	patternMS[14].name='D';
	patternMS[14].count=3;
	patternMS[14].bits[0]=ZZ;
	patternMS[14].bits[1]=ZO;
	patternMS[14].bits[2]=OO;

	patternMS[15].name='E';
	patternMS[15].count=3;
	patternMS[15].bits[0]=OZ;
	patternMS[15].bits[1]=ZO;
	patternMS[15].bits[2]=OO;

	



}

/** Reference:
 *
 *	bitPattern abcd;
 *	abcd.count = 2;
 *	abcd.bits[0] = OZ;
 *
 *	printf("'%d' \n ", abcd.bits[0].bit1); 
 *
 */


	