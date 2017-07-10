#include <stdio.h>

#define N 4
static int graph[N][N] = {
	0, 1, 1, 0,
	0, 0, 1, 0,
	1, 0, 0, 1,
	0, 0, 0, 1,
};

static int visited[N];

static void dfs(int startNode) {
	visited[startNode] = 1;

	printf("%d ", startNode);

	for (int dest = 0; dest < N; dest++) {
		if (graph[startNode][dest] == 0) //not an edge
			continue;
		if (visited[dest])//already visited
			continue;
		dfs(dest);
	}
}

int dfs_main(void) {
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
	dfs(2);
	getch();
#endif
	return 0;
}