/* A Naive recursive implementation of LCS problem */
#include<stdio.h>

int max(int a, int b);

/* Returns length of LCS for X[0..m-1], Y[0..n-1] */
static int lcs(char *X, char *Y)
{
	if (*X == 0 || *Y == 0)
		return 0;
	if (X[0] == Y[0])
		return 1 + lcs(X+1, Y+1);
	else
		return max(lcs(X, Y+1), lcs(X+1, Y));
}

/* Utility function to get max of 2 integers */
int max(int a, int b)
{
	return (a > b) ? a : b;
}

/* Driver program to test above function */
int main_recursion()
{
	char X[] = "AGGTAB";
	char Y[] = "GXTXAYB";

	//int m = strlen(X);
	//int n = strlen(Y);

	printf("Length of LCS is %d\n", lcs(X, Y));

	getch();
	return 0;
}