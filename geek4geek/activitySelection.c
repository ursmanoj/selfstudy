#include <stdio.h>

//#define MULTI_CASE

#define MAX 1000

//static int startTimes[MAX] = {1,3,0,5,8,5};
//static int finishTimes[MAX] = { 2,4,6,7,9,9 };

static int startTimes[MAX] = { 17,91,41,80,36,7,73,99 };//{ 50,74,59,31,73,45,79,24 };
static int finishTimes[MAX] = { 33,101,66,104,56,28,99,106 };// { 70, 75, 65, 44, 76, 73, 103, 32 };

static int N = 8;// sizeof(finishTimes) / sizeof(finishTimes[0]);

static void quickSort(int first, int last);

static int countMaxPossible(void) {
	int prevFinishTime = -1;
	int counter = 0;
	quickSort(0,N-1);

	for (int i = 0; i < N; i++) {
		if (startTimes[i] >= prevFinishTime) {
			counter++;
			prevFinishTime = finishTimes[i];
		}
	}
	return counter;
}


int asmain(void) {
#ifdef MULTI_CASE
	int T;

	scanf("%d", &T);

	while (T) {
		scanf("%d", &N);
		for (int i = 0; i < N; i++) {
			scanf("%d", &startTimes[i]);
		}
		for (int i = 0; i < N; i++) {
			scanf("%d", &finishTimes[i]);
		}
		printf("%d\n", countMaxPossible());
		T--;
	}

#else
	printf("%d\n", countMaxPossible());
#endif
	return 0;
}


static void quickSort(int first, int last)
{
	int pivot;
	int i;
	int j;
	int temp;

	if (first < last)
	{
		pivot = first;
		i = first;
		j = last;

		while (i < j)
		{
			while (finishTimes[i] <= finishTimes[pivot] && i < last)
			{
				i++;
			}
			while (finishTimes[j] > finishTimes[pivot])
			{
				j--;
			}
			if (i < j)
			{
				temp = finishTimes[i];
				finishTimes[i] = finishTimes[j];
				finishTimes[j] = temp;


				temp = startTimes[i];
				startTimes[i] = startTimes[j];
				startTimes[j] = temp;
			}
		}

		temp = finishTimes[pivot];
		finishTimes[pivot] = finishTimes[j];
		finishTimes[j] = temp;

		temp = startTimes[pivot];
		startTimes[pivot] = startTimes[j];
		startTimes[j] = temp;

		quickSort(first, j - 1);
		quickSort(j + 1, last);
	}
}
