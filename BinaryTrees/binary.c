/*
 * File: binary.c
 * Author: Kristoffer Johansson
 * --------------
 * This file implements the tree.h abstraction using
 * simple(not balanced) binary trees.
 */

#include <stdio.h>
#include "binary.h"
#include "genlib.h"


typedef struct nodeT {
	elementT key;
	struct nodeT *left,*right,*parent;
} *nodeT;

struct treeCDT {
	nodeT root;
};

/* Private Function Prototypes */
static nodeT newNode(void);
static void freeNode(nodeT node);
static void printPreOrder(nodeT node);
static void printInOrder(nodeT node);
static void printPostOrder(nodeT node);
static void recDisplayTreeStructure(nodeT node, int depth, string label);
static int recTreeHeight(nodeT node);

/* Exported Entries */

treeADT newTree(void){
	treeADT tree;

	tree=New(treeADT);
	tree->root=NULL;
	return (tree);
}

void freeTree(treeADT tree){
	freeNode(tree->root);
	FreeBlock(tree);
}

void treeInsert(treeADT tree, elementT value){
	nodeT x,y,z=newNode();

	z->key=value;
	y=NULL;
	x=tree->root;
	while(x!=NULL){
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
	if(y==NULL)
		tree->root=z;
	else if(z->key < y->key)
		y->left=z;
	else /* (z->key == y->key) */
		y->right=z;
}

void printTree(treeADT tree, traverseOrderT order){
	
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

	recDisplayTreeStructure(tree->root, 0, NULL);
	printf("\n");
}

int treeHeight(treeADT tree){
	return (recTreeHeight(tree->root));
}

/* End of Exported */

static nodeT newNode(void){
	nodeT node;

	node=New(nodeT);
	node->key=0;
	node->left=NULL;
	node->right=NULL;
	node->parent=NULL;
	return (node);
}

static void freeNode(nodeT node){
	if(node!=NULL){
		freeNode(node->left);
		freeNode(node->right);
		FreeBlock(node);
	}
}

static void printPreOrder(nodeT node){

	if(node!=NULL){
		printf("%d ",node->key);
		printPreOrder(node->left);
		printPreOrder(node->right);
	}
}

static void printInOrder(nodeT node){

	if(node!=NULL){
		printInOrder(node->left);
		printf("%d ",node->key);
		printInOrder(node->right);
	}
}

static void printPostOrder(nodeT node){

	if(node!=NULL){
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
	if(node == NULL) return;
    printf("%*s", 3 * depth, "");
    if(label != NULL)
		printf("%s: ", label);
    printf("(%d)\n", node->key);
    recDisplayTreeStructure(node->left, depth + 1, "L");
    recDisplayTreeStructure(node->right, depth + 1, "R");
}

static int recTreeHeight(nodeT node){
	int leftHeight,rightHeight;
	
	if (node==NULL) 
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