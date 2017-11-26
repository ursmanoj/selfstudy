#include <iostream>
using namespace std;

#define LOCAL static

LOCAL const int N = 5;
static int graph[N][N] = {
	0,1,0,0,1,
	1,0,1,1,1,
	0,1,0,1,0,
	0,1,1,0,1,
	1,1,0,1,0
};

static bool visited[N];//read as isEnqued in case of bfs

static void dfs(int v) {
	cout << v << " " << endl;
	visited[v] = true;
	
	//for each non-visited nb
	for (int nb = 0; nb < N; nb++) {
		if (!graph[v][nb] || nb == v || visited[nb])
			continue;
		dfs(nb);
	}
}


void pushQ(int val);	
int pullQ();
bool isEmptyQ();

static void bfs(int v) {
	pushQ(v);
	visited[v] = true;

	while (!isEmptyQ()) {
		v = pullQ();
		cout << v << " " << endl;
		for (int nb = 0; nb < N; nb++) {
			if (!graph[v][nb] || nb == v || visited[nb])
				continue;
			pushQ(nb);
			visited[nb] = true;
		}
	}
}

void main_graph_matrix() {
	int startV = 0;
	//dfs(startV);
	bfs(startV);
}