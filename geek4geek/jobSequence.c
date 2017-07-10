#include <stdio.h>

typedef struct {
	char label;
	int deadline;
	int profit;
	int visited;
} job_t;

//static job_t jobs[] = {
//	{ 'a', 2, 100, 0},
//	{ 'b', 1, 19 , 0},
//	{ 'c', 2, 27 , 0},
//	{ 'd', 1, 25 , 0},
//	{ 'e', 3, 15 , 0}
//};

static job_t jobs[] = {
	{ 'a', 4, 20, 0 },
	{ 'b', 1, 10 , 0 },
	{ 'c', 1, 40 , 0 },
	{ 'c', 1, 30 , 0 },
	//{ 'e', 3, 15 , 0 }
};


static int N = sizeof(jobs) / sizeof(jobs[0]);

static int maxDeadline(void) {
	int last = 1;

	for (int i = 0; i < N; i++) {
		if (jobs[i].deadline > last)
			last = jobs[i].deadline;
	}
	return last;
}


static int indexOfMaxProfiteNotVisited(int minDeadline) {
	int maxProfit = 0;
	int index = -1;

	for (int i = 0; i < N; i++) {
		if (jobs[i].visited)
			continue;
		if (jobs[i].deadline < minDeadline)
			continue;
		if (jobs[i].profit > maxProfit) {
			maxProfit = jobs[i].profit;
			index = i;
		}
	}
	return index;
}

static void findMaxProfitSequence(void) {
	int curSec = maxDeadline();

	while (curSec) {
		int index = indexOfMaxProfiteNotVisited(curSec);
		curSec--;
		if (index == -1)
			continue;
		jobs[index].visited = 1;
		printf("%c ", jobs[index].label);
		
	}
}

int job_main(void) {
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
	//printf("%d\n", countMaxPossible());
	findMaxProfitSequence();
	getch();
#endif
	return 0;
}