#include <stdio.h>

static int arr[] = {0, 8, 4, 12, 2, 10, 6, 14, 1, 9, 5, 13, 3, 11, 7, 15};// { 10, 22, 9, 33, 21, 50, 41, 60, 80 };

static const int N = sizeof(arr) / sizeof(int);

static int sizes[sizeof(arr) / sizeof(int)] = { { 1 } };

void lsi_main(void) {

	int i,j;

	for (i = 0; i < N; i++)
		sizes[i] = 1;

	for (i = 1; i < N; i++) {
		int num = arr[i];

		for (j = 0; j < i; j++) {
			if (num <= arr[j])
				continue;

			int len = sizes[j] + 1;
			if (len > sizes[i])
				sizes[i] = len;
		}

	}

	printf("\nResult: ");
	for (i = 0; i < N; i++)
		printf("%d ", sizes[i]);
	getch();
}
