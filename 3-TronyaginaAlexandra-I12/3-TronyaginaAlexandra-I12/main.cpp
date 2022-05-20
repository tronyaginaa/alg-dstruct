//
//  main.c
//  3-TronyaginaAlexandra-I12
//
//  Created by Alexandra Tronyagina on 14.04.2022.
//
//
#include "LabI_header.h"

void labSolution(void){
    tree_t tree = {NULL};
    createTree(&tree);
    char command = '\0';
    int key = 0;
    while (fscanf(stdin, "%c%i", &command, &key) != EOF)
        switch (command) {
            case 'a':
                addElement(&tree, key);
                break;
            case 'r':
                removeElement(&tree, key);
                break;
            case 'f':
                if(findElement(&tree, key))
                    fprintf(stdout, "yes\n");
                else
                    fprintf(stdout, "no\n");
                break;
            default:
                break;
        }
    return;
}

int main(){
    labSolution();
    return 0;
