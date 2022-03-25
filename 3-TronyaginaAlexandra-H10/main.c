//
//  main.c
//  Lab_H
//
//  Created by Alexandra Tronyagina on 25.03.2022.
//

#include "Lab_H_header.h"

void labSolution(void){
    node_t* tree = NULL;
    char command = '\0';
    int key = 0;
    while (fscanf(stdin, "%c %i", &command, &key) != EOF)
        switch (command) {
            case 'a':
                tree = addElement(tree, key);
                break;
            case 'r':
                tree = removeElement(tree, key);
                break;
            case 'f':
                findElement(tree, key);
                break;
            default:
                break;
        }
    deleteTree(tree);
    return;
}

int main(void){
    labSolution();
    return 0;
}
