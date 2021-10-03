#pragma once
#ifdef __cplusplus
extern "C" {
#endif
#pragma warning (disable:4996)
#include <stdio.h>
#include <stdlib.h>

#define N 12

    typedef struct list {
        char date[N];
        int temp;
        struct list* ptr;
    }list;

    list* listInitialization(char* date, int temp);
    int dateComparison(char* first, char* second);
    list* push(list* head, char* date, int temp);
    list* readFile(char const* fileName);
    int weatherBelowZero(list* head);
    int averageTemperatureSearch(list* head, int temp);
    void deleteList(list* head);

#ifdef __cplusplus
}
#endif
