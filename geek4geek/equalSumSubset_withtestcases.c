#include <stdio.h>

#define MAX 100

static int input[MAX] = { 1,5,11,5,4 };
static int half;
static int N;
static int *endLoc;

static int isPossible(int pSum, int * arr) {
	if (pSum + arr[0] == half)
		return 1;

	if ((pSum + arr[0]) > half)
		return 0;

	for (int *tmp = arr + 1; tmp <= endLoc; tmp++) {
		if (isPossible(pSum + arr[0], tmp))
			return 1;
	}
	return 0;
}

static int reset(void) {
	int sum = 0;
	endLoc = input + N - 1;

	for (int *tmp = input; tmp <= endLoc; tmp++) {
		sum += *tmp;
	}
	half = sum / 2;

	return !(sum % 2);
}

static int isSubSetPossible() {
	if (!reset())
		return 0;
	for (int *tmp = input; tmp <= endLoc; tmp++) {
		if (isPossible(0, tmp))
			return 1;
	}
	return 0;
}


int ymain(void) {
	int T;

	scanf("%d", &T);

	while (T) {
		scanf("%d", &N);
		endLoc = input + N - 1;

		for (int *tmp = input; tmp <= endLoc; tmp++) {
			scanf("%d", tmp);
		}
		int res = isSubSetPossible();
		printf("%s\n", res ? "YES" : "NO");
		T--;
	}

	//getch();
	return 0;
}