#include <stdio.h>
#include <conio.h>
#include <iostream>
using namespace std;

struct node {
	node * left, *right;
	int val;

	node(int val) {
		this->val = val;
		this->left = this->right = nullptr;
	}
};


static node * insert(node * root, int val) {
	if (root == nullptr) {
		return new node(val);
	}
	if (val <= root->val)
		root->left = insert(root->left, val);
	else
		root->right = insert(root->right, val);

	return root;
}

static node * detachMinValNode(node * root) {
	node * par = nullptr, *cur=root;
	while (cur->left) {
		par = cur;
		cur = cur->left;
	}
	//detach from parent
	par->left = nullptr;
	//return detached node
	return cur;
}

static node * del(node * root, int val) {
	if (root == nullptr)
		return nullptr;
	if (val < root->val)
		root->left =  del(root->left, val);
	else if(val>root->val)
		root->right = del(root->right, val);
	else //match: this node to be deleted
	{
		//only one child
		if (root->right == nullptr) {
			node * t = root->left;
			delete root;
			return t;
		} else if (root->left == nullptr) {
			node * t = root->right;
			delete root;
			return t;
		}
		//both right and left children exist
		node * newRoot = detachMinValNode(root->right);
		newRoot->left = root->left;
		newRoot->right = root->right;
		delete root;
		return newRoot;
	}
	return root;
}

static void inorder(node * root) {
	if (root == nullptr)
		return;

	inorder(root->left);
	cout << root->val<<" ";
	inorder(root->right);
}

void main_bst(void) {
	/* Let us create following BST
	50
	/     \
	30      70
	/  \    /  \
	20   40  60   80 */
	node *root = nullptr;
	root = insert(root, 50);
	root = insert(root, 30);
	root = insert(root, 20);
	root = insert(root, 40);
	root = insert(root, 70);
	root = insert(root, 60);
	root = insert(root, 80);

	printf("Inorder traversal of the given tree \n");
	inorder(root);

	printf("\nDelete 20\n");
	root = del(root, 20);
	printf("Inorder traversal of the modified tree \n");
	inorder(root);

	printf("\nDelete 30\n");
	root = del(root, 30);
	printf("Inorder traversal of the modified tree \n");
	inorder(root);

	printf("\nDelete 50\n");
	root = del(root, 50);
	printf("Inorder traversal of the modified tree \n");
	inorder(root);

}