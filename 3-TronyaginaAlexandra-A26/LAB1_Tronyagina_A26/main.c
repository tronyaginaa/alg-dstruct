//
//  main.c
//  LAB1_Tronyagina_26
//
//  Created by Alexandra Tronyagina on 13.09.2021.
//
#pragma warning (disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 12

typedef struct list {
   char date[N];
   int temp;
   struct list* ptr;
}list;


void deleteList(list* head) {
   list* p = NULL;
   while (head) {
       p = head;
       head = head->ptr;
       free(p);
   }
   free(head);
}

list* listInitialization(char* date, int temp) {
   int i;
   list* head = (list*)malloc(sizeof(list));
   if (head == NULL) {
      printf("Memory initalization error");
      return NULL;
   }
   strcpy(head->date, date);
   head->temp = temp;
   head->ptr = NULL;
   return head;
}

int dateComparison(char* first, char* second) {
   int firstDate[3];
   int secondDate[3];
   int i = 0;
   int k;
   sscanf(first, "%i-%i-%i", &firstDate[0], &firstDate[1], &firstDate[2]);
   sscanf(second, "%i-%i-%i", &secondDate[0], &secondDate[1], &secondDate[2]);
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
      return NULL;
   }
   strcpy(tmp->date, date);
   tmp->temp = temp;
   if (tmp->temp < head->temp) {
      tmp->ptr = head;
      head = tmp;
      return head;
   }
   if (tmp->temp == head->temp && dateComparison(tmp->date, head->date)) {
      tmp->ptr = head;
      head = tmp;
      return head;
   }
   list* p = head;
   while (p->ptr != NULL && p->ptr->temp < temp) {
      p = p->ptr;
   }
   while (p->ptr != NULL && temp == p->ptr->temp && dateComparison(p->ptr->date, date)) {
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
   char date[N];
   int temp;
   int k;
   list* head = NULL;
   list* tmp = NULL;
   while (k = fscanf(file, "%s %i", date, &temp) != EOF) {
      if (k < 1) {
         printf("fscanf error\n");
         deleteList(head);
         fclose(file);
         return NULL;
      }  
      tmp = push(head, date, temp);
      if (tmp == NULL) {
         printf("List filling error\n");
         deleteList(head);
         fclose(file);
         return NULL;
      }
      head = tmp;
   }
   fclose(file);
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

