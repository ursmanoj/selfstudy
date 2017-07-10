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


static void resetVisited(void) {
	for (int v = 0; v < N; v++)
		visited[v] = 0;
}

static int parent[MAX];
static int unionSet(int X, int Y) {
	parent[X] = Y;
}

static int findSet(int item) {
	if (parent[item] == -1)
		return item;
	return findSet(parent[item]);
}

static int checkCycle(void) {
	//for each edge e(u,v):
	for(int u =0; u<N; u++)
		for (int v = u + 1; v < N; v++) {
			//find sets of u and v 
			int X = findSet(u);
			int Y = findSet(v);

			if (X == Y)
				return 1;
			//X and Y are disjoint hence merge (union) them
			unionSet(X, Y);
		}
	return 0;
}

static void reset(void) {
	for (int src = 0; src < N; src++) {
		parent[src] = -1;
	}
}

int set_main(void) {
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
	reset();
	printf("\nCycle: %d\n", checkCycle());
	getch();
#endif
	return 0;
}