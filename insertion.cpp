#include<iostream>

using namespace std;

class Node {
public:
	int data;
	Node* p;
	Node* left;
	Node* right;
	int color;           // 1- red and 0- black
};

typedef Node* NodePtr;

class RBTree {
public:
	NodePtr root;
	NodePtr TNULL;

	RBTree() {
		TNULL = new Node;
		TNULL->color = 0;
		TNULL->left = nullptr;
		TNULL->right = nullptr;
		root = NULL;
	}

	void insert(int key);
	void RBInsert(NodePtr k);
	void leftRotate(NodePtr x);
	void rightRotate(NodePtr x);
};

void RBTree::insert(int key) {
	NodePtr node = new Node;
	node->p = nullptr;
	node->data = key;
	node->left = TNULL;
	node->right = TNULL;
	node->color = 1;


	NodePtr y = nullptr;
	NodePtr x = this->root;

	while (x!=TNULL) {
		y = x;
		if (node->data < x->data) {
			x = x->left;
		}
		else {
			x = x->right;
		}
	}

	node->p = y;
	if (y == nullptr) {
		root = node;
	}
	else if (node->data < y->data) {
		y->left = node;
	}
	else {
		y->right = node;
	}

	//if new node is the root node return 
	if (node->p == nullptr) {
		node->color = 0;
		return;
	}

	if (node->p->p == nullptr) {
		return;
	}
	RBInsert(node);
}

void RBTree::RBInsert(NodePtr k) {

}

void RBTree::leftRotate(NodePtr x) {
	NodePtr y = x->right;            //set y
	x->right = y->left;               //turn y's left subtree into x's right subtree

	if (y->left != TNULL) {
		y->left->p = x;
	}

	y->p = x->p;

	if (x->p == TNULL) {
		this->root = y;
	}
	else if (x == x->p->left) {
		x->p->left = y;
	}
	else {
		x->p->right = y;
	}
	y->left = x;              //put x on y's left                                                       
	x->p = y;
}

void RBTree::rightRotate(NodePtr x) {
	NodePtr y = x->p;
	y->left = x->right;

	if (x->right != TNULL) {
		x->right->p = y;
	}

	x->p = y->p;

	if (y->p == TNULL) {
		this->root = x;
	}
	else if (y == y->p->left) {
		y->p->left = x;
	}
	else {
		y->p->right = x;
	}
	x->right = y;
	y->p = x;
}

int main()
{

	system("pause");
	return 0;
}