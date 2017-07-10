#include <stdio.h>

//#define MULTI_CASE

#define MAX 7

//static int graph[MAX][MAX] = {
//	0, 1, 1, 0,
//	0, 0, 1, 0,
//	1, 0, 0, 1,
//	0, 0, 0, 1,
//};

static int graph[MAX][MAX] = {
	0, 1, 0, 0, 0, 0, 0,
	1, 0, 1, 1, 0, 0, 0,
	0, 1, 0, 0, 0, 0, 0,
	0, 1, 0, 0, 1, 1, 0,
	0, 0, 0, 1, 0, 1, 1,
	0, 0, 0, 1, 1, 0, 0,
	0, 0, 0, 0, 1, 0, 0,
};

static int visited[MAX];
static int N = MAX, M;
static int startNode;

static int isCycle(int vertex, int parent) {
	if (visited[vertex])
		return 1;

	visited[vertex] = 1;

	printf("%d ", vertex);

	for (int dest = 0; dest < N; dest++) {
		if (graph[vertex][dest] == 0) //not an edge
			continue;

		if (dest == parent)
			continue;

		if (visited[dest]) {//this neighbor already visited, and we reached it again meaning a cycle
			printf("\nAlready Visited: %d", dest);
			return 1;
		}
		int ret = isCycle(dest, vertex);
		if (ret)
			return 1;
	}
	return 0;
}

static void resetVisited(void) {
	for (int v = 0; v < N; v++)
		visited[v] = 0;
}

static int checkCycle(void) {
	return isCycle(3, -1);
}

static void reset(void) {
	for (int src = 0; src < N; src++) {
		visited[src] = 0;
		for (int dst = 0; dst < N; dst++) {
			graph[src][dst] = 0;
		}
	}
}

int cycleUn_dfs_main(void) {
#ifdef MULTI_CASE
	int T;

	scanf("%d", &T);

	while (T) {
		scanf("%d", &N);
		scanf("%d", &M);
		reset();
		for (int i = 0; i < M; i++) {
			int src, dst;
			scanf("%d %d", &src, &dst);

			graph[src][dst] = 1;
		}
		printf("%d\n", checkCycle());
		T--;
	}

#else
	printf("\nCycle: %d\n", checkCycle());
	getch();
#endif
	return 0;
}