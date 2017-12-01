#include <iostream>
using namespace std;

int SEG_FUNC(int x, int y) {
	if (x < y)
		return x;
	return y;
}

#define SEG_DEF_VALUE 50000

static int A[] = { 1, 8, 20, 3, 11, 7, 16, 13 };

static const int N = sizeof(A)/sizeof(A[0]);

static int st[3 * N];

static void constructSegtree(int r, int b, int e) {
	if (b == e) {
		st[r] = A[b];
		return;
	}
	int mid = b + (e - b) / 2;

	constructSegtree(2 * r + 1, b, mid);
	constructSegtree(2 * r + 2, mid+1, e);
	st[r] = SEG_FUNC(st[2 * r + 1], st[2 * r + 2]);
}

static int findSegtree(int r, int b, int e, int qb, int qe) {
	if (qe<b || qb>e)//if out of range
		return SEG_DEF_VALUE;

	//if full overalp
	if (qb <= b && qe >= e)
		return st[r];

	//partial overlap
	int mid = b + (e - b) / 2;
	int v1 = findSegtree(2 * r + 1, b, mid, qb, qe);
	int v2 = findSegtree(2 * r + 2, mid + 1, e, qb, qe);

	return SEG_FUNC(v1, v2);
}

void main_segtreeMin() {

	constructSegtree(0, 0, N - 1);

	cout << findSegtree(0, 0, N - 1, 0, 2) << endl;
	cout << findSegtree(0, 0, N - 1, 0, 7) << endl;
	cout << findSegtree(0, 0, N - 1, 3, 7) << endl;
	cout << findSegtree(0, 0, N - 1, 5, 7) << endl;
}