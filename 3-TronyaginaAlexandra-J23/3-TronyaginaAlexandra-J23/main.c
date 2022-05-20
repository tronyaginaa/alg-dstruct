//
//  main.c
//  3-TronyaginaAlexandra-J23
//
//  Created by Alexandra Tronyagina on 20.05.2022.
//

#include "LabJ_Header.h"

void labSolution(void){
    char comand;
    char str[STR_SIZE];
    const int TABLE_SIZE = 100000;
    hash_t* table = NULL;
    if (!createTable(&table, TABLE_SIZE))
        return;
    while (1) {
        comand = (char)fgetc(stdin);
        if (comand == EOF || comand == '\n')
            break;
        scanf("%s", str);
        switch (comand) {
            case 'a':
                addElement(table, str, TABLE_SIZE);
                break;
            case 'f':
                if (findElement(table, str, TABLE_SIZE))
                    fprintf(stdout,"yes\n");
                else
                    fprintf(stdout,"no\n");
                break;
            case 'r':
                removeElement(table, str, TABLE_SIZE);
            default:
                break;
        }
        comand = (char)fgetc(stdin); //get '\n' from stdin
    }
    free(table);
    return;
}

int main(){
    labSolution();
    return 0;
}
