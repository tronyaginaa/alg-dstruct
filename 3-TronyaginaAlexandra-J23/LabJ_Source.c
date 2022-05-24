//
//  LabJ_Source.c
//  3-TronyaginaAlexandra-J23
//
//  Created by Alexandra Tronyagina on 14.05.2022.
//

#include "LabJ_Header.h"

int createTable(hash_t** table, int tableSize){
    (*table) = (hash_t*)malloc(tableSize*sizeof(hash_t));
    if (!(*table))
        return FALSE;
    for (int i = 0; i < tableSize; i++)
        (*table)[i].status = NOT_INITED;
    return TRUE;
}

int hashFunction1(char* str, int size){
    int res = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        res += (int)str[i];
        res %= size;
    }
    return res;
}

int hashFunction2(char* str, int size){
    int res = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        res += (int)str[i] + 2 * res;
        res %= size;
    }
    return res;
}

int addElement(hash_t* table, char* str, const int tableSize){
    if (str[0] == '\0' || findElement(table, str, tableSize))
        return FALSE;
    int x = hashFunction1(str, tableSize);
    int y = hashFunction2(str, tableSize);
    for (int i = 0; i < tableSize; i++) {
        if (table[x].status == NOT_INITED || table[x].status == FREE) {
            strcpy(table[x].str, str);
            table[x].status = NOT_FREE;
            return TRUE;
        }
        else if (table[x].status == NOT_FREE && strcmp(table[x].str, str) == 0)
            return FALSE;
        else
            x = (x + y) % tableSize;
    }
    return FALSE;
}

int findElement(hash_t* table, char* str, const int tableSize){
    if (str[0] == '\0')
        return FALSE;
    int x = hashFunction1(str, tableSize);
    int y = hashFunction2(str, tableSize);
    for (int i = 0; i < tableSize; i++) {
        if (table[x].status == NOT_FREE && strcmp(table[x].str, str) == 0)
            return TRUE;
        else if (table[x].status == NOT_INITED)
            return FALSE;
        x = (x + y) % tableSize;
    }
    return FALSE;
}

int removeElement(hash_t* table, char* str, const int tableSize){
    if (str[0] == '\0')
        return FALSE;
    int x = hashFunction1(str, tableSize);
    int y = hashFunction2(str, tableSize);
    for (int i = 0; i < tableSize; i++) {
        if (table[x].status == NOT_FREE && strcmp(table[x].str, str) == 0) {
            table[x].status = FREE;
            return TRUE;
        }
        else if (table[x].status == NOT_INITED)
            return FALSE;
        x = (x + y) % tableSize;
    }
    return FALSE;
}

void destroyTable(hash_t* table){
    if (table)
        free(table);
    return;
}
