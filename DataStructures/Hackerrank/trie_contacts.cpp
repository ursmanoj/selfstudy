#include <iostream>
using namespace std;

struct node {
	bool isWord;
	node *branches[26];
	int prefixCount;
	node() {
		isWord = false;
		prefixCount = 1;
		for (int i = 0; i < 26; i++)
			branches[i] = 0;
	}
};

static node* root;

static void insert(char *word) {
	char *s = word;
	node *t = root;

	while (*s) {
		t->prefixCount++;
		int i = *s - 'a';

		if (t->branches[i] == 0)
			break;
		t = t->branches[i];
		s++;
	}
	if (*s == 0) {
		//already present
		t->isWord = true;
		t->prefixCount++;
		return;
	}
	//few chars remaining, create branch for char
	while (*s) {
		int i = *s - 'a';

		t->branches[i] = new node;
		t = t->branches[i];
		s++;
	}
	t->isWord = true;
}
static char word[20];
static void printtrie(node * r, char *w) {
	
	for (int i = 0; i < 26; i++) {
		if (r->branches[i]) {
			*w = 'a' + i;
			printtrie(r->branches[i], w + 1);
		}
	}
	*w = 0;
	if (r->isWord)
		cout << word << endl;
}

static void deleteTrie(node *r) {
	if (r == 0)
		return;

	for (int i = 0; i < 26; i++) {
		if (r->branches[i] == 0)
			continue;
		deleteTrie(r->branches[i]);
		delete r->branches[i];
		r->branches[i] = 0;
	}
}

static int find(char * part) {

	char *s = part;
	node * t = root;

	while (*s) {
		int i = *s - 'a';

		if (t->branches[i] == 0)
			return 0;
		t = t->branches[i];
		s++;
	}
	if (*s == 0) {
		//found
		return t->prefixCount;
	}
	return 0;
}


void main_hackerTrie() {
	root = new node;
	//root->prefixCount = 0;

	insert("manoj");
	insert("man");
	insert("manmohan");
	insert("devendra");
	insert("amit");


	printtrie(root, word);

	cout << find("a") << endl;
	deleteTrie(root);
	//printtrie(root, word);
}