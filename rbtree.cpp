#include <iostream>


using namespace std;

// data structure that represents a node in the tree
class Node {
public:
	int data; // holds the key
	Node *p; // pointer to the parent
	Node *left; // pointer to left child
	Node *right; // pointer to right child
	int color; // 1 -> Red, 0 -> Black
};

typedef Node *NodePtr;

// class RBTree implements the operations in Red Black Tree
class RBTree {
private:
	NodePtr root;
	NodePtr TNULL;

	// initializes the nodes with appropirate values
	// all the pointers are set to point to the null pointer
	void initializeNULLNode(NodePtr node, NodePtr p) {
		node->data = 0;
		node->p = p;
		node->left = NULL;
		node->right = NULL;
		node->color = 0;
	}

	void preOrderHelper(NodePtr node) {
		if (node != TNULL) {
			cout<<node->data<<" ";
			preOrderHelper(node->left);
			preOrderHelper(node->right);
		} 
	}

	void inOrderHelper(NodePtr node) {
		if (node != TNULL) {
			inOrderHelper(node->left);
			cout<<node->data<<" ";
			inOrderHelper(node->right);
		} 
	}

	void postOrderHelper(NodePtr node) {
		if (node != TNULL) {
			postOrderHelper(node->left);
			postOrderHelper(node->right);
			cout<<node->data<<" ";
		} 
	}

	NodePtr searchTreeHelper(NodePtr node, int key) {
		if (node == TNULL || key == node->data) {
			return node;
		}

		if (key < node->data) {
			return searchTreeHelper(node->left, key);
		} 
		return searchTreeHelper(node->right, key);
	}

	// fix the rb tree modified by the delete operation
	void fixDelete(NodePtr x) {
		NodePtr s;
		while (x != root && x->color == 0) {
			if (x == x->p->left) {
				s = x->p->right;
				if (s->color == 1) {
					// case 3.1
					s->color = 0;
					x->p->color = 1;
					leftRotate(x->p);
					s = x->p->p;
				}

				if (s->left->color == 0 && s->right->color == 0) {
					// case 3.2
					s->color = 1;
					x = x->p;
				} else {
					if (s->right->color == 0) {
						// case 3.3
						s->left->color = 0;
						s->color = 1;
						rightRotate(s);
						s = x->p->right;
					} 

					// case 3.4
					s->color = x->p->color;
					x->p->color = 0;
					s->right->color = 0;
					leftRotate(x->p);
					x = root;
				}
			} else {
				s = x->p->left;
				if (s->color == 1) {
					// case 3.1
					s->color = 0;
					x->p->color = 1;
					rightRotate(x->p);
					s = x->p->left;
				}

				if (s->right->color == 0 && s->right->color == 0) {
					// case 3.2
					s->color = 1;
					x = x->p;
				} else {
					if (s->left->color == 0) {
						// case 3.3
						s->right->color = 0;
						s->color = 1;
						leftRotate(s);
						s = x->p->left;
					} 

					// case 3.4
					s->color = x->p->color;
					x->p->color = 0;
					s->left->color = 0;
					rightRotate(x->p);
					x = root;
				}
			} 
		}
		x->color = 0;
	}


	void rbTransplant(NodePtr u, NodePtr v){
		if (u->p == NULL) {
			root = v;
		} else if (u == u->p->left){
			u->p->left = v;
		} else {
			u->p->right = v;
		}
		v->p = u->p;
	}

	void deleteNodeHelper(NodePtr node, int key) {
		// find the node containing key
		NodePtr z = TNULL;
		NodePtr x, y;
		while (node != TNULL){
			if (node->data == key) {
				z = node;
			}

			if (node->data <= key) {
				node = node->right;
			} else {
				node = node->left;
			}
		}

		if (z == TNULL) {
			cout<<"Couldn't find key in the tree"<<endl;
			return;
		} 

		y = z;
		int y_original_color = y->color;
		if (z->left == TNULL) {
			x = z->right;
			rbTransplant(z, z->right);
		} else if (z->right == TNULL) {
			x = z->left;
			rbTransplant(z, z->left);
		} else {
			y = minimum(z->right);
			y_original_color = y->color;
			x = y->right;
			if (y->p == z) {
				x->p = y;
			} else {
				rbTransplant(y, y->right);
				y->right = z->right;
				y->right->p = y;
			}

			rbTransplant(z, y);
			y->left = z->left;
			y->left->p = y;
			y->color = z->color;
		}
		delete z;
		if (y_original_color == 0){
			fixDelete(x);
		}
	}
	
	// fix the red-black tree
	void fixInsert(NodePtr k){
		NodePtr u;
		while (k->p->color == 1) {
			if (k->p == k->p->p->right) {
				u = k->p->p->left; // uncle
				if (u->color == 1) {
					// case 3.1
					u->color = 0;
					k->p->color = 0;
					k->p->p->color = 1;
					k = k->p->p;
				} else {
					if (k == k->p->left) {
						// case 3.2.2
						k = k->p;
						rightRotate(k);
					}
					// case 3.2.1
					k->p->color = 0;
					k->p->p->color = 1;
					leftRotate(k->p->p);
				}
			} else {
				u = k->p->p->right; // uncle

				if (u->color == 1) {
					// mirror case 3.1
					u->color = 0;
					k->p->color = 0;
					k->p->p->color = 1;
					k = k->p->p;	
				} else {
					if (k == k->p->right) {
						// mirror case 3.2.2
						k = k->p;
						leftRotate(k);
					}
					// mirror case 3.2.1
					k->p->color = 0;
					k->p->p->color = 1;
					rightRotate(k->p->p);
				}
			}
			if (k == root) {
				break;
			}
		}
		root->color = 0;
	}



public:
	RBTree() {
		TNULL = new Node;
		TNULL->color = 0;
		TNULL->left = NULL;
		TNULL->right = NULL;
		root = TNULL;
	}

	// Pre-Order traversal
	// Node->Left Subtree->Right Subtree
	void preorder() {
		preOrderHelper(this->root);
	}

	// In-Order traversal
	// Left Subtree -> Node -> Right Subtree
	void inorder() {
		inOrderHelper(this->root);
	}

	// Post-Order traversal
	// Left Subtree -> Right Subtree -> Node
	void postorder() {
		postOrderHelper(this->root);
	}

	// search the tree for the key k
	// and return the corresponding node
	NodePtr searchTree(int k) {
		return searchTreeHelper(this->root, k);
	}

	// find the node with the minimum key
	NodePtr minimum(NodePtr node) {
		while (node->left != TNULL) {
			node = node->left;
		}
		return node;
	}

	// find the node with the maximum key
	NodePtr maximum(NodePtr node) {
		while (node->right != TNULL) {
			node = node->right;
		}
		return node;
	}

	// find the successor of a given node
	NodePtr successor(NodePtr x) {
		// if the right subtree is not null,
		// the successor is the leftmost node in the
		// right subtree
		if (x->right != TNULL) {
			return minimum(x->right);
		}

		// else it is the lowest ancestor of x whose
		// left child is also an ancestor of x.
		NodePtr y = x->p;
		while (y != TNULL && x == y->right) {
			x = y;
			y = y->p;
		}
		return y;
	}

	// find the predecessor of a given node
	NodePtr predecessor(NodePtr x) {
		// if the left subtree is not null,
		// the predecessor is the rightmost node in the 
		// left subtree
		if (x->left != TNULL) {
			return maximum(x->left);
		}

		NodePtr y = x->p;
		while (y != TNULL && x == y->left) {
			x = y;
			y = y->p;
		}

		return y;
	}

	// rotate left at node x
	void leftRotate(NodePtr x) {
		NodePtr y = x->right;
		x->right = y->left;
		if (y->left != TNULL) {
			y->left->p = x;
		}
		y->p = x->p;
		if (x->p == NULL) {
			this->root = y;
		} else if (x == x->p->left) {
			x->p->left = y;
		} else {
			x->p->right = y;
		}
		y->left = x;
		x->p = y;
	}

	// rotate right at node x
	void rightRotate(NodePtr x) {
		NodePtr y = x->left;
		x->left = y->right;
		if (y->right != TNULL) {
			y->right->p = x;
		}
		y->p = x->p;
		if (x->p == NULL) {
			this->root = y;
		} else if (x == x->p->right) {
			x->p->right = y;
		} else {
			x->p->left = y;
		}
		y->right = x;
		x->p = y;
	}

	// insert the key to the tree in its appropriate position
	// and fix the tree
	void insert(int key) {
		// Ordinary Binary Search Insertion
		NodePtr node = new Node;
		node->p = NULL;
		node->data = key;
		node->left = TNULL;
		node->right = TNULL;
		node->color = 1; // new node must be red

		NodePtr y = NULL;
		NodePtr x = this->root;

		while (x != TNULL) {
			y = x;
			if (node->data < x->data) {
				x = x->left;
			} else {
				x = x->right;
			}
		}

		// y is parent of x
		node->p = y;
		if (y == NULL) {
			root = node;
		} else if (node->data < y->data) {
			y->left = node;
		} else {
			y->right = node;
		}

		// if new node is a root node, simply return
		if (node->p == NULL){
			node->color = 0;
			return;
		}

		// if the grandparent is null, simply return
		if (node->p->p == NULL) {
			return;
		}

		// Fix the tree
		fixInsert(node);
	}

	NodePtr getRoot(){
		return this->root;
	}

	// delete the node from the tree
	void deleteNode(int data) {
		deleteNodeHelper(this->root, data);
	}

	// print the tree structure on the screen


};

int main() {
	RBTree bst;
	bst.insert(8);
	bst.insert(5);
	bst.insert(15);
	bst.insert(12);
	bst.insert(19);
	bst.insert(9);
	bst.insert(13);
	bst.insert(23);


	bst.inorder();
	return 0;
}