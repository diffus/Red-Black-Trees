/*
 * File: binary.h
 * Author: Kristoffer Johansson
 * --------------------------------
 * This file is used to make trees grow!
 */

#ifndef _binary_h
#define _binary_h

#include <stdio.h>
#include "genlib.h"

/*
 * Type: traverseOrderT
 * --------------------------
 * The enum-type traverseOrderT is used to simplify the
 * chocice of traverse method.
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
 * Function: treeInsert
 * Usage: treeInsert(tree, value);
 * -------------------------------
 * This procedure inserts a value into the tree.
 */

void treeInsert(treeADT tree, elementT value);

/*
 * Function: displayTree
 * Usage: displayTree(tree, traverseOrder);
 * -------------------------------
 * This procedure prints the tree in chosen
 * tree-traverse order.
 */

void printTree(treeADT tree, traverseOrderT order);

/*
 * Function: displayStructure
 * Usage: displayStructure(tree);
 * -------------------------------
 * This procedure displays the structure of the tree.
 */

void displayTreeStructure(treeADT tree);

/*
 * Function: treeHeight
 * Usage: height=treeHeight(tree);
 * -------------------------------
 * This function returns the height of the tree.
 */

int treeHeight(treeADT tree);


#endif