/*
 * File: main.c
 * Author: Kristoffer Johansson
 * -------------
 * This program uses an implemention of
 * unbalanced binary trees. It is used for testing the
 * efficiency of the implementation and for comparision
 * with red-black trees.
 */

#include <stdio.h>
#include "strlib.h"
#include "simpio.h"
#include "binary.h"
#include "random.h"

/* Function Prototypes */
void printMenu(void);
void heightTest(void);
void structureTest(void);
void buildTree(void);
treeADT buildTestTreeOrdered(int size);
treeADT buildTestTreeReversed(int size);
treeADT buildTestTreeRandom(int size);

/* Main Program */
main(){
	int menu;

	Randomize();
	while(TRUE){
		printMenu();
		menu=GetInteger();
		switch (menu){
			case 1: heightTest();break;
			case 2: structureTest();break;
			case 3: buildTree();break;
			case 0: exit(0);
			default: printf("Invalid choice. Try again.");
		}
	}
}

void printMenu(void){
	system("cls");
	printf("******* Binary Tree Interface *******\n\n");
	printf("Author: Kristoffer Johansson\n\n");
	printf("1. Height Test\n");
	printf("2. Structure Test\n");
	printf("3. Build your own tree!\n");
	printf("0. Quit\n");
	printf("Your choice: ");
}

void heightTest(void){
	treeADT treeOrd,treeRev,treeRan;
	int i,TEST_SIZE,NUM_OF_TESTS;
	double sum=0;

	system("cls");
	printf("Tree Height Tester\n\n");
	printf("Enter tree size: ");
	TEST_SIZE=GetInteger();
	if(TEST_SIZE<=0)
		Error("I refuse!");
	printf("Enter number of tests to run: ");
	NUM_OF_TESTS=GetInteger();
	printf("\n");
	if(NUM_OF_TESTS<=0)
		Error("I refuse!");

	printf("Random input || Tree size: %d || Number of tests: %d\n",TEST_SIZE,NUM_OF_TESTS);
	for(i=0;i<NUM_OF_TESTS;i++){
		treeRan=buildTestTreeRandom(TEST_SIZE);
		sum+=treeHeight(treeRan);
		freeTree(treeRan);
	}
	sum/=NUM_OF_TESTS;
	printf("Average height: %.2f\n\n",sum);
	sum=0;

	if(TEST_SIZE>20000){
		printf("Warning! This function uses recursion to measure height\n");
		printf("Big inputs makes it sad :-(\n");
		printf("To avoid crash, the height is just printed out.\n\n");
		printf("Increasing input || Tree size: %d\n",TEST_SIZE);
		printf("Average height: %d\n\n",TEST_SIZE);
		printf("Decreasing input || Tree size: %d\n",TEST_SIZE);
		printf("Average height: %d\n\n",TEST_SIZE);
	}
	else{
		printf("Increasing input || Tree size: %d || Number of tests: %d\n",TEST_SIZE,NUM_OF_TESTS);
		for(i=0;i<NUM_OF_TESTS;i++){
			treeOrd=buildTestTreeOrdered(TEST_SIZE);
			sum+=treeHeight(treeOrd);
			freeTree(treeOrd);
		}
		sum/=NUM_OF_TESTS;
		printf("Average height: %.2f\n\n",sum);
		sum=0;

		printf("Decreasing input || Tree size: %d || Number of tests: %d\n",TEST_SIZE,NUM_OF_TESTS);
		for(i=0;i<NUM_OF_TESTS;i++){
			treeRev=buildTestTreeReversed(TEST_SIZE);
			sum+=treeHeight(treeRev);
			freeTree(treeRev);
		}
		sum/=NUM_OF_TESTS;
		printf("Average height: %.2f\n\n",sum);
		sum=0;
	}
	printf("\nPress enter to return.");
	getchar();
}

void structureTest(void){
	treeADT treeOrd,treeRev,treeRan;
	int TEST_SIZE;

	system("cls");
	printf("Tree Structure Tester\n\n");
	printf("Enter tree size (rec. max: 25): ");
	TEST_SIZE=GetInteger();
	if(TEST_SIZE<=0)
		Error("I refuse!");
	
	treeOrd=buildTestTreeOrdered(TEST_SIZE);
	printf("Increasing input || Tree size: %d\n\n",TEST_SIZE);
	displayTreeStructure(treeOrd);
	printf("Tree-height is: %d\n",treeHeight(treeOrd));
	printf("\n\n");
	printf("--------------------------------------------\n");
	printf("\n");
	freeTree(treeOrd);

	treeRev=buildTestTreeReversed(TEST_SIZE);
	printf("Decreasing input || Tree size: %d\n\n",TEST_SIZE);
	displayTreeStructure(treeRev);
	printf("Tree-height is: %d\n",treeHeight(treeRev));
	printf("\n\n");
	printf("--------------------------------------------\n");
	printf("\n");
	freeTree(treeOrd);

	treeRan=buildTestTreeRandom(TEST_SIZE);
	printf("Random input || Tree size: %d\n\n",TEST_SIZE);
	displayTreeStructure(treeRan);
	printf("Tree-height is: %d\n",treeHeight(treeRan));
	printf("\n\n");
	printf("--------------------------------------------\n");
	printf("\n");
	freeTree(treeRan);

	printf("\nPress enter to return.");
	getchar();
}

void buildTree(void){
	treeADT tree=newTree();
	string userOP;
	int userInt;

	printf("\n**** Tree builder ****\n\n");
	while(TRUE){
		printf("(i)nsert, (p)rint, (q)uit\n");
		printf("Your choice: ");
		userOP=GetLine();
		if(StringEqual(userOP,"i")){
			printf("To end insertion enter: -1.\n");
			while(TRUE){
				printf("TreeInsert: ");
				userInt=GetInteger();
				if(userInt==-1)
					break;
				treeInsert(tree,userInt);
			}
		}
		if(StringEqual(userOP,"p")){
			printf("\nThis is your current tree:\n");
			displayTreeStructure(tree);
			printf("Preorder: ");
			printTree(tree,preOrder);
			printf("Inorder: ");
			printTree(tree,inOrder);
			printf("Postorder: ");
			printTree(tree,postOrder);
			printf("\n");
			printf("Height: %d\n\n",treeHeight(tree));
		}
		if(StringEqual(userOP,"q")) break;
	}
	freeTree(tree);
}

treeADT buildTestTreeOrdered(int TEST_SIZE){
	treeADT tree;
	int i;

	tree=newTree();
	for(i=0;i<TEST_SIZE;i++)
		treeInsert(tree,i);
	return (tree);
}

treeADT buildTestTreeReversed(int TEST_SIZE){
	treeADT tree;
	int i;

	tree=newTree();
	for(i=TEST_SIZE-1;i>=0;i--)
		treeInsert(tree,i);
	return (tree);
}

treeADT buildTestTreeRandom(int TEST_SIZE){
	treeADT tree;
	int i,MIN_INTERVAL,MAX_INTERVAL;

	if(TEST_SIZE<26){
		MIN_INTERVAL=0;
		MAX_INTERVAL=30;
	} else {
		MIN_INTERVAL=-9000000;
		MAX_INTERVAL=9000000;
	}
	tree=newTree();
	for(i=0;i<TEST_SIZE;i++)
		treeInsert(tree,RandomInteger(MIN_INTERVAL,MAX_INTERVAL));
	return (tree);
}