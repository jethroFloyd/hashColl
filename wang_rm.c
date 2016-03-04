/* The MD4 hashing algorithm is one of the most widely used hashing algorithms in the world of cryptology and information security. The main applications include those in digital signatures. A "hash" is a sort of a fingerprint which can be generated. However, obviously, hashing involves generating a fixed m-bit value from an arbitrary file size of l-bits, where l is nearly always much greater than m. For MD4, m is 128 bits, whereas a normal file can have sizes upto a few gigabytes. The implication of this statement is that a function mapping l to m cannot be one-to-one, and eventually, two distinct files must produce the same hash. This is called a collision. Although collisions are extremely rare in the practical world, theoretically collisions may be found. The objective of exposing collisions is to find a better algorithm (like MD5, SHA-family) to hash. We cannot have a perfectly collision-resistant algorithm (it would need a minimum of l bits in the hash itself) but we may make finding the collision arbitrarily difficult.

The MD4 algorithm was originally designed and restrengthened by Prof. Ronald Rivest, Massachussetts Institute of Technology.
In the following code, an attack on the MD4 algorithm is carried out. The algorithm improves upon the attack described by Xiaoyun Wang, Shandong University et al in her revolutionary research paper "Cryptanalysis of the Hash Function MD4 and RIPEMD", published in 2005 in the Journal of Cryptology, and conference-reviewed at EUROCRYPT, 2005.

The new improved algorithm as implemented below will generate collisions with  an extremely high probability, within a few microseconds on any average personal computer.

Ritobroto Maitra, 2014. */

/*Include the necessary header files. */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*Define the functions necessary in MD4, rounds, round constants and the initialisation vectors. */

#define IV0	0x67452301
#define IV1	0xefcdab89
#define IV2	0x98badcfe
#define IV3	0x10325476
#define rt2 	0x5a827999
#define rt3 	0x6ed9eba1

/* f is the IF function. g is the MAJORITY function. h is the XOR or PARITY function. left is the left circular rotation function. right is the right circular rotation function */

#define left(x, y) (((x) << (y)) | ((x) >> (32 - (y))))
#define right(x, y) (((x) >> (y)) | ((x) << (32 - (y))))

#define f(x, y, z) ((x & y) | ( ~x & z))
#define g(x, y, z) ((x & y) | (y & z) | (z & x))
#define h(x, y, z) (x ^ y ^ z)

/* Reg and Reg1 arrays store the 48 register values for steps 1 to 48 for messages X0 and X1 respectively. */
unsigned int Reg[49], Reg1[49];
unsigned int X0[16], X1[16];
unsigned int IV[4] = { IV0, IV1, IV2, IV3 };
void collision();

int main()

{
	int i;
	clock_t start, end; 
	double time_used;
	start = clock();
	
	srand(time(NULL));

	collision();
	printf("\nThe message words which are different are capitalised.\n\nThe first message is:\n");
	
	for(i=0;i<16;i++)
	{
		if(i==1 || i == 2 || i== 12)
			printf("%08X ", X0[i]);
		else
			printf("%08x ", X0[i]);

		if((i+1)%4==0)
			printf("\n");
	}
	printf("\nThe second message is:\n");

	for(i=0;i<16;i++)
	{
		if(i==1 || i == 2 || i== 12)
			printf("%08X ", X1[i]);
		else
			printf("%08x ", X1[i]);

		if((i+1)%4==0)
			printf("\n");
	}
	printf("\n");
	
	printf("\nThe Common MD4 Hash Value is:\n");
	printf("\n%#x %x %x %x\n", Reg[45], Reg[46],Reg[47],Reg[48]);
	
	end = clock();
	time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
	
	printf("\nThe time taken to generate the collision is %f seconds.\n", time_used);
}

void collision()
{
	int i;


check:	while(1)
	{
		/* No conditions for A1 register value */
	
		/* For D1 Register  */
		Reg[2] = rand() & ~0x00000040;
		Reg1[2] = Reg[2] - 0xffffffc0;

		/* For C1 Register */
		Reg[3] = (rand() | 0x000000c0) & ~(0x00000800 | 0x02000000);
		Reg[3] |= (Reg[2] & 0x02000000);
		Reg1[3] = Reg[3] - 0xfffffc80;

		/* For B1 Register */
		Reg[4] = (rand() | 0x00000040) & ~0x02000480;
		Reg1[4] = Reg[4] - 0xfe000000;

		/* For A2 Register */
		Reg[5] = (rand() | 0x00000480) & ~(0x02000000 | 0x00002000);
		Reg[5] |= (Reg[4] & 0x00002000);
		Reg1[5] = Reg[5];

		/* For D2 Register */
		Reg[6] = (rand() | 0x02000000) & ~(0x00002000 | 0x003c0000);
		Reg[6] |= (Reg[5] & 0x003c0000);
		Reg1[6] = Reg[6] - 0xffffe000;

		/* 6th Message Modification */
		X0[5] = right(Reg[6], 7) - f(Reg[5], Reg[4], Reg[3]) - Reg[2];
		X1[5] = right(Reg1[6], 7) - f(Reg1[5], Reg1[4], Reg1[3]) - Reg1[2];
		if(X0[5] != X1[5])
			continue;

		/* For C2 Register */
		Reg[7] = (rand() | 0x00100000) & ~(0x002c2000 | 0x00005000);
		Reg[7] |= (Reg[6] & 0x00005000);
		Reg1[7] = Reg[7] - 0xffe40000;
		
		/* 7th Message Modification */
		X0[6] = right(Reg[7], 11) - f(Reg[6], Reg[5], Reg[4]) - Reg[3];
		X1[6] = right(Reg1[7], 11) - f(Reg1[6], Reg1[5], Reg1[4]) - Reg1[3];
		if(X0[6] != X1[6])
			continue;

		/* For B2 Register */
		Reg[8] = (rand() | 0x00003000) & ~(0x003c4000 | 0x00010000);
		Reg[8] |= (Reg[7] & 0x00010000);
		Reg1[8] = Reg[8] - 0xfffff000;

		/* 8th Message Modification */
		X0[7] = right(Reg[8], 19) - f(Reg[7], Reg[6], Reg[5]) - Reg[4];
		X1[7] = right(Reg1[8], 19) - f(Reg1[7], Reg1[6], Reg1[5]) - Reg1[4];
		if(X0[7] != X1[7])
			continue;

		/* For A3 Register */
		Reg[9] = (rand() | 0x00207000) & ~(0x001d0000 | 0x02400000);
		Reg[9] |= (Reg[8] & 0x02400000);
		Reg1[9] = Reg[9] - 0xffff0000;
	
		/* 9th Message Modification */
		X0[8] = right(Reg[9], 3) - f(Reg[8], Reg[7], Reg[6]) - Reg[5];
		X1[8] = right(Reg1[9], 3) - f(Reg1[8], Reg1[7], Reg1[6]) - Reg1[5];
		if(X0[8] != X1[8])
			continue;

		/* For D3 Register */
		Reg[10] = (rand() | 0x02307000) & ~(0x00490000 | 0x20000000);
		Reg[10] |= (Reg[9] & 0x20000000);
		Reg1[10] = Reg[10] - 0x01e80000;

		/* 10th Message Modification */
		X0[9] = right(Reg[10], 7) - f(Reg[9], Reg[8], Reg[7]) - Reg[6];
		X1[9] = right(Reg1[10], 7) - f(Reg1[9], Reg1[8], Reg1[7]) - Reg1[6];
		if(X0[9] != X1[9])
			continue;

		/* For C3 Register */
		Reg[11] = (rand() | 0x20010000) & ~(0x02780000 | 0x80000000);
		Reg[11] |= (Reg[10] & 0x80000000);
		Reg1[11] = Reg[11] - 0x20000000;

		/* 11th Message Modification */
		X0[10] = right(Reg[11], 11) - f(Reg[10], Reg[9], Reg[8]) - Reg[7];
		X1[10] = right(Reg1[11], 11) - f(Reg1[10], Reg1[9], Reg1[8]) - Reg1[7];
		if(X0[10] != X1[10])
			continue;

		/* For B3 Register */
		Reg[12] = (rand() | 0x02300000) & ~(0xa0080000 | 0x00400000);
		Reg[12] |= (Reg[11] & 0x00400000);
		Reg1[12] = Reg[12] - 0x80000000;
	
		/* 12th Message Modification */
		X0[11] = right(Reg[12], 19) - f(Reg[11], Reg[10], Reg[9]) - Reg[8];
		X1[11] = right(Reg1[12], 19) - f(Reg1[11], Reg1[10], Reg1[9]) - Reg1[8];
		if(X0[11] != X1[11])
			continue;

		/* For A4 Register */
		Reg[13] = (rand() | 0x20000000) & ~(0x82400000 | 0x14000000);
		Reg[13] |= (Reg[12] & 0x14000000);
		Reg1[13] = Reg[13] - 0xfdc00000;
		
		/* 13th Message Modification */
		X0[12] = right(Reg[13], 3) - f(Reg[12], Reg[11], Reg[10]) - Reg[9];
		X1[12] = right(Reg1[13], 3) - f(Reg1[12], Reg1[11], Reg1[10]) - Reg1[9];
		if((X0[12] ^ X1[12]) != 0x00010000)
			continue;

		/* For D4 Register */
		Reg[14] = (rand() | 0x94000000) & ~0x22400000;
		Reg1[14] = Reg[14] - 0xf4000000;

		/* 14th Message Modification */
		X0[13] = right(Reg[14], 7) - f(Reg[13], Reg[12], Reg[11]) - Reg[10];
		X1[13] = right(Reg1[14], 7) - f(Reg1[13], Reg1[12], Reg1[11]) - Reg1[10];
		if(X0[13] != X1[13])
			continue;

		/* For C4 Register */
		Reg[15] = (rand() | 0x02400000) & ~(0x34000000 | 0x00040000);
		Reg[15] |= (Reg[14] & 0x00040000);
		Reg1[15] = Reg[15];
	
		/* 15th Message Modification */
		X0[14] = right(Reg[15], 11) - f(Reg[14], Reg[13], Reg[12]) - Reg[11];
		X1[14] = right(Reg1[15], 11) - f(Reg1[14], Reg1[13], Reg1[12]) - Reg1[11];
		if(X0[14] != X1[14])
			continue;

		/* For B4 Register */
		Reg[16] = (rand() | 0x14000000) & ~0x20040000;
		Reg1[16] = Reg[16] - 0xfffc0000;

		/* 16th Message Modification */
		X0[15] = right(Reg[16], 19) - f(Reg[15], Reg[14], Reg[13]) - Reg[12];
		X1[15] = right(Reg1[16], 19) - f(Reg1[15], Reg1[14], Reg1[13]) - Reg1[12];
		if(X0[15] != X1[15])
			continue;

		break;
	}


	for(i=0;i<1000;i++)
	{
		Reg[1] = rand() & ~(0x00000040 | 0x00000480);
		Reg[1] |= (IV[1] & 0x00000040) | (Reg[2] & 0x00000480);
		Reg1[1] = Reg[1];

		X0[0] = right(Reg[1], 3) - f(IV[1], IV[2], IV[3]) - IV[0];
		X1[0] = X0[0];

		
		X0[1] = right(Reg[2], 7) - f(Reg[1], IV[1], IV[2]) - IV[3];
		X1[1] = right(Reg1[2], 7) - f(Reg1[1], IV[1], IV[2]) - IV[3];
		if((X0[1] ^ X1[1]) != 0x80000000)
			continue;

		X0[2] = right(Reg[3], 11) - f(Reg[2], Reg[1], IV[1]) - IV[2];
		X1[2] = right(Reg1[3], 11) - f(Reg1[2], Reg1[1], IV[1]) - IV[2];
		if((X0[2] ^ X1[2]) != 0x90000000)
			continue;

		X0[3] = right(Reg[4], 19) - f(Reg[3], Reg[2], Reg[1]) - IV[1];
		X1[3] = right(Reg1[4], 19) - f(Reg1[3], Reg1[2], Reg1[1]) - IV[1];
		if(X0[3] != X1[3])
			continue;

		X0[4] = right(Reg[5], 3) - f(Reg[4], Reg[3], Reg[2]) - Reg[1];
		X1[4] = right(Reg1[5], 3) - f(Reg1[4], Reg1[3], Reg1[2]) - Reg1[1];
		if(X0[4] != X1[4])
			continue;

		Reg[17] = left(g(Reg[16], Reg[15], Reg[14]) + Reg[13]+ X0[0] + rt2, 3);
		Reg1[17] = left(g(Reg1[16], Reg1[15], Reg1[14]) + Reg1[13]+ X1[0] + rt2, 3);
		if((Reg[17] - Reg1[17]) != 0x8e000000)
			continue;

		Reg[18] = left(g(Reg[17], Reg[16], Reg[15]) + Reg[14]+ X0[4] + rt2, 5);
		Reg1[18] = left(g(Reg1[17], Reg1[16], Reg1[15]) + Reg1[14]+ X1[4] + rt2, 5);
		if(Reg[18] != Reg1[18])
			continue;

        Reg[19] = left(g(Reg[18], Reg[17], Reg[16]) + Reg[15] + X0[8] + rt2, 9);
        Reg1[19] = left(g(Reg1[18], Reg1[17], Reg1[16]) + Reg1[15]+ X1[8] + rt2, 9);
		if(Reg[19] != Reg1[19])
			continue;

        Reg[20] = left(g(Reg[19], Reg[18], Reg[17]) + Reg[16]+ X0[12] + rt2, 13);
        Reg1[20] = left(g(Reg1[19], Reg1[18], Reg1[17]) + Reg1[16] + X1[12] + rt2, 13);
		if((Reg[20] - Reg1[20]) != 0xa0000000)
			continue;
		break;
	}
	if(i >= 1000)
		goto check;



    for(i=0;i<60000000;i++)
    {
        Reg[1] = rand() & ~(0x00000040 | 0x00000480);
        Reg[1] |= (IV[1] & 0x00000040) | (Reg[2] & 0x00000480);
        Reg1[1] = Reg[1];

        X0[0] = right(Reg[1], 3) - f(IV[1], IV[2], IV[3]) - IV[0];
        X1[0] = X0[0];


        X0[1] = right(Reg[2], 7) - f(Reg[1], IV[1], IV[2]) - IV[3];
        X1[1] = right(Reg1[2], 7) - f(Reg1[1], IV[1], IV[2]) - IV[3];
      		  if((X0[1] ^ X1[1]) != 0x80000000)
           		 continue;

        X0[2] = right(Reg[3], 11) - f(Reg[2], Reg[1], IV[1]) - IV[2];
        X1[2] = right(Reg1[3], 11) - f(Reg1[2], Reg1[1], IV[1]) - IV[2];
       		 if((X0[2] ^ X1[2]) != 0x90000000)
           		 continue;

        X0[3] = right(Reg[4], 19) - f(Reg[3], Reg[2], Reg[1]) - IV[1];
        X1[3] = right(Reg1[4], 19) - f(Reg1[3], Reg1[2], Reg1[1]) - IV[1];
       		 if(X0[3] != X1[3])
           		 continue;

        X0[4] = right(Reg[5], 3) - f(Reg[4], Reg[3], Reg[2]) - Reg[1];
        X1[4] = right(Reg1[5], 3) - f(Reg1[4], Reg1[3], Reg1[2]) - Reg1[1];
       		 if(X0[4] != X1[4])
           		 continue;

        Reg[17] = left(g(Reg[16], Reg[15], Reg[14]) + Reg[13]+ X0[0] + rt2, 3);
        Reg1[17] = left(g(Reg1[16], Reg1[15], Reg1[14]) + Reg1[13]+ X1[0] + rt2, 3);
        	if((Reg[17] - Reg1[17]) != 0x8e000000)
           		 continue;

        Reg[18] = left(g(Reg[17], Reg[16], Reg[15]) + Reg[14]+ X0[4] + rt2, 5);
        Reg1[18] = left(g(Reg1[17], Reg1[16], Reg1[15]) + Reg1[14]+ X1[4] + rt2, 5);
       		if(Reg[18] != Reg1[18])
            		continue;

        Reg[19] = left(g(Reg[18], Reg[17], Reg[16]) + Reg[15]+ X0[8] + rt2, 9);
        Reg1[19] = left(g(Reg1[18], Reg1[17], Reg1[16]) + Reg1[15]+ X1[8] + rt2, 9);
		if(Reg[19] != Reg1[19])
			continue;

        Reg[20] = left(g(Reg[19], Reg[18], Reg[17]) + Reg[16]+ X0[12] + rt2, 13);
        Reg1[20] = left(g(Reg1[19], Reg1[18], Reg1[17]) + Reg1[16]+ X1[12] + rt2, 13);
		if((Reg[20] - Reg1[20]) != 0xa0000000)
			continue;

        Reg[21] = left(g(Reg[20], Reg[19], Reg[18]) + Reg[17]+ X0[1] + rt2, 3);
        Reg1[21] = left(g(Reg1[20], Reg1[19], Reg1[18]) + Reg1[17]+ X1[1] + rt2, 3);
		if((Reg[21] - Reg1[21]) != 0x70000000)
			continue;

        Reg[22] = left(g(Reg[21], Reg[20], Reg[19]) + Reg[18]+ X0[5] + rt2, 5);
        Reg1[22] = left(g(Reg1[21], Reg1[20], Reg1[19]) + Reg1[18]+ X1[5] + rt2, 5);
		if(Reg[22] != Reg1[22])
			continue;

        Reg[23] = left(g(Reg[22], Reg[21], Reg[20]) + Reg[19]+ X0[9] + rt2, 9);
        Reg1[23] = left(g(Reg1[22], Reg1[21], Reg1[20]) + Reg1[19]+ X1[9] + rt2, 9);
		if(Reg[23] != Reg1[23])
			continue;

        Reg[24] = left(g(Reg[23], Reg[22], Reg[21]) + Reg[20]+ X0[13] + rt2, 13);
        Reg1[24] = left(g(Reg1[23], Reg1[22], Reg1[21]) + Reg1[20]+ X1[13] + rt2, 13);
		if(Reg[24] != Reg1[24])
			continue;

        Reg[25] = left(g(Reg[24], Reg[23], Reg[22]) + Reg[21]+ X0[2] + rt2, 3);
        Reg1[25] = left(g(Reg1[24], Reg1[23], Reg1[22]) + Reg1[21]+ X1[2] + rt2, 3);
		if(Reg[25] != Reg1[25])
			continue;

        Reg[26] = left(g(Reg[25], Reg[24], Reg[23]) + Reg[22]+ X0[6] + rt2, 5);
        Reg1[26] = left(g(Reg1[25], Reg1[24], Reg1[23]) + Reg1[22]+ X1[6] + rt2, 5);
		if(Reg[26] != Reg1[26])
			continue;

        Reg[27] = left(g(Reg[26], Reg[25], Reg[24]) + Reg[23]+ X0[10] + rt2, 9);
        Reg1[27] = left(g(Reg1[26], Reg1[25], Reg1[24]) + Reg1[23]+ X1[10] + rt2, 9);
		if(Reg[27] != Reg1[27])
			continue;

        Reg[28] = left(g(Reg[27], Reg[26], Reg[25]) + Reg[24]+ X0[14] + rt2, 13);
        Reg1[28] = left(g(Reg1[27], Reg1[26], Reg1[25]) + Reg1[24]+ X1[14] + rt2, 13);
		if(Reg[28] != Reg1[28])
			continue;

        Reg[29] = left(g(Reg[28], Reg[27], Reg[26]) + Reg[25]+ X0[3] + rt2, 3);
        Reg1[29] = left(g(Reg1[28], Reg1[27], Reg1[26]) + Reg1[25]+ X1[3] + rt2, 3);
		if(Reg[29] != Reg1[29])
			continue;

        Reg[30] = left(g(Reg[29], Reg[28], Reg[27]) + Reg[26]+ X0[7] + rt2, 5);
        Reg1[30] = left(g(Reg1[29], Reg1[28], Reg1[27]) + Reg1[26]+ X1[7] + rt2, 5);
		if(Reg[30] != Reg1[30])
			continue;

        Reg[31] = left(g(Reg[30], Reg[29], Reg[28]) + Reg[27]+ X0[11] + rt2, 9);
        Reg1[31] = left(g(Reg1[30], Reg1[29], Reg1[28]) + Reg1[27]+ X1[11] + rt2, 9);
		if(Reg[31] != Reg1[31])
			continue;

        Reg[32] = left(g(Reg[31], Reg[30], Reg[29]) + Reg[28]+ X0[15] + rt2, 13);
        Reg1[32] = left(g(Reg1[31], Reg1[30], Reg1[29]) + Reg1[28]+ X1[15] + rt2, 13);
		if(Reg[32] != Reg1[32])
			continue;

        Reg[33] = left(h(Reg[32], Reg[31], Reg[30]) + Reg[29]+ X0[0] + rt3, 3);
        Reg1[33] = left(h(Reg1[32], Reg1[31], Reg1[30]) + Reg1[29]+ X1[0] + rt3, 3);
		if(Reg[33] != Reg1[33])
			continue;

        Reg[34] = left(h(Reg[33], Reg[32], Reg[31]) + Reg[30]+ X0[8] + rt3, 9);
        Reg1[34] = left(h(Reg1[33], Reg1[32], Reg1[31]) + Reg1[30]+ X1[8] + rt3, 9);
		if(Reg[34] != Reg1[34])
			continue;

        Reg[35] = left(h(Reg[34], Reg[33], Reg[32]) + Reg[31]+ X0[4] + rt3, 11);
        Reg1[35] = left(h(Reg1[34], Reg1[33], Reg1[32]) + Reg1[31]+ X1[4] + rt3, 11);
		if(Reg[35] != Reg1[35])
			continue;

        Reg[36] = left(h(Reg[35], Reg[34], Reg[33]) + Reg[32]+ X0[12] + rt3, 15);
        Reg1[36] = left(h(Reg1[35], Reg1[34], Reg1[33]) + Reg1[32]+ X1[12] + rt3, 15);
		if((Reg[36] ^ Reg1[36]) != 0x80000000)
			continue;

        Reg[37] = left(h(Reg[36], Reg[35], Reg[34]) + Reg[33]+ X0[2] + rt3, 3);
        Reg1[37] = left(h(Reg1[36], Reg1[35], Reg1[34]) + Reg1[33]+ X1[2] + rt3, 3);
		if((Reg[37] ^ Reg1[37]) != 0x80000000)
			continue;

        Reg[38] = left(h(Reg[37], Reg[36], Reg[35]) + Reg[34]+ X0[10] + rt3, 9);
        Reg1[38] = left(h(Reg1[37], Reg1[36], Reg1[35]) + Reg1[34]+ X1[10] + rt3, 9);
		if(Reg[38] != Reg1[38])
			continue;

        Reg[39] = left(h(Reg[38], Reg[37], Reg[36]) + Reg[35]+ X0[6] + rt3, 11);
        Reg1[39] = left(h(Reg1[38], Reg1[37], Reg1[36]) + Reg1[35]+ X1[6] + rt3, 11);
		if(Reg[39] != Reg1[39])
			continue;

        Reg[40] = left(h(Reg[39], Reg[38], Reg[37]) + Reg[36]+ X0[14] + rt3, 15);
        Reg1[40] = left(h(Reg1[39], Reg1[38], Reg1[37]) + Reg1[36]+ X1[14] + rt3, 15);
		if(Reg[40] != Reg1[40])
			continue;

        Reg[41] = left(h(Reg[40], Reg[39], Reg[38]) + Reg[37]+ X0[1] + rt3, 3);
        Reg1[41] = left(h(Reg1[40], Reg1[39], Reg1[38]) + Reg1[37]+ X1[1] + rt3, 3);
		if(Reg[41] != Reg1[41])
			continue;

        Reg[42] = left(h(Reg[41], Reg[40], Reg[39]) + Reg[38]+ X0[9] + rt3, 9);
        Reg1[42] = left(h(Reg1[41], Reg1[40], Reg1[39]) + Reg1[38]+ X1[9] + rt3, 9);
		if(Reg[42] != Reg1[42])
			continue;

        Reg[43] = left(h(Reg[42], Reg[41], Reg[40]) + Reg[39]+ X0[5] + rt3, 11);
        Reg1[43] = left(h(Reg1[42], Reg1[41], Reg1[40]) + Reg1[39]+ X1[5] + rt3, 11);
		if(Reg[43] != Reg1[43])
			continue;

        Reg[44] = left(h(Reg[43], Reg[42], Reg[41]) + Reg[40]+ X0[13] + rt3, 15);
        Reg1[44] = left(h(Reg1[43], Reg1[42], Reg1[41]) + Reg1[40]+ X1[13] + rt3, 15);
		if(Reg[44] != Reg1[44])
			continue;

        Reg[45] = left(h(Reg[44], Reg[43], Reg[42]) + Reg[41]+ X0[3] + rt3, 3);
        Reg1[45] = left(h(Reg1[44], Reg1[43], Reg1[42]) + Reg1[41]+ X1[3] + rt3, 3);
		if(Reg[45] != Reg1[45])
			continue;

        Reg[46] = left(h(Reg[45], Reg[44], Reg[43]) + Reg[42]+ X0[11] + rt3, 9);
        Reg1[46] = left(h(Reg1[45], Reg1[44], Reg1[43]) + Reg1[42]+ X1[11] + rt3, 9);
		if(Reg[46] != Reg1[46])
			continue;

        Reg[47] = left(h(Reg[46], Reg[45], Reg[44]) + Reg[43]+ X0[7] + rt3, 11);
        Reg1[47] = left(h(Reg1[46], Reg1[45], Reg1[44]) + Reg1[43]+ X1[7] + rt3, 11);
		if(Reg[47] != Reg1[47])
			continue;

        Reg[48] = left(h(Reg[47], Reg[46], Reg[45]) + Reg[44] + X0[15] + rt3, 15);
        Reg1[48] = left(h(Reg1[47], Reg1[46], Reg1[45]) + Reg1[44]+ X1[15] + rt3, 15);
		if(Reg[48] != Reg1[48])
			continue;
        break;
    }
	if(i >= 60000000)
		goto check;
	return;
}
