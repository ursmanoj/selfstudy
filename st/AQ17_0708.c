#include <malloc.h>
typedef struct _dictNode {
	int count;
	struct _dictNode * subtrees[26];
	int *indices;//use malloc and realloc to adjust count
	int branchCount;//words branching out of this character ie parent
} dictNode;

dictNode root;

static void initNode(dictNode * n) {
	n->count = 0;
	n->indices = NULL;
	n->branchCount = 0;

	for (int i = 0; i < 26; i++)
		n->subtrees[i] = NULL;
}

static dictNode * createNode(char * str) {
	dictNode * n = malloc(sizeof(dictNode));
	initNode(n);

	if (*str == 0) {//string terminated
		n->count = 1;
		return n;
	}

	n->subtrees[*str - 'a'] = createNode(str + 1);
	n->branchCount++;
	return n;
}

typedef enum {
	EXIST,
	NOT_EXIST
} existence;
//#define EXIST 1
//#define NOT_EXIST 0
#define INSERT 1
#define SEARCHONLY 0

static int searchNInsert(dictNode * cur, char * str, int option) {
	if (*str == 0) {
		if (option == INSERT)
			cur->count++;
		if (cur->count == 0)
			return NOT_EXIST;
		return EXIST;
	}
	int i = *str - 'a';

	if (cur->subtrees[i] != NULL) {
		return searchNInsert(cur->subtrees[i], str + 1, option);
	}
	if (option == SEARCHONLY)
		return NOT_EXIST;

	cur->subtrees[i] = createNode(str+1);
	cur->branchCount++;

}
static char wordTemp[21];

static void traverse(dictNode * cur, char * word) {
	if (cur->count) {
		*word = 0;
		printf("%s\n", wordTemp);
	}
	for (int i = 0; i < 26; i++) {
		if (cur->subtrees[i]) {
			//printf("%c", 'a'+i);
			*word = 'a' + i;
			traverse(cur->subtrees[i], word+1);
		}
	}
}

static char autoTmp[21];

static int autoSuggest(dictNode * cur, char * str, char * autoStr) {
	if (str!=NULL && *str) {
		//string still exist so to be matched
		int i = *str - 'a';
		if (cur->subtrees[i]) {
			*autoStr = *str;
			return autoSuggest(cur->subtrees[i], str + 1, autoStr + 1);
		}
		//not matched
		return 0;
	}
	//str already matched, now just keep going until multiple branches
	if (cur->branchCount == 1) {
		for(int i=0;i<26;i++) 
			if (cur->subtrees[i]) {
				*autoStr = i + 'a';
				return autoSuggest(cur->subtrees[i], NULL, autoStr + 1);
			}
	}
	//mutlibranch
	//end mark
	*autoStr = 0;
	return 1;
}

static void displayDict(void) {
	traverse(&root, wordTemp);
}


int main_dict(void) {
	initNode(&root);

	searchNInsert(&root, "manoj", INSERT);
	searchNInsert(&root, "manmohan", INSERT);
	searchNInsert(&root, "suhyang", INSERT);
	searchNInsert(&root, "suhyandoor", INSERT);
	searchNInsert(&root, "sooji", INSERT);
	searchNInsert(&root, "superman", INSERT);
	searchNInsert(&root, "supergirl", INSERT);
	searchNInsert(&root, "apple", INSERT);

	existence find = searchNInsert(&root, "manoj", SEARCHONLY);

	//find = searchNInsert(&root, "manoj", SEARCHONLY);
	//find = searchNInsert(&root, "manmohan", SEARCHONLY);
	//find = searchNInsert(&root, "manok", SEARCHONLY);
	//find = searchNInsert(&root, "man", SEARCHONLY);

	displayDict();

	char autoWord[21];
	char *curWord = "suh";
	if (autoSuggest(&root, curWord, autoWord))
		printf("\nIncomplete: %s, suggested: %s", curWord, autoWord);
	else
		printf("\nNo match for %s", curWord);

	return 0;
}
