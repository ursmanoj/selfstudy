#include <stdio.h>

static char str[] = "ABCD";

static void swap(char * a, char *b) {
	char t = *a;
	*a = *b;
	*b = t;
}

static void permute(char * begin) {
	if (*begin == 0) {
		printf("%s\n", str);
		return;
	}

	for (char *tmp = begin; *tmp; tmp++) {
		if (tmp != begin && *begin == *tmp) //This will take care of duplicate chars
			continue;
		swap(begin, tmp);
		permute(begin + 1);
		swap(begin, tmp);
	}
}

void permute_main(void) {
	permute(str);
	getch();
}