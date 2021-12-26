//
//  main.c
//  3-TronyaginaAlexandra-F20
//
//  Created by Alexandra Tronyagina on 21.12.2021.
//

#include <stdio.h>
#include <stdlib.h>
#include "LabF.h"


tree_t* createTree(int key) {
	tree_t* myTree = (tree_t*)malloc(sizeof(tree_t));
	if (!myTree)
		return NULL;
	myTree->key = key;
	myTree->left = myTree->right = NULL;
	myTree->number = 1;
	return myTree;
}

void deleteTree(tree_t* myTree) {
	if (!myTree)
		return;
	deleteTree(myTree->left);
	deleteTree(myTree->right);
	free(myTree);
	return;
}

int addElement(tree_t* myTree, int key) {
	int flag = 0;
	if (!myTree)
		return 0;
	if (key < myTree->key) {
		if (!myTree->left) {
			myTree->left = createTree(key);
			if (myTree->left) {
				myTree->number++;
				flag = 1;
			}
		}
		else {
			flag = addElement(myTree->left, key);
			if (flag)
				myTree->number++;
		}
	}
	if (key > myTree->key) {
		if (!myTree->right) {
			myTree->right = createTree(key);
			if (myTree->right) {
				myTree->number++;
				flag = 1;
			}
		}
		else {
			flag = addElement(myTree->right, key);
			if (flag)
				myTree->number++;
		}
	}
	return flag;
}

tree_t* kMin(tree_t* myTree, int k) {
	int r;
	if (!myTree)
		return NULL;
	if (myTree->left)
		r = myTree->left->number + 1;
	else
		r = 1;
	if (r != k) {
		if (r > k)
			myTree = kMin(myTree->left, k);
		else
			myTree = kMin(myTree->right, k - r);
	}
	return myTree;
}

void printLesser(tree_t* myTree, int key, FILE* file) {
	if (!myTree)
		return;
	printLesser(myTree->left, key, file);
	if (myTree->key < key) {
		fprintf(file, "%i ", myTree->key);
		printLesser(myTree->right, key, file);
	}
	return;
}

void printTree(tree_t* myTree) {
	if (!myTree)
		return;
	printf("%i ", myTree->key);
	if (myTree->left)
		printTree(myTree->left);
	if (myTree->right)
		printTree(myTree->right);
}

void printKMin(tree_t* myTree, int k, FILE* file) {
	tree_t* tmpTree = kMin(myTree, k);
	if (!tmpTree)
		return;
	if (tmpTree->key % 2 == 0) {
		printLesser(myTree, tmpTree->key, file);
	}
	else
		fprintf(file, "%i", tmpTree->key);
	return;
}

tree_t* readFile(FILE* file) {
	int key;
	tree_t* myTree = NULL;
	fscanf(file, "%i", &key);
	myTree = createTree(key);
	if (!myTree)
		return NULL;
	while (fscanf(file, "%i", &key) != EOF)
		if (!addElement(myTree, key))
			return myTree;
	return myTree;
}

void sol(FILE* input, FILE* output, int k) {
	tree_t* myTree = readFile(input);
	if (!myTree)
		return;
	printKMin(myTree, k, output);
	deleteTree(myTree);
	return;
}

