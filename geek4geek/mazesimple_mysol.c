#include <stdio.h>

#define N 5

static int result[8][8];

static int matrix[N][N] = {
{ 1, 0, 0, 0, 0 },
{ 1, 1, 1, 1, 0 },
{ 0, 1, 0, 0, 0 },
{ 1, 1, 1, 1, 0 },
{ 1, 1, 0, 1, 1 },
};

static int visited[8][8];
static int stepCounter = 0;

typedef struct _move {
	int r;
	int c;
} move_t;
static move_t moves[] = {
	{ 0,1 },
	{ 1,0 }
};

static void reset(void) {
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			visited[i][j] = -1;
}

static int isValid(int rPos, int cPos) {
	if (rPos < 0 || rPos > (N-1) || cPos < 0 || cPos > (N-1))
		return 0;

	if (matrix[rPos][cPos] == 0)
		return 0;
	return 1;
}

static void calculateNewPos(int curR, int curC, move_t * move, int *pNewR, int *pNewC) {
	*pNewR = curR + move->r;
	*pNewC = curC + move->c;
}

static int findRoute(int curR, int curC) {
	int newR, newC;
	for (int i = 0; i < sizeof(moves)/sizeof(moves[0]); i++) {
		move_t *move = &moves[i];

		calculateNewPos(curR, curC, move, &newR, &newC);
		if (!isValid(newR, newC))
			continue;

		result[newR][newC] = 1;

		if (newR == (N-1) && newC == (N-1))//reached destination
			return 1;

		//For now newPos is valid however dest not reached yet, therefore calc next position
		if (findRoute(newR, newC))
			return 1;
		else {
			//revert
			result[newR][newC] = 0;
			continue;
		}
	}
	//Control reach here means this tree couldnt find a solution
	return 0;
}

static void printResult(void) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++)
			printf("%d ", result[i][j]);
		printf("\n");
	}
}

void maze_main(void) {
	//reset();
	visited[0][0] = 0;
	findRoute(0, 0);
	printResult();
	getch();
}