/*
 * File: redblack.h
 * Author: Kristoffer Johansson
 * --------------------------------
 * This file is used to make red-black trees grow!
 */

#ifndef _redblack_h
#define _redblack_h

#include <stdlib.h>
#include "genlib.h"

/* Constants */

#define NOT_FOUND -9999

/*
 * Type: traverseOrderT
 * --------------------------
 * The enum-type traverseOrderT is used to simplify the
 * choice of tree-traverse method.
 */

typedef enum {preOrder,inOrder,postOrder} traverseOrderT;

/*
 * Type: elementT
 * --------------------------
 * The type elementT can be any type thats ordered.
 */

typedef int elementT;

/*
 * Type: treeADT
 * --------------------------
 * The type treeADT points to a super secret type CDT!
 */

typedef struct treeCDT *treeADT;

/*
 * Function: newTree
 * Usage: tree = newTree();
 * --------------------------
 * This function allocates and returns an empty tree.
 */

treeADT newTree(void);

/*
 * Function: freeTree
 * Usage: freeTree(tree);
 * -------------------------------
 * This procedure frees the storage associated with the tree.
 */

void freeTree(treeADT tree);

/*
 * Function: findNode
 * Usage: value=findNode(tree, value);
 * -------------------------------
 * This function is used to find a value in the tree.
 * If the value doesn't exist the function returns the
 * constant NOT_FOUND.
 */

elementT findNode(treeADT tree, elementT value);

/*
 * Function: treeInsert
 * Usage: treeInsert(tree, value);
 * -------------------------------
 * This procedure inserts a value into the tree.
 */

void treeInsert(treeADT tree, elementT value);

/*
 * Function: treeDelete
 * Usage: treeDelete(tree, value);
 * -------------------------------
 * This procedure deletes a value from the tree.
 */

void treeDelete(treeADT tree, elementT value);

/*
 * Function: displayTree
 * Usage: displayTree(tree, traverseOrder);
 * -------------------------------
 * This procedure prints the tree in chosen
 * tree-traverse order.
 */

void printTree(treeADT tree, traverseOrderT order);

/*
 * Function: displayTreeStructure
 * Usage: displayTreeStructure(tree);
 * -------------------------------
 * This procedure displays the structure of the tree.
 */

void displayTreeStructure(treeADT tree);

/*
 * Function: treeDeleteMin
 * Usage: treeDeleteMin(tree);
 * -------------------------------
 * This procedure deletes the minimum value.
 */

void treeDeleteMin(treeADT tree);

/*
 * Function: treeDeleteMax
 * Usage: treeDeleteMax(tree);
 * -------------------------------
 * This procedure deletes the maximum value.
 */

void treeDeleteMax(treeADT tree);

/*
 * Function: treeHeight
 * Usage: height=treeHeight(tree);
 * -------------------------------
 * This function returns the height of the tree.
 */

int treeHeight(treeADT tree);

/*
 * Function: blackHeight
 * Usage: bHeight=blackHeight(tree);
 * -------------------------------
 * This function returns the black height of a red-black tree.
 * Which is the number of black node on any path from the root
 * to a leaf (not including the root).
 */

int blackHeight(treeADT tree);

#endif