//
 //  Lab_H_header.h
 //  Lab_H
 //
 //  Created by Alexandra Tronyagina on 13.03.2022.
 //
 #ifndef Lab_H_header_h
 #define Lab_H_header_h
     #include <stdio.h>
     #include <stdlib.h>

     typedef struct tree{
         int height;
         int key;
         struct tree* left;
         struct tree* right;
     }node_t;

     void printTree(node_t* myTree);
     node_t* createTree(int key);
     void deleteTree(node_t* node);
     node_t* simpleLeftRotate(node_t* node);
     node_t* simpleRightRotate(node_t* node);
     node_t* doubleLeftRotate(node_t* node);
     node_t* doubleRightRotate(node_t* node);
     int balanceFactor(node_t* node);
     node_t* balanceTree(node_t* node);
     int nodeHeight(node_t* node);
     int maxHeight(node_t* node1, node_t* node2);
     node_t* removeMinElement(node_t* node);
     node_t* minElement(node_t* node);
     node_t* addElement(node_t* node, int key);
     node_t* removeElement(node_t* node, int key);
     void findElement(node_t* node, int key);

 #endif 
