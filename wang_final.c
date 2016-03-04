#include "wang_rm.h"

void collision()

{
	int i;

	/*Create Shift Array */
	for(i=1;i<17;i++)
	{
		if((i%4)==1)
			s[i]=3;
		if((i%4)==2)
			s[i]=7;
		if((i%4)==3)
			s[i]=11;
		if((i%4)==0)
			s[i]=19;
		
	}

	for(i=17;i<33;i++)
	{
		if((i%4)==1)
			s[i]=3;
		if((i%4)==2)
			s[i]=5;
		if((i%4)==3)
			s[i]=9;
		if((i%4)==0)
			s[i]=13;
		
	}

	for(i=33;i<49;i++)
	{
		if((i%4)==1)
			s[i]=3;
		if((i%4)==2)
			s[i]=9;
		if((i%4)==3)
			s[i]=11;
		if((i%4)==0)
			s[i]=15;
		
	}

	/* Generating Message-Index Value for Last Set of 16 Steps */
	j[0]=0;	
	for(i=1;i<16;i++)
	{
		if(i<4)
		{
			j[i]=((j[i-1]+8)%16) + (4*(((i%2)+1)%2));
		}
		else if((i>=4) && (i<8))
		{
			j[i] = j[i-4] + 2;
		}
		else if((i>=8) && (i<12))
		{
			j[i] = j[i-4] - 1;
		}
		else if((i>=12) && (i<16))
		{
			j[i] = j[i-4] + 2;
		}
	}

	/* Generate the message words */
	
	/* Steps 1 to 16 */
	beginning:
	
	Reg[0] = B;	
	
	/* For A1 Register */
	Reg[1] = rand ();
	Prev(1,0,7);
	NOT(1,33,33,33,33,33);

	X0[0] = right(Reg[1], 3) - f(B, C, D) - A;
	X1[0] = X0[0];
	
	/* For D1 Register */
	Reg[2] = (rand() AND(7));
	Prev(2,1,8);
	Prev(2,1,11);
	NOT(2,7,33,33,33,33);

	X0[1] = right(Reg[2], 7) - f(Reg[1], B, C) - D;
	X1[1] = right(Reg1[2], 7) - f(Reg1[1], B, C) - D;
	if((X0[1] ^ X1[1]) != 0x80000000)
			goto beginning;
	
	/* For C1 Register */
	Reg[3] = (((rand() OR(7))OR(8))AND(11));
	Prev(3,2,26);
	NOT(3,8,11,33,33,33);
	msgMod(3);
	msgMod1(3);
	if((X0[2] ^ X1[2]) != 0x90000000)
			goto beginning;

	/* For B1 Register */
	Reg[4] = (((( rand() OR(7)) AND(8)) AND(11)) AND(26));
	NOT(4,26,33,33,33,33); 
	msgcheck(4);

	/* For A2 Register */
	Reg[5] = ((( rand() OR(8)) OR(11))AND(26));
	Prev(5,4,14);
	NOT(5,33,33,33,33,33);
	msgcheck(5);

	/* For D2 Register */
	Reg[6] = (( rand() OR(26)) AND(14));
	for(i=19;i<23;i++)
		Prev(6,5,i);
	NOT(6,14,33,33,33,33);
	msgcheck(6);

	/* For C2 Register */
	Reg[7] = ((((( rand() OR(21)) AND(14)) AND(19)) AND(20)) AND(22));
	Prev(7,6,13);
	Prev(7,6,15);
	NOT(6,19,20,21,22,33);
	msgcheck(7);

	/* For B2 Register */
	Reg[8] = ((((((( rand() OR(13)) OR(14)) AND(15)) AND(19)) AND(20)) AND(21)) AND(22));
	Prev(8,7,17);
	NOT(8,13,14,15,33,33);
	msgcheck(8);
	
	/* For A3 Register */
	Reg[9] = (((((((( rand() OR(13)) OR(14)) OR(15)) OR(22)) AND(17)) AND (19)) AND(20)) AND(21));
	Prev(9,8,23);
	Prev(9,8,26);
	NOT(9,17,33,33,33,33);
	msgcheck(9);

	/* For D3 Register */
	Reg[10] = ((((((((( rand() OR(13)) OR(14)) OR(15)) OR(21)) OR(22)) OR(26)) AND(17)) AND(20)) AND(23));
	Prev(10,9,30);
	NOT(10,20,21,22,23,26);
	msgcheck(10);
	
	/* For C3 Register */
	Reg[11] = ((((((( rand() OR(17)) OR(30)) AND(20)) AND(21)) AND(22)) AND(23)) AND(26));
	Prev(11,10,30);
	NOT(11,30,33,33,33,33);
	msgcheck(11);

	/*For B3 Register */
	Reg[12] = (((((( rand() OR(21)) OR(22)) OR(26)) AND(20)) AND(30)) AND(32));
	Prev(12,11,23);
	NOT(12,32,33,33,33,33);
	msgcheck(12);

	/* For A4 Register */
	Reg[13] = (((( rand() OR(30)) AND(23)) AND(26)) AND(32));
	Prev(13,12,27);
	Prev(13,12,29);
	NOT(13,23,26,33,33,33);
	msgMod(13);
	msgMod1(13);
	if((X0[12] ^ X1[12]) != 0x00010000)
			goto beginning;

	/* For D4 Register */
	Reg[14] = (((((( rand() OR(23)) OR(26)) OR(30)) AND(27)) AND(29)) AND(32));
	NOT(14,27,29,30,33,33);
	msgcheck(14);

	/*For C4 Register */
	Reg[15] = ((((( rand() OR(23)) OR(26)) AND(27)) AND(29)) AND(30));
	Prev(15,14,19);
	NOT(15,33,33,33,33,33);
	msgcheck(15);

	/* For B4 Register */
	Reg[16] = ((((( rand() OR(26)) OR(27)) OR(29)) AND(19)) AND(30));
	NOT(16,19,33,33,33,33);
	msgcheck(16);
	
	/* End of Message Modification */

	/* For steps 17 to 32 - There should be differences in 17th, 20th and 21st Step */
	
	for (i=17;i<33;i++)
	{	
		
		if(i==32)
		{
			Reg[32] = left(Reg[28] + g(Reg[31],Reg[30],Reg[29]) + X0[15] + rt2, s[32]);
			Reg1[32] = left(Reg1[28] + g(Reg1[31],Reg1[30],Reg1[29]) + X1[15] + rt2, s[32]);
		}
		else
		{
			genReg(i);
			genReg1(i);
		}

		if(i==17)
		{
			if((Reg[17] - Reg1[17])!=0x8e000000)
				goto beginning;
		}
		else if(i==20)
		{		
			if((Reg[20] - Reg1[20]) != 0xa0000000)
				goto beginning;		
		}
		else if(i==21)
		{ 
			if((Reg[21] - Reg1[21]) != 0x70000000)
				goto beginning;		
		}
		else
		{
			if(Reg[i]!=Reg1[i])
				goto beginning;
		}
	}
		
	/* For steps 33 to 48 - There should be differences in 36th and 37th step. */

	for(i=33; i<49;i++)
	{
		genRegh(i);
		genRegh1(i);
		if(i==36)
		{
			if((Reg[36] ^ Reg1[36]) != 0x80000000)
				goto beginning;
		}
		else if(i==37)
		{
			if((Reg[37] ^ Reg1[37]) != 0x80000000);
				goto beginning;
		}
		else
		{
			if(Reg[i]!=Reg1[i])
				goto beginning;
		}		
	}

	Reg[45] += A;
	Reg[46] += B;
	Reg[47] += C;
	Reg[48] += D;
}

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

