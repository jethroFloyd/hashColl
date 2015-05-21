/** 
 * Code to Propagate Conditions
 *
 * Author: Ritobroto Maitra, ritobrotomaitra [at] gmail.com
 * Mentor: Dr. Somitra Sanadhya, somitra [at] iiitd.ac.in
 *
 * Code is as yet unoptimized.
 * Needs to be changed in order to conform to generalized differences.
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
char choose (char, char, char, bitPattern *);
int main() {


	/* Defining the four different possibilities */

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

	/* Pattern Mother Set */

	bitPattern patternMS[16]; 
	
	
	/**
	 *
	 *	Notation for Possible Generalized Conditions 
	 *	To generate the following lines, use auxProp.c 
	 *	Run: gcc auxProp.c -o auxProp.o && ./auxProp.o 
	 * 	This creates a file called auxProp.txt in the directory. 
	 *
	 *
	 */

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

	/* Dealing with the function 'choose' */
	/* Test condition */
	
	char result = choose ('3', '5', '7', patternMS);

	printf("\n%c\n", result);

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

char choose (char a, char b, char c, bitPattern *patternMS) {

	/* 
	 * We receive as parameters the differential conditions.
  	 * For example : choose (x, u, n)
  	 * We return a differential condition only.
  	 *
  	 */

  	 int i,j,k,p,q,r;
  	 for (i=0; i<16;i++) {
  	 	if(patternMS[i].name == a)
  	 		break;
  	 }

  	 for (j=0; j<16;j++) {
  	 	if (patternMS[j].name == b)
  	 		break;
  	 }

  	 for (k=0; k<16;k++) {
  	 	if (patternMS[k].name == c)
  	 		break;
  	 }

  	 int countA = patternMS[i].count;
  	 int countB = patternMS[j].count;
  	 int countC = patternMS[k].count;

  	 bitPattern patternFind;
  	 patternFind.name = '.';
  	 patternFind.count = 0;

  	 /* Consider the bit possibilities */
  	 int bit1A = -1;
  	 int bit2A = -1;

  	 for (p=0; p<countA; p++) {
  	 	if (p == 0) {
  	 		
  	 		bit1A = patternMS[i].bits[p].bit1;
  	 		bit2A = patternMS[i].bits[p].bit2;
  	 		continue;
  	 	}

  	 	if ((bit1A!= 2) && (patternMS[i].bits[p].bit1 != bit1A))
  	 		bit1A = 2;

		if ((bit2A!= 2) && (patternMS[i].bits[p].bit2 != bit2A))
  	 		bit2A = 2;  	 	
  	 }

  	 int bit1F = -1;
  	 int bit2F = -1;

  	 /* Find possibilities for Bit 1 of result. */

  	int s;
  	if (bit1A == 0)
  		s = k;
  	else if (bit1A == 1)
  		s = j;

  	if( bit1A != 2){
  	go: for (p=0; p<countC; p++) {

  			if (bit1F == 2)
  				break;

  	 		if(p == 0) {
  	 			bit1F = patternMS[s].bits[p].bit1;
  	 			continue;
  	 		}

  	 		if (bit1F != patternMS[s].bits[p].bit1) {
  	 			bit1F = 2;
  	 			break;
  	 		}

  	 	}
  	 }

  	 if (bit1A == 2) {
  	 		s = k;
  	 			goto go;
  	 		s = j;
  	 			goto go;
  	 }

  	 /* Find same for Bit 2 of Result. */

  	 if (bit2A == 0)
  		s = k;
  	else if (bit2A == 1)
  		s = j;

  	if( bit2A != 2){
  	go2: for (p=0; p<countC; p++) {

  			if (bit2F == 2)
  				break;

  	 		if(p == 0) {
  	 			bit2F = patternMS[s].bits[p].bit2;
  	 			continue;
  	 		}

  	 		if (bit2F != patternMS[s].bits[p].bit2) {
  	 			bit2F = 2;
  	 			break;
  	 		}

  	 	}
  	 }

  	if (bit2A == 2) {
  	 		s = k;
  	 			goto go2;
  	 		s = j;
  	 			goto go2;
  	 }

  	 /* Now let us populate the result field. */
  	char ret;
  	
  	if (bit1F == 0) {
  		if(bit2F == 0)	
  			ret = '0';
  		if(bit2F == 1)	
  			ret = 'n';
  		if(bit2F == 2)	
  			ret = '5';
  	}

	if (bit1F == 1) {
  		if(bit2F == 0)	
  			ret = 'u';
  		if(bit2F == 1)	
  			ret = '1';
  		if(bit2F == 2)	
  			ret = 'A';
  	}

  	if (bit1F == 2) {
  		if(bit2F == 0)	
  			ret = '3';
  		if(bit2F == 1)	
  			ret = 'C';
  		if(bit2F == 2)	
  			ret = '?';
  	}  	

  	return ret;


}

int checkExist (bitPattern toCheck, bitStyle b) {
	int i;
	int check = 0;
	for (i=0; i<toCheck.count; i++) {
		//if (toCheck.bits[i] == b) // change this
			check = 1;
	}

	return check;
}











	