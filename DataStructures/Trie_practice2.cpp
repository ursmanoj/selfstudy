#include <iostream>
using namespace std;

struct node {
	bool isWord;
	node *chars[26];
	node() {
		isWord = false;

		for (int i = 0; i < 26; i++) {
			chars[i] = 0;
		}
	}
	~node() {
		//cout << "destroyed" << endl;
		/*for (int i = 0; i < 26; i++) {
			if (chars[i])
				delete chars[i];
		}*/ //win has problem with delete when struct has pointer of its own type
	}
};

static node topNode;

static bool find(char word[]) {
	node * t = &topNode;
	char * s = word;

	while (*s) {
		int i = *s - 'a';

		if (t->chars[i] == 0)
			break;
		t = t->chars[i];
		s++;
	}

	if (*s == 0 && t->isWord) {
		//word in trie, 
		return true;
	}
	return false;
}

static void insert(char word[]) {
	node * t = &topNode;
	char * s = word;

	while (*s) {
		int i = *s - 'a';

		if (t->chars[i] == 0)
			break;
		t = t->chars[i];
		s++;
	}

	if (*s == 0) {
		//word already in trie, just mark it
		t->isWord = true;
		return;
	}
	//some chars not in trie yet, add them in form of branches
	while (*s) {
		int i = *s - 'a';

		t->chars[i] = new node;
		t = t->chars[i];
		s++;
	}
	//all chars added, mark the word
	t->isWord = 1;
}

static void printTrie(node *t, char original[], char * curPtr) {
	if (t->isWord) {
		*curPtr = 0;
		cout << original << endl;
	}

	for (int i = 0; i < 26; i++) {
		if (t->chars[i]) {
			*curPtr = 'a' + i;
			printTrie(t->chars[i], original, curPtr + 1);
		}
	}
}


static void deleteTrie(node *t) {
	for (int i = 0; i < 26; i++) {
		if (t->chars[i]) {
			delete t->chars[i];
			t->chars[i] = 0;
		}
	}
}

static void testFind() {
	char * words[] = { "manoj", "man", "anm", "anmol", "anki", "ankit" };
	int count = sizeof(words) / sizeof(words[0]);
	for (int i = 0; i < count;i++)
		cout << words[i] << " found: " << find(words[i])<<endl;

}

void main_trie2() {
#if 1
	insert("manoj");
	insert("manda");
	insert("ankit");
	insert("anmol");
	insert("an");
	insert("mano");
#endif
	//insert("a");
	//insert("ab");
	char tmp[20];
	printTrie(&topNode, tmp, tmp);

	testFind();
	//deleteTrie(&topNode);
	//topNode;
	//node *t = new node;
	//delete t;
}