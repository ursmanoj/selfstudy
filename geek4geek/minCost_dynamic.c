#include<stdio.h>
#include<limits.h>

#define R 4
#define C 4

static int mat[R][C] =
{
	1,2,3,1,
	4,8,2,12,
	1,5,3,1
};

static int minPathLens[R][C];


static int min(int x, int y, int z) {
	int min = x;

	min = x < y ? x : y;
	min = z < min ? z : min;

	return min;
}



static int minCost(int dstR, int dstC) {
	if (dstR == 0 && dstC == 0) {
		minPathLens[0][0] = mat[0][0];
		return mat[0][0];
	}

	if (dstR < 0 || dstC < 0)
		return 10000;

	if (minPathLens[dstR][dstC] == -1)
		minPathLens[dstR][dstC] = mat[dstR][dstC] + min(minCost(dstR - 1, dstC), minCost(dstR, dstC - 1), minCost(dstR - 1, dstC - 1));
	
	return minPathLens[dstR][dstC];
}


static void reset(void) {
	int i, j;
	for (i = 0; i < R; i++)
		for (j = 0; j < C; j++)
			minPathLens[i][j] = -1;
}

void dn_main(void) {
	reset();
	printf("MinPath Len: %d", minCost(3, 3));
	getch();
}