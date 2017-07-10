#include <stdio.h>

//#define MULTI_CASE

#define MAX 6

//static int graph[MAX][MAX] = {
//	0, 1, 1, 0,
//	0, 0, 1, 0,
//	1, 0, 0, 1,
//	0, 0, 0, 1,
//};

static int graph[MAX][MAX] = {
	0, 1, 1, 0, 0, 0,
	0, 0, 1, 0, 1, 1,
	0, 0, 0, 1, 0, 0,
	0, 0, 0, 0, 1, 0,
	0, 0, 0, 0, 0, 1,
	0, 0, 0, 0, 0, 0,
};

static int visited[MAX];
static int N = MAX, M;
static int startNode;

static int isCycle(int vertex) {
	visited[vertex] = 1;

	printf("%d ", vertex);

	for (int dest = 0; dest < N; dest++) {
		if (graph[vertex][dest] == 0) //not an edge
			continue;
		if (dest == startNode) {//reached startpoint again hence a cycle
			printf("\nAlready Visited: %d", dest);
			return 1;
		}
		if (visited[dest])
			continue;
		int ret = isCycle(dest);
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
	for (int i = 0; i < N; i++) {
		printf("\n");
		startNode = i;
		resetVisited();
		if (isCycle(i))
			return 1;
	}
	return 0;
}

static void reset(void) {
	for (int src = 0; src < N; src++) {
		visited[src] = 0;
		for (int dst = 0; dst < N; dst++) {
			graph[src][dst] = 0;
		}
	}
}

int cycleD_main(void) {
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