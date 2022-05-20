//
//  LabI_source.h
//  3-TronyaginaAlexandra-I12
//
//  Created by Alexandra Tronyagina on 14.04.2022.
//
#ifndef LabI_source_h
#define LabI_source_h

#include <stdlib.h>
#include <stdio.h>

#define PARAMETR 3
#define FALSE 0
#define TRUE  1

typedef enum status {
    NOT_FOUND,
    SUCCESS,
    NOT_ENOUGH_KEYS,
} status_t;

typedef struct node{
    int num;
    int* keys;
    struct node** childrens;
    int isLeaf;
} node_t;

typedef struct tree_t {
     node_t* root;
 } tree_t;

node_t* createNode(void);
int createTree(tree_t* tree);
int findPosition(int key, int* keyArr, int n);
int splitChild(node_t* node, int ind);
int addKey(node_t* node, int key);
status_t removeKey(tree_t* tree, node_t* node, int key);
void removeElement(tree_t* tree, int key);
int findElement(tree_t* tree, int key);
void addElement(tree_t* tree, int key);
void deleteTree(node_t* node);

#endif /* LabI_source_h */
