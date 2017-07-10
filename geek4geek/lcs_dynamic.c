/* A Naive recursive implementation of LCS problem */
#include<stdio.h>

static int max(int a, int b);

static int table[10][10];
static char * str1, *str2;

/* Returns length of LCS for X[0..m-1], Y[0..n-1] */
static int lcs(char *X, char *Y)
{
	int xi, yi;
	xi =  X - str1;
	yi =  Y - str2;

	if (table[xi][yi] != -1)
		return table[xi][yi];

	if (*X == 0 || *Y == 0) {
		table[xi][yi] = 0;
		return 0;
	}
	if (X[0] == Y[0]) {
		table[xi][yi] = 1 + lcs(X + 1, Y + 1);
		return table[xi][yi];
	}
	else {
		return max(lcs(X, Y + 1), lcs(X + 1, Y));
	}
}

/* Utility function to get max of 2 integers */
int max(int a, int b)
{
	return (a > b) ? a : b;
}

void reset(void) {
	int i, j;
	for(i=0;i<100;i++)
		for (j = 0; j < 100; j++) {
			table[i][j] = -1;
		}
}

/* Driver program to test above function */
int dynamic_main()
{
	char X[] = "AGGTAB";
	char Y[] = "GXTXAYB";

	reset();
	str1 = X;
	str2 = Y;

	//int m = strlen(X);
	//int n = strlen(Y);

	printf("Length of LCS is %d\n", lcs(X, Y));

	getch();
	return 0;
}