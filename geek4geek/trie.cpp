#include <stdio.h>
#include <conio.h>
#include <iostream>
using namespace std;

#define ARRAY_SIZE(a) sizeof(a)/sizeof(a[0])

struct TrieNode {
	bool isWordEnd;
	int branchCount;

	TrieNode * branches[26];

	TrieNode() {
		isWordEnd = false;
		branchCount = 0;
		for (int i = 0; i < 26; i++)
			branches[i] = nullptr;
	}
};


static void insert(TrieNode * root, char * key) {
	TrieNode * cur = root;

	for (int i = 0; key[i]; i++) {
		int j = key[i] - 'a';

		if (cur->branches[j] == nullptr) {
			cur->branches[j] = new TrieNode;
			cur->branchCount++;
		}
		cur = cur->branches[j];
	}
	//Key terminated at this node, so mark it
	cur->isWordEnd = true;
}

static bool search(TrieNode * root, char * key) {
	TrieNode * cur = root;

	for (int i = 0; key[i]; i++) {
		int j = key[i] - 'a';

		if (cur==nullptr ||cur->branches[j] == nullptr)
			return false;
		cur = cur->branches[j];
	}
	//Key terminated at this node, so mark it
	return cur->isWordEnd;
}
//return indicates weather to delete cur node or not
static bool deleteKey(TrieNode * root, char * str) {
	TrieNode * cur = root;
	int j = *str - 'a';
	
	//end of string not reached yet but no branch for next char-> str not exist, simply return
	if (*str && cur->branches[j] == nullptr)
		return false;

	//end of str reached
	if (*str==0) {
		if (cur->isWordEnd == false)//this string ended but actually not present in trie
			return false;
		cur->isWordEnd = false;//since this word to be deleted mark it not ending here
		if (cur->branchCount == 0)//no branches out of it, so safe to be deleted from parent
			return true;
		return false;
	}

	//end of str not reached, go deeper
	bool deleteChild = deleteKey(cur->branches[j], str + 1);

	if (deleteChild == false)//some reason caused child not be deleted, propagate same to upper nodes
		return false;

	//Child to deleted
	delete cur->branches[j];
	cur->branches[j] = nullptr;
	cur->branchCount--;

	if (cur->branchCount == 0 && cur->isWordEnd == false)//we can tell upper node to delete this only if it has no branches out of it AND no other words end here
		return true;
	return false;

}

void main_trie() {
	char keys[][8] = { "she", "sells", "sea", "shore", "the", "by", "sheer" };


	char output[][32] = { "Not present in trie", "Present in trie" };

	TrieNode *root = new TrieNode;
	// Construct trie
	int i;
	for (i = 0; i < ARRAY_SIZE(keys); i++)
		insert(root, keys[i]);

	// Search for different keys
	printf("%s --- %s\n", "the", output[search(root, "the")]);
	printf("%s --- %s\n", "these", output[search(root, "these")]);
	printf("%s --- %s\n", "their", output[search(root, "their")]);
	printf("%s --- %s\n", "thaw", output[search(root, "thaw")]);

	deleteKey(root,"sheer");

	char * findWord = "sheer";
	printf("%s %s\n", findWord, search(root, findWord) ? "Present in trie" : "Not present in trie");

	cout << "";
}