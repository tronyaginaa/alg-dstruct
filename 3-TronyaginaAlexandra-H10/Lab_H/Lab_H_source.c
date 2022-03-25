//
//  main.cpp
//  Lab_H
//
//  Created by Alexandra Tronyagina on 04.03.2022.
//
#include "Lab_H_header.h"

node_t* createNode(node_t* node, int key){
    node = (node_t*)malloc(sizeof(node_t));
    if (!node)
        return NULL;
    else {
        node->key = key;
        node->left = NULL;
        node->right = NULL;
        node->height = 1;
        return node;
    }
}

void deleteTree(node_t* node){
    if (!node)
        return;
    deleteTree(node->left);
    deleteTree(node->right);
    free(node);
    return;
}

void printTree(node_t* myTree){
    if (!myTree)
        return;
    printf("%i ", myTree->key);
    if (myTree->left != NULL)
        printTree(myTree->left);
    if (myTree->right != NULL)
        printTree(myTree->right);
    return;
}

int nodeHeight(node_t* node){
    if (!node)
        return 0;
    return node->height;
}

int balanceFactor(node_t* node){
    return nodeHeight(node->right) - nodeHeight(node->left);
}

int maxHeight(node_t* node1, node_t* node2){
    int height1 = nodeHeight(node1);
    int height2 = nodeHeight(node2);
    if (height1 < height2)
        return height2 + 1;
    return height1 + 1;
}

node_t* rotateRight(node_t* node){
    node_t* tmp = node->left;
    node->left = tmp->right;
    tmp->right = node;
    node->height = maxHeight(node->left, node->right);
    tmp->height = maxHeight(tmp->left, node);
    return tmp;
}

node_t* rotateLeft(node_t* node){
    node_t* tmp = node->right;
    node->right = tmp->left;
    tmp->left = node;
    node->height = maxHeight(node->left, node->right);
    tmp->height = maxHeight(tmp->right, node);
    return tmp;
}

node_t* doubleRotateRight(node_t* node){
    node->right = rotateRight(node->right);
    return rotateLeft(node);
}

node_t* doubleRotateLeft(node_t* node){
    node->left = rotateLeft(node->left);
    return rotateRight(node);
}

node_t* balanceTree(node_t* node){
    node->height = maxHeight(node->left, node->right);
    if (balanceFactor(node) == 2){
        if (balanceFactor(node->right) < 0)
            node = doubleRotateRight(node);
        else
            node = rotateLeft(node);
    }
    if (balanceFactor(node) == -2){
        if (balanceFactor(node->left) > 0)
            node = doubleRotateLeft(node);
        else
            node = rotateRight(node);
    }
    return node;
}

node_t* findMinElement(node_t* node){
    if (!node->left)
        return node;
    return findMinElement(node->left);
}

node_t* removeMinElement(node_t* node){
    if (!node->left)
        return node->right;
    node->left = removeMinElement(node->left);
    node = balanceTree(node);
    return node;
}

node_t* addElement(node_t* node, int key){
    if (!node)
        return createNode(node, key);
    if (key < node->key)
        node->left = addElement(node->left, key);
    if (key > node->key)
        node->right = addElement(node->right, key);
    node = balanceTree(node);
    return node;
}

node_t* removeElement(node_t* node, int key){
    if (!node)
        return NULL;
    if (key < node->key)
        node->left = removeElement(node->left, key);
    else if (key > node->key)
        node->right = removeElement(node->right, key);
    else {
        node_t* q = node->left;
        node_t* r = node->right;
        free(node);
        if (!r)
            return q;
        node_t* min = findMinElement(r);
        min->right = removeMinElement(r);
        min->left = q;
        min = balanceTree(min);
        return min;
    }
    node = balanceTree(node);
    return node;
}

void findElement(node_t* node, int key){
    if (!node){
        fprintf(stdout, "no\n");
        return;
    }
    if (key == node->key){
        fprintf(stdout, "yes\n");
        return;
    }
    if (key < node->key)
        findElement(node->left, key);
    else
        findElement(node->right, key);
    return;
}
