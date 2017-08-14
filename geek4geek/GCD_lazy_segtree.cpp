#include <stdio.h>
#ifdef WIN32
#define DBGMODE
#include "IDEResolver.h"

#ifdef DBGMODE
#define dbg printf
#define waituser getch
#else
#define waituser()
#define dbg
#endif

#else

#define INPUTFILEOPEN
#define waituser()
#define dbg
#endif


//output so far
/*
#1 445321183
#2 919188783
#3 765929301
#4 561445095
#5 158953157
*/
#include <iostream>
using namespace std;

#define MIN(a,b) ((a)<(b)?(a):(b))
#define MAX(a,b) ((a)>(b)?(a):(b))

static int N, M, k;
static unsigned long long A[100001], answer;

#define MIN(a,b) ((a)<(b)?(a):(b))

static unsigned long long *arr = A;

static unsigned long long segTree[262145];
static  long long lazyTree[262145];

static unsigned long long GCD(unsigned long long a, unsigned long long b);

static void constructSegTree(int first = 1, int last = N, int pos = 1) {
	if (first == last) {
		segTree[pos] = arr[first];
		lazyTree[pos] = 0;
		return;
	}

	int mid = (first + last) / 2;

	constructSegTree(first, mid, 2 * pos);
	constructSegTree(mid + 1, last, 2 * pos + 1);
	segTree[pos] = GCD(segTree[2 * pos], segTree[2 * pos + 1]);
	lazyTree[pos] = 0;
}

static unsigned long long findGCDRange(int low, int high, int first = 1, int last = N, int pos = 1) {
	if (low > last || high < first)//no overlap
		return 0;

	if (low <= first && high >= last) {//full overlap
		if(lazyTree[pos]==0)
			return segTree[pos];

		//detected that this node and all children to be incremented and then GCD tree to be recalculated

	}

	//partial overlap, check both child trees
	int mid = (first + last) / 2;
	unsigned long long gcd1, gcd2;

	gcd1 = findGCDRange(low, high, first, mid, 2 * pos);
	gcd2 = findGCDRange(low, high, mid + 1, last, 2 * pos + 1);

	if (gcd1 == 0)
		return gcd2;
	if (gcd2 == 0)
		return gcd1;

	return GCD(gcd1, gcd2);
}


static unsigned long long GCD(unsigned long long a, unsigned long long b) {
	unsigned long long n1 = MAX(a, b);
	unsigned long long n2 = MIN(a, b);
	unsigned long long r;

	do {
		r = n1%n2;
		n1 = n2;
		n2 = r;
	} while (r);
	return n1;
}

static void updateSegTree(int low, int high, long long c, int first = 1, int last = N, int pos = 1) {
	if (low > last || high < first)//no overlap
		return;

	if (first == last) {//leaf node
		segTree[pos] += c;
		return;
	}

	if (low <= first && high >= last) {//full overlap
		//Just update this lazy node, as its marked non-zero, later it will a detection to update real segtree
		lazyTree[pos] += c;
		return;
	}

	//partial overlap
	int mid = (first + last) / 2;
	//this node is partial overlap, so mark it as -1, later it will be a detection that at least one child is to beupdated
	lazyTree[pos] = -1;
	updateSegTree(low, high, c, first, mid, 2 * pos);
	updateSegTree(low, high, c, mid + 1, last, 2 * pos + 1);
	
}

static void runAlgo() {
	k = 1;
	answer = 0;
	constructSegTree();
	for (int i = 1; i <= M; i++) {
		//take commands and execute them
		int cmd, l, r;

		cin >> cmd >> l >> r;

		if (cmd == 1) {
			unsigned long long gcd = findGCDRange(l, r);
			//int gcd = findGCDRange(2, 4);
			answer += k*gcd;
			k++;
		}

		else if (cmd == 2) {
			long long c;
			cin >> c;
			updateSegTree(l, r, c);
		}
	}
}

#ifdef WIN32
int main_gcd_segtreeLazy(void)
#else
int main(int argc, char** argv)
#endif
{
	int test_case;
	int T;
	/*
	freopen function below opens input.txt file in read only mode, and afterward,
	the program will read from input.txt file instead of standard(keyboard) input.
	To test your program, you may save input data in input.txt file,
	and use freopen function to read from the file when using scanf function.
	You may remove the comment symbols(//) in the below statement and use it.
	But before submission, you must remove the freopen function or rewrite comment symbols(//).
	*/
	INPUTFILEOPEN;
	/*
	If you remove the statement below, your program's output may not be recorded
	when your program is aborted due to the time limit.
	For safety, please use setbuf(stdout, NULL); statement.
	*/
	setbuf(stdout, NULL);
	//T = 10;
	cin >> T;

	/*
	Read each test case from standard input.
	*/

	for (test_case = 1; test_case <= T; ++test_case)
	{
		cin >> N >> M;

		for (int i = 1; i <= N; i++)
			cin >> A[i];

		runAlgo();

		cout << "#" << test_case << " " << answer % (1000000007) << endl;

	}
	return 0; //Your program should return 0 on normal termination.
}
