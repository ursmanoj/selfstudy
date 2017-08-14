#include <iostream>

using namespace std;

#define MIN(a,b) ((a)<(b)?(a):(b))

//static int arr[] = { -1,3,4,0,2,1 };
static int arr[] = { 1,3,5,7,9,11 };

static int segTree[5 * sizeof(arr) / sizeof(arr[0])];

static const int arrSize = sizeof(arr) / sizeof(arr[0]);
static int maxNum;

static void constructSegTree(int first = 0, int last = arrSize - 1, int pos = 0) {
	if (first == last) {
		segTree[pos] = arr[first];
		return;
	}

	int mid = (first + last) / 2;

	constructSegTree(first, mid, 2 * pos + 1);
	constructSegTree(mid + 1, last, 2 * pos + 2);
	segTree[pos] = segTree[2 * pos + 1]+ segTree[2 * pos + 2];
}

static int findSum(int low, int high, int first = 0, int last = arrSize - 1, int pos = 0) {
	if (low > last || high < first)//no overlap
		return 0;

	if (low <= first && high >= last)//full overlap
		return segTree[pos];

	//partial overlap, check both child trees
	int mid = (first + last) / 2;

	return findSum(low, high, first, mid, 2 * pos + 1)+
		findSum(low, high, mid + 1, last, 2 * pos + 2);
}

void main_segtree_sum(void) {
	////find maxNum
	//maxNum = arr[0];
	//for (int i = 1; i < arrSize; i++)
	//	if (arr[i] > maxNum)
	//		maxNum = arr[i];
	//construct seg tree
	constructSegTree();

	//testing
	int low = 1, high = 4;
	cout << "MinRange(" << low << ", " << high << "): " << findSum(low, high) << endl;
}


