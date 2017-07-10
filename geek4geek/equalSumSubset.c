#include <stdio.h>

#define N 5

//static int input[] = { 1,5,11,5,4,4,2,6,1,565,123, 126, 176,766,1 };
static int input[] = { 478,757,314,471,729,100,459,618 };
static int half;
static int *endLoc = input + sizeof(input) / sizeof(int) -1 ;

static int isPossible(int pSum, int * arr) {
	if (pSum + arr[0] == half) {
		printf("%d ", arr[0]);
		return 1;
	}

	if ((pSum + arr[0]) > half)
		return 0;

	for (int *tmp = arr + 1; tmp <= endLoc; tmp++) {
		if (isPossible(pSum + arr[0], tmp)) {
			printf("%d ", tmp[0]);
			return 1;
		}
	}
	return 0;
}

static int reset(void) {
	int sum = 0;
	for (int *tmp = input; tmp <= endLoc; tmp++) {
		sum += *tmp;
	}
	half = sum / 2;
	printf("Sum: %d, half: %d\n", sum, half);

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




void emain(void) {
	int res = isSubSetPossible();
	printf("\n%s", res?"YES":"NO");
	getch();
}