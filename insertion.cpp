#include<iostream>

using namespace std;

class Node {
public:
	int data;
	Node* parent;
	Node* left;
	Node* right;
	int color;           // 1- red and 0- black
};

typedef Node* NodePtr;

class RBTree {
public:
	NodePtr root;
	NodePtr leaf;

	RBTree() {
		leaf = new Node;
		leaf->color = 0;
		leaf->left = nullptr;
		leaf->right = nullptr;
		root = NULL;
	}

	void insert(int key);
	void RBInsert(NodePtr k);
};

void RBTree::insert(int key) {
	NodePtr node = new Node;
	node->parent = nullptr;
	node->data = key;
	node->left = leaf;
	node->right = leaf;
	node->color = 1;


	NodePtr y = nullptr;
	NodePtr x = this->root;

	while (x!=leaf) {
		y = x;
		if (node->data < x->data) {
			x = x->left;
		}
		else {
			x = x->right;
		}
	}

	node->parent = y;
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
	if (node->parent == nullptr) {
		node->color = 0;
		return;
	}

	if (node->parent->parent == nullptr) {
		return;
	}
	RBInsert(node);
}

void RBTree::RBInsert(NodePtr k) {

}

int main()
{

	system("pause");
	return 0;
}