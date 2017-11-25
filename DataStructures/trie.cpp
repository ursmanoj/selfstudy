#include <iostream>
using namespace std;

struct node {
	bool isWord;
	node *branches[26];
	node() {
		isWord = false;
		for (int i = 0; i < 26; i++)
			branches[i] = 0;
	}
};

node* root;

static void insert(char *word) {
	char *s = word;
	node *t = root;

	while (*s) {
		int i = *s - 'a';

		if (t->branches[i] == 0)
			break;
		t = t->branches[i];
		s++;
	}
	if (*s == 0) {
		//already present
		t->isWord = true;
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
char word[20];
void printtrie(node * r, char *w) {
	*w = 0;
	for (int i = 0; i < 26; i++) {
		if (r->branches[i]) {
			*w = 'a' + i;
			printtrie(r->branches[i], w+1);
		}
	}
	if (r->isWord)
		cout << word<<endl;
}

void deleteTrie(node *r) {
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

void main_trie() {
	root = new node;

	insert("manoj");
	insert("manmohan");
	insert("devendra");
	insert("amit");

	
	printtrie(root, word);
	deleteTrie(root);
	printtrie(root, word);
}