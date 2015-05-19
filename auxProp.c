#include <stdio.h>
#include "sha2.h"

/* Code to generate code for propagate.c  and fill the pattern mother set. */
int main() {

	int i,j;
	char name, garbage;
	int count;
	char style[4][2];

	FILE *fp;

	fp=fopen("auxprop.txt","w");
	fprintf(fp, "\n");

	for (i=0;i<16;i++) {
		scanf("%c", &garbage);
		printf("\nRound %d:\n\n Enter Name:\n", i);
		scanf("%c", &name);
		fprintf(fp, "patternMS[%d].name='%c';\n", i, name);

		printf("\nFor %c Enter Count:\n", name);
		scanf("%d", &count);
		fprintf(fp, "patternMS[%d].count=%d;\n", i, count);

		for(j=0;j<count;j++) {
			printf("\nEnter style %d:\n", j);
			scanf("%s", style[j]);
			fprintf(fp, "patternMS[%d].bits[%d]=%s;\n", i,j,style[j]);
		}
		
		fprintf(fp, "\n");
	}

	fclose(fp);
}