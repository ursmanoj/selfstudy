#include <stdio.h>

static int result[8][8];
static int visited[8][8];
static int stepCounter = 0;

typedef struct _move {
	int r;
	int c;
} move_t;
static move_t moves[] = {
	{-2,1},
	{-1,2},
	{1,2},
	{2,1},
	{ 2,-1 },
	{ 1,-2 },
	{ -1,-2 },
	{-2,-1}
};

static void reset(void) {
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
			visited[i][j] = -1;
}

static int isValid(int rPos, int cPos) {
	if (rPos < 0 || rPos > 7 || cPos < 0 || cPos > 7)
		return 0;
	return 1;
}

static void calculateNewPos(int curR, int curC, move_t * move, int *pNewR, int *pNewC) {
	*pNewR = curR + move->r;
	*pNewC = curC + move->c;
}

static int findRoute(int curR, int curC) {
	int newR, newC;
	for (int i = 0; i < 8; i++) {
		move_t *move = &moves[i];
		//if (!isValid(move, curR, curC))
		//	continue;

		calculateNewPos(curR, curC, move, &newR, &newC);
		if (!isValid(newR, newC))
			continue;

		if (visited[newR][newC]>=0)
			continue;

		visited[newR][newC] = stepCounter + 1;
		stepCounter++;

		if (stepCounter == 63)//All cells visited
			return 1;

		//For now newPos is valid however all cells not visited yet, therefore calc next position
		if (findRoute(newR, newC))
			return 1;
		else {
			//revert visited matrix
			visited[newR][newC] = -1;
			stepCounter--;
			continue;
		}
	}
	//Control reach here means this tree couldnt find a solution
	return 0;
}

static void printResult(void) {
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++)
			printf("%2d ",visited[i][j]);
		printf("\n");
	}
}

void knight_main(void) {
	reset();
	visited[0][0] = 0;
	findRoute(0, 0);
	printResult();
	getch();
}