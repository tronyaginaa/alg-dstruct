//
//  LabJ_Source.h
//  3-TronyaginaAlexandra-J23
//
//  Created by Alexandra Tronyagina on 14.05.2022.
//

#ifndef LabJ_Source_h
#define LabJ_Source_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STR_SIZE 100
#define TRUE 1
#define FALSE 0

typedef enum {
    NOT_INITED = 0,
    NOT_FREE = 1,
    FREE = 2
}status_t;

typedef struct{
    char str[STR_SIZE];
    status_t status;
} hash_t;

int createTable(hash_t** table, int tableSize);
int hashFunction1(char* str, int size);
int hashFunction2(char* str, int size);
int addElement(hash_t* table, char* str, const int tableSize);
int findElement(hash_t* table, char* str, const int tableSize);
int removeElement(hash_t* table, char* str, const int tableSize);
void destroyTable(hash_t* table);

#endif /* LabJ_Source_h */
