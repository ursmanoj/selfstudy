#include <stdio.h>
//static char str[] = "GEEKSFORGKEES";
static char str[] = "MYNAMEISHMANOJKUMARSHARMA";

typedef struct _maxstr {
	char * ptr;
	char * end;
} helper_t;

helper_t StrStruct, *newStr, maxStr;

static void updateMaxLen(helper_t * newFound) {
	if ((newFound->end - newFound->ptr) > (maxStr.end - maxStr.ptr))
		maxStr = *newFound;
}

static char* isExist(helper_t * str, char ch) {
	char * tmp = str->ptr;

	while (tmp <= str->end) {
		if (ch == *tmp)
			return tmp;
		tmp++;
	}
	return NULL;
}


static helper_t * findLongestSub(void) {
	newStr = &StrStruct;
	newStr->ptr = str;
	newStr->end = str;
	maxStr = *newStr;

	char * ptr = newStr->ptr + 1;

	while (*ptr) {
		char * pre;
		pre = isExist(newStr, *ptr);
		if (pre == NULL) {
			newStr->end++;
			ptr++;
		}
		else {
			updateMaxLen(newStr);
			newStr->ptr = pre+1;
			newStr->end = ptr;
			ptr = ptr + 1;
		}

	}
	return &maxStr;
}

void effmymain(void) {
	char result[20];
	int len;

	findLongestSub();

	len = maxStr.end - maxStr.ptr + 1;

	memcpy(result, maxStr.ptr, len);
	result[len] = 0;
	printf("Longest substr: %s\n", result);
	getch();
}