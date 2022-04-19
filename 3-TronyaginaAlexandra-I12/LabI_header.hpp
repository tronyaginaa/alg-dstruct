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

node_t* createNode(void);
int findPosition(int key, int* keyArr, int n);
status_t removek(node_t* node, int key);
void removeElement(int key);
void splitChild(node_t* node, int ind);
static void add(node_t* node, int key);
int findElement(int key);
void addElement(int key);
void deleteTree(node_t* node);

#endif /* LabI_source_h */
