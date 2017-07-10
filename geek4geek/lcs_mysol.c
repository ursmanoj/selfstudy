#include <stdio.h>

//static char str1[] = "AGGTAB";
//static char str2[] = "GXTXAYB";

static char str1[] = "ABCDGH";
static char str2[] = "AEDFHR";

/*static char str1[] = "ABCDGH";
static char str2[] = "AAEDBFHCRDGwerewgsgHdafgew";*/

static char * search(char ch, char * str) {
	char * tmp = str;
	while (*tmp) {
		if (*tmp == ch)
			return tmp;
		tmp++;
	}
	return NULL;
}
static char subSeq[100];
static char subSeqTmp[100];

static int findLCI(void) {
	int maxlen = 0, curlen=0;
	int i, j;
	char * t = str1;
	char *subSeqPtr = subSeq;
	char * subSeqTmpPtr = subSeqTmp;

	for (; *t; t++) {
		char ch1 = *t;
		char * loc1 = t;
		char * loc2 = str2;

		curlen = 0;
		subSeqTmpPtr = subSeqTmp;
		

		while (*loc1) {
			char * loc = search(*loc1, loc2);

			if (loc == NULL) {
				loc1++;
				continue;
			}

			//Found char so increment len
			*subSeqTmpPtr = *loc1;
			subSeqTmpPtr++;
			loc1++;
			loc2 = loc+1;
			curlen++;
		}
		*subSeqTmpPtr = 0;
		if (curlen > maxlen) {
			maxlen = curlen;
			//Update subseq:
			strcpy(subSeq, subSeqTmp);

		}
	}
	return maxlen;
}

void mysol_main(void) {
	int len = findLCI();
	printf("MaxCommon Len: %d\n", len);
	printf("Max Common Sub Sequenc: %s", subSeq);
	getch();
}