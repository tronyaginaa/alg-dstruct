//
//  main.c
//  LAB1_Tronyagina_26
//
//  Created by Alexandra Tronyagina on 13.09.2021.
//
#pragma warning (disable:4996)
#include <stdio.h>
#include <stdlib.h>

#define N 12

typedef struct list {
    char date[N];
    int temp;
    struct list* ptr;
}list;

list* listInitialization(char* date, int temp) {
    int i;
    list* head = (list*)malloc(sizeof(list));
    if (head == NULL) {
        printf("Memory initalization error");
        exit(1);
    }
    for (i = 0; i < N; i++) {
        head->date[i] = date[i];
    }
    head->temp = temp;
    head->ptr = NULL;
    return head;
}

int dateComparison(char* first, char* second) {
    int firstDate[3];
    int secondDate[3];
    int i = 0;
    int k;
    k = sscanf(first, "%i-%i-%i", &firstDate[0], &firstDate[1], &firstDate[2]);
    if (k != 3) {
        printf("sscanf error");
        exit(1);
    }
    k = sscanf(second, "%i-%2i-%i", &secondDate[0], &secondDate[1], &secondDate[2]);
    if (k != 3) {
        printf("sscanf error");
        exit(1);
    }
    for (i = 0; i < 3; i++) {
        if (firstDate[i] < secondDate[i]) {
            return 1;
        }
        else if (firstDate[i] > secondDate[i]) {
            return 0;
        }
    }
    return 0;
}
list* push(list* head, char* date, int temp) {
    if (head == NULL) {
        return head = listInitialization(date, temp);
    }
    list* tmp = (list*)malloc(sizeof(list));
    if (tmp == NULL) {
        printf("Memory initalization error");
        exit(1);
    }
    int i;
    for (i = 0; i < N; i++) {
        tmp->date[i] = date[i];
    }
    tmp->temp = temp;
    if (tmp->temp < head->temp) {
        tmp->ptr = head;
        head = tmp;
        return head;
    }
    if (tmp->temp == head->temp) {
        if (dateComparison(tmp->date, head->date)) {
            tmp->ptr = head;
            head = tmp;
            return head;
        }
    }
    list* p = head;
    while (p->ptr != NULL && p->ptr->temp < tmp->temp) {
        p = p->ptr;
    }
    while (p->ptr != NULL && tmp->temp == p->ptr->temp && dateComparison(p->ptr->date, tmp->date)) {
        p = p->ptr;
    }
    tmp->ptr = p->ptr;
    p->ptr = tmp;
    return head;
}

list* readFile(char const* fileName) {
    FILE* file;
    file = fopen(fileName, "r");
    if (file == NULL) {
        printf("The file was not open.\n");
        return NULL;
    }
    char* date = malloc(sizeof(char) * 12);
    if (date == NULL) {
        printf("Memory initalization error");
        exit(1);
    }
    int temp;
    int k;
    list* head = NULL;
    while (k = fscanf(file, "%s %i", date, &temp) != EOF) {
        if (k < 1) {
            printf("fscanf error");
            return NULL;
        }
    head = push(head, date, temp);
    }
    fclose(file);
    free(date);
    return head;
}

int weatherBelowZero(list* head) {
    int i = 0;
    do {
        if (head->temp < 0) {
            printf("%s\n", head->date);
            i++;
        }
        head = head->ptr;
    } while (head != NULL && head->temp < 0);
    return i;
}

int averageTemperatureSearch(list* head, int temp) {
    int i = 0;
    do {
        if (head->temp == temp) {
            printf("%s\n", head->date);
            i++;
        }
        head = head->ptr;
    } while (head != NULL && head->temp <= temp);
    return i;
}

int printList(list* head) {
    int i = 0;
    while (head != NULL) {
        printf("%s %i\n", head->date, head->temp);
        head = head->ptr;
        i++;
    }
    return i;
}

void deleteList(list* head) {
    list* p = NULL;
    while (head) {
        p = head;
        head = head->ptr;
        free(p);
    }
    free(head);
}

list* deleteFirstElement(list* head) {
    list* tmp = head;
    head = head->ptr;
    free(tmp);
    return head;
}
