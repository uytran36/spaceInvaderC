#include <stdio.h>

#include "setting.h"


void highScore(int score, char *filename1)
{
	FILE *f;
	int max;
	
	f = fopen(filename1, "rb");
	if(f == NULL)
	{
		return;
	}
	
	fscanf(f, "%d", &max);
	
	if(max < score)
	{
		max = score;
	}
	printf("\n\n\n               High score: %d\n", max);
	
	f = fopen(filename1, "wt");
	fprintf(f, "%d", max);
	
	fclose(f);
}


