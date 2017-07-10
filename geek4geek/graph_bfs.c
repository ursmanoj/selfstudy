#include <stdio.h>

#define N 4
static int graph[N][N] = { 
				0, 1, 1, 0,
				0, 0, 1, 0,
				1, 0, 0, 1,
				0, 0, 0, 1,
				};

static int visited[N];

static void bfs(void) {
	int startNode = 0;

	queueEnqueue(startNode);
	visited[startNode] = 1;

	while (!queueIsEmpty()) {
		int vertex;
		queueDequeue(&vertex);

		printf("%d ", vertex);

		for (int dest = 0; dest < N; dest++) {
			if (graph[vertex][dest] == 0) //not an edge
				continue;
			if (visited[dest])//already visited
				continue;
			queueEnqueue(dest);
			visited[dest] = 1;
		}
	}
}

int bfs_main(void) {
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
	bfs();
	getch();
#endif
	return 0;
}