#pragma once
#ifdef __cplusplus
extern "C" {
#endif

    #pragma warning (disable:4996)
    #include <stdio.h>
    #include <stdlib.h>
    typedef struct tree {
        int number;
        int key;
        struct tree* left;
        struct tree* right;
    }tree_t;

    tree_t* createTree(int key);
    void deleteTree(tree_t* myTree);
    int addElement(tree_t* myTree, int key);
    tree_t* kMin(tree_t* myTree, int k);
    void printLesser(tree_t* myTree, int key, FILE* file);
    void printTree(tree_t* myTree);
    void printKMin(tree_t* myTree, int k, FILE* file);
    tree_t* readFile(FILE* file);
    void sol(FILE* input, FILE* output, int k);

#ifdef __cplusplus
}
#endif