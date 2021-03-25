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
	void print_out(NodePtr root);
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

// 1- red and 0- black
void RBTree::RBInsert(NodePtr z){
	NodePtr y;          //this is the sibiling of the parent (uncle node)
	
	while (z->p->color == 1) {
		if (z->p == z->p->p->left) {
			y = z->p->p->right;
			if (y->color == 1) {
				z->p->color = 0;
				y->color = 0;
				z->p->p->color = 1;
				z = z->p->p;
			}
			else if (z == z->p->right) {
				z = z->p;
				leftRotate(z);
			}
			else {
				z->p->color = 0;
				z->p->p->color = 1;
				rightRotate(z->p->p);
			}
		}
		else {
			y = z->p->p->left;
			if (y->color == 1) {
				z->p->color = 0;
				y->color = 0;
				z->p->p->color = 1;
				z = z->p->p;
			}
			else if (z == z->p->left) {
				z = z->p;
				rightRotate(z);
			}
			else {
				z->p->color = 0;
				z->p->p->color = 1;
				leftRotate(z->p->p);
			}
		}
	}
	this->root->color = 0;
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

void RBTree::print_out(NodePtr val)
{
	if (val != NULL)
	{
		
		if (val->color == 0)
			printf("black ");
		else
			printf("red ");
		if (val->p != NULL)
			printf("%d ", root->p->data);
		else
			printf("- ");
		if (val->left != NULL)
			printf("%d ", val->left->data);
		else
			printf("- ");
		if (val->right != NULL)
			printf("%d ", root->right->data);
		else
			printf("- ");
		printf("\n");

		print_out(val->left);
		if (root->right != NULL)
		{
			print_out(val->right);
		}
	}
}


int main()
{
	RBTree bst;
	bst.insert(8);
	bst.insert(18);
	bst.insert(5);
	bst.insert(15);
	bst.insert(17);
	bst.insert(25);
	bst.insert(40);
	bst.insert(80);

	

	system("pause");
	return 0;
}