/**
  * Sample Implementation of SHA-256 for Message "abc"
  * Ritobroto Maitra, 2015
  */

/**
 * ALWAYS USE UNSIGNED
 *
 */

#include "sha2.h"

int main() {
	int i;
	unsigned int test[64]={0};

	for(i=0;i<16;i++)	
		test[i] = 0;

	test[0] = 0x61626380;
	test[15] = 0x00000018;
	
	/**
	* Message Expansion
 	*
 	*/
	
	for(i=16;i<64;i++)
		test[i] = (s1(test[i-2])) + test[i-7] + (s0(test[i-15])) + test[i-16];
	
	unsigned int a, b, c, d, e, f, g, h;
	a = h0;
	b = h1;
	c = h2;
	d = h3;
	e = h4;
	f = h5;
	g = h6;
	h = h7;
	i = 0;

	printf("\nStep: %2d\t%8x %8x %8x %8x\n\t\t%8x %8x %8x %8x\n", i,a, b, c, d, e, f, g, h);

	int t1, t2;
	
	for(i=0;i<64;i++) {
		t1 = h + (S1(e)) + (ch(e, f, g)) + k[i] + test[i];
		t2 = (S0(a)) + (mj(a,b,c));
		h = g;
		g = f;
		f = e;
		e = d + t1;
		d = c;
		c = b;
		b = a;
		a = t1 + t2;

		printf("\nStep: %2d\t%8x %8x %8x %8x\n\t\t%8x %8x %8x %8x\n", i+1,a, b, c, d, e, f, g, h);
	}

	a += h0;
	b += h1;
	c += h2;
	d += h3;
	e += h4;
	f += h5;
	g += h6;
	h += h7;

	printf("\n%8x %8x %8x %8x\n%8x %8x %8x %8x\n", a, b, c, d, e, f, g, h);
	
}

/* End of Implementation */