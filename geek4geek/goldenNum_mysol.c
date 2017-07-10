#include <stdio.h>


static int isGolden(int n) {
	int k = 2;

	int curPos = n;

	while (1) {
		if (curPos%k == 0)
			return 0;

		int removed = (curPos - 1) / k;

		int newPos = curPos - removed;
		k++;
		if (newPos < k)
			return 1;

		curPos = newPos;
	}
}

static int testData = 3;
void goldenmain(void) {
	printf("Isgolden(%d): %s", testData, isGolden(testData)?"TRUE":"FALSE");
	getch();
}