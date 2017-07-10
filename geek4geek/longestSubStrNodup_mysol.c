static char str[] = "GEEKSFORGEEKS";
//static char str[] = "MYNAMEISHMANOJKUMARSHARMA";

typedef struct _maxstr {
	char * ptr;
	char * end;
} helper_t;

helper_t StrStruct, *newStr, maxStr;

static void updateMaxLen(helper_t * newFound) {
	if ((newFound->end - newFound->ptr) > (maxStr.end - maxStr.ptr))
		maxStr = *newFound;
}

static int isExist(helper_t * str, char ch) {
	char * tmp = str->ptr;

	while (tmp <= str->end) {
		if (ch == *tmp)
			return 1;
		tmp++;
	}
	return 0;
}


static helper_t * findLongestSub(void) {
	newStr = &StrStruct;
	newStr->ptr = str;
	newStr->end = str;
	maxStr = *newStr;

	char * ptr = newStr->ptr + 1;

	while (*ptr) {
		if (!isExist(newStr, *ptr)) {
			newStr->end++;
			ptr++;
		} else {
			updateMaxLen(newStr);
			newStr->ptr++;
			newStr->end = newStr->ptr;
			ptr = newStr->ptr + 1;
		}
		
	}
	return &maxStr;
}

void my_main(void) {
	char result[20];
	int len;

	findLongestSub();

	len = maxStr.end - maxStr.ptr + 1;

	memcpy(result, maxStr.ptr, len);
	result[len] = 0;
	printf("Longest substr: %s\n", result);
	getch();
}