#include <iostream>
using namespace std;

static int SEG_FUNC(int x, int y) {
	if (x < y)
		return x;
	return y;
}

#define SEG_DEF_VALUE 50000

static int A[] = { 1, 8, 20, 3, 11, 7, 16, 13 };

static const int N = sizeof(A) / sizeof(A[0]);

static int st[3 * N];
static int lazy[3 * N];

static void constructSegtree(int r, int b, int e) {
	if (b == e) {
		st[r] = A[b];
		return;
	}
	int mid = b + (e - b) / 2;

	constructSegtree(2 * r + 1, b, mid);
	constructSegtree(2 * r + 2, mid + 1, e);
	st[r] = SEG_FUNC(st[2 * r + 1], st[2 * r + 2]);
}

static void passToChildren(int r, int b, int e) {

	if (lazy[r] == 0)
		return;

	//pass to children
	if (b != e) {
		lazy[2 * r + 1] += lazy[r];
		lazy[2 * r + 2] += lazy[r];
	}
	//update current node and then clear lazy field
	st[r] += lazy[r];
	lazy[r] = 0;

}

static int findSegtree(int r, int b, int e, int qb, int qe) {
	passToChildren(r, b, e);//update current node and pass to children if lazy is pending

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



static void updateSegtree(int r, int b, int e, int qb, int qe, int v) {
	passToChildren(r, b, e);//update current node and pass to children if lazy is pending

	//now check about current update reqeust.

	if (qe<b || qb>e)//if out of range
		return;

	//if leaf
	if (b == e) {
		st[r] += v;
		return;
	}

	//if full overalp
	if (qb <= b && qe >= e) {
		//just update lazy and return
		lazy[r] += v;
		return;
	}

	//partial overlap
	
	//current node 
	int mid = b + (e - b) / 2;
	updateSegtree(2 * r + 1, b, mid, qb, qe, v);
	updateSegtree(2 * r + 2, mid+1, e, qb, qe, v);

	//child st might have been updated , update here too
	st[r] = SEG_FUNC(st[2 * r + 1], st[2 * r + 2]);
}

void main_segtreeMinLazy() {

	constructSegtree(0, 0, N - 1);

	for (int i = 0; i < N; i++)
		printf("%2d ", i);
	cout << endl;
	

	updateSegtree(0, 0, N - 1, 3, 7, 5);

	for (int i = 0; i < N; i++)
		printf("%2d ", A[i]);
	cout << endl;

	cout << findSegtree(0, 0, N - 1, 0, 2) << endl;
	cout << findSegtree(0, 0, N - 1, 0, 7) << endl;
	cout << findSegtree(0, 0, N - 1, 3, 3) << endl;
	cout << findSegtree(0, 0, N - 1, 5, 7) << endl;
}