/*
 * File: redblack.c
 * Author: Kristoffer Johansson
 * --------------
 * This file implements the tree.h abstraction using red-black trees.
 */

#include <stdio.h>
#include "redblack.h"
#include "genlib.h"

typedef enum {red,black} colorT;

typedef struct nodeT {
	colorT color;
	elementT key;
	struct nodeT *left,*right,*parent;
} *nodeT;

struct treeCDT {
	nodeT root;
};

/*
 * nullNode
 * ---------------------------
 * This node is used as a sentinel node.
 * It replaces all instances of NULL in order
 * to simplify the algorithms for insert/delete.
 * nullNode gets initialized once newTree has been
 * called.
 */
static nodeT nullNode=NULL;

/* Private Function Prototypes */
static nodeT newNode(void);
static void freeNode(nodeT node);
static void insertFixup(treeADT tree, nodeT node);
static void leftRotate(treeADT tree, nodeT node);
static void rightRotate(treeADT tree, nodeT node);
static nodeT nodeToDelete(treeADT tree, elementT value);
static nodeT treeMinimum(nodeT node);
static nodeT treeMaximum(nodeT node);
static void deleteFixup(treeADT tree, nodeT node);
static void transplant(treeADT tree, nodeT u, nodeT v);
static void printPreOrder(nodeT node);
static void printInOrder(nodeT node);
static void printPostOrder(nodeT node);
static void recDisplayTreeStructure(nodeT node, int depth, string label);
static int recTreeHeight(nodeT node);

/******************* Exported entries **********************/

treeADT newTree(void){
	treeADT tree;

	if(!nullNode){ //Not yet initialized
		nullNode=New(nodeT);
		nullNode->color=black;
		nullNode->key=42;
		nullNode->left=nullNode;
		nullNode->right=nullNode;
		nullNode->parent=nullNode;
	}
	tree=New(treeADT);
	tree->root=nullNode;
	return (tree);
}

void freeTree(treeADT tree){
	freeNode(tree->root);
	FreeBlock(tree);
}

elementT findNode(treeADT tree, elementT value){
	nodeT x=tree->root;

	if(tree->root==NULL)
		Error("Tree not initialized!");
	while(x!=nullNode){
		if(value < x->key)
			x=x->left;
		else if(value > x->key)
			x=x->right;
		else /* (value == x->key) */
			return (x->key);
	}
	return (NOT_FOUND);
}

void treeInsert(treeADT tree, elementT value){
	nodeT x,y,z=newNode();

	if(tree->root==NULL)
		Error("Tree not initialized!");
	z->key=value;
	y=nullNode;
	x=tree->root;
	while(x!=nullNode){
		y=x;
		if(z->key < x->key)
			x=x->left;
		else // Duplicates are allowed in order to test tree height
			x=x->right;
		//else { /* z->key == x->key */
		//	x->key=z->key;
		//	FreeBlock(z);
		//	return;
		//}
	}
	z->parent=y;
	if(y==nullNode)
		tree->root=z;
	else if(z->key < y->key)
		y->left=z;
	else /* (z->key >= y->key) */
		y->right=z;
	z->color=red;
	insertFixup(tree,z);
}

void treeDelete(treeADT tree, elementT value){
	nodeT x,y,z;
	colorT yColor;

	if(tree->root==NULL)
		Error("Tree not initialized!");
	z=nodeToDelete(tree,value);
	if(z==NULL) return;
	y=z;
	yColor=y->color;
	if(z->left==nullNode){
		x=z->right;
		transplant(tree,z,z->right);
	} else if(z->right==nullNode){
		x=z->left;
		transplant(tree,z,z->left);
	} else { /* 2 children */
		y=treeMinimum(z->right);
		yColor=y->color;
		x=y->right;
		if(y->parent==z)
			x->parent=y;
		else {
			transplant(tree,y,y->right);
			y->right=z->right;
			y->right->parent=y;
		}
		transplant(tree,z,y);
		y->left=z->left;
		y->left->parent=y;
		y->color=z->color;
	}
	if(yColor==black)
		deleteFixup(tree,x);
	FreeBlock(z);
}

void printTree(treeADT tree, traverseOrderT order){
	
	if(tree->root==NULL)
		Error("Tree not initialized!");
	switch (order) {
		case preOrder: 
			printPreOrder(tree->root);
			break;
		case inOrder:
			printInOrder(tree->root);
			break;
		case postOrder:
			printPostOrder(tree->root);
			break;
		default:
			printf("Not a valid traverse-order");
			break;
	}
	printf("\n");
}

void displayTreeStructure(treeADT tree){

	if(tree->root==NULL)
		Error("Tree not initialized!");
	recDisplayTreeStructure(tree->root, 0, NULL);
	printf("\n");
}

void treeDeleteMin(treeADT tree){
	nodeT node;

	if(tree->root==NULL)
		Error("Tree not initialized!");
	node=treeMinimum(tree->root);
	treeDelete(tree,node->key);
}

void treeDeleteMax(treeADT tree){
	nodeT node;

	if(tree->root==NULL)
		Error("Tree not initialized!");
	node=treeMaximum(tree->root);
	treeDelete(tree,node->key);
}

int treeHeight(treeADT tree){

	if(tree->root==NULL)
		Error("Tree not initialized!");
	return (recTreeHeight(tree->root));
}

int blackHeight(treeADT tree){
	nodeT node;
	int bHeight=0;

	if(tree->root==NULL)
		Error("Tree not initialized!");
	node=tree->root;
	if(node==nullNode) return 0;
	while(node->left!=nullNode){
		node=node->left;
		if(node->color==black)
			bHeight+=1;
	}
	return (bHeight);
}

/**************** End of exported entries *******************/

static nodeT newNode(void){
	nodeT node;

	node=New(nodeT);
	node->color=black;
	node->key=0;
	node->left=nullNode;
	node->right=nullNode;
	node->parent=nullNode;
	return (node);
}

static void freeNode(nodeT node){
	if(node!=nullNode){
		freeNode(node->left);
		freeNode(node->right);
		FreeBlock(node);
	}
}

static void insertFixup(treeADT tree, nodeT z){
	while(z->parent->color==red){
		if(z->parent==z->parent->parent->left){
			nodeT y=z->parent->parent->right;
			if(y->color==red){
				z->parent->color=black;
				y->color=black;
				z->parent->parent->color=red;
				z=z->parent->parent;
			} else {
				if(z==z->parent->right){
					z=z->parent;
					leftRotate(tree,z);
				}
				z->parent->color=black;
				z->parent->parent->color=red;
				rightRotate(tree,z->parent->parent);
			}
		} else {/* (z->parent==z->parent->parent->right) */
			nodeT x=z->parent->parent->left;
			if(x->color==red){
				z->parent->color=black;
				x->color=black;
				z->parent->parent->color=red;
				z=z->parent->parent;
			} else {
				if(z==z->parent->left){
					z=z->parent;
					rightRotate(tree,z);
				}
				z->parent->color=black;
				z->parent->parent->color=red;
				leftRotate(tree,z->parent->parent);
			}
		}
	}
	tree->root->color=black;
}

static void leftRotate(treeADT tree, nodeT x){
	nodeT y;

	y=x->right;
	x->right=y->left;
	if(y->left!=nullNode)
		y->left->parent=x;
	y->parent=x->parent;
	if(x->parent==nullNode)
		tree->root=y;
	else if(x==x->parent->left)
		x->parent->left=y;
	else /* (x==x->parent->right) */
		x->parent->right=y;
	y->left=x;
	x->parent=y;
}

static void rightRotate(treeADT tree, nodeT y){
	nodeT x;

	x=y->left;
	y->left=x->right;
	if(x->right!=nullNode)
		x->right->parent=y;
	x->parent=y->parent;
	if(y->parent==nullNode)
		tree->root=x;
	else if(y==y->parent->right)
		y->parent->right=x;
	else /* (y==y->parent->left) */
		y->parent->left=x;
	x->right=y;
	y->parent=x;
}

static nodeT nodeToDelete(treeADT tree, elementT value){
	nodeT x=tree->root;

	while(x!=nullNode){
		if(value < x->key)
			x=x->left;
		else if(value > x->key)
			x=x->right;
		else /* (value == x->key) */
			return (x);
	}
	return (NULL);
}

static nodeT treeMinimum(nodeT node){

	while(node->left!=nullNode)
		node=node->left;
	return (node);
}

static nodeT treeMaximum(nodeT node){

	while(node->right!=nullNode)
		node=node->right;
	return (node);
}

static void deleteFixup(treeADT tree, nodeT x){
	nodeT w;

	while(x!=tree->root && x->color==black){
		if(x==x->parent->left){
			w=x->parent->right;
			if(w->color==red){
				w->color=black;
				x->parent->color=red;
				leftRotate(tree,x->parent);
				w=x->parent->right;
			}
			if(w->left->color==black && w->right->color==black){
				w->color=red;
				x=x->parent;
			} else { /* something red */
				if(w->right->color==black){
					w->left->color=black;
					w->color=red;
					rightRotate(tree,w);
					w=x->parent->right;
				}
				w->color=x->parent->color;
				x->parent->color=black;
				w->right->color=black;
				leftRotate(tree,x->parent);
				x=tree->root;
			}
		} else { /* (x=x->parent->right) */
			w=x->parent->left;
			if(w->color=red){
				w->color=black;
				x->parent->color=red;
				rightRotate(tree,x->parent);
				w=x->parent->left;
			}
			if(w->right->color==black && w->left->color==black){
				w->color=red;
				x=x->parent;
			} else { /* something red */
				if(w->left->color==black){
					w->right->color=black;
					w->color=red;
					leftRotate(tree,w);
					w=x->parent->left;
				}
				w->color=x->parent->color;
				x->parent->color=black;
				w->left->color=black;
				rightRotate(tree,x->parent);
				x=tree->root;
			}
		}
	}
	x->color=black;
	nullNode->parent=nullNode; //Reset parent, transplant() may have changed it.
}

static void transplant(treeADT tree, nodeT u, nodeT v){

	if(u->parent==nullNode)
		tree->root=v;
	else if(u==u->parent->left)
		u->parent->left=v;
	else /* (u==u->parent->right) */
		u->parent->right=v;
	v->parent=u->parent;
}

static void printPreOrder(nodeT node){

	if(node!=nullNode){
		printf("%d ",node->key);
		printPreOrder(node->left);
		printPreOrder(node->right);
	}
}

static void printInOrder(nodeT node){

	if(node!=nullNode){
		printInOrder(node->left);
		printf("%d ",node->key);
		printInOrder(node->right);
	}
}

static void printPostOrder(nodeT node){

	if(node!=nullNode){
		printPostOrder(node->left);
		printPostOrder(node->right);
		printf("%d ",node->key);
	}
}

/*
 * Function: recDisplayTreeStructure
 * This is a borrowed and rewritten function.
 * -------------------------------------------
 * The original function was written by Eric Roberts for the textbook:
 * "Programming Abstractions in C - A Second Course in Computer Science"
 */
static void recDisplayTreeStructure(nodeT node, int depth, string label){
	if(node == nullNode) return;
    printf("%*s", 3 * depth, "");
    if(label != NULL)
		printf("%s: ", label);
	if(node->color==black)
		printf("%s","Bla");
	else
		printf("%s","Red");
    printf("(%d)\n", node->key);
    recDisplayTreeStructure(node->left, depth + 1, "L");
    recDisplayTreeStructure(node->right, depth + 1, "R");
}

static int recTreeHeight(nodeT node){
	int leftHeight,rightHeight;
	
	if (node==nullNode) 
		return 0;
	else {
		leftHeight = recTreeHeight(node->left);
		rightHeight = recTreeHeight(node->right);
		if (leftHeight > rightHeight) 
			return(leftHeight+1);
		else
			return(rightHeight+1);
	}
}