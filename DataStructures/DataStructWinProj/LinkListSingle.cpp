#include <iostream>
using namespace std;


struct Node {
	int data;
	struct Node* next;
};


static Node* Insert(Node *head, int data)
{
	// Complete this method
	Node *n = new Node;
	n->data = data;
	n->next = NULL;

	if (head == NULL)
		return n;
	Node * t = head;
	while (t->next) {
		t = t->next;
	}
	t->next = n;
	return head;
}

bool has_cycle(Node* head) {
	// Complete this function
	// Do not write the main method
	if (!head)
		return false;

	Node * fst, *slw;
	slw = head;
	fst = head->next;
	while (fst) {
		if (fst == slw)
			return true;
		slw = slw->next;
		fst = fst->next;
		if (fst == slw)
			return true;
		if (fst)
			fst = fst->next;
	}
	return false;
}

void main_sll() {
	Node *head = 0;

	head = Insert(head, 1);
	head = Insert(head, 2);
	head = Insert(head, 3);

	cout << "Cycle: " << has_cycle(head) << endl;

	head->next->next->next = head->next;//Make a cycle


	cout << "Cycle: " << has_cycle(head) << endl;
}